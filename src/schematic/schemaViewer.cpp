/*  -----------------------------------
 *  Project     : sapiens
 *  File        : schemaViewer.cpp
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

//  Include standard-headers:
#include <cmath>

//  QtCore module:
#include <QWheelEvent>

//  Include project headers:
#include "schematic/schemaViewer.h"
#include "schematic/schemaCanvas.h"

//  Constructor:
schemaViewer::schemaViewer(QWidget* parent) :
/*  Initializer list  */
//  Base-class constructor:
	QGraphicsView(parent),
//  Default Attribute(s):
	attr{ZOOM_INIT, ZOOM_MAX, ZOOM_MIN},
//  struct _canvas_:
	canvas{
		QRect(0, 0, SCENE_XS, SCENE_YS),
		new schemaCanvas(canvas.sceneBoundary, this),
		new QGridLayout(reinterpret_cast<QWidget*>(canvas.pointer))
	}

//  -------------------------
//  Constructor (body) begin:
{
//	Enable panning the QGraphicsScene using mouse-drag operations:
	setObjectName("schemaViewer");
	setDragMode(ScrollHandDrag);
	setResizeAnchor(AnchorUnderMouse);
	setRenderHint(QPainter::Antialiasing);

//  Set <canvas.ptr> as the primary scene:
	setScene(canvas.pointer);

//  Signal constructor completion:
	emit initialized();
}

void
schemaViewer::wheelEvent(QWheelEvent* event) {

	auto scroll = static_cast<float>(event->angleDelta().y()) / WHEEL_DELTA; //  Retrieve scroll amount
	auto factor = pow(WHEEL_EXP, scroll); //  Adjust WHEEL_EXP to fine-tune zoom step-size

//  If zoom-in exceeds max scale, ignore further input:
	if (scroll > 0 && attr.zoom * factor >= attr.zmax)      //  If zoom exceeds ZOOM_MAX,
		factor = attr.zmax / attr.zoom;                     //  clip zoom to maximum value.

//	If zoom-out exeeds min scale, ignore further input:
	else if (scroll < 0 && attr.zoom * factor <= attr.zmin) //  If zoom exceeds ZOOM_MIN,
		factor = attr.zmin / attr.zoom;                     //  clip zoom to minimum value.

//	Update current zoom and scale the view:
	attr.zoom *= factor;   //  Store new zoom factor
	scale(factor, factor); //  Execute zoom operation
}

//	Event-handler for key-press events:
void
schemaViewer::keyPressEvent(QKeyEvent* event) {

//	If <Shift> is pressed, toggle RubberBandDrag (to drag-select multiple items):
	if (event->modifiers() == Qt::ShiftModifier && //  If <shift> is pressed
		!itemAt(mapFromGlobal(QCursor::pos())))    //  If there are no items in the scene below the cursor
	{
		setDragMode(RubberBandDrag); //  Switch to RubberBandDrag mode
		setCursor(Qt::CrossCursor);  //  Indicate RubberBandDrag mode with cross-cursor
		event->accept();             //  Accept event
	}
	else
		QGraphicsView::keyPressEvent(event); //  Call base-class implementation
}

//	Reset cursor and drag-mode upon key-release:
void
schemaViewer::keyReleaseEvent(QKeyEvent* event) {

//  Reset cursor and drag mode:
	unsetCursor();
	setDragMode(ScrollHandDrag);

//  Call base-class implementation
	QGraphicsView::keyPressEvent(event);
}
