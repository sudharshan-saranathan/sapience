/*  -----------------------------------
 *  Project     : sapience-debug
 *  File        : nodeCtrl.cpp
 *  Date        : 19.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#include <QPen>
#include <QDrag>
#include <QBrush>
#include <QPainter>
#include <QMimeData>
#include <QTextDocument>
#include <QRandomGenerator>

#include "core/coreQSS.h"
#include "node/nodeCtrl.h"
#include "ampl/amplDatabase.h"
#include "schematic/schemaCanvas.h"

#include <QGraphicsProxyWidget>

#define VERBOSE

#define RGB_RAIL	QColor(109, 50, 109)
#define RGB_SELECT  QColor(243, 149, 22)

#define PEN_RAIL	QPen(QBrush(RGB_RAIL, Qt::DiagCrossPattern), 6.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
#define PEN_BLACK   QPen(Qt::black, 2.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
#define PEN_SELECT	QPen(QBrush(RGB_SELECT), 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)

//	Class destructor:
nodeCtrl::~nodeCtrl() {

	qDebug() << __FILE__ << __func__;									//	Print file and function name
	while (!stack.list.inp.isEmpty()) {									//	Loop over input variables

		const auto variablePointer = stack.list.inp.takeLast();			//	Pop the last element (more efficient than popping the first)
#ifdef VERBOSE
		qInfo() << "\t- Variable "										//	Print variable information if logging is
				<< variablePointer->name()								//	verbose
				<< " deleted";
#endif
		variablePointer->free();										//	Unpair the variable and its conjugate
		variablePointer->variableDeleted(variablePointer);				//	Emit the variable's delete signal
	}

	while (!stack.list.out.isEmpty()) {									//	Loop over output variables

		const auto variablePointer = stack.list.out.takeLast();			//	Pop the last element
#ifdef VERBOSE
		qInfo() << "\t- Variable "										//	Print variable information if logging is
				<< variablePointer->name()								//	verbose
				<< " deleted";
#endif
		variablePointer->free();										//	Unpair the variable and its conjugate
		variablePointer->variableDeleted(variablePointer);				//	Emit the variables's delete signal
	}

	if (scene())														//	Remove the node from scene, if applicable
		scene()->removeItem(this);

	if (amplDatabase::nodeList.removeOne(this))
		qInfo() << "\t- Node removed from AMPL Database";				//	Print status information

	if (disconnect())
		qInfo() << "\t- QObject::disconnect() successful";
}

nodeCtrl::nodeCtrl(const QPointF &nodePosition, const QString &nodeName, QGraphicsItem *parent) :
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
		false
	},
	//	struct _stack_:
	stack{
		{new QGraphicsRectItem(this), QRect(2, 2, HDR_WS, HDR_HS)},
		{new QItemL(this), new QItemL(this), new QItemE(stack.rails.left), new QItemE(stack.rails.right)},
		{new QGraphicsTextItem(stack.header.ptr)},
		{
			new nodeSVG(":/icons/circle-down.svg", QSize(ICONSIZE, ICONSIZE), true, stack.header.ptr),
			new nodeSVG(":/icons/circle-up.svg", QSize(ICONSIZE, ICONSIZE), true, stack.header.ptr),
			new nodeSVG(":/icons/lambda.svg", QSize(ICONSIZE, ICONSIZE), true, stack.header.ptr),
			new nodeSVG(":/icons/node.close.svg", QSize(ICONSIZE, ICONSIZE), true, stack.header.ptr),
			new nodeSVG(":/icons/node-unlock.svg", QSize(ICONSIZE, ICONSIZE), true, stack.header.ptr)
		},
		{QList<nodeVar *>(), QList<nodeVar *>(), QList<nodeVar *>()},
		{QString("Node Created"), new QItemR(this), new status(stack.statusBar.board)}
	},
	//	struct _menu_:
	menu{
		new QMenu,
		new QAction("Save as Template"),
		new QAction("Delete Node"),
		new QAction("New Input"),
		new QAction("New Output"),
		new QAction("New Parameter"),
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

	//	Initialize header:
	stack.header.ptr->setRect(stack.header.rect);
	stack.header.ptr->setBrush(QBrush(QSSRGB::moonstone, Qt::SolidPattern));
	stack.header.ptr->setPen(QPen(QSSRGB::moonstone, 1.0));

	//	Initialize the node-title and its characteristics:
	stack.title.ptr->setPos(attr.rect.width() / 2.0 - NODE_TEXT_WIDTH / 2.0, 6);
	stack.title.ptr->setTextInteractionFlags(Qt::TextEditorInteraction);
	stack.title.ptr->setPlainText(attr.name);

	//	Fix text alignment, and connect text-change signal to lambda function:
	stack.title.ptr->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter));
	stack.title.ptr->document()->setTextWidth(NODE_TEXT_WIDTH);
	auto t1 = connect(stack.title.ptr->document(), &QTextDocument::contentsChanged, [&]() {
		attr.name = stack.title.ptr->document()->toPlainText();
	});

	//	Setup SVG buttons:
	stack.svg.input->moveBy(18, 18);
	stack.svg.output->moveBy(43, 18);
	stack.svg.params->moveBy(68, 18);
	stack.svg.toggle->setToggleFile(":/icons/node-lock.svg");
	stack.svg.toggle->moveBy(257, 18);
	stack.svg.close->moveBy(282, 18);

	stack.svg.input->setToolTip("Define Input");
	stack.svg.output->setToolTip("Define Output");
	stack.svg.params->setToolTip("Define Constant");
	stack.svg.close->setToolTip("Delete Node");

	auto c1 = connect(stack.svg.input, &nodeSVG::leftClicked, [&]() { createVariable(Input); });
	auto c2 = connect(stack.svg.output, &nodeSVG::leftClicked, [&]() { createVariable(Output); });
	auto c3 = connect(stack.svg.params, &nodeSVG::leftClicked, [&]() { createVariable(Parameter); });
	auto c4 = connect(stack.svg.toggle, &nodeSVG::leftClicked, [&]() { attr.locked = !attr.locked; onLockToggled(attr.locked); });
	auto c5 = connect(stack.svg.close, &nodeSVG::leftClicked, [&]() { emit nodeDeleted(this); });

	/*	Draw rails (inpRail and outRail) on either side of the node. Input and output variables
	 *	can be vertically moved along these rails.
	 */
	stack.rails.right->setPen(PEN_RAIL);
	stack.rails.right->setLine(0, 0, 0, 120);
	stack.rails.right->setPos(292, 45);
	stack.rails.right->setData(0, QVariant::fromValue<StreamType>(Output));

	stack.rails.left->setPen(PEN_RAIL);
	stack.rails.left->setLine(0, 0, 0, 120);
	stack.rails.left->setPos(8, 45);
	stack.rails.left->setData(0, QVariant::fromValue<StreamType>(Input));

	stack.rails.hintL->setRect(0, 0, 8, 8);
	stack.rails.hintL->setBrush(QBrush(QColor("#3BCE5B"), Qt::SolidPattern));
	stack.rails.hintL->setOpacity(0.3);
	stack.rails.hintL->hide();

	stack.rails.hintR->setRect(0, 0, 8, 8);
	stack.rails.hintR->setBrush(QBrush(QColor("#3BCE5B"), Qt::SolidPattern));
	stack.rails.hintR->setOpacity(0.3);
	stack.rails.hintR->hide();

	//	Initialize status bar:
	stack.statusBar.board->setBrush(QBrush("#22333B", Qt::SolidPattern));
	stack.statusBar.board->setRect(0, 0, NODE_WS - 1.0, 24.0);
	stack.statusBar.board->setPos(0.5, QGraphicsRectItem::boundingRect().bottom() - 25.0);
	stack.statusBar.pointer->print(stack.statusBar.message, Info);
	stack.statusBar.pointer->setPos(1, 1);

	menu.pointer->addAction(menu.save);
	menu.pointer->addSeparator();
	menu.pointer->addAction(menu.input);
	menu.pointer->addAction(menu.output);
	menu.pointer->addAction(menu.constant);
	menu.pointer->addSeparator();
	menu.pointer->addAction(menu.close);

	menu.save->setShortcutVisibleInContextMenu(true);								//	Show the shortcut in the menu
	menu.save->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));			//	Define the custom shortcut
	menu.save->setShortcutContext(Qt::WidgetWithChildrenShortcut);					//	Do not remove or modify

	menu.input->setShortcutVisibleInContextMenu(true);								//	Show the shortcut in the menu
	menu.input->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_I));		//	Define the custom shortcut
	menu.input->setShortcutContext(Qt::WidgetWithChildrenShortcut);					//	Do not remove or modify

	menu.output->setShortcutVisibleInContextMenu(true);								//	Show the shortcut in the menu
	menu.output->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_O));		//	Define the custom shortcut
	menu.output->setShortcutContext(Qt::WidgetWithChildrenShortcut);				//	Do not remove or modify

	menu.constant->setShortcutVisibleInContextMenu(true);							//	Show the shortcut in the menu
	menu.constant->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_C));		//	Define the custom shortcut
	menu.constant->setShortcutContext(Qt::WidgetWithChildrenShortcut);				//	Do not remove or modify

	menu.close->setShortcutVisibleInContextMenu(true);								//	Show the shortcut in the menu
	menu.close->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Q));		//	Define the custom shortcut
	menu.close->setShortcutContext(Qt::WidgetWithChildrenShortcut);					//	Do not remove or modify

	auto m1 = connect(menu.save, &QAction::triggered, [&]() { actionSave(); });
	auto m2 = connect(menu.close, &QAction::triggered, [&]() { stack.svg.close->leftClicked(); });
	auto m4 = connect(menu.input, &QAction::triggered, [&]() { stack.svg.input->leftClicked(); });
	auto m5 = connect(menu.output, &QAction::triggered, [&]() { stack.svg.output->leftClicked(); });

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

