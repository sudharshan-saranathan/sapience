//
// Created by Sudharshan Saranathan on 25/11/24.
//

#include <cmath>
#include <QThread>
#include <QWidgetAction>

#include "node/node_connect.h"

#include <QRandomGenerator>

#include "node/node_handle.h"
#include "schematic/schema_canvas.h"

#define HEX_RANDOM QString("#%1").arg(QRandomGenerator::global()->generate() & 0xFFFFFF, 6, 16, QChar('0'))

NodeConnect::~NodeConnect() {

#ifdef VERBOSE
	qInfo() << __FILE__ << __func__;
#endif

	if (disconnect())
		qInfo() << "\t- QObject::disconnect() successful";
	else
		qWarning() << "\t- QObject::disconnect() returned false";

//	Reset m_pointers to nullptr. This is not needed, but it's good practice:
	m_pointers.sourceNode   = nullptr;
	m_pointers.targetNode   = nullptr;
	m_pointers.sourceHandle = nullptr;
	m_pointers.targetHandle = nullptr;

//	If the path is added to a scene, remove from scene:
	if (scene())
		scene()->removeItem(this);

	clear();
	deleteLater();
}

NodeConnect::NodeConnect(const QPen& pen, QGraphicsItem* parent) :
/*	Initializer list	*/
//	Base-class constructor:
	QGraphicsPathItem(parent),
//	struct _attr_:
	m_attr{pen, QString()},
//	Initialize helper-m_pointers:
    m_pointers{nullptr, nullptr, nullptr, nullptr},
//	struct _curve_:
	m_curve{QPainterPath()},
//	struct _menu_:
	m_menu{new QMenu, new QLineEdit, new QWidgetAction(m_menu.pointer)}

//	-------------------------
//	Constructor (body) begin:
{
	setZValue(-1);
	setPen(QPen(categoryList[0].getColor(), 3.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	setAcceptHoverEvents(true);

	//	Initialize the variable category selection m_menu:
	m_menu.createCategory->setPlaceholderText("Create Category");
	m_menu.createCategory->setFocusPolicy(Qt::StrongFocus);

	// Create a QWidgetAction to hold the QLineEdit:
	m_menu.createAction->setDefaultWidget(m_menu.createCategory);
	m_menu.createAction->setObjectName(QString("QWidgetAction"));

	//	Add the widget-action to the m_menu as the first entry:
	m_menu.pointer->addAction(m_menu.createAction);

	//	Handle the QLineEdit's returnPressed() signal (i.e. the user has pressed <Enter>):
	QObject::connect(m_menu.createCategory, &QLineEdit::returnPressed, [this]() {
		//	If the entered string is not empty:
		if (const auto categoryName = m_menu.createCategory->text(); !categoryName.isEmpty()) {

			//	Clear the QLineEdit once returnPressed() signal is emitted:
			m_menu.createCategory->clear();

			//	Create a new category with the entered type:
			const uint_t ID = static_cast<uint_t>(categoryList.size());
			categoryList.append(varCategory{categoryName, ID, HEX_RANDOM});

			//	Clear the QLineEdit after emitting the returnPressed() signal:
			const auto action   = m_menu.pointer->addAction(categoryName);
			const auto category = categoryList.last();

			action->setShortcut(0x30 + ID);												//	Set shortcut
			action->setShortcutContext(Qt::WidgetWithChildrenShortcut);					//	Set shortcut context
			action->setShortcutVisibleInContextMenu(true);								//	Set shortcut visible

			//	Do not close the m_menu when new categories are created:
			//	This is achieved with the following instruction:
			m_menu.pointer->setActiveAction(nullptr);

			//	Wait for the user to select a category:
			QObject::connect(action, &QAction::triggered, [this, category]{ setCategory(category); });
		}
	});
}

void NodeConnect::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	Q_UNUSED(event)
	setOpacity(0.6);
	setCursor(Qt::ArrowCursor);
}

void NodeConnect::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	Q_UNUSED(event)
	setOpacity(1.0);
	unsetCursor();
}

