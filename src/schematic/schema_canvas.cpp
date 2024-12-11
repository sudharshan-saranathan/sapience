/*  -----------------------------------
 *  Project     : sapience
 *  File        : SchemaCanvas.cpp
 *  Date        : 18.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

/*  Include Qt Core Classes */
#include <QMenu>
#include <QRandomGenerator>

/*  Include project headers */
#include "schematic/schema_canvas.h"

#include <QGraphicsSceneMouseEvent>

#include "node/node_connect.h"
#include "node/node_group.h"
#include "schematic/schema_viewer.h"

#define HEX_RANDOM QString("#%1").arg(QRandomGenerator::global()->generate() & 0xFFFFFF, 6, 16, QChar('0'))

SchemaCanvas::SchemaCanvas(const QRect& areaRect, QObject* parent) :
	/*  Initializer m_list  */
	//  Base-class constructor:
	QGraphicsScene(parent),
	//	Default m_attribute(s)
	m_attr{areaRect, 5},
	//	Container for various useful lists
	m_list{QList<NodeCtrl*>(), QList<QString>(), QList<QGraphicsItem*>(), QList<q_group*>()},
	//	Context m_menu and actions
	m_menu{
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
	setObjectName("SchemaCanvas");
	setBackgroundBrush(QBrush(Qt::black, Qt::Dense6Pattern));
	setSceneRect(m_attr.areaRect);

	//	Add actions to context-m_menu:
	m_menu.pointer->addAction(m_menu.createNode);
	m_menu.pointer->addAction(m_menu.createSource);
	m_menu.pointer->addAction(m_menu.createSink);
	m_menu.pointer->addSeparator();
	m_menu.pointer->addAction(m_menu.groupItems);
	m_menu.pointer->addAction(m_menu.createFolder);
	m_menu.pointer->addSeparator();
	m_menu.pointer->addAction(m_menu.importSchema);
	m_menu.pointer->addAction(m_menu.exportSchema);
	m_menu.pointer->addSeparator();
	m_menu.pointer->addAction(m_menu.deleteSchema);
	m_menu.pointer->addAction(m_menu.quitApp);

	//  Do not change shortcut context:
	m_menu.createNode->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the m_menu
	m_menu.createNode->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));    //	Define the custom shortcut
	m_menu.createNode->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	//  Do not change shortcut context:
	m_menu.createSource->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the m_menu
	m_menu.createSource->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Less)); //	Define the custom shortcut
	m_menu.createSource->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	//  Do not change shortcut context:
	m_menu.createSink->setShortcutVisibleInContextMenu(true);                 //	Show the shortcut in the m_menu
	m_menu.createSink->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Greater)); //	Define the custom shortcut
	m_menu.createSink->setShortcutContext(Qt::WidgetWithChildrenShortcut);    //	Do not remove or modify

	m_menu.groupItems->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the m_menu
	m_menu.groupItems->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_G));    //	Define the custom shortcut
	m_menu.groupItems->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	m_menu.createFolder->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the m_menu
	m_menu.createFolder->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_F));    //	Define the custom shortcut
	m_menu.createFolder->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	m_menu.importSchema->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the m_menu
	m_menu.importSchema->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_F));    //	Define the custom shortcut
	m_menu.importSchema->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	m_menu.exportSchema->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the m_menu
	m_menu.exportSchema->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_F));    //	Define the custom shortcut
	m_menu.exportSchema->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	m_menu.deleteSchema->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the m_menu
	m_menu.deleteSchema->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_D));    //	Define the custom shortcut
	m_menu.deleteSchema->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	m_menu.quitApp->setShortcutVisibleInContextMenu(true);              //	Show the shortcut in the m_menu
	m_menu.quitApp->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));    //	Define the custom shortcut
	m_menu.quitApp->setShortcutContext(Qt::WidgetWithChildrenShortcut); //	Do not remove or modify

	connect(m_menu.createNode, &QAction::triggered, [&]() { createNode(m_menu.position); });
	connect(m_menu.groupItems, &QAction::triggered, [&]() { createGroup(selectedItems()); });
	connect(m_menu.createFolder, &QAction::triggered, [&]() { createFolder(m_menu.position); });
	connect(m_menu.deleteSchema, &QAction::triggered, [&]() { deleteSchema(); });
	connect(m_menu.quitApp, &QAction::triggered, [&]() { emit quitProgram(); });

	/*	Create a default NodeConnect and add it to the scene. This path element is used to temporarily
	 *	draw the path as the user drags the mouse across the scene. It is reset and re-used
	 */
	m_connection.connector = new NodeConnect(QPen(QColor(243, 149, 22), 2.0));
	addItem(m_connection.connector);

	//	Signal constructor completion:
	emit initialized();
}

