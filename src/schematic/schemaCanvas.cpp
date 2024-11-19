/*  -----------------------------------
 *  Project     : sapiens
 *  File        : canvas.cpp
 *  Date        : 18.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

//  Include Class Header:
#include "schematic/schemaCanvas.h"
#include "core/coreIOF.h"

//  Constructor:
schemaCanvas::schemaCanvas(const QRect& rect, QObject* parent) :
//  Initialize base-class constructor:
    QGraphicsScene(parent),

//  Initialize attributes:
    attr(rect, 1.0)

{
//  Add gridpoints to the scene:
    addItem(new schemaGrid(attr.rect));

//  Emit initialized() signal upon Constructor completion:
    emit initialized();
}

void schemaCanvas::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    Q_UNUSED(event)
    QGraphicsScene::mouseMoveEvent(event);
}

void schemaCanvas::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    Q_UNUSED(event)
    QGraphicsScene::mousePressEvent(event);

    switch(event->button()) {
        case Qt::LeftButton: {
            qDebug() << "Left Button";
            mouse::is_pressed_lmb = true;
            break;
        }
        case Qt::MiddleButton: {
            mouse::is_pressed_mmb = true;
            auto cpos = event->scenePos();
            auto node = new nodeControl(cpos.x(), cpos.y(), QString("Node"));

            addItem(node);
            node->setPos(cpos.x(), cpos.y());

            qDebug() << node->scenePos();
            break;
        }
        case Qt::RightButton: {
            qDebug() << "Right Button";
            mouse::is_pressed_rmb = true;
            break;
        }
        default:
            break;
    }
}

void schemaCanvas::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    Q_UNUSED(event)
    QGraphicsScene::mouseReleaseEvent(event);

    mouse::is_pressed_lmb = false;
    mouse::is_pressed_mmb = false;
    mouse::is_pressed_rmb = false;
}