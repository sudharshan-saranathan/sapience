/*  -----------------------------------
 *  Project     : sapience-debug
 *  File        : NodeCtrl.cpp
 *  Date        : 19.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#include <QBrush>
#include <QDrag>
#include <QGraphicsProxyWidget>
#include <QInputDialog>
#include <QLineEdit>
#include <QMimeData>
#include <QPainter>
#include <QPen>
#include <QStyleOptionGraphicsItem>
#include <QTextDocument>


#include "node/node_ctrl.h"

#include <QGraphicsSceneHoverEvent>

#include "node/node_connect.h"
#include "core/core_qss.h"
#include "custom/custom_dialog.h"
#include "schematic/schema_canvas.h"

#define VERBOSE

#define RGB_RAIL	QColor(109, 50, 109)
#define RGB_SELECT  QColor(243, 149, 22)

#define PEN_RAIL	QPen(QBrush(RGB_RAIL, Qt::DiagCrossPattern), 6.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
#define PEN_BLACK   QPen(Qt::black, 2.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
#define PEN_SELECT	QPen(QBrush(RGB_SELECT), 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)

//	Class destructor:
NodeCtrl::~NodeCtrl()
{
#ifdef VERBOSE
	qDebug() << __FILE__ << __func__; //	Print file and function name
#endif

	//	Loop over input handles:
	while (!m_list.inp.isEmpty())
	{
		//	Pop the last element (more efficient than popping the first)
		const auto handlePointer = m_list.inp.takeLast();

#ifdef VERBOSE
		qDebug() << "\t- Variable " << handlePointer->name() << " deleted"; //  Display handle's information
#endif

		handlePointer->free();                       //	Unpair the variable and its conjugate
		handlePointer->handleDeleted(handlePointer); //	Emit the variable's delete signal
	}

	//	Loop over output handles:
	while (!m_list.out.isEmpty())
	{
		const auto handlePointer = m_list.out.takeLast(); //	Pop the last element
#ifdef VERBOSE
		qInfo() << "\t- Variable " << handlePointer->name() << " deleted";
#endif
		handlePointer->free();                       //	Unpair the variable and its conjugate
		handlePointer->handleDeleted(handlePointer); //	Emit the variables's delete signal
	}

	if (scene()) //	Remove the node from scene, if applicable
		scene()->removeItem(this);

	if (OptimDB::nodeCtrlList.removeOne(this))
		qInfo() << "\t- Node removed from AMPL Database"; //	Print status information

	if (disconnect())
		qInfo() << "\t- QObject::disconnect() successful";
}

NodeCtrl::NodeCtrl(const QPointF& nodePosition, const QString& nodeName, QGraphicsItem* parent) :

	/*	Initializer list	*/
	//	Base-class constructor:
	QGraphicsRectItem{parent},

	//	Initialize <m_attr>:
	m_attr{
		nodeName,
		"N" + QString::number(RANDOMID),
		nodePosition,
		QColor(Qt::black),
		QRect(0, 0, NODE_WS, NODE_HS),
		false,
		false
	},

	//	Initialize <m_header>:
	m_header{
		new QGraphicsRectItem(this),
		QRect(2, 2, HDR_WS, HDR_HS)
	},

	//	Initialize rails:
	m_rails{
		new q_line(this),
		new q_line(this),
		new QItemE(m_rails.west),
		new QItemE(m_rails.east)
	},

	//	Initialize <m_title>
	m_title{new QGraphicsTextItem(m_header.pointer)},

	//	Initialize <m_svg>:
	m_svg{
		new NodeSVG(":/icons/circle-down.svg", QSize(ICONSIZE, ICONSIZE), true, m_header.pointer),
		new NodeSVG(":/icons/circle-up.svg", QSize(ICONSIZE, ICONSIZE), true, m_header.pointer),
		new NodeSVG(":/icons/lambda.svg", QSize(ICONSIZE, ICONSIZE), true, m_header.pointer),
		new NodeSVG(":/icons/node.close.svg", QSize(ICONSIZE, ICONSIZE), true, m_header.pointer),
		new NodeSVG(":/icons/node-unlock.svg", QSize(ICONSIZE, ICONSIZE), true, m_header.pointer)
	},

	//	Initialize <m_list>:
	m_list{
		QList<NodeHandle*>(),
		QList<NodeHandle*>(),
		QList<NodeParams*>()
	},

	//	Initialize <m_statusbar>:
	m_statusbar{
		QString("Node Created"),
		new q_rect(this),
		new status(m_statusbar.board)
	},

	//	Initialize <m_menu>:
	m_menu{
		new QMenu,
		new QAction("Save as Template"),
		new QAction("Delete Node"),
		new QAction("New Input"),
		new QAction("New Output"),
		new QAction("New Constant"),
	}

