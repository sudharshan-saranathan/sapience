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

	//  Adjust factor if scrolling exceeds zoom limits:
	if (scroll > 0 && attr.zoom * factor >= attr.zmax)      //  If zoom exceeds ZOOM_MAX,
		factor = attr.zmax / attr.zoom;                     //  clip zoom to maximum value.
	else if (scroll < 0 && attr.zoom * factor <= attr.zmin) //  If zoom exceeds ZOOM_MIN,
		factor = attr.zmin / attr.zoom;                     //  clip zoom to minimum value.

	attr.zoom *= factor;   //  Store new zoom factor
	scale(factor, factor); //  Execute zoom operation
}

void
schemaViewer::mousePressEvent(QMouseEvent* event) {
	//  qDebug() << "schemaViewer::mousePressEvent()";
	QGraphicsView::mousePressEvent(event);
}

void
schemaViewer::mouseReleaseEvent(QMouseEvent* event) {
	/*  Resolve event-handlers of schemaCanvas and its children first   */
	QGraphicsView::mouseReleaseEvent(event);
}

void
schemaViewer::keyPressEvent(QKeyEvent* event) {

	/*  Switch to RubberBandDrag (for selecting multiple items) when the Control
	 *  key is pressed. Only switch when there are no graphics items below the
	 *  cursor position. */
	if (event->modifiers() == Qt::ShiftModifier && //  Check if <control> (<cmd> on MacOS) key is pressed
		!itemAt(mapFromGlobal(QCursor::pos())))    //  Verify that there are no graphics items below the cursor
	{
		setDragMode(RubberBandDrag); //  Switch to RubberBandDrag mode
		setCursor(Qt::CrossCursor);  //  Indicate RubberBandDrag mode with cross-cursor
		event->accept();             //  Accept event
	}
	else
		QGraphicsView::keyPressEvent(event); //  Propagate event downstream
}

void
schemaViewer::keyReleaseEvent(QKeyEvent* event) {
	//  Reset to default drag mode and cursor:
	unsetCursor();
	setDragMode(ScrollHandDrag);

	//  Propagate event downstream:
	QGraphicsView::keyPressEvent(event);
}
