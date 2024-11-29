/*  -----------------------------------
 *  Project     : sapience
 *  File        : schemaCanvas.cpp
 *  Date        : 18.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

/*  Include Qt Core Classes */
#include <QMenu>
#include <QGraphicsView>

/*  Include project headers */
#include "schematic/schemaCanvas.h"
#include "path/pathElement.h"

schemaCanvas::schemaCanvas(const QRect &areaRect, QObject *parent) :

	/*  Initializer list  */
	//  Base-class constructor:
	QGraphicsScene(parent),
	//	struct _attr_
	attr{
		areaRect,
		5
	},
	//	struct _list_
	list{
		QList<nodeCtrl *>(),
		QList<QString>(),
		QList<QGraphicsItem *>()
	},
	//	struct _menu_
	menu
	{
		QPointF(), new QMenu,
		new QAction("New Node"),
		new QAction("Delete All"),
		new QAction("Quit")
	}

//	-------------------------
//	Constructor (body) begin:
{
	//	Set background texture:
	setBackgroundBrush(QBrush(Qt::black, Qt::Dense6Pattern));
	setSceneRect(attr.areaRect);

	//	Customize menu and actions:
	//	---------------------------

	menu.ptr->addAction(menu.createNode);
	menu.ptr->addAction(menu.clearScene);
	menu.ptr->addSeparator();
	menu.ptr->addAction(menu.quitApp);

	/*	Do not change shortcut context, or it may break the behaviour
	 *	of the QAction	*/
	menu.createNode->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the menu
	menu.createNode->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));    //	Define the custom shortcut
	menu.createNode->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	menu.clearScene->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the menu
	menu.clearScene->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_D));    //	Define the custom shortcut
	menu.clearScene->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	menu.quitApp->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the menu
	menu.quitApp->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));    //	Define the custom shortcut
	menu.quitApp->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	auto c1 = connect(menu.createNode, &QAction::triggered, [&]() { createNode(menu.pos); });
	auto c3 = connect(menu.quitApp, &QAction::triggered, [&]() { emit quitProgram(); });

	/*	Create a default pathElement and add it to the scene. This path element is used to temporarily
	 *	draw the path as the user drags the mouse across the scene. It is reset and re-used
	 */
	connection.pathElementPointer = new pathElement(QPen(QColor(243, 149, 22), 2.0));
	addItem(connection.pathElementPointer);

	//	Signal constructor completion:
	emit initialized();
}

void schemaCanvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	//	Resolve event handlers of nested item(s) first, if any:
	QGraphicsScene::mouseMoveEvent(event);

	//	Draw and update connection while the mouse moves:
	if (connection.inProgress) {
		const auto spos = connection.sourceVariablePointer->scenePos() + connection.sourceVariablePointer->rect().
		                  center();
		const auto tpos = event->scenePos();
		connection.pathElementPointer->connect(spos, tpos);
	}
}

void schemaCanvas::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	//	Resolve the event handlers of nested items first:
	QGraphicsScene::mousePressEvent(event);
}

void schemaCanvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
	/*	Custom implementation of QGraphicsItem::mouseReleaseEvent() for derived class schemaCanvas.
	 *	If the user is attempting to connect two variables in two different nodes, this handler
	 *	executes the required tasks. For e.g., it connects each handle's signals to appropriate
	 *	slots.
	 */

	/*	The first if-condition checks a) the item below the cursor (if any) at mouse button
	 *	release, and b) if the user is attempting to draw a connection.
	 */
	if (const auto item = itemAt(event->scenePos(), QTransform()); item && connection.inProgress) {
		/*	The first nested-if condition checks if the cursor is positioned over the rails of
		 *	a node at mouse-button release. If yes, the node is identified and a new variable
		 *	is created.
		 */
		if (item->type() == QGraphicsLineItem::Type) {
			//	Cast the item pointer to a QGraphicsLineItem, and the nodeRail
			const auto nodeRail    = qgraphicsitem_cast<QGraphicsLineItem *>(item);
			const auto nodePointer = qgraphicsitem_cast<nodeCtrl *>(nodeRail->parentItem());

			//	Retrieve the VariableType of the source and target variables:
			const auto railType   = nodeRail->data(0).value<VariableType>();
			const auto sourceType = connection.sourceVariablePointer->getVariableType();

			/*	Check if:
			 *	1. The rails in the target node are of the opposite type of the source variable.
			 *	2. The targert node is different from the source node.
			 */
			if (railType != sourceType && nodePointer && nodePointer->getUID() != connection.sourceNodePointer->
			    getUID()) {
				//	Convert the position of the cursor to the rail's local coordinates:
				const auto ypos = nodeRail->mapFromScene(event->scenePos()).y() - nodeRail->mapFromParent(QPointF(0, 0))
				                  .y() - 4.0;

				//	Create a new variable on the rail at the cursor's position (in local coordinates):
				nodePointer->createVariable(railType, connection.sourceVariablePointer->name(), QPointF(0.0, ypos));
			}
		}

		/*	The previous if-block creates a new variable on the node's rail if none existed. The following
		 *	block establishes a connection to the created (or another variable) on the rail.
		 */
		if (const auto itemReload = itemAt(event->scenePos(), QTransform());
			itemReload->type() == QGraphicsItem::UserType + 2) {
			//	Store the pointer to the node and the node's handle:
			const auto variablePointer = qgraphicsitem_cast<nodeVar *>(itemReload);
			const auto nodePointer     = qgraphicsitem_cast<nodeCtrl *>(item->parentItem());

			/*	If a variable already exists at the release position, attempt connecting to the variable.
			 *	If the pairing is successful, proceed to draw the path and connect the handle's signals to
			 *	appropriate event-handlers.
			 */

			if (variablePointer && nodePointer && nodePointer->getUID() != connection.sourceNodePointer->getUID()) {
				//	Try pairing the variable:
				if (variablePointer->pair(connection.sourceVariablePointer)) {
					//	If pairing is successful, change handle-colours to orange and create a new connection:
					const auto pen  = QPen(QBrush(QColor("#F39516")), 3.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
					const auto path = new pathElement(pen);

					//	Define the coordinates of the endpoints:
					const auto sourceCoordinate =
							connection.sourceVariablePointer->scenePos() + connection.sourceVariablePointer->rect().
							center();
					const auto targetCoordinate = variablePointer->scenePos() + variablePointer->rect().center();

					//	Draw the path, and initialize the connection's convenience pointers:
					path->connect(sourceCoordinate, targetCoordinate);
					path->setAttr(connection.sourceNodePointer, connection.sourceVariablePointer, nodePointer,
					              variablePointer);

					//	Add the path to the scene, and store it's reference in the database:
					addItem(path);
					amplSolver::connectionList.append(path);

					auto c2 = connect(connection.sourceNodePointer, &nodeCtrl::nodeShifted, path, &pathElement::update);
					auto c4 = connect(connection.sourceVariablePointer, &nodeVar::variableShifted, path,
					                  &pathElement::update);
					auto c6 = connect(connection.sourceVariablePointer, &nodeVar::variableDeleted, path,
					                  &pathElement::clearConnection);
					auto c3 = connect(nodePointer, &nodeCtrl::nodeShifted, path, &pathElement::update);
					auto c5 = connect(variablePointer, &nodeVar::variableShifted, path, &pathElement::update);
					auto c7 = connect(variablePointer, &nodeVar::variableDeleted, path, &pathElement::clearConnection);
				}
			}
		}

		/*	Reset the temporary variables for reuse	*/
		connection.inProgress            = false;
		connection.sourceVariablePointer = nullptr;
		connection.pathElementPointer->setPath(QPainterPath());
	}

	//	Resolve event handlers of nested item(s) first, if any:
	QGraphicsScene::mouseReleaseEvent(event);
}

