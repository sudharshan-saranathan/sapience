//
// Created by Sudharshan Saranathan on 21/11/24.
//

/*  Include class header    */
#include "node/node_handle.h"
#include "node/node_connect.h"
#include "schematic/schema_canvas.h"

/*  QtCore module   */
#include <QGraphicsProxyWidget>
#include <QRadioButton>
#include <QRandomGenerator>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsView>
#include <QShortcut>
#include <QTimer>

//  Class Destructor:
NodeHandle::~NodeHandle()
{
	qInfo() << __FILE__ << __func__; //  Print file and function name
	free();                          //  Reset the conjugate pointers

	if (disconnect())                                      //  Disconnect this m_handle's signals
		qInfo() << "\t- QObject::disconnect() successful"; //  from all slots

	emit handleDeleted(this); //  Emit signal variableDeleted(this)
}

/*  Class Constructor  */
NodeHandle::NodeHandle(const StreamType& type, QGraphicsItem* parent) :
	//	Initializer list:
	//	Initialize base-class constructor:
	QGraphicsEllipseItem{parent},
	/*  Default Attribute(s)  */
	m_attr{type, categoryList[0], "V" + RANDOMHEX, QRect(0, 0, HANDLE_XS, HANDLE_YS)},
	//  Variable Handle:
	m_handle{
		new q_item_t(this),
		new q_item_t(this),
		new QItemE(this),
		(m_attr.type == INP) * 4.0 + (m_attr.type == OUT) * 288.0,
		{false, nullptr, nullptr}
	}

//  --------------------------
/*  Constructor body-begin  */
{
	//  Customize the appearance and size of the m_handle:
	setObjectName("NodeHandle");
	setBrush(QBrush(QColor(4, 220, 69), Qt::SolidPattern));
	setPen(QPen(Qt::black, 1.0));
	setRect(m_attr.rect);

	/*  Customize the behaviour of the m_handle. Since the m_handle is temporarily enlarged when the m_handle is clicked, it's
	 *  origin point must be shifted from the default location to its rectangle's center. This is accomplished with
	 *  QGraphicsItem::setTransformOriginPoint().	*/
	setAcceptHoverEvents(true);
	setTransformOriginPoint(rect().center());
	setFlag(ItemSendsScenePositionChanges, true);

	//  Set cache mode to ItemCoordinateCache. This is supposed to reduce the viewport's lag when scrolling:
	setCacheMode(DeviceCoordinateCache);

	/*  The QGraphicsTextItem (symbol) is placed next to the m_handle. It shows any connected variable's symbolic name (e.g.
	 *  X1, X2, ...). The following properties are customized: font, font-colour, font-size, textbox width, position,
	 *  alignment, and editability  */
	m_handle.symbol->setDefaultTextColor(Qt::black);
	m_handle.symbol->setFont(QFont("Monaco", FONT_SIZE));
	m_handle.symbol->setPos(type == INP ? 10 : -24, FONT_SIZE - 20.0);
	m_handle.symbol->document()->setDefaultTextOption(QTextOption(type == INP ? Qt::AlignLeft : Qt::AlignRight));
	m_handle.symbol->document()->setTextWidth(20);

	//	This QGraphicsItemText displays the variable's informal name:
	m_handle.text->setTabChangesFocus(true);
	m_handle.text->setDefaultTextColor(Qt::gray);
	m_handle.text->setPlainText("Variable");
	m_handle.text->setFont(QFont("Monaco", FONT_SIZE));
	m_handle.text->setPos(type == INP ? 30 : -87, FONT_SIZE - 20.0);
	m_handle.text->setTextInteractionFlags(Qt::TextEditorInteraction);
	m_handle.text->document()->setDefaultTextOption(QTextOption(type == INP ? Qt::AlignLeft : Qt::AlignRight));
	m_handle.text->document()->setTextWidth(60);

	/*  The m_handle also includes a black selector that appears when the user hovers over
	 *  the m_handle, similar to a radio-button. The following lines customize its properties:
	 *  appearance, position, colour, and size  */
	m_handle.selector->setRect(QRect(0, 0, HANDLE_XS - 4, HANDLE_YS - 4));
	m_handle.selector->setBrush(QBrush(Qt::black, Qt::SolidPattern));
	m_handle.selector->setPen(QPen(Qt::black));
	m_handle.selector->setPos(rect().center() - QPointF(2, 2));
	m_handle.selector->hide();

	//  Emit signal:
	emit handleCreated();
}

