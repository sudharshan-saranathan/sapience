/*  -----------------------------------
 *  Project     : sapience-debug
 *  File        : nodeCtrl.cpp
 *  Date        : 19.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#include <QBrush>
#include <QDrag>
#include <QMimeData>
#include <QPainter>
#include <QPen>
#include <QLineEdit>
#include <QInputDialog>

#include "node/nodeCtrl.h"
#include "ampl/amplDatabase.h"
#include "core/coreQSS.h"
#include <schematic/schemaCanvas.h>

#include <QGraphicsProxyWidget>
#include <node/nodeConnect.h>
#include <custom/customDialog.h>

#define VERBOSE

#define RGB_RAIL	QColor(109, 50, 109)
#define RGB_SELECT  QColor(243, 149, 22)

#define PEN_RAIL	QPen(QBrush(RGB_RAIL, Qt::DiagCrossPattern), 6.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
#define PEN_BLACK   QPen(Qt::black, 2.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
#define PEN_SELECT	QPen(QBrush(RGB_SELECT), 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)

//	Class destructor:
nodeCtrl::~nodeCtrl() {

#ifdef VERBOSE
	qDebug() << __FILE__ << __func__; //	Print file and function name
#endif

//	Loop over input handles:
	while (!list.inp.isEmpty()) {

		//	Pop the last element (more efficient than popping the first)
		const auto handlePointer = list.inp.takeLast();

#ifdef VERBOSE
		qDebug() << "\t- Variable " << handlePointer->name() << " deleted"; //  Display handle's information
#endif

		handlePointer->free();                       //	Unpair the variable and its conjugate
		handlePointer->handleDeleted(handlePointer); //	Emit the variable's delete signal
	}

	//	Loop over output handles:
	while (!list.out.isEmpty()) {
		const auto handlePointer = list.out.takeLast(); //	Pop the last element
#ifdef VERBOSE
		qInfo() << "\t- Variable " << handlePointer->name() << " deleted";
#endif
		handlePointer->free();                       //	Unpair the variable and its conjugate
		handlePointer->handleDeleted(handlePointer); //	Emit the variables's delete signal
	}

	if (scene()) //	Remove the node from scene, if applicable
		scene()->removeItem(this);

	if (amplDatabase::nodeList.removeOne(this))
		qInfo() << "\t- Node removed from AMPL Database"; //	Print status information

	if (disconnect())
		qInfo() << "\t- QObject::disconnect() successful";
}

nodeCtrl::nodeCtrl(const QPointF& nodePosition, const QString& nodeName, QGraphicsItem* parent) :

/*	Initializer list	*/
//	Base-class constructor:
	QGraphicsRectItem{parent},

//	struct _attr_:
	attr{
		nodeName,
		QString("N#") + QString::number(QRandomGenerator::global()->bounded(0x1000)),
		nodePosition,
		QColor(Qt::black),
		QRect(0, 0, NODE_WS, NODE_HS),
		false,
		false
	},

//	Initialize header
	header{new QGraphicsRectItem(this), QRect(2, 2, HDR_WS, HDR_HS)},

//	Initialize rails
	rails{new QItemL(this), new QItemL(this), new QItemE(rails.west), new QItemE(rails.east)},

//	Initialize title
	title{new QGraphicsTextItem(header.ptr)},

//	Initialize SVG buttons
	svg{
		new nodeSVG(":/icons/circle-down.svg", QSize(ICONSIZE, ICONSIZE), true, header.ptr),
		new nodeSVG(":/icons/circle-up.svg", QSize(ICONSIZE, ICONSIZE), true, header.ptr),
		new nodeSVG(":/icons/lambda.svg", QSize(ICONSIZE, ICONSIZE), true, header.ptr),
		new nodeSVG(":/icons/node.close.svg", QSize(ICONSIZE, ICONSIZE), true, header.ptr),
		new nodeSVG(":/icons/node-unlock.svg", QSize(ICONSIZE, ICONSIZE), true, header.ptr)
	},

//	Initialize lists
	list{QList<nodeHandle*>(), QList<nodeHandle*>(), QList<nodeParams*>()},

//	Initialize status bar
	statusbar{QString("Node Created"), new QItemR(this), new status(statusbar.board)},

