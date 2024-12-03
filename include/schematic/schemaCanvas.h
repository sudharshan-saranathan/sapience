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

/*  QtWidgets module    */
#include <QAction>
#include <QKeyEvent>
#include <QGraphicsScene>

//  Include node-objects:
#include "node/nodeCtrl.h"
#include "node/nodeVar.h"

using QItemL = QGraphicsLineItem;
using QGroup = QGraphicsItemGroup;

/*  Forward declaration of class schemaViewer   */
class schemaViewer;
class nodeVar;

/*  Class schemaCanvas  */
class schemaCanvas final : public QGraphicsScene {

    Q_OBJECT
    Q_DISABLE_COPY_MOVE(schemaCanvas)
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
    ~schemaCanvas() override = default;
     schemaCanvas()           = default;
     schemaCanvas(const QRect&, QObject* parent);

protected:
    /*  Default attributes  */
    struct _attr_ {
        QRect  areaRect;                     //  Store the bounding rectangle for the scene
        float  distance;                     //  Snapping proximity for connections
    } attr;

    //  List of nodes, names, and other things:
    struct _list_ {
        QList<nodeCtrl*> nodes;             //  QList of pointers to the currently drawn node(s)
        QList<QString>   nUIDs;             //  QList of node IDs
        QList<QItemG*> clipboard;           //  Clipboard used for copy-paste operation
        QList<QGroup*> itemsGroup;          //  QList of item-groups
    } list;

    //  Context menu and associated actions:
    struct _menu_ {
        QPointF  pos;                       //  Context menu position (in scene coordinates)
        QMenu*   ptr;                       //  Pointer to QMenu
        QAction* createNode;                //  QAction for creating a new node at pos
        QAction* groupItems;                //  QAction for creating an item-group
        QAction* createFolder;              //  QAction for creating a new folder at pos
        QAction* deleteSchema;              //  QAction for deleting all elements in the scene
        QAction* quitApp;                   //  QAction for quitting the application
    } menu;

    struct _connection_ {
        bool      inProgress = false;
        bool      handleSnap = true;
        nodeCtrl* sourceNodePointer     = nullptr;
        nodeVar*  sourceVariablePointer = nullptr;
        nodeConnect* connector = nullptr;
    } connection;

signals:
    void initialized();                     //  Emitted when the constructor has finished initialization
    void quitProgram();                     //  Emitted when the user quits the program

protected slots:
    /*  Event-handlers for mouse click operations   */
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void createLink  (nodeCtrl*, nodeVar*);     //  Begins drawing a new connection from the specified variable
    void createNode  (const QPointF&);          //  Creates a new node at cursor position (in scene coordinates)
    void createNode  (const nodeCtrl&);         //  Copies an existing node and its variables
    void groupItems  (const QList<QItemG*>&);   //  Groups the selected items
    void deleteNode  (nodeCtrl*);               //  Deletes the node pointer to by the argument
    void createFolder(const QPointF&);          //  Moves selected nodes into a folder
    void deleteSchema() const;                  //  Deletes all items in the scene
};

#endif