nodeCtrl::nodeCtrl(const nodeCtrl &source) :
	//	Call the shared constructor-with-args
	nodeCtrl(source.scenePos() + QPointF(25, 25), source.name(), source.parentItem()) {
	//	Copy the source-node's variables and equations:
	for (auto j: source.stack.list.inp)
		createVariable(Input, j->name());

	for (auto j: source.stack.list.out)
		createVariable(Output, j->name());

	for (auto j: source.stack.list.par)
		createVariable(Parameter, j->name());
}

QVariant nodeCtrl::itemChange(const GraphicsItemChange change, const QVariant &value) {
	/*	Switch-case block to handle item changes	*/
	switch (change) {
		//	If the node was moved, emit signal:
		case ItemScenePositionHasChanged: {
			emit nodeShifted();
			break;
		}
		//	If the node is shown or hidden (e.g. when moved into/out of a folder):
		case ItemVisibleChange: {
			emit nodeShifted();
		}
		//	Default block:
		default:
			break;
	}
	return(value);
}

void nodeCtrl::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

	//	Change border color when node is selected:
	setPen(isSelected() ? PEN_SELECT : PEN_BLACK);

	//	Reset node state to remove dashed lines:
	auto modOption(*option);
	modOption.state = QStyle::State_None;

	//	Call base-class event-handler:
	QGraphicsRectItem::paint(painter, &modOption, widget);
}