void
SchemaCanvas::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	//	Resolve event handlers of nested item(s) first, if any:
	QGraphicsScene::mouseMoveEvent(event);

	//	Draw and update m_connection while the mouse moves:
	if (m_connection.handleClicked && m_connection.originHandle)
	{
		const auto tpos = event->scenePos();
		const auto spos = m_connection.originHandle->scenePos() +
			m_connection.originHandle->rect().center();

		m_connection.connector->connect(spos, tpos);
	}
}

void
SchemaCanvas::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	//	Resolve the event handlers of nested items first:
	QGraphicsScene::mousePressEvent(event);
}

void
SchemaCanvas::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	/*	Custom implementation of QGraphicsItem::mouseReleaseEvent() for derived class SchemaCanvas.
	 *	If the user is attempting to connect two variables in two different nodes, this handler
	 *	executes the required tasks. For e.g., it connects each handle's signals to appropriate
	 *	slots.
	 */

	//	Retrieve the item below the cursor at mouse-button release:
	if (const auto item = itemAt(event->scenePos(), QTransform()); item && m_connection.handleClicked)
	{
		//	If the item is a node-rail, create a handle at its position:
		if (item->type() == QGraphicsLineItem::Type)
		{
			//	Cast the item pointer to a QGraphicsLineItem, and the nodeRail:
			const auto nodeRail    = qgraphicsitem_cast<QGraphicsLineItem*>(item);
			const auto nodePointer = qgraphicsitem_cast<NodeCtrl*>(nodeRail->parentItem());

			//	Retrieve the type of the handle that was clicked:
			const auto railType   = nodeRail->data(0).value<NodeHandle::StreamType>();
			const auto sourceType = m_connection.originHandle->streamType();

			/*	Check if:
			 *	1. The rails in the target node are of the opposite type of the source handle.
			 *	2. The target node is different from the source node.	*/
			if (railType != sourceType && nodePointer && nodePointer->UID() != m_connection.originNode->UID())
			{
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
			itemReload->type() == QGraphicsItem::UserType + HANDLEITEM)
		{
			//	Store the target node and handle's pointer:
			const auto handlePointer = qgraphicsitem_cast<NodeHandle*>(itemReload);
			const auto nodePointer   = qgraphicsitem_cast<NodeCtrl*>(item->parentItem());

			//	Connect the two variables:
			if (handlePointer && nodePointer)
			{
				if (const auto path = handlePointer->pair(m_connection.originHandle))
					qInfo() << "m_connection established";
			}
		}
	}

	m_connection.handleClicked = false;
	m_connection.originHandle  = nullptr;
	m_connection.connector->setPath(QPainterPath());

	//	Resolve event handlers of nested item(s), if any:
	QGraphicsScene::mouseReleaseEvent(event);
}

void
SchemaCanvas::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
	//	Resolve event handlers of nested item(s) first:
	QGraphicsScene::contextMenuEvent(event);

	//	Ignore the event if it is already accepted i.e. a child's context m_menu has been executed:
	if (!event->isAccepted())
	{
		m_menu.position = event->scenePos();
		m_menu.pointer->exec(event->screenPos());
		event->setAccepted(true);
	}
}

void
SchemaCanvas::keyPressEvent(QKeyEvent* event)
{
	//	Print the file and function name:
	qInfo() << __FILE__ << __func__;

	//	If user presses Ctrl + C, copy selected items into clipboard:
	if (event->matches(QKeySequence::Copy))
		m_list.clipboard = selectedItems();

		//	If user presses Ctrl + V, paste selected items onto scene:
	else if (event->matches(QKeySequence::Paste))
	{
		//	If the clipboard isn't empty, begin copying items:
		if (!m_list.clipboard.isEmpty())
		{
			//	Loop over clipboard items:
			for (const auto item : m_list.clipboard)
			{
				//	Allocate and copy from node:
				if (const auto nodeOriginal = qgraphicsitem_cast<NodeCtrl*>(item);
					nodeOriginal != nullptr)
				{
					//	Create a copy:
					const auto nodeCopy = createNode(*nodeOriginal);

					//	Keep the copied node selected, deselect original node:
					nodeCopy->setSelected(true);
					nodeOriginal->setSelected(false);
				}
			}

			//	Set the clipboard to the newly pasted items. This allows chain-pasting.
			m_list.clipboard = selectedItems();

			//	Loop over the pasted nodes and connect them to others:
			for (const auto item : m_list.clipboard)
			{
				//	Allocate and copy from node:
				if (const auto node = qgraphicsitem_cast<NodeCtrl*>(item);
					node != nullptr)
				{
					//	Reconnect:
					node->reconnect();
				}
			}
		}
		event->accept();
	}

	//	If the user presses Ctrl + A, all items are selected:
	else if (event->matches(QKeySequence::SelectAll))
	{
		for (auto j : OptimDB::nodeCtrlList) { j->setSelected(true); }
	}

	else if (event->matches(QKeySequence::Print))
	{
		for (const auto node : OptimDB::nodeCtrlList)
			qInfo() << "\t- Active nodes: " << node->name();

		for (const auto var : OptimDB::variableList) { qInfo() << "\t- Active variables: " << var->getSymbol(); }
	}

	//	If the user presses <Delete>, all selected items are deleted:
	if (event->key() == Qt::Key_Delete)
	{
		for (const auto deleteList = selectedItems();
		     const auto item : deleteList)
			delete item;
	}

	//	Call the base-class implementation last:
	QGraphicsScene::keyPressEvent(event);
}