//	Initialize and status bar:
	menu{
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
	setPos(attr.origin);
	setRect(attr.rect);
	setObjectName("nodeCtrl");

	//	Initialize header:
	header.ptr->setRect(header.rect);
	header.ptr->setBrush(QBrush(QSSRGB::moonstone, Qt::SolidPattern));
	header.ptr->setPen(QPen(QSSRGB::moonstone, 1.0));

	//	Initialize the node-title and its characteristics:
	title.ptr->setPos(attr.rect.width() / 2.0 - NODE_TEXT_WIDTH / 2.0, 6);
	title.ptr->setTextInteractionFlags(Qt::TextEditorInteraction);
	title.ptr->setPlainText(attr.name);

	//	Fix text alignment, and connect text-change signal to lambda function:
	title.ptr->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter));
	title.ptr->document()->setTextWidth(NODE_TEXT_WIDTH);
	auto t1 = connect(title.ptr->document(),
					  &QTextDocument::contentsChanged,
					  [&]() { attr.name = title.ptr->document()->toPlainText(); });

	//	Setup SVG buttons:
	svg.input->moveBy(18, 18);
	svg.output->moveBy(43, 18);
	svg.params->moveBy(68, 18);
	svg.toggle->setToggleFile(":/icons/node-lock.svg");
	svg.toggle->moveBy(257, 18);
	svg.close->moveBy(282, 18);

	svg.input->setToolTip("Define Input");
	svg.output->setToolTip("Define Output");
	svg.params->setToolTip("Define Constant");
	svg.close->setToolTip("Delete Node");

	connect(svg.close, &nodeSVG::leftClicked, [&]() { emit nodeDeleted(this); });
	connect(svg.input, &nodeSVG::leftClicked, [&]() { createHandle(Input); });
	connect(svg.output, &nodeSVG::leftClicked, [&]() { createHandle(Output); });
	connect(svg.params, &nodeSVG::leftClicked, [&]() { createParams(); });
	connect(svg.toggle,
			&nodeSVG::leftClicked,
			[&]()
			{
				attr.locked = !attr.locked;
				onLockToggled(attr.locked);
			});

/*	Draw rails (inpRail and outRail) on either side of the node. Input and output variables
 *	can be vertically moved along these rails
 */
	rails.east->setPen(PEN_RAIL);
	rails.east->setLine(0, 0, 0, 120);
	rails.east->setPos(292, 45);
	rails.east->setData(0, QVariant::fromValue<StreamType>(Output));

	rails.west->setPen(PEN_RAIL);
	rails.west->setLine(0, 0, 0, 120);
	rails.west->setPos(8, 45);
	rails.west->setData(0, QVariant::fromValue<StreamType>(Input));

	rails.hintWest->setRect(0, 0, 8, 8);
	rails.hintWest->setBrush(QBrush(QColor(0x3BCE5B), Qt::SolidPattern));
	rails.hintWest->setOpacity(0.3);
	rails.hintWest->hide();

	rails.hintEast->setRect(0, 0, 8, 8);
	rails.hintEast->setBrush(QBrush(QColor(0x3BCE5B), Qt::SolidPattern));
	rails.hintEast->setOpacity(0.3);
	rails.hintEast->hide();

	//	Initialize status bar:
	statusbar.board->setBrush(QBrush(0x22333B, Qt::SolidPattern));
	statusbar.board->setRect(0, 0, NODE_WS - 1.0, 24.0);
	statusbar.board->setPos(0.5, QGraphicsRectItem::boundingRect().bottom() - 25.0);
	statusbar.pointer->print(statusbar.message, Info);
	statusbar.pointer->setPos(1, 1);

	menu.pointer->addAction(menu.save);
	menu.pointer->addSeparator();
	menu.pointer->addAction(menu.input);
	menu.pointer->addAction(menu.output);
	menu.pointer->addAction(menu.constant);
	menu.pointer->addSeparator();
	menu.pointer->addAction(menu.close);

	menu.save->setShortcutVisibleInContextMenu(true);                       //	Show the shortcut in the menu
	menu.save->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S)); //	Define the custom shortcut
	menu.save->setShortcutContext(Qt::WidgetWithChildrenShortcut);          //	Do not remove or modify

	menu.input->setShortcutVisibleInContextMenu(true);                       //	Show the shortcut in the menu
	menu.input->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_I)); //	Define the custom shortcut
	menu.input->setShortcutContext(Qt::WidgetWithChildrenShortcut);          //	Do not remove or modify

	menu.output->setShortcutVisibleInContextMenu(true);                       //	Show the shortcut in the menu
	menu.output->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_O)); //	Define the custom shortcut
	menu.output->setShortcutContext(Qt::WidgetWithChildrenShortcut);          //	Do not remove or modify

	menu.constant->setShortcutVisibleInContextMenu(true);                       //	Show the shortcut in the menu
	menu.constant->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_C)); //	Define the custom shortcut
	menu.constant->setShortcutContext(Qt::WidgetWithChildrenShortcut);          //	Do not remove or modify

	menu.close->setShortcutVisibleInContextMenu(true);                       //	Show the shortcut in the menu
	menu.close->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Q)); //	Define the custom shortcut
	menu.close->setShortcutContext(Qt::WidgetWithChildrenShortcut);          //	Do not remove or modify

	connect(menu.save, &QAction::triggered, [&]() { actionSave(); });
	connect(menu.close, &QAction::triggered, [&]() { svg.close->leftClicked(); });
	connect(menu.input, &QAction::triggered, [&]() { svg.input->leftClicked(); });
	connect(menu.output, &QAction::triggered, [&]() { svg.output->leftClicked(); });
	connect(menu.constant, &QAction::triggered, [&]() { svg.params->leftClicked(); });

