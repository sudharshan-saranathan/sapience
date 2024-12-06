//
// Created by Sudharshan Saranathan on 25/11/24.
//

#include <cmath>
#include <QThread>
#include <QWidgetAction>

#include "schematic/schemaCanvas.h"
#include "node/nodeConnect.h"
#include "node/nodeHandle.h"

#define HEX_RANDOM QString("#%1").arg(QRandomGenerator::global()->generate() & 0xFFFFFF, 6, 16, QChar('0'))

nodeConnect::~nodeConnect() {

#ifdef VERBOSE
	qInfo() << __FILE__ << __func__;
#endif

	if (disconnect())
		qInfo() << "\t- QObject::disconnect() successful";
	else
		qWarning() << "\t- QObject::disconnect() returned false";

//	Reset pointers to nullptr. This is not needed, but it's good practice:
	pointers.sourceNode   = nullptr;
	pointers.targetNode   = nullptr;
	pointers.sourceHandle = nullptr;
	pointers.targetHandle = nullptr;

//	If the path is added to a scene, remove from scene:
	if (scene())
		scene()->removeItem(this);

	clear();
	deleteLater();
}

nodeConnect::nodeConnect(const QPen& pen, QGraphicsItem* parent) :
/*	Initializer list	*/
//	Base-class constructor:
	QGraphicsPathItem(parent),
//	struct _attr_:
	attr{pen, QString()},
//	Initialize helper-pointers:
    pointers{nullptr, nullptr, nullptr, nullptr},
//	struct _curve_:
	curve{QPainterPath()},
//	struct _menu_:
	menu{new QMenu, new QLineEdit, new QWidgetAction(menu.pointer)}

//	-------------------------
//	Constructor (body) begin:
{
	setZValue(-1);
	setPen(QPen(categoryList[0].getColor(), 3.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	setAcceptHoverEvents(true);

	//	Initialize the variable category selection menu:
	menu.createCategory->setPlaceholderText("Create Category");
	menu.createCategory->setFocusPolicy(Qt::StrongFocus);

	// Create a QWidgetAction to hold the QLineEdit:
	menu.createAction->setDefaultWidget(menu.createCategory);
	menu.createAction->setObjectName(QString("QWidgetAction"));

	//	Add the widget-action to the menu as the first entry:
	menu.pointer->addAction(menu.createAction);

	//	Handle the QLineEdit's returnPressed() signal (i.e. the user has pressed <Enter>):
	QObject::connect(menu.createCategory, &QLineEdit::returnPressed, [this]() {
		//	If the entered string is not empty:
		if (const auto categoryName = menu.createCategory->text(); !categoryName.isEmpty()) {

			//	Clear the QLineEdit once returnPressed() signal is emitted:
			menu.createCategory->clear();

			//	Create a new category with the entered type:
			const uint_t ID = static_cast<uint_t>(categoryList.size());
			categoryList.append(varCategory{categoryName, ID, HEX_RANDOM});

			//	Clear the QLineEdit after emitting the returnPressed() signal:
			const auto action   = menu.pointer->addAction(categoryName);
			const auto category = categoryList.last();

			action->setShortcut(0x30 + ID);												//	Set shortcut
			action->setShortcutContext(Qt::WidgetWithChildrenShortcut);					//	Set shortcut context
			action->setShortcutVisibleInContextMenu(true);								//	Set shortcut visible

			//	Do not close the menu when new categories are created:
			//	This is achieved with the following instruction:
			menu.pointer->setActiveAction(nullptr);

			//	Wait for the user to select a category:
			QObject::connect(action, &QAction::triggered, [this, category]{ setCategory(category); });
		}
	});
}

void nodeConnect::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	Q_UNUSED(event)
	setOpacity(0.6);
	setCursor(Qt::ArrowCursor);
}

void nodeConnect::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	Q_UNUSED(event)
	setOpacity(1.0);
	unsetCursor();
}

void nodeConnect::contextMenuEvent(QGraphicsSceneContextMenuEvent* event) {

	menu.pointer->addSeparator();
	for (const auto& category : categoryList) {

		const auto name   = category.getName();
		const auto action = menu.pointer->addAction(name);						//	Create a new action with typeName

		action->setShortcut(0x30 + category.getID());							//	Set shortcut
		action->setShortcutContext(Qt::WidgetWithChildrenShortcut);				//	Set shortcut context
		action->setShortcutVisibleInContextMenu(true);							//	Set shortcut visible

		QObject::connect(action, &QAction::triggered, [this, &category]() { setCategory(category); });
	}

	//	Show the menu:
	menu.pointer->exec(event->screenPos());								//	Show the menu

	//	Cleanup the list:
	for (const auto action : menu.pointer->actions()) {						//	Remove the actions from the menu
		if (action->objectName().isEmpty())
			menu.pointer->removeAction(action);
	}
}

void nodeConnect::setCategory(const varCategory& category) {

	qInfo() << category.getColor() << " " << category.getName();
	setPen(QPen(category.getColor(), 3.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	pointers.sourceHandle->setCategory(category);
	pointers.targetHandle->setCategory(category);

	menu.pointer->close();
}

void nodeConnect::clearConnection(const nodeHandle* handle) const {
	Q_UNUSED(handle)

	const auto counter = symbol.split("X")[1].toInt();

//	Remove connection from database, add symbol to the deletedSymbols list (so that it can be reused):
	amplDatabase::deletedSymbols.append(counter);
	amplDatabase::variableList.removeAll(this);

	delete this;
}

void nodeConnect::connect(const QPointF tpos) {

	if (pointers.sourceNode && pointers.sourceHandle) {
		const auto spos = pointers.sourceHandle->scenePos() + pointers.sourceHandle->rect().center();
		connect(spos, tpos);
	}
}

//	Method that draws a QGraphicsPathItem between two positions on the scene:
void nodeConnect::connect(const QPointF spos, const QPointF tpos) {

	//	Clear current path:
	curve.path.clear();

	//	Define coordinates:
	const double xi = spos.x();
	const double yi = spos.y();
	const double xf = tpos.x();
	const double yf = tpos.y();

	const double xm = (xi + xf) / 2.0;
	const double dx = 0.25 * (xf - xi);
	const double ep = 0.45 * dx;

	//	Construct path;
	curve.path.moveTo(spos);
	curve.path.lineTo(xm - dx - ep, yi);
	curve.path.cubicTo(xm, yi, xm, yf, xm + dx + ep, yf);
	curve.path.lineTo(xf, yf);
	setPath(curve.path);
}

void nodeConnect::setAttr(nodeCtrl* srcn , nodeHandle* srcv, nodeCtrl* tarn, nodeHandle* tarv) {

	pointers.sourceNode = srcn;
	pointers.targetNode = tarn;
	pointers.sourceHandle  = srcv;
	pointers.targetHandle  = tarv;
}

void nodeConnect::refresh() {

	if (pointers.sourceNode != nullptr && pointers.targetNode != nullptr && \
		pointers.sourceHandle  != nullptr && pointers.targetHandle  != nullptr)
	{
		const auto spos  = pointers.sourceHandle->scenePos() + pointers.sourceHandle->rect().center();
		const auto tpos  = pointers.targetHandle->scenePos() + pointers.targetHandle->rect().center();
		const auto color = pointers.sourceHandle->categoryColor();

		setPen(QPen(color, 3.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		connect(spos, tpos);
	}

	if (pointers.sourceNode->isVisible() && pointers.targetNode->isVisible())
		setVisible(true);
	else
		setVisible(false);
}