void
SchemaCanvas::startConnection(NodeCtrl* nptr, NodeHandle* vptr)
{
	//	This function is triggered when the user clics a handle to start drawing a m_connection:
	if (!m_connection.handleClicked)
	{
#ifdef VERBOSE
		qInfo() << __FILE_NAME__ << __func__;
		qInfo() << "\t- Starting a new m_connection";
#endif
		//	Store pointers to the m_connection's origin node and handle:
		m_connection.originNode   = qgraphicsitem_cast<NodeCtrl*>(nptr);
		m_connection.originHandle = qgraphicsitem_cast<NodeHandle*>(vptr);

		//	Change m_connection.inProgress to true:
		m_connection.handleClicked = true;
	}
}

NodeCtrl*
SchemaCanvas::createNode(const QPointF& pos)
{
	//	Create a new node at cursor position pos (in scene coordinates):
	const auto node = new NodeCtrl(pos, "Node");

	//	Store node pointer in database:
	OptimDB::nodeCtrlList.append(node);

	//	Add created node to scene:
	addItem(node);

	//	Connect node signals to slots:
	connect(node, &NodeCtrl::connectHandle, this, &SchemaCanvas::startConnection);
	connect(node, &NodeCtrl::nodeDeleted, this, &SchemaCanvas::deleteNode);

	//	Return the created node-pointer:
	return (node);
}

NodeCtrl*
SchemaCanvas::createNode(const NodeCtrl& node)
{
	//	Allocate and copy from node:
	const auto copy = new NodeCtrl(node);

	//	Store node pointer in database:
	OptimDB::nodeCtrlList.append(copy);

	//	Add copied node to scene:
	addItem(copy);

	//	Connect node signals to slots:
	connect(copy, &NodeCtrl::connectHandle, this, &SchemaCanvas::startConnection);
	connect(copy, &NodeCtrl::nodeDeleted, this, &SchemaCanvas::deleteNode);

	//	Return the created node-pointer:
	return (copy);
}

q_group*
SchemaCanvas::createGroup(const QList<q_item_g*>& itemList)
{

#ifdef VERBOSE
	qInfo() << __FILE__ << __func__;           //	Print file and function name
#endif

	const auto group = new QGraphicsItemGroup; //	Create a new QGraphicsItemGroup instance
	const auto color = HEX_RANDOM;

	for (const auto item : itemList)
	{
		group->addToGroup(item);
		group->setFlag(QGraphicsItem::ItemIsMovable);
		group->setFlag(QGraphicsItem::ItemIsSelectable);

		if (item->type() == q_item_g::UserType + 1)
			qgraphicsitem_cast<NodeCtrl*>(item)->setColor(color);
	}

	//	Add the group to the scene:
	m_list.itemGroup.append(group);
	addItem(group);

	//	Return the created group:
	return (group);
}

void
SchemaCanvas::createFolder(const QPointF& pos)
{
	if (const auto items = selectedItems();
		!items.empty())
	{
		//	Create a folder and add it to the scene:
		const auto pointer = new NodeGroup(pos, ":/icons/folder-not-empty.svg");

		//	Add the folder to the scene:
		addItem(pointer);

		//	Move all selected items into the folder (i.e. set as children):
		for (const auto item : items)
			pointer->hold(item);
	}
}

void
SchemaCanvas::deleteNode(NodeCtrl* nodePointer)
{
	/*	This SLOT is automatically triggered by SIGNAL(NodeCtrl::nodeDeleted(NodeCtrl*)).
	 *	Here, the specified node is removed from the scene and scheduled for deletion.
	 */

	qInfo() << __FILE__ << __func__; //	Print file and function name
	removeItem(nodePointer);         //	Remove the node from the scene
	nodePointer->deleteLater();      //	Delete the node using QObject::deleteLater()
}

void
SchemaCanvas::deleteSchema() const
{
	qInfo() << __FILE__ << __func__; //	Print file and function name
	for (const auto items = selectedItems();
	     const auto item : items) //	Loop over items
		delete item;              //	Delete them
}

void
SchemaCanvas::shortcutCopy() { m_list.clipboard = selectedItems(); }

void
SchemaCanvas::shortcutPaste()
{
}

void
SchemaCanvas::shortcutDelete()
{
}

void
SchemaCanvas::shortcutSelect()
{
}
