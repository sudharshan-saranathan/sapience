/*  -----------------------------------
 *  Project     : sapiens
 *  File        : schemaCanvas.h
 *  Date        : 18.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef CANVAS_H
#define CANVAS_H

//  Include Qt Core Classes:
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

//  Include class schemaGrid:
#include "schematic/schemaGrid.h"

//  Include class nodeControl:
#include "node/nodeControl.h"

//  Forward declaration of QGraphicsView-Derived Class:
class viewer;

//  Main Class:
class schemaCanvas : public QGraphicsScene {

    Q_OBJECT
    Q_DISABLE_COPY_MOVE(schemaCanvas)
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
   ~schemaCanvas() override = default;
    schemaCanvas()          = default;
    explicit schemaCanvas(const QRect&, QObject* parent = nullptr);

protected:
    struct _attr_ {
        QRect rect;
        float dist;
    } attr;

signals:
    void initialized(void);

protected slots:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

public slots:
    static void createNode(QPointF, schemaCanvas*);
    static void deleteNode(schemaCanvas*);
    static void updateNode(schemaCanvas*);
};

#endif
