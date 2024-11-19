/*  -----------------------------------
 *  Project     : sapiens
 *  File        : schemaViewer.cpp
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

//  Include standard-headers:
#include <cmath>
#include <iostream>

//  Include Class Header:
#include "schematic/schemaViewer.h"

//  Constructor:
schemaViewer::schemaViewer(QWidget *parent)  :
//  Initialize base-class constructor:
    QGraphicsView(parent),

//  Initialize attributes:
    attr(1.0, 4.0, 0.25),

//  Initialize QGraphicsScene object:
    canvas(QRect(0, 0, SCENE_XS, SCENE_YS), new schemaCanvas(canvas.canvasBounds, this))
{
//  Set RenderHint:
    setRenderHint(QPainter::Antialiasing);

//  Set QGraphicsScene object:
    setScene(canvas.item);

//  Emit initialized() signal upon Constructor completion:
    emit initialized();
}

void schemaViewer::wheelEvent(QWheelEvent *event) {
    Q_UNUSED(event)

    auto scroll = (double) event->angleDelta().y() / WHEEL_DELTA;
    auto factor = pow(WHEEL_EXP, scroll);

    if(scroll > 0 && attr.zoom * factor >= attr.zmax)
        factor = attr.zmax / attr.zoom;
    else if(scroll < 0 && attr.zoom * factor <= attr.zmin)
        factor = attr.zmin / attr.zoom;

    attr.zoom *= factor;
    scale(factor, factor);
}

void schemaViewer::keyPressEvent(QKeyEvent *event) {
    Q_UNUSED(event)

//  Propagate event to base-class handler:
    QGraphicsView::keyPressEvent(event);

//  Switch-Case Block:
    switch(event->modifiers())
    {
        //  Filter Shift modifier:
        case Qt::ShiftModifier:
            setDragMode(QGraphicsView::ScrollHandDrag);
            event->accept();
            break;

        //  Default:
        default:
            event->ignore();
            break;
    }

}

void schemaViewer::keyReleaseEvent(QKeyEvent *event) {
    Q_UNUSED(event)

//  Propagate event to base-class handler:
    QGraphicsView::keyReleaseEvent(event);

//  Unset drag-mode:
    setDragMode(QGraphicsView::NoDrag);
}