void nodeCtrl::hoverMoveEvent(QGraphicsSceneHoverEvent* event) {

	const auto leftRail  = stack.rails.left ->mapFromParent(event->pos());
	const auto rightRail = stack.rails.right->mapFromParent(event->pos());

	if (stack.rails.left->contains(leftRail)) {
		const auto x = stack.rails.left->pos().x() - 12.0;
		const auto y = event->pos().y() - 49.0;
		stack.rails.hintL->setPos(x, y);
		stack.rails.hintL->show();
	}
	else
		stack.rails.hintL->hide();

	if (stack.rails.right->contains(rightRail)) {
		const auto x = stack.rails.right->pos().x() - 296.0;
		const auto y = event->pos().y() - 49.0;
		stack.rails.hintR->setPos(x, y);
		stack.rails.hintR->show();
	}
	else
		stack.rails.hintR->hide();

	//	Propagate event downstream:
	QGraphicsRectItem::hoverMoveEvent(event);
	event->accept();
}


void nodeCtrl::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {

	//	Within bounding rectangle, switch to Qt::ArrowCursor:
	setCursor(Qt::ArrowCursor);

	//	Propagate event downstream:
	QGraphicsRectItem::hoverEnterEvent(event);
	event->accept();
}

void nodeCtrl::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {

	//	Hide handle hints:
	stack.rails.hintL->hide();
	stack.rails.hintR->hide();

	//	Propagate event downstream:
	unsetCursor();
	QGraphicsRectItem::hoverLeaveEvent(event);
}