//	-------------------------
//	Constructor (body) begin:
{
	//	Setup position, size, and appearance of the node:
	const auto brush = QBrush(Qt::white, Qt::SolidPattern);
	const auto pen   = QPen(Qt::black, 1.5);

	setBrush(brush);
	setPen(pen);
	setPos(m_attr.origin);
	setRect(m_attr.rect);
	setObjectName("NodeCtrl");

	//	Initialize header:
	m_header.pointer->setRect(m_header.rect);
	m_header.pointer->setBrush(QBrush(QSSRGB::moonstone, Qt::SolidPattern));
	m_header.pointer->setPen(QPen(QSSRGB::moonstone, 1.0));

	//	Initialize the node-title and its characteristics:
	m_title.pointer->setPos(m_attr.rect.width() / 2.0 - NODE_TEXT_WIDTH / 2.0, 4.5);
	m_title.pointer->setTextInteractionFlags(Qt::TextEditorInteraction);
	m_title.pointer->setPlainText(m_attr.name);

	//	Fix text alignment, and connect text-change signal to lambda function:
	m_title.pointer->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter));
	m_title.pointer->document()->setTextWidth(NODE_TEXT_WIDTH);
	auto t1 = connect(m_title.pointer->document(),
	                  &QTextDocument::contentsChanged,
	                  [&]() { m_attr.name = m_title.pointer->document()->toPlainText(); });

	//	Setup SVG buttons:
	m_svg.input->moveBy(18, 18);
	m_svg.output->moveBy(43, 18);
	m_svg.params->moveBy(68, 18);
	m_svg.toggle->setToggleFile(":/icons/node-lock.svg");
	m_svg.toggle->moveBy(257, 18);
	m_svg.close->moveBy(282, 18);

	m_svg.input->setToolTip("Define Input");
	m_svg.output->setToolTip("Define Output");
	m_svg.params->setToolTip("Define Constant");
	m_svg.close->setToolTip("Delete Node");

	connect(m_svg.close, &NodeSVG::leftClicked, [&]() { emit nodeDeleted(this); });
	connect(m_svg.input, &NodeSVG::leftClicked, [&]() { createHandle(NodeHandle::StreamType::INP); });
	connect(m_svg.output, &NodeSVG::leftClicked, [&]() { createHandle(NodeHandle::StreamType::OUT); });
	connect(m_svg.params, &NodeSVG::leftClicked, [&]() { createParams(); });
	connect(m_svg.toggle,
	        &NodeSVG::leftClicked,
	        [&]()
	        {
		        m_attr.locked = !m_attr.locked;
		        onLockToggled(m_attr.locked);
	        });

	/*	Draw rails (inpRail and outRail) on either side of the node. Input and output variables
	 *	can be vertically moved along these rails	*/
	m_rails.east->setPen(PEN_RAIL);
	m_rails.east->setLine(0, 0, 0, 110);
	m_rails.east->setPos(292, 45);
	m_rails.east->setData(0, QVariant::fromValue<NodeHandle::StreamType>(NodeHandle::StreamType::OUT));

	m_rails.west->setPen(PEN_RAIL);
	m_rails.west->setLine(0, 0, 0, 110);
	m_rails.west->setPos(8, 45);
	m_rails.west->setData(0, QVariant::fromValue<NodeHandle::StreamType>(NodeHandle::StreamType::INP));

	m_rails.hint_west->setRect(0, 0, 8, 8);
	m_rails.hint_west->setBrush(QBrush(QColor(0x3BCE5B), Qt::SolidPattern));
	m_rails.hint_west->setOpacity(0.3);
	m_rails.hint_west->hide();

	m_rails.hint_east->setRect(0, 0, 8, 8);
	m_rails.hint_east->setBrush(QBrush(QColor(0x3BCE5B), Qt::SolidPattern));
	m_rails.hint_east->setOpacity(0.3);
	m_rails.hint_east->hide();

	//	Initialize status bar:
	m_statusbar.board->setBrush(QBrush(0x22333B, Qt::SolidPattern));
	m_statusbar.board->setPen(QPen());
	m_statusbar.board->setRect(0, 0, HDR_WS, 25);
	m_statusbar.board->setPos(2.0, QGraphicsRectItem::boundingRect().bottom() - 25 - 2.8);
	m_statusbar.pointer->print(m_statusbar.message, info);
	m_statusbar.pointer->setPos(1, 1);

	m_menu.pointer->addAction(m_menu.save);
	m_menu.pointer->addSeparator();
	m_menu.pointer->addAction(m_menu.input);
	m_menu.pointer->addAction(m_menu.output);
	m_menu.pointer->addAction(m_menu.constant);
	m_menu.pointer->addSeparator();
	m_menu.pointer->addAction(m_menu.close);

	m_menu.save->setShortcutVisibleInContextMenu(true);                       //	Show the shortcut in the m_menu
	m_menu.save->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S)); //	Define the custom shortcut
	m_menu.save->setShortcutContext(Qt::WidgetWithChildrenShortcut);          //	Do not remove or modify

	m_menu.input->setShortcutVisibleInContextMenu(true);                       //	Show the shortcut in the m_menu
	m_menu.input->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_I)); //	Define the custom shortcut
	m_menu.input->setShortcutContext(Qt::WidgetWithChildrenShortcut);          //	Do not remove or modify

	m_menu.output->setShortcutVisibleInContextMenu(true);                       //	Show the shortcut in the m_menu
	m_menu.output->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_O)); //	Define the custom shortcut
	m_menu.output->setShortcutContext(Qt::WidgetWithChildrenShortcut);          //	Do not remove or modify

	m_menu.constant->setShortcutVisibleInContextMenu(true);                       //	Show the shortcut in the m_menu
	m_menu.constant->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_C)); //	Define the custom shortcut
	m_menu.constant->setShortcutContext(Qt::WidgetWithChildrenShortcut);          //	Do not remove or modify

	m_menu.close->setShortcutVisibleInContextMenu(true);                       //	Show the shortcut in the m_menu
	m_menu.close->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Q)); //	Define the custom shortcut
	m_menu.close->setShortcutContext(Qt::WidgetWithChildrenShortcut);          //	Do not remove or modify

	//connect(m_menu.save, &QAction::triggered, [&]() { actionSave(); });
	connect(m_menu.close, &QAction::triggered, [&]() { m_svg.close->leftClicked(); });
	connect(m_menu.input, &QAction::triggered, [&]() { m_svg.input->leftClicked(); });
	connect(m_menu.output, &QAction::triggered, [&]() { m_svg.output->leftClicked(); });
	connect(m_menu.constant, &QAction::triggered, [&]() { m_svg.params->leftClicked(); });
	connect(m_title.pointer->document(), &QTextDocument::contentsChanged,
	        [&]() { m_attr.name = m_title.pointer->toPlainText(); });

	//	Customize behaviour of node:
	setAcceptHoverEvents(true);
	setFlag(ItemIsMovable, true);
	setFlag(ItemIsSelectable, true);
	setFlag(ItemSendsGeometryChanges, true);
	setFlag(ItemSendsScenePositionChanges, true);
	setFlag(ItemClipsChildrenToShape, true);

	//	These are supposed to improve performance:
	setCacheMode(ItemCoordinateCache);
	setTransform(QTransform(), false);
}

