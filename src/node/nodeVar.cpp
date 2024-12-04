//
// Created by Sudharshan Saranathan on 21/11/24.
//

/*  Include class header    */
#include "node/nodeVar.h"
#include "schematic/schemaCanvas.h"

/*  QtCore module   */
#include <QGraphicsProxyWidget>
#include <QRadioButton>
#include <QRandomGenerator>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsView>
#include <QTimer>

#include "node/nodeConnect.h"

//  Class Destructor:
nodeVar::~nodeVar() {

	qInfo() << __FILE__ << __func__; //  Print file and function name
	free();                          //  Reset the conjugate pointers

	if (disconnect())                                      //  Disconnect this variable's signals
		qInfo() << "\t- QObject::disconnect() successful"; //  from all slots

	emit variableDeleted(this); //  Emit signal variableDeleted(this)
}

/*  Class Constructor  */
nodeVar::nodeVar(const QString& name, const QString& symbol, const StreamType type, QGraphicsItem* parent) :
/*  Initialize base-class constructor   */
	QGraphicsEllipseItem{parent},
/*  Default Attribute(s)  */
	attr{type, categoryList[0], HEX_RANDOM, symbol, QRect(0, 0, HANDLE_XS, HANDLE_YS)},
	//  Variable Handle:
	handle{
		new QItemT(symbol, this),
		//  Symbol that appears next to the handle
		new QItemE(this),
		//  Black hover indicator
		(attr.type == Input) * 4.0 + (attr.type == Output) * 288.0,
	},
	//  struct _conjugate_:
	variable{false, nullptr}

//  --------------------------
/*  Constructor body-begin  */
{
	//  Customize the appearance and size of the handle:
	setBrush(QBrush(QColor(4, 220, 69), Qt::SolidPattern));
	setPen(QPen(Qt::black, 1.0));
	setRect(attr.rect);

	/*  Customize the behaviour of the handle. Since the variable is temporarily enlarged when the handle is clicked,
	 *  it's origin point must be shifted from the default location to its rectangle's center. This is accomplished
	 *  with QGraphicsItem::setTransformOriginPoint()
	 */
	setAcceptHoverEvents(true);
	setTransformOriginPoint(rect().center());
	setFlag(ItemSendsScenePositionChanges, true);

	//  Set cache mode to ItemCoordinateCache. This is supposed to reduce the viewport's lag when scrolling:
	setCacheMode(DeviceCoordinateCache);

	/*  The QGraphicsTextItem is placed next to the handle. It shows the symbolic name
	 *  of the variable (e.g. X1, X2, ...). The following customize its properties:
	 *  font, font-colour, font-size, textbox width, position, alignment, and editability  */
	handle.pointer->setDefaultTextColor(Qt::black);
	handle.pointer->setFont(QFont("Verdana", FONT_SIZE));
	handle.pointer->setPos(type == Input
							   ? 10
							   : -63,
						   FONT_SIZE - 16.3);
	handle.pointer->setTextInteractionFlags(Qt::TextEditorInteraction);
	handle.pointer->document()->setDefaultTextOption(QTextOption(type == Input
																	 ? Qt::AlignLeft
																	 : Qt::AlignRight));
	handle.pointer->document()->setTextWidth(60);

	/*  The handle also includes a black selector that appears when the user hovers over
	 *  the handle, similar to a radio-button. The following lines customize its properties:
	 *  appearance, position, colour, and size  */
	handle.selector->setRect(QRect(0, 0, HANDLE_XS - 4, HANDLE_YS - 4));
	handle.selector->setBrush(QBrush(Qt::black, Qt::SolidPattern));
	handle.selector->setPen(QPen(Qt::black));
	handle.selector->setPos(rect().center() - QPointF(2, 2));
	handle.selector->hide();

	//  Emit signal:
	emit variableCreated();
}

