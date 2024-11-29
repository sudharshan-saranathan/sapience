/*  -----------------------------------
 *  Project     : sapiens
 *  File        : schemaCanvas.h
 *  Date        : 18.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef CANVAS_H
#define CANVAS_H

/*  QtWidgets module    */
#include <QAction>
#include <QKeyEvent>
#include <QGraphicsScene>

//  Include nodeCtrl:
#include "node/nodeCtrl.h"
#include "node/nodeVar.h"

using QItemL = QGraphicsLineItem;

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
        QRect areaRect;                     //  Store the bounding rectangle for the scene
        float distance;                     //  Snapping proximity for connections
    } attr;

    //  List of nodes, names, and other things:
    struct _list_ {
        QList<nodeCtrl*> nodes;             //  QList of pointers to the currently drawn node(s)
        QList<QString>   nUIDs;             //  QList of node IDs
        QList<QItemG*> clipboard;           //  Clipboard used for copy-paste operation
    } list;

    //  Context menu and associated actions:
    struct _menu_ {
        QPointF  pos;                       //  Context menu position (in scene coordinates)
        QMenu*   ptr;                       //  Pointer to QMenu
        QAction* createNode;                //  QAction for creating a new node at pos
        QAction* clearScene;                //  QAction for deleting all elements in the scene
        QAction* quitApp;                   //  QAction for quitting the application
    } menu;

    struct _connection_ {
        bool      inProgress = false;
        bool      handleSnap = true;
        nodeCtrl* sourceNodePointer     = nullptr;
        nodeVar*  sourceVariablePointer = nullptr;
        pathElement* pathElementPointer = nullptr;
    } connection;

signals:
    void initialized();                     //  Signal emitted upon constructor completion
    void quitProgram();                     //  Signal emitted by scene context menu

protected slots:
    /*  Methods to handle keyboard and mouse events that trigger
     *  various functions (e.g. copy, paste, delete). Do not delete
     *  these   */
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public slots:
    void onCreateLink(nodeCtrl*, nodeVar*);
    void onDeleteNode(nodeCtrl*);

public:
    /*  Methods to create a new node    */
    void createNode(const QPointF&);                //  Create a new node at the cursor position (scene coordinates)
    void createNode(const nodeCtrl&);               //  Copy an existing node using the copy-constructor of nodeCtrl
};

#endif