//	Copy constructor, also delegates to the constructor above for initialization:
NodeCtrl::NodeCtrl(const NodeCtrl& source) :

	//	Call the delegate constructor:
	NodeCtrl(source.scenePos() + QPointF(25, 25), source.name(), source.parentItem())

//	-----------------------------
//	Copy-contructor (body) begin:
{
#ifdef VERBOSE
	qInfo() << __FILE_NAME__ << __func__;
#endif

	//	Temporary variable:
	NodeHandle* variable = nullptr;

	//	Copy the original node's input variables:
	for (const auto src : source.m_list.inp)
	{
		variable = createHandle(NodeHandle::StreamType::INP);
		variable->setPos(src->pos());
		variable->setCategory(src->category());

		/*	If the original variable is paired, store its relative displacement from its conjugate. This is required to
		 *	preserve connections when nodes are copy-pasted.
		 */
		if (src->isPaired())
		{
			const auto diff = src->conjugate()->scenePos() - src->scenePos();
			variable->setData(0, QVariant::fromValue(diff));
		}
	}

	//	Copy the original node's output variables:
	for (const auto src : source.m_list.out)
	{
		variable = createHandle(NodeHandle::StreamType::INP);
		variable->setPos(src->pos());

		/*	If the original variable is paired, store its relative displacement from its conjugate. This is required to
		 *	preserve connections when nodes are copy-pasted.
		 */
		if (src->isPaired())
		{
			const auto diff = src->conjugate()->scenePos() - src->scenePos();
			variable->setData(0, QVariant::fromValue(diff));
		}
	}
}