NodeConnect*
NodeHandle::pair(NodeHandle* vsrc, const QColor color)
{
	//	If origin m_handle is null or paired, reject connection:
	if (vsrc == nullptr || vsrc->isPaired() || m_handle.state.connected)
		return (nullptr);

	//	If origin m_handle is of the same stream type as this, reject connection:
	if (vsrc->m_attr.type == this->m_attr.type)
		return (nullptr);

	//	Initialize helper pointers to origin and target nodes:
	const auto sourceNode = qgraphicsitem_cast<NodeCtrl*>(vsrc->parentItem());
	const auto targetNode = qgraphicsitem_cast<NodeCtrl*>(this->parentItem());

	//	If casting fails or if origin and target nodes are the same, reject connection:
	if (!sourceNode || !targetNode || sourceNode->getUID() == targetNode->getUID())
		return (nullptr);

	//	Create a new connection (NodeConnect object) and add it to the scene:
	const auto pen  = QPen(vsrc->categoryColor(), 3.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	const auto path = new NodeConnect(pen);

	//	Compute the coordinates of the connection's endpoints:
	const auto sourceCoordinate = vsrc->scenePos() + vsrc->rect().center();
	const auto targetCoordinate = this->scenePos() + this->rect().center();

	//	Define a symbol for the variable:
	auto symbol  = QString();
	auto counter = 0;
	if (OptimDB::deletedSymbols.isEmpty())
		symbol = QString("X") + QString::number(OptimDB::variableList.size());

	else
	{
		std::sort(OptimDB::deletedSymbols.begin(), OptimDB::deletedSymbols.end());
		counter = OptimDB::deletedSymbols.takeAt(0);
		symbol  = QString("X") + QString::number(counter);
	}

	vsrc->m_handle.symbol->setPlainText(symbol);
	this->m_handle.symbol->setPlainText(symbol);
	this->m_handle.text->setPlainText(vsrc->m_handle.text->toPlainText());

	//	Set the symbol for the variable:
	path->setSymbol(symbol);

	//	Draw the path, initialize NodeConnect's convenience pointers:
	path->connect(sourceCoordinate, targetCoordinate);
	path->setAttr(sourceNode, vsrc, targetNode, this);

	//	Add path to the scene, and store pointer to the variable:
	if (scene())
		scene()->addItem(path);

	OptimDB::variableList.append(path);

	//	Connect signals to slots:
	connect(sourceNode, &NodeCtrl::nodeShifted, path, &NodeConnect::refresh);
	connect(targetNode, &NodeCtrl::nodeShifted, path, &NodeConnect::refresh);

	connect(vsrc, &NodeHandle::handleShifted, path, &NodeConnect::refresh);
	connect(vsrc, &NodeHandle::handleDeleted, path, &NodeConnect::clearConnection);
	connect(this, &NodeHandle::handleShifted, path, &NodeConnect::refresh);
	connect(this, &NodeHandle::handleDeleted, path, &NodeConnect::clearConnection);

	//	Set appropriate flags and initialize the m_handle's convenience pointers:
	m_handle.state.connected = true; //	Set the connected status to true
	m_handle.state.conjugate = vsrc; //	Set <vsrc> as this m_handle's conjugate
	m_handle.state.connector = path; //   Store the pointer to the connector
	m_attr.category          = vsrc->m_attr.category;

	//	Customize appearance of the connected m_handle:
	setBrush(QBrush(color, Qt::SolidPattern));
	hideSelector();
	setOpacity(1.0);

	//	Set the m_handle's state to connected. Store pointer to the conjugate m_handle:
	vsrc->m_handle.state.connected = true;
	vsrc->m_handle.state.conjugate = this;
	vsrc->m_handle.state.connector = path;
	vsrc->setBrush(QBrush(color, Qt::SolidPattern));
	vsrc->hideSelector();
	vsrc->setOpacity(1.0);

	//	Return pointer to NodeConnect object:
	//	path->refresh();
	return (path);
}

//  Open m_handle for new connections:
void
NodeHandle::free(const QColor color)
{
	//	Reset connection state and helper pointers:
	if (m_handle.state.connected && m_handle.state.conjugate != nullptr)
	{
		m_handle.state.conjugate->setBrush(QBrush(color, Qt::SolidPattern));
		m_handle.state.conjugate->m_handle.state.connected = false;
		m_handle.state.conjugate->m_handle.state.conjugate = nullptr;
		m_handle.state.conjugate->m_handle.state.connector = nullptr;

		setBrush(QBrush(color, Qt::SolidPattern));
		m_handle.state.conjugate = nullptr;
		m_handle.state.connector = nullptr;
		m_handle.state.connected = false;
	}
}

QVariant
NodeHandle::itemChange(const GraphicsItemChange change, const QVariant& value)
{
	//	Switch-case block to detect m_handle shifts:
	switch (change)
	{
	//	If the m_handle was moved, emit signal:
	case ItemScenePositionHasChanged:
		{
			emit handleShifted();
			break;
		}
	//	Default block:
	default:
		break;
	}

	return (value);
}

/*  Event-handler for hoverEnterEvent   */
void
NodeHandle::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	QGraphicsEllipseItem::hoverEnterEvent(event);

	//  Select button and accept event:
	if (!m_handle.state.connected)
		showSelector();

	event->accept();
}