void schemaCanvas::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
	//	Resolve event handlers of nested item(s) first:
	QGraphicsScene::contextMenuEvent(event);

	if (!event->isAccepted()) {
		menu.pos = event->scenePos();
		menu.ptr->exec(event->screenPos());
		event->setAccepted(true);
	}
}

void schemaCanvas::keyPressEvent(QKeyEvent *event) {
	if (event->matches(QKeySequence::Copy))
		list.clipboard = selectedItems();

	else if (event->matches(QKeySequence::Paste)) {
		if (!list.clipboard.isEmpty()) {
			for (const auto j: list.clipboard) {
				//	Allocate and copy from node:
				const auto nodePointer = qgraphicsitem_cast<nodeCtrl *>(j);
				createNode(*nodePointer);

				//	Keep the pasted node(s) selected, and deselect the original node:
				amplSolver::nodeList.last()->setSelected(true);
				nodePointer->setSelected(false);
			}
			list.clipboard = selectedItems();
		}
		event->accept();
	} else if (event->matches(QKeySequence::SelectAll)) {
		for (auto j: amplSolver::nodeList) {
			j->setSelected(true);
		}
	}

	if (event->key() == Qt::Key_Delete) {
		const auto deleteList = selectedItems();
		for (int i = 0; i < deleteList.size(); i++) {
			if (const auto pointer = qgraphicsitem_cast<nodeCtrl*>(deleteList.at(i))) {
				pointer->onCloseClicked();
			}
		}
	}
	//	Call the base-class implementation last:
	QGraphicsScene::keyPressEvent(event);
}

void schemaCanvas::keyReleaseEvent(QKeyEvent *event) {
	//	Call base-class implementation:
	QGraphicsScene::keyReleaseEvent(event);
}

void schemaCanvas::createNode(const QPointF &pos) {
	//	Create a new node at cursor position pos (in scene coordinates):
	const auto node = new nodeCtrl(pos, "Node");

	//	Store node pointer in database:
	amplSolver::nodeList.append(node);

	//	Add created node to scene:
	addItem(node);

	//	Connect node signals to slots:
	auto c1 = connect(node, &nodeCtrl::linkVariable, this, &schemaCanvas::onCreateLink);
	auto c2 = connect(node, &nodeCtrl::nodeDeleted, this, &schemaCanvas::onDeleteNode);
}

void schemaCanvas::createNode(const nodeCtrl &node) {
	//	Allocate and copy from node:
	const auto copy = new nodeCtrl(node);

	//	Store node pointer in database:
	amplSolver::nodeList.append(copy);

	//	Add copied node to scene:
	addItem(copy);

	//	Connect node signals to slots:
	auto c1 = connect(copy, &nodeCtrl::linkVariable, this, &schemaCanvas::onCreateLink);
	auto c2 = connect(copy, &nodeCtrl::nodeDeleted, this, &schemaCanvas::onDeleteNode);
}

void schemaCanvas::onCreateLink(nodeCtrl *nptr, nodeVar *vptr) {
	/*	This slot is triggered by a variable's handle when the user attempts to create a new connection	*/
	if (!connection.inProgress) {
		//	Store the connection's origin node and variable:
		connection.sourceNodePointer     = qgraphicsitem_cast<nodeCtrl *>(nptr);
		connection.sourceVariablePointer = qgraphicsitem_cast<nodeVar *>(vptr);

		//	Change connection.inProgress to true:
		connection.inProgress = true;
	}
}

void schemaCanvas::onDeleteNode(nodeCtrl *nptr) {
	/*	This function is automatically triggered by the signal
	 *	nodeCtrl::nodeDeleted(nodeCtrl*). Here, the pointer is
	 *	removed from the database, cleared from the scene, and
	 *	scheduled for deletion	*/

	qInfo() << "schemaCanvas::onDeleteNode(): Removing node from scene";
	amplSolver::nodeList.removeAll(nptr);

	removeItem(nptr);
	nptr->deleteLater();
}