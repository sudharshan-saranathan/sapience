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

//  Include Qt Core Classes:
#include <QKeyEvent>
#include <QGraphicsView>

//  Include QGraphicsScene:
#include "schematic/schemaCanvas.h"

class schemaViewer final : public QGraphicsView {

    Q_OBJECT
    Q_DISABLE_COPY_MOVE(schemaViewer)
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
   ~schemaViewer() override = default;
    schemaViewer(QWidget* parent = nullptr);

protected:
    struct _attr_ {
        double zoom;
        double zmax;
        double zmin;
    } attr;

    struct _canvas_ {
        QRect canvasBounds;
        schemaCanvas *item;
    } canvas;

signals:
    void initialized();

protected slots:
    void wheelEvent(QWheelEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;
};

#endif