QVariant
NodeCtrl::itemChange(const GraphicsItemChange change, const QVariant& value)
{
	//	Switch case block to execute custom tasks when the object is moved:
	switch (change)
	{
	//	If the node was moved, emit signal:
	case ItemScenePositionHasChanged:
		{
			emit nodeShifted();
			break;
		}

	//	If the node is shown or hidden (e.g. when moved into/out of a folder):
	case ItemVisibleChange: { emit nodeShifted(); }

	//	Default block:
	default:
		break;
	}
	return (value);
}

void
NodeCtrl::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	//	Change border color when node is selected:
	setPen(isSelected()
		       ? PEN_SELECT
		       : PEN_BLACK);

	//	Reset node state to remove dashed lines:
	auto modOption(*option);
	modOption.state = QStyle::State_None;

	//	Call base-class event-handler:
	QGraphicsRectItem::paint(painter, &modOption, widget);
}

void
NodeCtrl::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
	const auto leftRail  = m_rails.west->mapFromParent(event->pos());
	const auto rightRail = m_rails.east->mapFromParent(event->pos());

	if (m_rails.west->contains(leftRail))
	{
		const auto x = m_rails.west->pos().x() - 12.0;
		const auto y = event->pos().y() - 49.0;
		m_rails.hint_west->setPos(x, y);
		m_rails.hint_west->show();
	}
	else
		m_rails.hint_west->hide();

	if (m_rails.east->contains(rightRail))
	{
		const auto x = m_rails.east->pos().x() - 296.0;
		const auto y = event->pos().y() - 49.0;
		m_rails.hint_east->setPos(x, y);
		m_rails.hint_east->show();
	}
	else
		m_rails.hint_east->hide();

	//	Propagate event downstream:
	QGraphicsRectItem::hoverMoveEvent(event);
	event->accept();
}

void
NodeCtrl::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	//	Within bounding rectangle, switch to Qt::ArrowCursor:
	setCursor(Qt::ArrowCursor);

	//	Propagate event downstream:
	QGraphicsRectItem::hoverEnterEvent(event);
	event->accept();
}

void
NodeCtrl::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	//	Hide handle hints:
	m_rails.hint_west->hide();
	m_rails.hint_east->hide();

	//	Propagate event downstream:
	unsetCursor();
	QGraphicsRectItem::hoverLeaveEvent(event);
}

void
NodeCtrl::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	//	If the mouse click is on the rails, create a new variable:
	const auto posLRail = m_rails.west->mapFromParent(event->pos());
	const auto posRRail = m_rails.east->mapFromParent(event->pos());
	const auto position = QPointF(0.0, event->pos().y() - 4.0);

	//	Initialize a temporary variable:
	NodeHandle* handle = nullptr;

	//	When the user clicks an input or output rail, a handle is automatically created.
	if (m_rails.west->contains(posLRail))
	{
		setFlag(ItemIsMovable, false);
		handle = createHandle(NodeHandle::StreamType::INP, position);
		handle->handleClicked(handle);
	}
	else if (m_rails.east->contains(posRRail))
	{
		setFlag(ItemIsMovable, false);
		handle = createHandle(NodeHandle::StreamType::OUT, position);
		handle->handleClicked(handle);
	}
	else
		setFlag(ItemIsMovable, true);

	//	Call base-class implementation:
	QGraphicsRectItem::mousePressEvent(event);
}

void
NodeCtrl::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	//	Resolve event-handlers of nested objects first, if any:
	QGraphicsRectItem::mouseReleaseEvent(event);
}

void
NodeCtrl::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
	//	Resolve event handlers of nested objects first, if any:
	QGraphicsRectItem::contextMenuEvent(event);

	//	Show context m_menu:
	m_menu.pointer->exec(event->screenPos());
	event->accept();
}

NodeHandle*
NodeCtrl::handleAt(const QPointF& pos) //  pos must be in scene coordinates:
{
	//	Print file and function name:
#ifdef VERBOSE
	qInfo() << __FILE_NAME__ << __func__;
#endif

	for (const auto var : m_list.inp)
		if (var->mapFromScene(pos) == QPointF(0, 0))
			return (var);

	for (const auto var : m_list.out)
		if (var->mapFromScene(pos) == QPointF(0, 0))
			return (var);

	return (nullptr);
}

