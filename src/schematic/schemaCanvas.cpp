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
#include "core/coreEnum.h"
#include "node/nodeCtrl.h"
#include "schematic/schemaGrid.h"
#include "schematic/schemaCanvas.h"

/*  Class constructor   */
schemaCanvas::schemaCanvas(const QRect &rect, QObject *parent) :

    /*  Initialize base-class constructor   */
    QGraphicsScene(parent),

    /*  Initialize attributes   */
    attr{rect, 1.0},

    /*  Initialize clipboard    */
    list{QList<QGraphicsItem *>{}, QList<nodeCtrl *>{}, QList<QString>{}}

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
            createNode(event->scenePos());
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
            for (const auto j: list.clipboard) {
                createNode(*qgraphicsitem_cast<nodeCtrl *>(j));
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

void schemaCanvas::createNode(const QPointF &cpos) {
    Q_UNUSED(cpos)

    const auto node = new nodeCtrl(cpos, "Node-I");
    list.nodelist.append(node);
    addItem(node);

    auto c4 = QObject::connect(node, &nodeCtrl::nodeDeleted, this, [this, node]() { deleteNode(node); });
}

void schemaCanvas::createNode(const nodeCtrl &node) {
    const auto copy = new nodeCtrl(node);
    list.nodelist.append(copy);
    addItem(copy);

    auto c4 = QObject::connect(copy, &nodeCtrl::nodeDeleted, this, [this, copy]() { deleteNode(copy); });
}

void schemaCanvas::deleteNode(nodeCtrl *node) {
    Q_UNUSED(node)

    qInfo() << "Deleting " << node->getName();
    removeItem(qgraphicsitem_cast<QGraphicsItem *>(node));
}
