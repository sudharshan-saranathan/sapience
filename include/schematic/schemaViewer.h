/*  -----------------------------------
 *  Project     : sapiens
 *  File        : schemaViewer.h
 *  Date        : 18.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef SCHEMAVIEWER_H
#define SCHEMAVIEWER_H

#define SCENE_XS    25000
#define SCENE_YS    25000
#define WHEEL_DELTA 100.0
#define WHEEL_EXP   1.15

#define ZOOM_INIT   1.00
#define ZOOM_MAX    4.00
#define ZOOM_MIN    0.10

#define PANE_OPAC   0.90

//  QtWidgets module:
#include <QGraphicsView>

//  Forward declaration of schemaCanvas:
class schemaCanvas;

//  Class schemaViewer:
class schemaViewer final : public QGraphicsView {

    Q_OBJECT
    Q_DISABLE_COPY_MOVE(schemaViewer)
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
    ~schemaViewer() override = default;
    explicit schemaViewer(QWidget *parent = nullptr);

private:
    /*  Default attribute(s)    */
    struct _attr_ {
        QRect bound = QRect();                      //  Bounding rectangle for the graph region
        float zoom  = ZOOM_INIT;                    //  Zoom factor, initialized to 1.0
        float zmax  = ZOOM_MAX;                     //  QWheelEvent ignored above ZOOM_MAX;
        float zmin  = ZOOM_MIN;                     //  QWheelEvent ignored below ZOOM_MIN;
    } attr;

    /*  Main canvas where items are drawn   */
    struct _canvas_ {
        schemaCanvas* ptr;                          //  Pointer to schemaCanvas
    } canvas;

signals:
    void initialized();                             //  Signal emitted upon constructor completion

protected slots:
    void wheelEvent(QWheelEvent*) override;                 //  Handle scrolling (zoom operation)
    void mousePressEvent(QMouseEvent *event) override;      //  Empty function for printf() debugging
    void mouseReleaseEvent(QMouseEvent *event) override;    //  Empty function for printf() debugging
    void keyPressEvent(QKeyEvent*) override;                //  Graph-level shortcut handler
    void keyReleaseEvent(QKeyEvent*) override;              //  Graph-level shortcut handler
};

#endif