NodeHandle*
NodeCtrl::createHandle(const NodeHandle::StreamType& handleType, const QPointF pos)
{
	/*	This function creates a new handle of the desired type (StreamType), stores it in the appropriate list and positions
	 *	it within the node according to its type (e.g. input and output variables are on the left and right, respectively).	*/

	//	Print file and function name:
#ifdef VERBOSE
	qInfo() << __FILE__ << __func__;
#endif

	//	Function body:
	auto        position = 0.0;
	NodeHandle* pointer  = nullptr;

	//	Switch-case block:
	switch (handleType)
	{
	//	StreamType = StreamType::Input (i.e. input handle):
	case NodeHandle::StreamType::INP:
		{
			//	Create handle and initialize its position:
			pointer  = new NodeHandle(handleType, this);
			position = m_rails.west->pos().x() - 4.0;

			//	Store the pointer to the handle in the node's local list:
			m_list.inp.append(pointer);

			//	Emit connectHandle() signal when the handle is clicked. This signal is processed by the node and scene:
			connect(pointer, &NodeHandle::handleClicked, [&](NodeHandle* handle) { emit connectHandle(this, handle); });
			connect(pointer, &NodeHandle::handleDeleted, [&](NodeHandle* handle) { emit deleteHandle(handle); });

			//	Adjust position of the handle (handles are automatically stacked, unless moved by the user):
			pointer->setPos(pos == QPointF()
				                ? QPointF(position, 12 + m_list.inp.size() * 40)
				                : QPointF(position, pos.y()));

			//	Display a status message:
			m_statusbar.pointer->print(QString("Input handle (" + pointer->UID() + ") created"));
			break;
		}

	//	StreamType = StreamType::Output (i.e. output handle):
	case NodeHandle::StreamType::OUT:
		{
			//	Create variable with appropriate attribute(s):
			pointer  = new NodeHandle(handleType, this);
			position = m_rails.east->pos().x() - 4.0;

			//	Store the variable in the input-list, and the AMPL list:
			m_list.out.push_back(pointer);

			/*	Emit createLink() signal when a variable within the node is clicked. This
			 *	signal is captured and handled by schemaCanvas::onCreateLink()	*/
			connect(pointer, &NodeHandle::handleClicked, [&](NodeHandle* handle) { emit connectHandle(this, handle); });
			connect(pointer, &NodeHandle::handleDeleted, [&](NodeHandle* handle) { emit deleteHandle(handle); });

			/*	Adjust position of the created variable. An input variable is positioned near
			 *	the left edge of the node, stacked sequentially below other input variables	*/
			pointer->setPos(pos == QPointF()
				                ? QPointF(position, 12 + m_list.out.size() * 40)
				                : QPointF(position, pos.y()));

			//	Display a status message:
			m_statusbar.pointer->print(QString("Output handle (" + pointer->UID() + ") created"));
			break;
		}

	default:
		break;
	}

	/*	First shift bottom boundary downwards, followed by the variable rails and the status
	 *	bar. The positions have been hardcoded, but a better solution will be found in the
	 *	future	*/
	if (const auto maxSize = qMax(m_list.inp.size(), m_list.out.size());
		maxSize >= 4)
	{
		//	Set bottom boundary according to the number of variables in the node:
		setRect(QRect(0, 0, m_attr.rect.width(), m_attr.rect.height() + (maxSize - 3) * 40.0));

		//	Update rail-length:
		m_rails.east->setLine(0, 0, 0, boundingRect().bottom() - 76.0);
		m_rails.west->setLine(0, 0, 0, boundingRect().bottom() - 76.0);

		//	Update status bar position:
		m_statusbar.board->setPos(0.5, QGraphicsRectItem::boundingRect().bottom() - 25.0);
	}

	//	Emit signal:
	emit handleCreated();

	//	Return pointer to the created handle:
	return (pointer);
}

