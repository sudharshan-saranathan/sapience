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

schemaCanvas::schemaCanvas(const QRect& areaRect, QObject* parent) :
/*  Initializer list  */
//  Base-class constructor:
	QGraphicsScene(parent),
//	Default Attribute(s)
	attr{areaRect, 5},
//	Container for various useful lists
	list{QList<nodeCtrl*>(), QList<QString>(), QList<QGraphicsItem*>(), QList<QGroup*>()},
//	Context menu and actions
	menu{
		QPointF(),
		new QMenu,
		new QAction("New Node"),
		new QAction("New Source"),
		new QAction("New Sink"),
		new QAction("Create Group "),
		new QAction("Create Folder"),
		new QAction("Import Schematic"),
		new QAction("Export Schematic"),
		new QAction("Delete All"),
		new QAction("Quit")
	}

//	-------------------------
//	Constructor (body) begin:
{
	//	Set background texture:
	setObjectName("schemaCanvas");
	setBackgroundBrush(QBrush(Qt::black, Qt::Dense6Pattern));
	setSceneRect(attr.areaRect);

	//	Add actions to context-menu:
	menu.pointer->addAction(menu.createNode);
	menu.pointer->addAction(menu.createSource);
	menu.pointer->addAction(menu.createSink);
	menu.pointer->addSeparator();
	menu.pointer->addAction(menu.groupItems);
	menu.pointer->addAction(menu.createFolder);
	menu.pointer->addSeparator();
	menu.pointer->addAction(menu.importSchema);
	menu.pointer->addAction(menu.exportSchema);
	menu.pointer->addSeparator();
	menu.pointer->addAction(menu.deleteSchema);
	menu.pointer->addAction(menu.quitApp);

	//  Do not change shortcut context:
	menu.createNode->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the menu
	menu.createNode->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));    //	Define the custom shortcut
	menu.createNode->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	//  Do not change shortcut context:
	menu.createSource->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the menu
	menu.createSource->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Less)); //	Define the custom shortcut
	menu.createSource->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	//  Do not change shortcut context:
	menu.createSink->setShortcutVisibleInContextMenu(true);                 //	Show the shortcut in the menu
	menu.createSink->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Greater)); //	Define the custom shortcut
	menu.createSink->setShortcutContext(Qt::WidgetWithChildrenShortcut);    //	Do not remove or modify

	menu.groupItems->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the menu
	menu.groupItems->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_G));    //	Define the custom shortcut
	menu.groupItems->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	menu.createFolder->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the menu
	menu.createFolder->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_F));    //	Define the custom shortcut
	menu.createFolder->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	menu.importSchema->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the menu
	menu.importSchema->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_F));    //	Define the custom shortcut
	menu.importSchema->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	menu.exportSchema->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the menu
	menu.exportSchema->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_F));    //	Define the custom shortcut
	menu.exportSchema->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	menu.deleteSchema->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the menu
	menu.deleteSchema->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_D));    //	Define the custom shortcut
	menu.deleteSchema->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	menu.quitApp->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the menu
	menu.quitApp->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));    //	Define the custom shortcut
	menu.quitApp->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	connect(menu.createNode, &QAction::triggered, [&]() { createNode(menu.position); });
	connect(menu.groupItems, &QAction::triggered, [&]() { createGroup(selectedItems()); });
	connect(menu.createFolder, &QAction::triggered, [&]() { createFolder(menu.position); });
	connect(menu.deleteSchema, &QAction::triggered, [&]() { deleteSchema(); });
	connect(menu.quitApp, &QAction::triggered, [&]() { emit quitProgram(); });

	/*	Create a default nodeConnect and add it to the scene. This path element is used to temporarily
	 *	draw the path as the user drags the mouse across the scene. It is reset and re-used
	 */
	connection.connector = new nodeConnect(QPen(QColor(243, 149, 22), 2.0));
	addItem(connection.connector);

	//	Signal constructor completion:
	emit initialized();
}

void
schemaCanvas::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {

//	Resolve event handlers of nested item(s) first, if any:
	QGraphicsScene::mouseMoveEvent(event);

//	Draw and update connection while the mouse moves:
	if (connection.handleClicked && connection.originHandle) {
		const auto spos = connection.originHandle->scenePos() + connection.originHandle->rect().center();
		const auto tpos = connection.proximityPointer
							  ? connection.proximityPointer->scenePos()
							  : event->scenePos();

		connection.connector->connect(spos, tpos);
	}
}

void
schemaCanvas::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	//	Resolve the event handlers of nested items first:
	QGraphicsScene::mousePressEvent(event);
}

