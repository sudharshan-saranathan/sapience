/*  -----------------------------------
 *  Project     : sapiens
 *  File        : schemaCanvas.h
 *  Date        : 18.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef CANVAS_H
#define CANVAS_H

/*  QtWidgets module   */
#include <QGraphicsScene>

/*  Project header(s) */
#include "node/nodeCtrl.h"

/*  Forward declaration of class schemaViewer */
class schemaViewer;

/*  Class schemaCanvas  */
class schemaCanvas final : public QGraphicsScene {

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

    struct _list_ {
        QList<QGraphicsItem*> clipboard;
        QList<nodeCtrl*>    nodelist;
        QList<QString>         namelist;
    } list;

signals:
    void initialized();

protected slots:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public slots:
    void createNode(const QPointF&);
    void createNode(const nodeCtrl&);
    void deleteNode(nodeCtrl*);
};

#endif