void NodeConnect::contextMenuEvent(QGraphicsSceneContextMenuEvent* event) {

	m_menu.pointer->addSeparator();
	for (const auto& category : categoryList) {

		const auto name   = category.getName();
		const auto action = m_menu.pointer->addAction(name);						//	Create a new action with typeName

		action->setShortcut(0x30 + category.getID());							//	Set shortcut
		action->setShortcutContext(Qt::WidgetWithChildrenShortcut);				//	Set shortcut context
		action->setShortcutVisibleInContextMenu(true);							//	Set shortcut visible

		QObject::connect(action, &QAction::triggered, [this, &category]() { setCategory(category); });
	}

	//	Show the m_menu:
	m_menu.pointer->exec(event->screenPos());								//	Show the m_menu

	//	Cleanup the list:
	for (const auto action : m_menu.pointer->actions()) {						//	Remove the actions from the m_menu
		if (action->objectName().isEmpty())
			m_menu.pointer->removeAction(action);
	}
}

void NodeConnect::setCategory(const varCategory& category) {

	qInfo() << category.getColor() << " " << category.getName();
	setPen(QPen(category.getColor(), 3.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	m_pointers.sourceHandle->setCategory(category);
	m_pointers.targetHandle->setCategory(category);

	m_menu.pointer->close();
}

void NodeConnect::clearConnection(const NodeHandle* handle) const {
	Q_UNUSED(handle)

	const auto counter = symbol.split("X")[1].toInt();

//	Remove connection from database, add symbol to the deletedSymbols list (so that it can be reused):
	OptimDB::deletedSymbols.append(counter);
	OptimDB::variableList.removeAll(this);

	delete this;
}

void NodeConnect::connect(const QPointF tpos) {

	if (m_pointers.sourceNode && m_pointers.sourceHandle) {
		const auto spos = m_pointers.sourceHandle->scenePos() + m_pointers.sourceHandle->rect().center();
		connect(spos, tpos);
	}
}

//	Method that draws a QGraphicsPathItem between two positions on the scene:
void NodeConnect::connect(const QPointF spos, const QPointF tpos) {

	//	Clear current path:
	m_curve.path.clear();

	//	Define coordinates:
	const double xi = spos.x();
	const double yi = spos.y();
	const double xf = tpos.x();
	const double yf = tpos.y();

	const double xm = (xi + xf) / 2.0;
	const double dx = 0.25 * (xf - xi);
	const double ep = 0.45 * dx;

	//	Construct path;
	m_curve.path.moveTo(spos);
	m_curve.path.lineTo(xm - dx - ep, yi);
	m_curve.path.cubicTo(xm, yi, xm, yf, xm + dx + ep, yf);
	m_curve.path.lineTo(xf, yf);
	setPath(m_curve.path);
}

void NodeConnect::setAttr(NodeCtrl* srcn , NodeHandle* srcv, NodeCtrl* tarn, NodeHandle* tarv) {

	m_pointers.sourceNode = srcn;
	m_pointers.targetNode = tarn;
	m_pointers.sourceHandle  = srcv;
	m_pointers.targetHandle  = tarv;
}

void NodeConnect::refresh() {

	if (m_pointers.sourceNode != nullptr && m_pointers.targetNode != nullptr && \
		m_pointers.sourceHandle  != nullptr && m_pointers.targetHandle  != nullptr)
	{
		const auto spos  = m_pointers.sourceHandle->scenePos() + m_pointers.sourceHandle->rect().center();
		const auto tpos  = m_pointers.targetHandle->scenePos() + m_pointers.targetHandle->rect().center();
		const auto color = m_pointers.sourceHandle->categoryColor();

		setPen(QPen(color, 3.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		connect(spos, tpos);
	}

	if (m_pointers.sourceNode->isVisible() && m_pointers.targetNode->isVisible())
		setVisible(true);
	else
		setVisible(false);
}