//	Event-handler for hover-leave events:
void
NodeHandle::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	//  Deselect button and accept event:
	hideSelector();
	event->accept();
}

void
NodeHandle::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	//	Switch-case block to m_handle mouse-button press events:
	switch (event->button())
	{
	//  If m_handle isn't paired, emit handleClicked():
	case Qt::LeftButton:
		{
			if (!m_handle.state.connected)
			{
				setOpacity(0.5);
				emit handleClicked(this);
			}
			else
				setFlag(ItemIsMovable, true);
			break;
		}

	case Qt::MiddleButton:
		//  Emit signal to request deletion:
		emit handleDeleted(this);
		break;

	default:
		break;
	}

	//  Call base-class implementation before accepting event:
	QGraphicsEllipseItem::mousePressEvent(event);
	event->accept();
}

void
NodeHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	if (!m_handle.state.connected)
		setOpacity(1.0);
	else
	{
		setFlag(ItemIsMovable, false);
		const auto xpos = m_handle.position;
		const auto ypos = pos().y();

		if (ypos <= 40.0)
			setPos(m_handle.position, 40.0);
		else if (ypos >= parentItem()->boundingRect().bottom() - 38.0)
			setPos(m_handle.position, parentItem()->boundingRect().bottom() - 38.0);
		else
			setPos(xpos, ypos);
	}

	//  Call base-class implementation before accepting the event:
	QGraphicsEllipseItem::mouseReleaseEvent(event);
	event->accept();
}

void
NodeHandle::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
	const auto menu    = new QMenu();
	const auto action1 = menu->addAction("Change Name");
	const auto action2 = menu->addAction("Save as Template");

	action1->setShortcutContext(Qt::WidgetWithChildrenShortcut);
	action2->setShortcutContext(Qt::WidgetWithChildrenShortcut);

	menu->exec(event->screenPos());
	event->accept();
}
