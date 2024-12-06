//
// Created by Sudharshan Saranathan on 21/11/24.
//

/*  Include class header    */
#include "node/nodeHandle.h"
#include "schematic/schemaCanvas.h"

/*  QtCore module   */
#include <QGraphicsProxyWidget>
#include <QRadioButton>
#include <QRandomGenerator>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsView>
#include <QShortcut>
#include <QTimer>

#include "node/nodeConnect.h"

sensor::sensor(const double& halfWidth, QGraphicsItem* parent) :
//	Initializer list:
//	Base-class constructor:
	QItemR(parent) {
	setAcceptHoverEvents(true);
	setBrush(Qt::white);
	setPen(QPen());
	setOpacity(0.3);

	setTransformOriginPoint(halfWidth, halfWidth);
	setRect(0, 0, 2 * halfWidth, 2 * halfWidth);
}

void
sensor::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	QGraphicsRectItem::hoverEnterEvent(event);

	qInfo() << "hoverEnterEvent";
	if (scene() && scene()->objectName() == "schemaCanvas") {
		const auto pointer = dynamic_cast<schemaCanvas*>(scene());
		const auto handle  = qgraphicsitem_cast<nodeHandle*>(parentItem());

		pointer->setProximity(handle);
		event->accept();
	}
}

void
sensor::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	QGraphicsRectItem::hoverLeaveEvent(event);

	qInfo() << "hoverLeaveEvent";
	if (scene() && scene()->objectName() == "schemaCanvas") {
		const auto pointer = dynamic_cast<schemaCanvas*>(scene());
		pointer->setProximity(nullptr);
	}
}

//  Class Destructor:
nodeHandle::~nodeHandle() {

	qInfo() << __FILE__ << __func__; //  Print file and function name
	free();                          //  Reset the conjugate pointers

	if (disconnect())                                      //  Disconnect this handle's signals
		qInfo() << "\t- QObject::disconnect() successful"; //  from all slots

	emit handleDeleted(this); //  Emit signal variableDeleted(this)
}

/*  Class Constructor  */
nodeHandle::nodeHandle(const StreamType& type, QGraphicsItem* parent) :
//	Initializer list:
//	Initialize base-class constructor:
	QGraphicsEllipseItem{parent},
/*  Default Attribute(s)  */
	attr{type, categoryList[0], HEX_RANDOM, QRect(0, 0, HANDLE_XS, HANDLE_YS)},
	//  Variable Handle:
	handle{
		new QItemT(this),
		new QItemT(this),
		new QItemE(this),
		(attr.type == Input) * 4.0 + (attr.type == Output) * 288.0,
		{false, nullptr, nullptr}
	}