void
schemaCanvas::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {

/*	Custom implementation of QGraphicsItem::mouseReleaseEvent() for derived class schemaCanvas.
 *	If the user is attempting to connect two variables in two different nodes, this handler
 *	executes the required tasks. For e.g., it connects each handle's signals to appropriate
 *	slots.
 */

//	Print file and function name:
	qInfo() << __FILE_NAME__ << __func__;

//	Retrieve the item below the cursor at mouse-button release:
	if (const auto item = itemAt(event->scenePos(), QTransform()); item && connection.handleClicked) {

		//	If the item is a node-rail, create a handle at its position:
		if (item->type() == QGraphicsLineItem::Type) {

			//	Cast the item pointer to a QGraphicsLineItem, and the nodeRail:
			const auto nodeRail    = qgraphicsitem_cast<QGraphicsLineItem*>(item);
			const auto nodePointer = qgraphicsitem_cast<nodeCtrl*>(nodeRail->parentItem());

			//	Retrieve the type of the handle that was clicked:
			const auto railType   = nodeRail->data(0).value<StreamType>();
			const auto sourceType = connection.originHandle->streamType();

			/*	Check if:
			 *	1. The rails in the target node are of the opposite type of the source handle.
			 *	2. The target node is different from the source node.	*/
			if (railType != sourceType && nodePointer && nodePointer->getUID() != connection.originNode->getUID()) {

				//	Convert the cursor's position (in scene coordinates) to the rail's local coordinates:
				const auto yposLocal  = nodeRail->mapFromScene(event->scenePos()).y();
				const auto yposOrigin = nodeRail->mapFromParent(QPointF(0, 0)).y() + 4.0;
				const auto ypos       = yposLocal - yposOrigin;

				//	Create a new handle on the rail at the cursor's position (in local coordinates):
				nodePointer->createHandle(railType, QPointF(0.0, ypos));
			}
		}

		//	If a handle exists under the cursor, retrieve its details:
		if (const auto itemReload = itemAt(event->scenePos(), QTransform());
			itemReload->type() == QGraphicsItem::UserType + HANDLEITEM) {

			//	Store the target node and handle's pointer:
			const auto handlePointer = qgraphicsitem_cast<nodeHandle*>(itemReload);
			const auto nodePointer   = qgraphicsitem_cast<nodeCtrl*>(item->parentItem());

			//	Connect the two variables:
			if (handlePointer && nodePointer) {
				if (const auto path = handlePointer->pair(connection.originHandle))
					qInfo() << "Connection established";

			}
		}
	}

	connection.handleClicked = false;
	connection.originHandle  = nullptr;
	connection.connector->setPath(QPainterPath());

//	Resolve event handlers of nested item(s), if any:
	QGraphicsScene::mouseReleaseEvent(event);
}

void
schemaCanvas::contextMenuEvent(QGraphicsSceneContextMenuEvent* event) {
//	Resolve event handlers of nested item(s) first:
	QGraphicsScene::contextMenuEvent(event);

//	Ignore the event if it is already accepted i.e. a child's context menu has been executed:
	if (!event->isAccepted()) {
		menu.position = event->scenePos();
		menu.pointer->exec(event->screenPos());
		event->setAccepted(true);
	}
}

void
schemaCanvas::keyPressEvent(QKeyEvent* event) {

//	Print the file and function name:
	qInfo() << __FILE__ << __func__;

//	If user presses Ctrl + C, copy selected items into clipboard:
	if (event->matches(QKeySequence::Copy))
		list.clipboard = selectedItems();

//	If user presses Ctrl + V, paste selected items onto scene:
	else if (event->matches(QKeySequence::Paste)) {

		//	If the clipboard isn't empty, begin copying items:
		if (!list.clipboard.isEmpty()) {

			//	Loop over clipboard items:
			for (const auto item : list.clipboard) {

				//	Allocate and copy from node:
				if (const auto nodeOriginal = qgraphicsitem_cast<nodeCtrl*>(item);
					nodeOriginal != nullptr) {
					//	Create a copy:
					const auto nodeCopy = createNode(*nodeOriginal);

					//	Keep the copied node selected, deselect original node:
					nodeCopy->setSelected(true);
					nodeOriginal->setSelected(false);
				}
			}

			//	Set the clipboard to the newly pasted items. This allows chain-pasting.
			list.clipboard = selectedItems();

			//	Loop over the pasted nodes and connect them to others:
			for (const auto item : list.clipboard) {

				//	Allocate and copy from node:
				if (const auto node = qgraphicsitem_cast<nodeCtrl*>(item);
					node != nullptr) {
					//	Reconnect:
					node->reconnect();
				}
			}
		}
		event->accept();
	}

//	If the user presses Ctrl + A, all items are selected:
	else if (event->matches(QKeySequence::SelectAll)) {
		for (auto j : amplDatabase::nodeList) { j->setSelected(true); }
	}

	else if (event->matches(QKeySequence::Print)) {
		for (const auto node : amplDatabase::nodeList)
			qInfo() << "\t- Active nodes: " << node->name();

		for (const auto var : amplDatabase::variableList) { qInfo() << "\t- Active variables: " << var->getSymbol(); }
	}

//	If the user presses <Delete>, all selected items are deleted:
	if (event->key() == Qt::Key_Delete) {
		for (const auto deleteList = selectedItems();
			 const auto item : deleteList)
			delete item;
	}

//	Call the base-class implementation last:
	QGraphicsScene::keyPressEvent(event);
}

