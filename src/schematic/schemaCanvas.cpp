/*  -----------------------------------
 *  Project     : sapience
 *  File        : schemaCanvas.cpp
 *  Date        : 18.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

/*  Include Qt Core Classes */
#include <QMenu>
#include <QRandomGenerator>

/*  Include project headers */
#include "schematic/schemaCanvas.h"
#include "node/nodeConnect.h"
#include "node/nodeGroup.h"
#include "schematic/schemaViewer.h"

#define HEX_RANDOM QString("#%1").arg(QRandomGenerator::global()->generate() & 0xFFFFFF, 6, 16, QChar('0'))

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
		QList<QGraphicsItem *>(),
		QList<QGroup*>()
	},
	//	struct _menu_
	menu
	{
		QPointF(), new QMenu,
		new QAction("New Node"),
		new QAction("Group Selection"),
		new QAction("Move to Folder"),
		new QAction("Delete Schema"),
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
	menu.ptr->addSeparator();
	menu.ptr->addAction(menu.groupItems);
	menu.ptr->addAction(menu.createFolder);
	menu.ptr->addAction(menu.deleteSchema);
	menu.ptr->addSeparator();
	menu.ptr->addAction(menu.quitApp);

	/*	Do not change shortcut context, or it may break the behaviour
	 *	of the QAction	*/
	menu.createNode->setShortcutVisibleInContextMenu(true);					//	Show the shortcut in the menu
	menu.createNode->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));		//	Define the custom shortcut
	menu.createNode->setShortcutContext(Qt::WidgetWithChildrenShortcut);	//	Do not remove or modify

	menu.groupItems->setShortcutVisibleInContextMenu(true);					//	Show the shortcut in the menu
	menu.groupItems->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_G));		//	Define the custom shortcut
	menu.groupItems->setShortcutContext(Qt::WidgetWithChildrenShortcut);	//	Do not remove or modify

	menu.createFolder->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the menu
	menu.createFolder->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_F));    //	Define the custom shortcut
	menu.createFolder->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	menu.deleteSchema->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the menu
	menu.deleteSchema->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_D));    //	Define the custom shortcut
	menu.deleteSchema->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	menu.quitApp->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the menu
	menu.quitApp->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));    //	Define the custom shortcut
	menu.quitApp->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	connect(menu.createNode, &QAction::triggered, [&]()		{ createNode(menu.pos); });
	connect(menu.groupItems, &QAction::triggered, [&]()		{ groupItems(selectedItems()); });
	connect(menu.createFolder, &QAction::triggered, [&]()	{ createFolder(menu.pos); });
	connect(menu.deleteSchema, &QAction::triggered, [&]()	{ deleteSchema(); });
	connect(menu.quitApp, &QAction::triggered, [&]()		{ emit quitProgram(); });

	/*	Create a default nodeConnect and add it to the scene. This path element is used to temporarily
	 *	draw the path as the user drags the mouse across the scene. It is reset and re-used
	 */
	connection.connector = new nodeConnect(QPen(QColor(243, 149, 22), 2.0));
	addItem(connection.connector);

	//	Signal constructor completion:
	emit initialized();
}

void schemaCanvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	//	Resolve event handlers of nested item(s) first, if any:
	QGraphicsScene::mouseMoveEvent(event);

	//	Draw and update connection while the mouse moves:
	if (connection.inProgress && connection.sourceVariablePointer) {
		const auto spos = connection.sourceVariablePointer->scenePos() +
						  connection.sourceVariablePointer->rect().center();
		const auto tpos = event->scenePos();
		connection.connector->connect(spos, tpos);
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
			const auto railType   = nodeRail->data(0).value<StreamType>();
			const auto sourceType = connection.sourceVariablePointer->getVariableType();

			/*	Check if:
			 *	1. The rails in the target node are of the opposite type of the source variable.
			 *	2. The targert node is different from the source node.
			 */
			if (railType != sourceType && nodePointer && nodePointer->getUID() != connection.sourceNodePointer->
			    getUID()) {
				//	Convert the position of the cursor to the rail's local coordinates:
				const auto ypos = nodeRail->mapFromScene(event->scenePos()).y() -
								  nodeRail->mapFromParent(QPointF(0, 0)).y() - 4.0;

				//	Create a new variable on the rail at the cursor's position (in local coordinates):
				nodePointer->createVariable(railType, connection.sourceVariablePointer->name(), QPointF(0.0, ypos));
			}

			if (const auto itemReload = itemAt(event->scenePos(), QTransform());
				itemReload->type() == QGraphicsItem::UserType + 2)
			{
				//	Store the node and variable's pointer:
				const auto variablePointer = qgraphicsitem_cast<nodeVar *>(itemReload);
				const auto nodePointer     = qgraphicsitem_cast<nodeCtrl*>(item->parentItem());

				/*	Attempt connecting to the variable. If the pairing is successful, proceed to draw
				 *	the path and connect the handle's signals to appropriate event-handlers.
				 */
				if (variablePointer && nodePointer && nodePointer->getUID() != connection.sourceNodePointer->getUID()) {
					//	Try pairing the variable:
					if (variablePointer->pair(connection.sourceVariablePointer)) {
						//	If pairing is successful, change handle-colours to orange and create a new connection:
						const auto pen  = QPen(QBrush(QColor("#F39516")), 3.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
						const auto path = new nodeConnect(pen);

						//	Define the coordinates of the endpoints:
						const auto sourceCoordinate =	connection.sourceVariablePointer->scenePos() +
														connection.sourceVariablePointer->rect().center();
						const auto targetCoordinate = variablePointer->scenePos() + variablePointer->rect().center();

						//	Draw the path, and initialize the connection's convenience pointers:
						path->connect(sourceCoordinate, targetCoordinate);
						path->setAttr(connection.sourceNodePointer, connection.sourceVariablePointer, nodePointer,
						              variablePointer);

						//	Add the path to the scene, and store its reference in the database:
						addItem(path);
						amplDatabase::connectionList.append(path);

						connect(connection.sourceNodePointer, &nodeCtrl::nodeShifted, path, &nodeConnect::update);
						connect(connection.sourceVariablePointer, &nodeVar::variableShifted, path, &nodeConnect::update);
						connect(connection.sourceVariablePointer, &nodeVar::variableDeleted, path, &nodeConnect::clearConnection);
						connect(nodePointer, &nodeCtrl::nodeShifted, path, &nodeConnect::update);
						connect(variablePointer, &nodeVar::variableShifted, path, &nodeConnect::update);
						connect(variablePointer, &nodeVar::variableDeleted, path, &nodeConnect::clearConnection);
					}
				}
			}
		}

		/*	Reset the temporary variables for reuse	*/
		connection.inProgress            = false;
		connection.sourceVariablePointer = nullptr;
		connection.connector->setPath(QPainterPath());
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

	//	If the user presses Ctrl + C
	if (event->matches(QKeySequence::Copy))
		list.clipboard = selectedItems();

	//	Handle Ctrl+V
	else if (event->matches(QKeySequence::Paste)) {
		if (!list.clipboard.isEmpty()) {
			for (const auto j: list.clipboard) {
				//	Allocate and copy from node:
				if (const auto nodePointer = qgraphicsitem_cast<nodeCtrl*>(j); nodePointer != nullptr) {
					createNode(*nodePointer);
					//	Keep the pasted node(s) selected, and deselect the original node:
					amplDatabase::nodeList.last()->setSelected(true);
					nodePointer->setSelected(false);
				}
			}
			list.clipboard = selectedItems();
		}
		event->accept();
	} else if (event->matches(QKeySequence::SelectAll)) {
		for (auto j: amplDatabase::nodeList) {
			j->setSelected(true);
		}
	}

	if (event->key() == Qt::Key_Delete) {
		for (const auto deleteList = selectedItems(); const auto item : deleteList)
			delete item;
	}

	//	Call the base-class implementation last:
	QGraphicsScene::keyPressEvent(event);
}