//  --------------------------
/*  Constructor body-begin  */
{
//  Customize the appearance and size of the handle:
	setObjectName("nodeHandle");
	setBrush(QBrush(QColor(4, 220, 69), Qt::SolidPattern));
	setPen(QPen(Qt::black, 1.0));
	setRect(attr.rect);

/*  Customize the behaviour of the handle. Since the handle is temporarily enlarged when the handle is clicked, it's
 *  origin point must be shifted from the default location to its rectangle's center. This is accomplished with
 *  QGraphicsItem::setTransformOriginPoint().	*/
	setAcceptHoverEvents(true);
	setTransformOriginPoint(rect().center());
	setFlag(ItemSendsScenePositionChanges, true);

//  Set cache mode to ItemCoordinateCache. This is supposed to reduce the viewport's lag when scrolling:
	setCacheMode(DeviceCoordinateCache);

/*  The QGraphicsTextItem (symbol) is placed next to the handle. It shows any connected variable's symbolic name (e.g.
 *  X1, X2, ...). The following properties are customized: font, font-colour, font-size, textbox width, position,
 *  alignment, and editability  */
	handle.symbol->setDefaultTextColor(Qt::black);
	handle.symbol->setFont(QFont("Verdana", FONT_SIZE));
	handle.symbol->setPos(type == Input
							  ? 10
							  : -23,
						  FONT_SIZE - 16.3);
	handle.symbol->document()->setDefaultTextOption(QTextOption(type == Input
																	? Qt::AlignLeft
																	: Qt::AlignRight));
	handle.symbol->document()->setTextWidth(20);

//	This QGraphicsItemText displays the variable's informal name:
	handle.text->setTabChangesFocus(true);
	handle.text->setDefaultTextColor(Qt::gray);
	handle.text->setPlainText("Variable");
	handle.text->setFont(QFont("Verdana", FONT_SIZE));
	handle.text->setPos(type == Input
							? 30
							: -83,
						FONT_SIZE - 16.7);
	handle.text->setTextInteractionFlags(Qt::TextEditorInteraction);
	handle.text->document()->setDefaultTextOption(QTextOption(type == Input
																  ? Qt::AlignLeft
																  : Qt::AlignRight));
	handle.text->document()->setTextWidth(60);

/*  The handle also includes a black selector that appears when the user hovers over
 *  the handle, similar to a radio-button. The following lines customize its properties:
 *  appearance, position, colour, and size  */
	handle.selector->setRect(QRect(0, 0, HANDLE_XS - 4, HANDLE_YS - 4));
	handle.selector->setBrush(QBrush(Qt::black, Qt::SolidPattern));
	handle.selector->setPen(QPen(Qt::black));
	handle.selector->setPos(rect().center() - QPointF(2, 2));
	handle.selector->hide();

//  Emit signal:
	emit handleCreated();
}