void nodeCtrl::mousePressEvent(QGraphicsSceneMouseEvent *event) {

	//	If the mouse click is on the rails, create a new variable:
	const auto posLRail = stack.rails.left ->mapFromParent(event->pos());
	const auto posRRail = stack.rails.right->mapFromParent(event->pos());
	const auto position = QPointF(0.0, event->pos().y() - 4.0);

	if (stack.rails.left ->contains(posLRail)) {
		setFlag(ItemIsMovable, false);
		createVariable(Input , QString(), position);
		stack.list.inp.last()->variableClicked(stack.list.inp.last());
	}
	else if (stack.rails.right->contains(posRRail)) {
		setFlag(ItemIsMovable, false);
		createVariable(Output, QString(), position);
		stack.list.out.last()->variableClicked(stack.list.out.last());
	}else
		setFlag(ItemIsMovable, true);

	//	Call base-class implementation:
	QGraphicsRectItem::mousePressEvent(event);
}

void nodeCtrl::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

	//	Resolve event-handlers of nested objects first, if any:
	QGraphicsRectItem::mouseReleaseEvent(event);
}

void nodeCtrl::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {

	//	Resolve event handlers of nested objects first, if any:
	QGraphicsRectItem::contextMenuEvent(event);

	//	Show context menu:
	menu.pointer->exec(event->screenPos());
	event->accept();
}