void
schemaCanvas::startConnection(nodeCtrl* nptr, nodeHandle* vptr) {

//	This function is triggered when the user clics a handle to start drawing a connection:
	if (!connection.handleClicked) {


#ifdef VERBOSE
		qInfo() << __FILE_NAME__ << __func__;
		qInfo() << "\t- Starting a new connection";
#endif
		//	Store pointers to the connection's origin node and handle:
		connection.originNode   = qgraphicsitem_cast<nodeCtrl*>(nptr);
		connection.originHandle = qgraphicsitem_cast<nodeHandle*>(vptr);

		//	Change connection.inProgress to true:
		connection.handleClicked = true;
	}
}

nodeCtrl*
schemaCanvas::createNode(const QPointF& pos) {
	//	Create a new node at cursor position pos (in scene coordinates):
	const auto node = new nodeCtrl(pos, "Node");

	//	Store node pointer in database:
	amplDatabase::nodeList.append(node);

	//	Add created node to scene:
	addItem(node);

	//	Connect node signals to slots:
	connect(node, &nodeCtrl::connectHandle, this, &schemaCanvas::startConnection);
	connect(node, &nodeCtrl::nodeDeleted, this, &schemaCanvas::deleteNode);

	//	Return the created node-pointer:
	return (node);
}

nodeCtrl*
schemaCanvas::createNode(const nodeCtrl& node) {

	//	Allocate and copy from node:
	const auto copy = new nodeCtrl(node);

	//	Store node pointer in database:
	amplDatabase::nodeList.append(copy);

	//	Add copied node to scene:
	addItem(copy);

	//	Connect node signals to slots:
	connect(copy, &nodeCtrl::connectHandle, this, &schemaCanvas::startConnection);
	connect(copy, &nodeCtrl::nodeDeleted, this, &schemaCanvas::deleteNode);

	//	Return the created node-pointer:
	return (copy);
}

QGroup*
schemaCanvas::createGroup(const QList<QItemG*>& itemList) {

	qInfo() << __FILE__ << __func__;           //	Print file and function name
	const auto group = new QGraphicsItemGroup; //	Create a new QGraphicsItemGroup instance
	const auto color = HEX_RANDOM;

	for (const auto item : itemList) {
		group->addToGroup(item);
		group->setFlag(QGraphicsItem::ItemIsMovable);
		group->setFlag(QGraphicsItem::ItemIsSelectable);

		if (item->type() == QItemG::UserType + 1)
			qgraphicsitem_cast<nodeCtrl*>(item)->setColor(color);
	}

	//	Add the group to the scene:
	list.itemsGroup.append(group);
	addItem(group);

	//	Return the created group:
	return (group);
}

void
schemaCanvas::createFolder(const QPointF& pos) {
	if (const auto items = selectedItems();
		!items.empty()) {
		//	Create a folder and add it to the scene:
		const auto pointer = new nodeGroup(pos, ":/icons/folder-not-empty.svg");

		//	Add the folder to the scene:
		addItem(pointer);

		//	Move all selected items into the folder (i.e. set as children):
		for (const auto item : items)
			pointer->hold(item);
	}
}

void
schemaCanvas::deleteNode(nodeCtrl* nodePointer) {

	/*	This SLOT is automatically triggered by SIGNAL(nodeCtrl::nodeDeleted(nodeCtrl*)).
	 *	Here, the specified node is removed from the scene and scheduled for deletion.
	 */

	qInfo() << __FILE__ << __func__; //	Print file and function name
	removeItem(nodePointer);         //	Remove the node from the scene
	nodePointer->deleteLater();      //	Delete the node using QObject::deleteLater()
}

void
schemaCanvas::deleteSchema() const {
	qInfo() << __FILE__ << __func__; //	Print file and function name
	for (const auto items = selectedItems();
		 const auto item : items) //	Loop over items
		delete item;              //	Delete them
}

void
schemaCanvas::shortcutCopy() { list.clipboard = selectedItems(); }

void
schemaCanvas::shortcutPaste() {
}

void
schemaCanvas::shortcutDelete() {}

void
schemaCanvas::shortcutSelect() {}