//	Customize behaviour of node:
	setAcceptHoverEvents(true);
	setFlag(ItemIsMovable, true);
	setFlag(ItemIsSelectable, true);
	setFlag(ItemSendsGeometryChanges, true);
	setFlag(ItemSendsScenePositionChanges, true);

//	These are supposed to improve performance:
	setCacheMode(ItemCoordinateCache);
	setTransform(QTransform(), false);
}

//	Copy constructor, also delegates to the constructor above for initialization:
nodeCtrl::nodeCtrl(const nodeCtrl& source) :

//	Call the delegate constructor:
	nodeCtrl(source.scenePos() + QPointF(25, 25), source.name(), source.parentItem())

//	-----------------------------
//	Copy-contructor (body) begin:
{
#ifdef VERBOSE
	qInfo() << __FILE_NAME__ << __func__;
#endif

//	Temporary variable:
	nodeHandle* variable = nullptr;

//	Copy the original node's input variables:
	for (const auto src : source.list.inp) {
		variable = createHandle(Input);
		variable->setPos(src->pos());
		variable->setCategory(src->category());

		/*	If the original variable is paired, store its relative displacement from its conjugate. This is required to
		 *	preserve connections when nodes are copy-pasted.
		 */
		if (src->isPaired()) {
			const auto diff = src->conjugate()->scenePos() - src->scenePos();
			variable->setData(0, QVariant::fromValue(diff));
		}
	}

//	Copy the original node's output variables:
	for (const auto src : source.list.out) {
		variable = createHandle(Output);
		variable->setPos(src->pos());

		/*	If the original variable is paired, store its relative displacement from its conjugate. This is required to
		 *	preserve connections when nodes are copy-pasted.
		 */
		if (src->isPaired()) {
			const auto diff = src->conjugate()->scenePos() - src->scenePos();
			variable->setData(0, QVariant::fromValue(diff));
		}
	}
}

