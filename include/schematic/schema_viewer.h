/*  -----------------------------------
 *  Project     : sapience
 *  File        : schema_viewer.h
 *  Date        : 18.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef SCHEMA_VIEWER_H
#define SCHEMA_VIEWER_H

#define SCENE_XS    10000
#define SCENE_YS    10000
#define WHEEL_DELTA 100.0
#define WHEEL_EXP   1.25

#define ZOOM_INIT   1.00
#define ZOOM_MAX    4.00
#define ZOOM_MIN    0.20

//  QtWidgets module:
#include <QGraphicsView>
#include <QGridLayout>

//  Forward declaration of SchemaCanvas:
class SchemaCanvas;

//  Class SchemaViewer:
class SchemaViewer final : public QGraphicsView
{
	Q_OBJECT Q_DISABLE_COPY_MOVE(SchemaViewer)
	Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
	~SchemaViewer() override = default;
	explicit
	SchemaViewer(QWidget* parent = nullptr);

signals:
	void
	initialized(); //  Signal emitted upon constructor completion

protected slots:
	void
	wheelEvent(QWheelEvent*) override; //  Handle scrolling (zoom operation)
	void
	keyPressEvent(QKeyEvent*) override; //  Graph-level shortcut handler
	void
	keyReleaseEvent(QKeyEvent*) override; //  Graph-level shortcut handler

private:
	//  Default Attribute(s)
	struct
	{
		double zoom = ZOOM_INIT; //  Zoom factor, initialized to 1.0
		double zmax = ZOOM_MAX;  //  QWheelEvent ignored above ZOOM_MAX;
		double zmin = ZOOM_MIN;  //  QWheelEvent ignored below ZOOM_MIN;
	} m_attr;

	//  QGraphicsScene containing QGraphicsItems and other widgets
	struct
	{
		QRect         sceneBoundary;     //  Boundary of the scene (in pixels)
		SchemaCanvas* pointer = nullptr; //  Pointer to SchemaCanvas
		QGridLayout*  layout  = nullptr; //	 Grid layout added on top of the QGraphicsView
	} m_canvas;
};

#endif