nodeConnect*
nodeHandle::pair(nodeHandle* vsrc, const QColor color) {

//	If origin handle is null or paired, reject connection:
	if (vsrc == nullptr || vsrc->isPaired() || handle.state.connected)
		return (nullptr);

//	If origin handle is of the same stream type as this, reject connection:
	if (vsrc->attr.type == this->attr.type)
		return (nullptr);

//	Initialize helper pointers to origin and target nodes:
	const auto sourceNode = qgraphicsitem_cast<nodeCtrl*>(vsrc->parentItem());
	const auto targetNode = qgraphicsitem_cast<nodeCtrl*>(this->parentItem());

//	If casting fails or if origin and target nodes are the same, reject connection:
	if (!sourceNode || !targetNode || sourceNode->getUID() == targetNode->getUID())
		return (nullptr);

//	Create a new connection (nodeConnect object) and add it to the scene:
	const auto pen  = QPen(vsrc->categoryColor(), 3.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	const auto path = new nodeConnect(pen);

//	Compute the coordinates of the connection's endpoints:
	const auto sourceCoordinate = vsrc->scenePos() + vsrc->rect().center();
	const auto targetCoordinate = this->scenePos() + this->rect().center();

//	Define a symbol for the variable:
	auto symbol  = QString();
	auto counter = 0;
	if (amplDatabase::deletedSymbols.isEmpty())
		symbol = QString("X") + QString::number(amplDatabase::variableList.size());

	else {
		std::sort(amplDatabase::deletedSymbols.begin(), amplDatabase::deletedSymbols.end());
		counter = amplDatabase::deletedSymbols.takeAt(0);
		symbol  = QString("X") + QString::number(counter);
	}

	vsrc->handle.symbol->setPlainText(symbol);
	this->handle.symbol->setPlainText(symbol);
	this->handle.text->setPlainText(vsrc->handle.text->toPlainText());

//	Set the symbol for the variable:
	path->setSymbol(symbol);

//	Draw the path, initialize nodeConnect's convenience pointers:
	path->connect(sourceCoordinate, targetCoordinate);
	path->setAttr(sourceNode, vsrc, targetNode, this);

//	Add path to the scene, and store pointer to the variable:
	if (scene())
		scene()->addItem(path);

	amplDatabase::variableList.append(path);

//	Connect signals to slots:
	connect(sourceNode, &nodeCtrl::nodeShifted, path, &nodeConnect::refresh);
	connect(targetNode, &nodeCtrl::nodeShifted, path, &nodeConnect::refresh);

	connect(vsrc, &nodeHandle::handleShifted, path, &nodeConnect::refresh);
	connect(vsrc, &nodeHandle::handleDeleted, path, &nodeConnect::clearConnection);
	connect(this, &nodeHandle::handleShifted, path, &nodeConnect::refresh);
	connect(this, &nodeHandle::handleDeleted, path, &nodeConnect::clearConnection);

//	Set appropriate flags and initialize the handle's convenience pointers:
	handle.state.connected = true; //	Set the connected status to true
	handle.state.conjugate = vsrc; //	Set <vsrc> as this handle's conjugate
	handle.state.connector = path; //   Store the pointer to the connector
	attr.category          = vsrc->attr.category;

//	Customize appearance of the connected handle:
	setBrush(QBrush(color, Qt::SolidPattern));
	hideSelector();
	setOpacity(1.0);

//	Set the handle's state to connected. Store pointer to the conjugate handle:
	vsrc->handle.state.connected = true;
	vsrc->handle.state.conjugate = this;
	vsrc->handle.state.connector = path;
	vsrc->setBrush(QBrush(color, Qt::SolidPattern));
	vsrc->hideSelector();
	vsrc->setOpacity(1.0);

//	Return pointer to nodeConnect object:
//	path->refresh();
	return (path);
}

//  Open handle for new connections:
void
nodeHandle::free(const QColor color) {

//	Reset connection state and helper pointers:
	if (handle.state.connected && handle.state.conjugate != nullptr) {
		handle.state.conjugate->setBrush(QBrush(color, Qt::SolidPattern));
		handle.state.conjugate->handle.state.connected = false;
		handle.state.conjugate->handle.state.conjugate = nullptr;
		handle.state.conjugate->handle.state.connector = nullptr;

		setBrush(QBrush(color, Qt::SolidPattern));
		handle.state.conjugate = nullptr;
		handle.state.connector = nullptr;
		handle.state.connected = false;
	}
}

QVariant
nodeHandle::itemChange(const GraphicsItemChange change, const QVariant& value) {

//	Switch-case block to detect handle shifts:
	switch (change) {
		//	If the handle was moved, emit signal:
		case ItemScenePositionHasChanged: {
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
nodeHandle::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	QGraphicsEllipseItem::hoverEnterEvent(event);

//  Select button and accept event:
	if (!handle.state.connected)
		showSelector();

	event->accept();
}

//	Event-handler for hover-leave events:
void
nodeHandle::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {

//  Deselect button and accept event:
	hideSelector();
	event->accept();
}

void
nodeHandle::mousePressEvent(QGraphicsSceneMouseEvent* event) {

//	Switch-case block to handle mouse-button press events:
	switch (event->button()) {

		//  If handle isn't paired, emit handleClicked():
		case Qt::LeftButton: {
			if (!handle.state.connected) {
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
nodeHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {

	if (!handle.state.connected)
		setOpacity(1.0);
	else {
		setFlag(ItemIsMovable, false);
		const auto xpos = handle.position;
		const auto ypos = pos().y();

		if (ypos <= 40.0)
			setPos(handle.position, 40.0);
		else if (ypos >= parentItem()->boundingRect().bottom() - 38.0)
			setPos(handle.position, parentItem()->boundingRect().bottom() - 38.0);
		else
			setPos(xpos, ypos);
	}

//  Call base-class implementation before accepting the event:
	QGraphicsEllipseItem::mouseReleaseEvent(event);
	event->accept();
}

void
nodeHandle::contextMenuEvent(QGraphicsSceneContextMenuEvent* event) {
	const auto menu    = new QMenu();
	const auto action1 = menu->addAction("Change Name");
	const auto action2 = menu->addAction("Save as Template");

	action1->setShortcutContext(Qt::WidgetWithChildrenShortcut);
	action2->setShortcutContext(Qt::WidgetWithChildrenShortcut);

	menu->exec(event->screenPos());
	event->accept();
}