//	This function is triggered when the user selects "New Parameter" from the node's context-m_menu:
QList<NodeParams*>
NodeCtrl::createParams()
{
#ifdef VERBOSE
	qInfo() << __FILE__ << __func__;
#endif

	auto dialog = CustomDialog("New parameter (" + m_attr.item_id + ")", //	Dialog-label
	                           "Name (comma-separated)",                 //	Placeholder text
	                           dynamic_cast<QWidget*>(parentWidget()));  //	Parent widget

	auto rcode    = dialog.exec();
	auto input    = dialog.parameters().split(',');
	auto parsList = QList<NodeParams*>();

	/*
	for (auto param : input) {

#ifdef VERBOSE
		qInfo() << param.simplified().toUpper();
#endif

		const auto pointer = new NodeParams(param.simplified().toUpper(), this);
		parsList.append(pointer); // This list is returned
		list.par.append(pointer); // This is the node's local list

		pointer->setTextWidth(80);
		pointer->setDefaultTextColor(QColor(0x67285A));
		pointer->setPos(110, 30 + list.par.size() * 20.0);

		connect(pointer, &NodeParams::parameterDeleted, this, &NodeCtrl::deleteParameter);
	}

//	Re-adjust the size of the node:
	if (const auto maxSize = qMax(list.par.size(), qMax(list.inp.size(), list.out.size()));
		maxSize >= 6) {

		//	Set bottom boundary according to the number of variables in the node:
		setRect(QRect(0, 0, attr.rect.width(), attr.rect.height() + (maxSize - 5) * 20.0));

		//	Update rail-length:
		rails.east->setLine(0, 0, 0, boundingRect().bottom() - 76.0);
		rails.west->setLine(0, 0, 0, boundingRect().bottom() - 76.0);

		//	Update status bar position:
		statusbar.board->setPos(0.5, QGraphicsRectItem::boundingRect().bottom() - 25.0);
	}
	*/

	return QList<NodeParams*>();
}

//	This SLOT is triggered by SIGNAL(NodeHandle::handleDeleted(NodeHandle*)):
void
NodeCtrl::deleteHandle(NodeHandle* handle)
{
#ifdef VERBOSE
	//	Print file and function name:
	qInfo() << __FILE__ << __func__;
#endif

	if (handle->streamType() == NodeHandle::StreamType::INP) //	Remove the variable from the node's list
		m_list.inp.removeAll(handle);
	else
		m_list.out.removeAll(handle);

	//	Delete handle using QObject::deleteLater():
	handle->deleteLater();

	//	Emit handleDeleted() signal:
	emit handleDeleted();
}

void
NodeCtrl::deleteParameter(NodeParams* pointer)
{
	/*
	#ifdef VERBOSE
		qInfo() << __FILE__ << __func__;
	#endif

		list.par.removeAll(pointer);
		if (scene())
			scene()->removeItem(pointer);

		pointer->setParentItem(nullptr);
		pointer->deleteLater();
	*/
}


void
NodeCtrl::onLockToggled(const bool lock)
{
	m_svg.input->setEnabled(!lock);
	m_svg.output->setEnabled(!lock);
	m_svg.params->setEnabled(!lock);
	m_svg.close->setEnabled(!lock);

	m_rails.west->setEnabled(!lock);
	m_rails.east->setEnabled(!lock);

	setAcceptHoverEvents(!lock);
	setFlag(ItemIsMovable, !lock);
	setFlag(ItemIsSelectable, !lock);
	setAcceptedMouseButtons(lock
		                        ? Qt::NoButton
		                        : Qt::AllButtons);
}

void
NodeCtrl::reconnect()
{
	//	Print file and function name:
	qInfo() << __FILE_NAME__ << __func__;

	//	Loop over input variables:
	for (const auto& var : m_list.inp)
	{
		const auto point = var->data(0).value<QPointF>() + var->scenePos();
		const auto item  = scene()
			                   ? scene()->itemAt(point, QTransform())
			                   : nullptr;

		if (item && item->type() == UserType + NODEITEM)
		{
			const auto node = qgraphicsitem_cast<NodeCtrl*>(item);
			const auto xvar = node->handleAt(node->mapFromScene(point));

			if (const auto path = var->pair(xvar))
				qInfo() << "\t- Connection established";
		}
	}

	//	Loop over output variables:
	for (const auto& var : m_list.out)
	{
		const auto point = var->data(0).value<QPointF>() + var->scenePos();
		const auto item  = scene()
			                   ? scene()->itemAt(point, QTransform())
			                   : nullptr;

		if (item && item->type() == UserType + NODEITEM)
		{
			const auto node = qgraphicsitem_cast<NodeCtrl*>(item);
			const auto xvar = node->handleAt(point);

			if (const auto path = var->pair(xvar))
				qInfo() << "\t- Connection established";
		}
	}
}
