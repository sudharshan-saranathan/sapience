/*  -----------------------------------
 *  Project     : sapiens
 *  File        : schemaViewer.h
 *  Date        : 18.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef SCHEMAVIEWER_H
#define SCHEMAVIEWER_H

#define SCENE_XS    10000
#define SCENE_YS    10000
#define WHEEL_DELTA 100
#define WHEEL_EXP   1.15

#define ZOOM_INIT   1.00
#define ZOOM_MAX    4.00
#define ZOOM_MIN    0.20

#define PANE_OPAC   0.90

/*  QtWidgets module  */
#include <QGraphicsView>

/*  Include project header  */
#include "schematic/schemaCanvas.h"

class schemaViewer final : public QGraphicsView {

    Q_OBJECT
    Q_DISABLE_COPY_MOVE(schemaViewer)
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
   ~schemaViewer() override = default;

    explicit schemaViewer(QWidget *parent = nullptr);

protected:
    struct _attr_ {
        double zoom = 1.0;
        double zmax = 4.0;
        double zmin = 0.20;
    } attr;

    struct _canvas_ {
        QRect bounds = QRect(0, 0, SCENE_XS, SCENE_YS);
        schemaCanvas *objptr = nullptr;
    } canvas;

signals:
    void initialized();

protected slots:
    void wheelEvent(QWheelEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;
};

#endif
