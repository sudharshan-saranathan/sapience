//
// Created by Sudharshan Saranathan on 25/11/24.
//

#include <cmath>
#include <QThread>
#include <QWidgetAction>

#include "schematic/schemaCanvas.h"
#include "node/nodeConnect.h"
#include "node/nodeVar.h"

#define HEX_RANDOM QString("#%1").arg(QRandomGenerator::global()->generate() & 0xFFFFFF, 6, 16, QChar('0'))

nodeConnect::~nodeConnect() {

	qInfo() << __FILE__ << __func__;
	if (disconnect())
		qInfo() << "\t- QObject::disconnect() successful";
	else
		qWarning() << "\t- QObject::disconnect() returned false";

	//	Reset pointers to nullptr. This is not needed, but it's good practice:
	attr.sourceNode = nullptr;
	attr.targetNode = nullptr;
	attr.sourceVar  = nullptr;
	attr.targetVar  = nullptr;

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
	attr{pen, nullptr, nullptr, nullptr, nullptr},
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
			const auto name  = categoryName;
			const uint_t ID  = static_cast<uint_t>(categoryList.size());
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
			QObject::connect(action, &QAction::triggered, [this, category]{ categorySelected(category); });
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

		QObject::connect(action, &QAction::triggered, [this, &category]() { categorySelected(category); });
	}

	//	Show the menu:
	menu.pointer->exec(event->screenPos());								//	Show the menu

	//	Cleanup the list:
	for (const auto action : menu.pointer->actions()) {						//	Remove the actions from the menu
		if (action->objectName().isEmpty())
			menu.pointer->removeAction(action);
	}
}

void nodeConnect::categorySelected(varCategory category) {

	qInfo() << category.getColor() << " " << category.getName();
	setPen(QPen(category.getColor(), 3.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	attr.sourceVar->setCategory(category);
	attr.targetVar->setCategory(category);
	menu.pointer->close();
}

void nodeConnect::clearConnection(const nodeVar* var){
	Q_UNUSED(var)

	delete this;

	/*
	qInfo() << __FILE__ << __func__;
	if (disconnect())
		qInfo() << "\t- QObject::disconnect() successful";

	//	Reset pointers to nullptr. This is not needed, but it's good practice:
	attr.sourceNode = nullptr;
	attr.targetNode = nullptr;
	attr.sourceVar  = nullptr;
	attr.targetVar  = nullptr;

	//	If the path is added to a scene, remove from scene:
	if (scene())
		scene()->removeItem(this);

	clear();
	deleteLater();
	*/
}

void nodeConnect::connect(const QPointF tpos) {

	if (attr.sourceNode && attr.sourceVar) {
		const auto spos = attr.sourceVar->scenePos() + attr.sourceVar->rect().center();
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

void nodeConnect::setAttr(nodeCtrl* srcn , nodeVar* srcv, nodeCtrl* tarn, nodeVar* tarv) {

	attr.sourceNode = srcn;
	attr.targetNode = tarn;
	attr.sourceVar  = srcv;
	attr.targetVar  = tarv;
}

void nodeConnect::update() {

	if (attr.sourceNode != nullptr && attr.targetNode != nullptr && \
		attr.sourceVar  != nullptr && attr.targetVar  != nullptr)
	{
		const auto spos = attr.sourceVar->scenePos() + attr.sourceVar->rect().center();
		const auto tpos = attr.targetVar->scenePos() + attr.targetVar->rect().center();
		connect(spos, tpos);
	}

	if (attr.sourceNode->isVisible() && attr.targetNode->isVisible())
		setVisible(true);
	else
		setVisible(false);
}