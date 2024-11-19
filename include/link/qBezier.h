#ifndef QBEZIER_H
#define QBEZIER_H

#include "core/qFunc.h"
#include "core/qInclude.h"

using QPath = QPainterPath;

typedef class qBezier : public QObject, public QPathG, public qDesign {

    Q_OBJECT

public:
   ~qBezier() = default;
    qBezier(QItemG* parent = nullptr);
    qBezier(QPointF, QPointF, QItemG* parent = nullptr);

protected:
    struct attr {
        QPath path;
    } attr;

public:
    void clear();
    void link (QPointF, QPointF);

protected slots:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent*);

} qBzr;

#endif
