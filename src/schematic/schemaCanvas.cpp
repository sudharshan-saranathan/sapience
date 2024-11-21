/*  -----------------------------------
 *  Project     : sapience
 *  File        : schemaCanvas.cpp
 *  Date        : 18.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

/*  Include Qt Core Classes */
#include <QPointF>

/*  Include project headers */
#include "core/coreIOF.h"
#include "node/nodeControl.h"
#include "schematic/schemaCanvas.h"

/*  Class constructor   */
schemaCanvas::schemaCanvas(const QRect &rect, QObject *parent) :

    /*  Initialize base-class constructor   */
    QGraphicsScene(parent),

    /*  Initialize attributes   */
    attr{rect, 1.0},

    /*  Initialize clipboard    */
    list{QList<QGraphicsItem *>{}, QList<nodeControl *>{}}

/*  Constructor body begin  */
{
    /*  Add grid-points to the QGraphicsScene   */
    addItem(new schemaGrid(attr.rect));

    /*  Emit initialized() to signal constructor completion */
    emit initialized();
}

/*  Event-handler for mouse-move    */
void schemaCanvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event)
    QGraphicsScene::mouseMoveEvent(event);
}

/*  Event-handler for mouse-press   */
void schemaCanvas::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event)
    QGraphicsScene::mousePressEvent(event);

    /*  Switch-case block   */
    switch (event->button()) {
        /*  Handle LMB-press events */
        case Qt::LeftButton: {
            mouse::is_pressed_lmb = true;
            break;
        }
        /*  Handle MMB-press events */
        case Qt::MiddleButton: {
            //  Create a new node, add it to scene:
            schemaCanvas::createNode(event->scenePos(), this);
            mouse::is_pressed_mmb = true;
            break;
        }
        /*  Handle RMB-press events */
        case Qt::RightButton: {
            mouse::is_pressed_rmb = true;
            break;
        }
        default:
            break;
    }
}

/*  Event-handler for mouse-release */
void schemaCanvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event)
    QGraphicsScene::mouseReleaseEvent(event);

    mouse::is_pressed_lmb = false;
    mouse::is_pressed_mmb = false;
    mouse::is_pressed_rmb = false;
}

/*  Event-handler for key-presses   */
void schemaCanvas::keyPressEvent(QKeyEvent *event) {
    Q_UNUSED(event)
    QGraphicsScene::keyPressEvent(event);

    /*  Handle Ctrl+C (Copy)    */
    if (event->matches(QKeySequence::Copy)) {
        list.clipboard = selectedItems();
        event->accept();
    }

    /*  Handle Ctrl+V (Paste)    */
    if (event->matches(QKeySequence::Paste)) {
        /*  Paste if clipboard isn't empty  */
        if (!list.clipboard.isEmpty()) {
            /*  Loop over clipboard items   */
            for (auto j: list.clipboard) {
                const auto node = qgraphicsitem_cast<nodeControl *>(j);
                const auto copy = new nodeControl(*node);
                addItem(copy);
            }
        }
        event->accept();
    }

    /*  Switch-case block to handle other key-presses   */
    switch (event->key()) {
        /*  Handle delete operation */
        case Qt::Key_Delete:
            /*  Loop over selection-clipboard to delete items   */
            for (auto j: selectedItems()) {
                removeItem(j);
                list.nodelist.removeAll(j);
            }
            event->accept();
            break;

        default:
            event->ignore();
            break;
    }
}

void schemaCanvas::keyReleaseEvent(QKeyEvent *event) {
    Q_UNUSED(event)
    QGraphicsScene::keyReleaseEvent(event);
}

void schemaCanvas::createNode(const QPointF &cpos, schemaCanvas *scenePtr) {
    Q_UNUSED(cpos)

    const auto node = new nodeControl(cpos, "Node", GITEM_::NODE);
    scenePtr->list.nodelist.append(node);
    scenePtr->addItem(node);
}

void schemaCanvas::deleteNode(const schemaCanvas *scenePtr) {
    Q_UNUSED(scenePtr)
}

void schemaCanvas::updateNode(const schemaCanvas *scenePtr) {
    Q_UNUSED(scenePtr)
}
