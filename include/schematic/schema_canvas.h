/*  -----------------------------------
 *  Project     : sapience
 *  File        : schema_canvas.h
 *  Date        : 18.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef SCHEMA_CANVAS_H
#define SCHEMA_CANVAS_H

#define FOLDER_XS 64
#define FOLDER_YS 64

//	QtWidgets module
#include <QAction>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>

//  Include node-objects:
#include "node/node_ctrl.h"
#include "node/node_handle.h"

//	Define aliases:
using q_line  = QGraphicsLineItem;
using q_group = QGraphicsItemGroup;

//	Forward declaration of class SchemaViewer
class SchemaViewer;

//	Class SchemaCanvas
class SchemaCanvas final : public QGraphicsScene
{
	Q_OBJECT Q_DISABLE_COPY_MOVE(SchemaCanvas)
	Q_CLASSINFO
	(
		"Author"
		,
		"Sudharshan Saranathan"
	)

public:
	~SchemaCanvas() override = default;
	SchemaCanvas()           = default;
	SchemaCanvas(const QRect&, QObject* parent);

protected slots:
	void
	startConnection(NodeCtrl*, NodeHandle*); //  Begins drawing a new connection when a handle is clicked

	NodeCtrl*
	createNode(const QPointF&); //  Creates a new node at cursor position (in scene coordinates)

	NodeCtrl*
	createNode(const NodeCtrl&); //  Copies an existing node and its variables

	q_group*
	createGroup(const QList<q_item_g*>&); //  Groups the selected items

	void
	createFolder(const QPointF&); //  Moves selected nodes into a folder

	void
	deleteNode(NodeCtrl*); //  Deletes the node emitting the nodeDeleted() signal

	void
	deleteSchema() const; //  Deletes all items in the scene

	void
	shortcutCopy();

	void
	shortcutPaste();

	void
	shortcutDelete();

	void
	shortcutSelect();

signals :
	void
	initialized(); //  Emitted when the constructor has finished initialization

	void
	quitProgram(); //  Emitted when the user quits the program

	//	Event-handlers
protected
slots :
	void
	mouseMoveEvent(QGraphicsSceneMouseEvent* event) override; //  Updates connections as the cursor is moved

	void
	mousePressEvent(QGraphicsSceneMouseEvent* event) override; //  Left-button click starts drawing a new connection

	void
	mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override; //  Establishes a successful connection

	void
	contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override; //  Context menu

	void
	keyPressEvent(QKeyEvent* event) override; //  Handles shortcuts (copy, paste, delete, select all)

protected:
	//  Default Attribute(s):
	struct
	{
		QRect areaRect; //  Store the bounding rectangle for the scene
		float distance; //  Snapping proximity for connections
	} m_attr;

	//  List of nodes, IDs, and other things:
	struct
	{
		QList<NodeCtrl*> nodes;     //  QList of pointers to the currently drawn node(s)
		QList<QString>   nUIDs;     //  QList of node IDs
		QList<q_item*>   clipboard; //  Clipboard used for copy-paste operation
		QList<q_group*>  itemGroup; //  QList of item-groups
	} m_list;

	//  Context menu and associated actions:
	struct
	{
		QPointF  position;     //  Context menu position (in scene coordinates)
		QMenu*   pointer;      //  Pointer to QMenu
		QAction* createNode;   //  QAction for creating a new node at pos
		QAction* createSource; //  QAction for creating a new source at pos
		QAction* createSink;   //  QAction for creating a new sink at pos
		QAction* groupItems;   //  QAction for creating an item-group
		QAction* createFolder; //  QAction for creating a new folder at pos
		QAction* importSchema; //  Import schematic from disk
		QAction* exportSchema; //  Export schematic to disk
		QAction* deleteSchema; //  QAction for deleting all elements in the scene
		QAction* quitApp;      //  QAction for quitting the application
	} m_menu;

	//  Helper-struct to store useful variables when the user is drawing a connection
	struct
	{
		bool handleClicked = false; //  Flag that is set to true when the user clicks a handle to draw a connection
		NodeCtrl* originNode = nullptr; //  Points to the node where the user starts drawing the connection
		NodeHandle* originHandle = nullptr; //  Points to the variable which was clicked to start the connection
		NodeConnect* connector = nullptr; //  Points to a QGraphicsPathItem that is repeatedly modified
	} m_connection;
};

#endif
