/*  -----------------------------------
 *  Project     : sapiens
 *  File        : schemaCanvas.h
 *  Date        : 18.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef CANVAS_H
#define CANVAS_H

#define FOLDERSIZE 64
#define FOLDERSIZE 64

//	QtWidgets module
#include <QAction>
#include <QKeyEvent>
#include <QGraphicsScene>

//  Include node-objects:
#include "node/nodeCtrl.h"
#include "node/nodeHandle.h"

//	Define aliases:
using QItemL = QGraphicsLineItem;
using QGroup = QGraphicsItemGroup;

//	Forward declaration of class schemaViewer
class schemaViewer;

//	Class schemaCanvas
class schemaCanvas final : public QGraphicsScene {

	Q_OBJECT Q_DISABLE_COPY_MOVE(schemaCanvas)
	Q_CLASSINFO("Author", "Sudharshan Saranathan")public:

	~schemaCanvas() override = default;
	schemaCanvas()           = default;
	schemaCanvas(const QRect&, QObject* parent);

public:
	void setProximity(nodeHandle* pointer) { connection.proximityPointer = pointer; }

protected slots:

	void
	startConnection(nodeCtrl*, nodeHandle*); //  Begins drawing a new connection when a handle is clicked
	nodeCtrl*
	createNode(const QPointF&); //  Creates a new node at cursor position (in scene coordinates)
	nodeCtrl*
	createNode(const nodeCtrl&); //  Copies an existing node and its variables
	QGroup*
	createGroup(const QList<QItemG*>&); //  Groups the selected items
	void
	createFolder(const QPointF&); //  Moves selected nodes into a folder
	void
	deleteNode(nodeCtrl*); //  Deletes the node emitting the nodeDeleted() signal
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

signals:

	void
	initialized(); //  Emitted when the constructor has finished initialization
	void
	quitProgram(); //  Emitted when the user quits the program

//	Event-handlers
protected slots:

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
	struct _attr_ {
		QRect areaRect; //  Store the bounding rectangle for the scene
		float distance; //  Snapping proximity for connections
	} attr;

	//  List of nodes, IDs, and other things:
	struct _list_ {
		QList<nodeCtrl*> nodes;      //  QList of pointers to the currently drawn node(s)
		QList<QString>   nUIDs;      //  QList of node IDs
		QList<QItemG*>   clipboard;  //  Clipboard used for copy-paste operation
		QList<QGroup*>   itemsGroup; //  QList of item-groups
	} list;

	//  Context menu and associated actions:
	struct _menu_ {
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
	} menu;

	//  Helper-struct to store useful variables when the user is drawing a connection
	struct _connection_ {
		bool handleClicked = false; //  Flag that is set to true when the user clicks a handle to draw a connection
		nodeCtrl* originNode = nullptr; //  Points to the node where the user starts drawing the connection
		nodeHandle* originHandle = nullptr; //  Points to the variable which was clicked to start the connection
		nodeHandle* proximityPointer = nullptr;
		nodeConnect* connector = nullptr; //  Points to a QGraphicsPathItem that is repeatedly modified
	} connection;
};

#endif
