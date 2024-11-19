/*  -----------------------------------
 *  Project     : sapiens
 *  File        : canvas.cpp
 *  Date        : 18.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

//  Include Qt Core Classes:
#include <QPointF>

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
            mouse::is_pressed_lmb = true;
            break;
        }
        case Qt::MiddleButton: {
        //  Create a new node and add it to scene:
            schemaCanvas::createNode(event->scenePos(), this);

            mouse::is_pressed_mmb = true;
            break;
        }
        case Qt::RightButton: {
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

void schemaCanvas::createNode(QPointF cpos, schemaCanvas* scenePtr) {
    Q_UNUSED(cpos)

    qDebug() << "schemaCanvas::createNode";
    auto node = new nodeControl(cpos.x(), cpos.y(), "Node");
    scenePtr->addItem(node);
}

void schemaCanvas::deleteNode(schemaCanvas* scenePtr) {
    Q_UNUSED(scenePtr)
}

void schemaCanvas::updateNode(schemaCanvas* scenePtr) {
    Q_UNUSED(scenePtr)
}