nodeConnect*
nodeVar::pair(nodeVar* vsrc, const QColor color) {

//	If source variable is null or paired, reject connection:
	if (vsrc == nullptr || vsrc->isPaired() || variable.connected)
		return (nullptr);

//	If the source variable is of the same stream type as this, reject connection:
	if (vsrc->attr.type == this->attr.type)
		return(nullptr);

//	Initialize helper pointers to the source and target nodes:
	const auto sourceNode = qgraphicsitem_cast<nodeCtrl*>(vsrc->parentItem());
	const auto targetNode = qgraphicsitem_cast<nodeCtrl*>(this->parentItem());

//	If casting fails or if the source and target nodes are the same, return nullptr:
	if (!sourceNode || !targetNode || sourceNode->getUID() == targetNode->getUID())
		return(nullptr);

//	Create a new connection (nodeConnect object) and add it to the scene:
	const auto pen  = QPen(vsrc->getCategoryColor(), 3.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	const auto path = new nodeConnect(pen);

//	Define the coordinates of the endpoints:
	const auto sourceCoordinate = vsrc->scenePos() + vsrc->rect().center();
	const auto targetCoordinate = this->scenePos() + this->rect().center();

//	Draw the path, initialize nodeConnect's convenience pointers:
	path->connect(sourceCoordinate, targetCoordinate);
	path->setAttr(sourceNode, vsrc, targetNode, this);

	qInfo() << "Source variable category: " << vsrc->getCategoryName();

//	Add the path to the scene, and store its reference in the database:
	if (scene()) scene()->addItem(path);
	amplDatabase::connectionList.append(path);

//	Connect signals to slots:
	connect(sourceNode, &nodeCtrl::nodeShifted, path, &nodeConnect::refresh);
	connect(targetNode, &nodeCtrl::nodeShifted, path, &nodeConnect::refresh);

	connect(vsrc, &nodeVar::variableShifted, path, &nodeConnect::refresh);
	connect(vsrc, &nodeVar::variableDeleted, path, &nodeConnect::clearConnection);
	connect(this, &nodeVar::variableShifted, path, &nodeConnect::refresh);
	connect(this, &nodeVar::variableDeleted, path, &nodeConnect::clearConnection);

//	Set appropriate flags and initialize the variable's convenience pointers:
	variable.connected = true;		//	Set the connected status to true
	variable.conjugate = vsrc;		//	Set <vsrc> as this variable's conjugate
	attr.category = vsrc->attr.category;

//	Customize appearance of the connected variable:
	setBrush(QBrush(color, Qt::SolidPattern));
	hideSelector();
	setOpacity(1.0);

	vsrc->variable.connected = true;
	vsrc->variable.conjugate = this;
	vsrc->setBrush(QBrush(color, Qt::SolidPattern));
	vsrc->hideSelector();
	vsrc->setOpacity(1.0);

//	Return pointer to nodeConnect object:
//	path->refresh();
	return (path);
}

//  Open variable for new connections:
void
nodeVar::free(const QColor color) {
	if (variable.connected && variable.conjugate != nullptr) {
		variable.conjugate->setBrush(QBrush(color, Qt::SolidPattern));
		variable.conjugate->variable.connected = false;
		variable.conjugate->variable.conjugate = nullptr;
		variable.conjugate  = nullptr;

		setBrush(QBrush(color, Qt::SolidPattern));
		variable.connected = false;
	}
}

QVariant
nodeVar::itemChange(const GraphicsItemChange change, const QVariant& value) {

//	Switch-case block to detect variable shifts:
	switch (change) {
	//	If the variable was moved, emit signal:
		case ItemScenePositionHasChanged: {
			emit variableShifted();
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
nodeVar::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	QGraphicsEllipseItem::hoverEnterEvent(event);

//  Select button and accept event:
	if (!variable.connected)
		showSelector();

	event->accept();
}

//	Event-handler for hover-leave events:
void
nodeVar::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {

//  Deselect button and accept event:
	hideSelector();
	event->accept();
}

void
nodeVar::mousePressEvent(QGraphicsSceneMouseEvent* event) {

/*  If variable isn't connected, request a new link through the
 *  createLink() signal, which is handled by schemaCanvas	*/
	switch (event->button()) {
		case Qt::LeftButton: {
			if (!variable.connected) {
				setOpacity(0.5);
				emit variableClicked(this);
			}
			else
				setFlag(ItemIsMovable, true);
			break;
		}

		case Qt::MiddleButton:
			//  Request deletion through SIGNAL(nodeVar::variableDeleted(nodeVar*)):
			emit variableDeleted(this);
			break;

		default:
			break;
	}

//  Call base-class implementation before accepting event:
	QGraphicsEllipseItem::mousePressEvent(event);
	event->accept();
}

void
nodeVar::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {

	if (!variable.connected)
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
nodeVar::contextMenuEvent(QGraphicsSceneContextMenuEvent* event) {
	const auto menu    = new QMenu();
	const auto action1 = menu->addAction("Change Name");
	const auto action2 = menu->addAction("Save as Template");

	action1->setShortcutContext(Qt::WidgetWithChildrenShortcut);
	action2->setShortcutContext(Qt::WidgetWithChildrenShortcut);

	menu->exec(event->screenPos());
	event->accept();
}