QVariant
nodeCtrl::itemChange(const GraphicsItemChange change, const QVariant& value) {

//	Switch case block to execute custom tasks when the object is moved:
	switch (change) {

		//	If the node was moved, emit signal:
		case ItemScenePositionHasChanged: {
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
nodeCtrl::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {

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
nodeCtrl::hoverMoveEvent(QGraphicsSceneHoverEvent* event) {

	const auto leftRail  = rails.west->mapFromParent(event->pos());
	const auto rightRail = rails.east->mapFromParent(event->pos());

	if (rails.west->contains(leftRail)) {
		const auto x = rails.west->pos().x() - 12.0;
		const auto y = event->pos().y() - 49.0;
		rails.hintWest->setPos(x, y);
		rails.hintWest->show();
	}
	else
		rails.hintWest->hide();

	if (rails.east->contains(rightRail)) {
		const auto x = rails.east->pos().x() - 296.0;
		const auto y = event->pos().y() - 49.0;
		rails.hintEast->setPos(x, y);
		rails.hintEast->show();
	}
	else
		rails.hintEast->hide();

//	Propagate event downstream:
	QGraphicsRectItem::hoverMoveEvent(event);
	event->accept();
}

void
nodeCtrl::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {

	//	Within bounding rectangle, switch to Qt::ArrowCursor:
	setCursor(Qt::ArrowCursor);

	//	Propagate event downstream:
	QGraphicsRectItem::hoverEnterEvent(event);
	event->accept();
}

void
nodeCtrl::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {

	//	Hide handle hints:
	rails.hintWest->hide();
	rails.hintEast->hide();

	//	Propagate event downstream:
	unsetCursor();
	QGraphicsRectItem::hoverLeaveEvent(event);
}

void
nodeCtrl::mousePressEvent(QGraphicsSceneMouseEvent* event) {

//	If the mouse click is on the rails, create a new variable:
	const auto posLRail = rails.west->mapFromParent(event->pos());
	const auto posRRail = rails.east->mapFromParent(event->pos());
	const auto position = QPointF(0.0, event->pos().y() - 4.0);

//	Initialize a temporary variable:
	nodeHandle* handle = nullptr;

//	When the user clicks an input or output rail, a handle is automatically created.
	if (rails.west->contains(posLRail)) {
		setFlag(ItemIsMovable, false);
		handle = createHandle(Input, position);
		handle->handleClicked(handle);
	}
	else if (rails.east->contains(posRRail)) {
		setFlag(ItemIsMovable, false);
		handle = createHandle(Output, position);
		handle->handleClicked(handle);
	}
	else
		setFlag(ItemIsMovable, true);

	//	Call base-class implementation:
	QGraphicsRectItem::mousePressEvent(event);
}

void
nodeCtrl::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {

	//	Resolve event-handlers of nested objects first, if any:
	QGraphicsRectItem::mouseReleaseEvent(event);
}

void
nodeCtrl::contextMenuEvent(QGraphicsSceneContextMenuEvent* event) {

	//	Resolve event handlers of nested objects first, if any:
	QGraphicsRectItem::contextMenuEvent(event);

	//	Show context menu:
	menu.pointer->exec(event->screenPos());
	event->accept();
}

nodeHandle*
nodeCtrl::handleAt(const QPointF& pos) //  pos must be in scene coordinates:
{
//	Print file and function name:
#ifdef VERBOSE
	qInfo() << __FILE_NAME__ << __func__;
#endif

	for (const auto var : list.inp)
		if (var->mapFromScene(pos) == QPointF(0, 0))
			return (var);

	for (const auto var : list.out)
		if (var->mapFromScene(pos) == QPointF(0, 0))
			return (var);

	return (nullptr);
}

nodeHandle*
nodeCtrl::createHandle(const StreamType& handleType, const QPointF pos) {

/*	This function creates a new handle of the desired type (StreamType), stores it in the appropriate list and positions
 *	it within the node according to its type (e.g. input and output variables are on the left and right, respectively).	*/

//	Print file and function name:
#ifdef VERBOSE
	qInfo() << __FILE__ << __func__;
#endif

//	Function body:
	auto        position = 0.0;
	nodeHandle* pointer  = nullptr;

//	Switch-case block:
	switch (handleType) {

		//	StreamType = StreamType::Input (i.e. input handle):
		case Input: {

			//	Create handle and initialize its position:
			pointer  = new nodeHandle(handleType, this);
			position = rails.west->pos().x() - 4.0;

			//	Store the pointer to the handle in the node's local list:
			list.inp.append(pointer);

			//	Emit connectHandle() signal when the handle is clicked. This signal is processed by the node and scene:
			connect(pointer, &nodeHandle::handleClicked, [&](nodeHandle* handle) { emit connectHandle(this, handle); });
			connect(pointer, &nodeHandle::handleDeleted, [&](nodeHandle* handle) { emit deleteHandle(handle); });

			//	Adjust position of the handle (handles are automatically stacked, unless moved by the user):
			pointer->setPos(pos == QPointF()
								? QPointF(position, 12 + list.inp.size() * 40)
								: QPointF(position, pos.y()));

			//	Display a status message:
			statusbar.pointer->print(QString("Input handle (" + pointer->UID() + ") created"));
			break;
		}

		//	StreamType = StreamType::Output (i.e. output handle):
		case Output: {

			//	Create variable with appropriate attribute(s):
			pointer  = new nodeHandle(handleType, this);
			position = rails.east->pos().x() - 4.0;

			//	Store the variable in the input-list, and the AMPL list:
			list.out.push_back(pointer);

			/*	Emit createLink() signal when a variable within the node is clicked. This
			 *	signal is captured and handled by schemaCanvas::onCreateLink()	*/
			connect(pointer, &nodeHandle::handleClicked, [&](nodeHandle* handle) { emit connectHandle(this, handle); });
			connect(pointer, &nodeHandle::handleDeleted, [&](nodeHandle* handle) { emit deleteHandle(handle); });

			/*	Adjust position of the created variable. An input variable is positioned near
			 *	the left edge of the node, stacked sequentially below other input variables	*/
			pointer->setPos(pos == QPointF()
								? QPointF(position, 12 + list.out.size() * 40)
								: QPointF(position, pos.y()));

			//	Display a status message:
			statusbar.pointer->print(QString("Output handle (" + pointer->UID() + ") created"));
			break;
		}

		default:
			break;
	}

/*	First shift bottom boundary downwards, followed by the variable rails and the status
 *	bar. The positions have been hardcoded, but a better solution will be found in the
 *	future	*/
	if (const auto maxSize = qMax(list.inp.size(), list.out.size());
		maxSize >= 4) {

		//	Set bottom boundary according to the number of variables in the node:
		setRect(QRect(0, 0, attr.rect.width(), attr.rect.height() + (maxSize - 3) * 40.0));

		//	Update rail-length:
		rails.east->setLine(0, 0, 0, boundingRect().bottom() - 76.0);
		rails.west->setLine(0, 0, 0, boundingRect().bottom() - 76.0);

		//	Update status bar position:
		statusbar.board->setPos(0.5, QGraphicsRectItem::boundingRect().bottom() - 25.0);
	}

//	Emit signal:
	emit handleCreated();

//	Return pointer to the created handle:
	return (pointer);
}

//	This function is triggered when the user selects "New Parameter" from the node's context-menu:
QList<nodeParams*>*
nodeCtrl::createParams() {

#ifdef VERBOSE
	qInfo() << __FILE__ << __func__;
#endif

	auto parent = dynamic_cast<QWidget*>(parentWidget());
	auto dialog = customDialog("New Parameter", "Name (comma-separated)", parent);

	int result = dialog.exec();

	const auto input = dialog.parameters();
	const auto plist = QList<nodeParams*>();
	qInfo() << "Entered parameters: " << input;

	for (QStringList paramsList = input.split(',');
		 auto        param : paramsList) {

#ifdef VERBOSE
		qInfo() << param.simplified();
#endif

		const auto pointer = new nodeParams(param.simplified());
		list.par.push_back(pointer);
	}
}


//	This SLOT is triggered by SIGNAL(nodeHandle::handleDeleted(nodeHandle*)):
void
nodeCtrl::deleteHandle(nodeHandle* handle) {

#ifdef VERBOSE
//	Print file and function name:
	qInfo() << __FILE__ << __func__;
#endif

	if (handle->streamType() == Input) //	Remove the variable from the node's list
		list.inp.removeAll(handle);
	else
		list.out.removeAll(handle);

//	Delete handle using QObject::deleteLater():
	handle->deleteLater();

//	Emit handleDeleted() signal:
	emit handleDeleted();
}

void
nodeCtrl::onLockToggled(const bool lock) {

	svg.input->setEnabled(!lock);
	svg.output->setEnabled(!lock);
	svg.params->setEnabled(!lock);
	svg.close->setEnabled(!lock);

	rails.west->setEnabled(!lock);
	rails.east->setEnabled(!lock);

	setAcceptHoverEvents(!lock);
	setFlag(ItemIsMovable, !lock);
	setFlag(ItemIsSelectable, !lock);
	setAcceptedMouseButtons(lock
								? Qt::NoButton
								: Qt::AllButtons);
}

void
nodeCtrl::reconnect() {

//	Print file and function name:
	qInfo() << __FILE_NAME__ << __func__;

//	Loop over input variables:
	for (const auto& var : list.inp) {
		const auto point = var->data(0).value<QPointF>() + var->scenePos();
		const auto item  = scene()
							   ? scene()->itemAt(point, QTransform())
							   : nullptr;

		if (item && item->type() == UserType + NODEITEM) {
			const auto node = qgraphicsitem_cast<nodeCtrl*>(item);
			const auto xvar = node->handleAt(node->mapFromScene(point));

			if (const auto path = var->pair(xvar))
				qInfo() << "\t- Connection established";
		}
	}

//	Loop over output variables:
	for (const auto& var : list.out) {
		const auto point = var->data(0).value<QPointF>() + var->scenePos();
		const auto item  = scene()
							   ? scene()->itemAt(point, QTransform())
							   : nullptr;

		if (item && item->type() == UserType + NODEITEM) {
			const auto node = qgraphicsitem_cast<nodeCtrl*>(item);
			const auto xvar = node->handleAt(point);

			if (const auto path = var->pair(xvar))
				qInfo() << "\t- Connection established";
		}
	}
}