void schemaCanvas::createLink(nodeCtrl *nptr, nodeVar *vptr) {
	/*	This slot is triggered by a variable's handle when the user attempts to create a new connection	*/
	if (!connection.inProgress) {
		//	Store the connection's origin node and variable:
		connection.sourceNodePointer     = qgraphicsitem_cast<nodeCtrl *>(nptr);
		connection.sourceVariablePointer = qgraphicsitem_cast<nodeVar *>(vptr);

		//	Change connection.inProgress to true:
		connection.inProgress = true;
	}
}

void schemaCanvas::deleteNode(nodeCtrl *nodePointer) {

	/*	This SLOT is automatically triggered by SIGNAL(nodeCtrl::nodeDeleted(nodeCtrl*)).
	 *	Here, the specified node is removed from the scene and scheduled for deletion.
	 */

	qInfo() << __FILE__ << __func__;									//	Print file and function name
	removeItem(nodePointer);											//	Remove the node from the scene
	nodePointer->deleteLater();											//	Delete the node using QObject::deleteLater()
}

void schemaCanvas::createNode(const QPointF &pos) {
	//	Create a new node at cursor position pos (in scene coordinates):
	const auto node = new nodeCtrl(pos, "Node");

	//	Store node pointer in database:
	amplDatabase::nodeList.append(node);

	//	Add created node to scene:
	addItem(node);

	//	Connect node signals to slots:
	auto c1 = connect(node, &nodeCtrl::linkVariable, this, &schemaCanvas::createLink);
	auto c2 = connect(node, &nodeCtrl::nodeDeleted , this, &schemaCanvas::deleteNode);
}

void schemaCanvas::createNode(const nodeCtrl &node) {
	//	Allocate and copy from node:
	const auto copy = new nodeCtrl(node);

	//	Store node pointer in database:
	amplDatabase::nodeList.append(copy);

	//	Add copied node to scene:
	addItem(copy);

	//	Connect node signals to slots:
	auto c1 = connect(copy, &nodeCtrl::linkVariable, this, &schemaCanvas::createLink);
	auto c2 = connect(copy, &nodeCtrl::nodeDeleted , this, &schemaCanvas::deleteNode);
}

void schemaCanvas::groupItems(const QList<QItemG*>& itemList) {

	qInfo() << __FILE__ << __func__;					//	Print file and function name
	const auto group = new QGraphicsItemGroup;			//	Create a new QGraphicsItemGroup instance
	const auto color = HEX_RANDOM;

	for (const auto item : itemList) {

		group->addToGroup(item);
		group->setFlag(QGraphicsItem::ItemIsMovable);
		group->setFlag(QGraphicsItem::ItemIsSelectable);

		if (item->type() == QItemG::UserType + 1)
			qgraphicsitem_cast<nodeCtrl*>(item)->setColor(color);
	}

	list.itemsGroup.append(group);
	addItem(group);
}

void schemaCanvas::createFolder(const QPointF &pos) {

	if (const auto items = selectedItems(); !items.empty()) {
		//	Create a folder and add it to the scene:
		const auto folderPointer = new nodeGroup(pos, ":/icons/folder-not-empty.svg");

		//	Add the folder to the scene:
		addItem(folderPointer);

		//	Move all selected items into the folder (i.e. set as children):
		for (const auto item : items)
			folderPointer->hold(item);
	}else
		qInfo() << "Please select items and try again";
}

void schemaCanvas::deleteSchema() const {

	qInfo() << __FILE__ << __func__;									//	Print file and function name
	for (const auto items = selectedItems(); const auto item : items)	//	Loop over items
		delete item;													//	Delete them
}
