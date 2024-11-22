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

//  Include project headers:
#include "schematic/schemaViewer.h"

//  Constructor:
schemaViewer::schemaViewer(QWidget *parent)  :
/*  Initialize base-class constructor  */
    QGraphicsView(parent),
/*  Instantiate schemaCanvas  */
    canvas(QRect(0, 0, SCENE_XS, SCENE_YS), new schemaCanvas(canvas.bounds, this))
/*  Constructor body-begin  */
{
/*  Set render hint, do not delete  */
    setRenderHint(QPainter::Antialiasing);

/*  Set QGraphicsScene object  */
    setScene(canvas.objptr);

/*  Signal contructor completion  */
    emit initialized();
}

void schemaViewer::wheelEvent(QWheelEvent *event) {
    Q_UNUSED(event)

    auto scroll = static_cast<double>(event->angleDelta().y()) / WHEEL_DELTA;
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

/*  Propagate event to base-class event-handler  */
    QGraphicsView::keyPressEvent(event);

/*  Switch-case block   */
    switch(event->modifiers())
    {
    /*  Filter <shift> presses  */
        case Qt::ShiftModifier:
            setDragMode(QGraphicsView::ScrollHandDrag);
            event->accept();
            break;
    /*  Filter <ctrl> presses (cmd on MacOS)  */
        case Qt::ControlModifier:
            setDragMode(QGraphicsView::RubberBandDrag);
            setCursor(Qt::CrossCursor);
            event->accept();
            break;
    /*  Default  */
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
    setCursor(Qt::ArrowCursor);
}
