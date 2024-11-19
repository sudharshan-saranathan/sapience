#ifndef QSVGB_H
#define QSVGB_H

#include "core/qFunc.h"
#include "core/qInclude.h"

class qSvgB : public QItemS {

    Q_OBJECT
    Q_DISABLE_COPY_MOVE(qSvgB)

public:
   ~qSvgB() = default;
    qSvgB(QString, QItemG* parent = nullptr);

    struct attr {
        QString file;
        uint_t  height;
        uint_t  width;
        QSize   size;
    } attr;

signals:
    void lclicked(void);
    void rclicked(void);
    void mclicked(void);

protected:
    virtual void hoverEnterEvent  (QGraphicsSceneHoverEvent*);
    virtual void hoverLeaveEvent  (QGraphicsSceneHoverEvent*);
    virtual void mousePressEvent  (QGraphicsSceneMouseEvent*);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

};

#endif
