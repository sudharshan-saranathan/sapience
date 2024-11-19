#ifndef QICONB_H
#define QICONB_H

#include "core/qFunc.h"
#include "core/qInclude.h"

class qIconB : public QObject, public QItemP {

    Q_OBJECT
    Q_DISABLE_COPY_MOVE(qIconB)

public:
   ~qIconB() = default;
    qIconB(QString, QItemG* parent = nullptr);

    struct attr {
        uint_t  height;
        uint_t  width;
        QSize   size;
        QPixmap pixm;
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