void nodeCtrl::createVariable(const StreamType& variableType, const QString& symbol, const QPointF pos) {

	/*	This function creates a new variable of the desired type (VariableType), stores it
	 *	in the appropriate list, and positions it within the node according to its type
	 *	(e.g. input and output variables are on the left and right, respectively)	*/

	qInfo() << __FILE__ << __func__;

	auto variableSymbol   = QString();
	auto variablePosition = 0.0;
	nodeVar* variablePtr  = nullptr;

	switch (variableType) {
		//	Create an input variable and add to node:
		case Input: {
			/*	Re-use symbols of deleted variables	*/
			if (amplDatabase::deletedSymbols.isEmpty())
				variableSymbol = QString("X") + QString::number(amplDatabase::variableList.size());
			else {
				amplDatabase::deletedSymbols.sort();
				variableSymbol = amplDatabase::deletedSymbols.first();
				amplDatabase::deletedSymbols.removeAll(variableSymbol);
			}
			//	Create variable with appropriate attribute(s):
			variablePtr		 = new nodeVar(symbol, variableSymbol, variableType, this);
			variablePosition = stack.rails.left->pos().x() - 4.0;

			//	Store the variable in the input-list, and the AMPL list:
			stack.list.inp.append(variablePtr);
			amplDatabase::variableList.append(variablePtr);

			/*	Emit createLink() signal when a variable within the node is clicked. This signal
			 *	is captured and handled by schemaCanvas::onCreateLink()	*/
			auto c1 = connect(variablePtr, &nodeVar::variableClicked, [&](nodeVar* var){ emit linkVariable(this, var); });
			auto c2 = connect(variablePtr, &nodeVar::variableDeleted, [&](nodeVar* var){ deleteVariable(var); });

			/*	Adjust position of the created variable. An input variable is positioned near
			 *	the left edge of the node, stacked sequentially below other input variables	*/
			variablePtr->setPos(pos == QPointF() ? QPointF(variablePosition, 12 + stack.list.inp.size() * 40) : QPointF(variablePosition, pos.y()));

			//	Display a status message:
			stack.statusBar.pointer->print(QString(	"Input Variable " + amplDatabase::variableList.last()->name() +
													" (" + amplDatabase::variableList.last()->getUID() +
													") added to Node"));
			break;

		}

		//	Create an output variable and add to node:
		case Output: {
			/*	Re-use the symbols of deleted variables*/
			if (amplDatabase::deletedSymbols.isEmpty())
				variableSymbol = QString("X") + QString::number(amplDatabase::variableList.size());
			else {
				amplDatabase::deletedSymbols.sort();
				variableSymbol = amplDatabase::deletedSymbols.first();
				amplDatabase::deletedSymbols.removeAll(variableSymbol);
			}

			//	Create variable with appropriate attribute(s):
			variablePtr		 = new nodeVar(symbol, variableSymbol, variableType, this);
			variablePosition = stack.rails.right->pos().x() - 4.0;

			//	Store the variable in the input-list, and the AMPL list:
			stack.list.out.push_back(variablePtr);
			amplDatabase::variableList.push_back(variablePtr);

			/*	Emit createLink() signal when a variable within the node is clicked. This
			 *	signal is captured and handled by schemaCanvas::onCreateLink()	*/
			auto c1 = connect(variablePtr, &nodeVar::variableClicked, [&](nodeVar* var){ emit linkVariable(this, var); });
			auto c2 = connect(variablePtr, &nodeVar::variableDeleted, [&](nodeVar* var){ deleteVariable(var); });

			/*	Adjust position of the created variable. An input variable is positioned near
			 *	the left edge of the node, stacked sequentially below other input variables	*/
			variablePtr->setPos(pos == QPointF() ? QPointF(variablePosition, 12 + stack.list.out.size() * 40) : QPointF(variablePosition, pos.y()));

			//	Display a status message:
			stack.statusBar.pointer->print(QString(	"Output Variable " + amplDatabase::variableList.last()->name() +
													" (" + amplDatabase::variableList.last()->getUID() +
													") added to Node"));
			break;
		}

		//	Create a parameter and add to node:
		case Parameter: {
			//	Create parameter with appropriate attribute(s) and position:
			variableSymbol	 = QString("C") + QString::number(amplDatabase::variableList.size());
			variablePtr		 = new nodeVar(symbol, variableSymbol, variableType, this);
			variablePosition = 280;

			//	Store the variable in the input-list, and the AMPL list:
			stack.list.par.push_back(variablePtr);
			break;
		}

		default:
			break;
	}

	/*	First shift bottom boundary downwards, followed by the variable rails and the status
	 *	bar. The positions have been hardcoded, but a better solution will be found in the
	 *	future	*/
	if (const auto maxSize = qMax(stack.list.inp.size(), stack.list.out.size()); maxSize >= 4) {

		//	Set bottom boundary according to the number of variables in the node:
		setRect(QRect(0, 0, attr.rect.width(), attr.rect.height() + (maxSize - 3) * 40.0));

		//	Update rail-length:
		stack.rails.right->setLine(0, 0, 0, boundingRect().bottom() - 76.0);
		stack.rails.left ->setLine(0, 0, 0, boundingRect().bottom() - 76.0);

		//	Update status bar position:
		stack.statusBar.board->setPos(0.5, QGraphicsRectItem::boundingRect().bottom() - 25.0);
	}

	emit variableCreated();
}

//	This SLOT is triggered by SIGNAL(nodeVar::variableDeleted(nodeVar*)):
void nodeCtrl::deleteVariable(nodeVar* variable) {

	qInfo() << __FILE__ << __func__;								//	Print file and function name

	if (variable->getVariableType() == Input)						//	Remove the variable from the node's list
		stack.list.inp.removeAll(variable);
	else if (variable->getVariableType() == Output)
		stack.list.out.removeAll(variable);
	else if (variable->getVariableType() == Parameter)
		stack.list.par.removeAll(variable);

	amplDatabase::deletedSymbols.append(variable->symbolName());
	amplDatabase::variableList.removeAll(variable);					//	Remove variable from the amplDatabase
	variable->deleteLater();										//	Delete variable using QObject::deleteLater()

	emit variableDeleted();
}

void nodeCtrl::onLockToggled(const bool lock) {

	stack.svg.input ->setEnabled(!lock);
	stack.svg.output->setEnabled(!lock);
	stack.svg.params->setEnabled(!lock);
	stack.svg.close ->setEnabled(!lock);

	stack.rails.left->setEnabled(!lock);
	stack.rails.right->setEnabled(!lock);

	setAcceptHoverEvents(!lock);
	setFlag(ItemIsMovable, !lock);
	setFlag(ItemIsSelectable, !lock);
	setAcceptedMouseButtons(lock ? Qt::NoButton : Qt::AllButtons);
}