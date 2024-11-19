/*  -----------------------------------
 *  Project     : sapience
 *  File        : nodeControl.h
 *  Date        : 19.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef NODECTRL_H
#define NODECTRL_H

//  Include Qt Core Classes:
#include <QRect>
#include <QPen>
#include <QBrush>
#include <QObject>
#include <QString>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

//  Convenience typedefs:
using uint_t = unsigned int;
using QItemG = QGraphicsItem;
using QItemR = QGraphicsRectItem;
using QItemT = QGraphicsTextItem;

class nodeControl : public QObject, public QItemR {

    Q_OBJECT
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
   ~nodeControl() = default;
    nodeControl() = delete;
    nodeControl(qreal, qreal, const QString&, QItemG* parent = nullptr);

private:
    struct _attr_ {
        QPoint cpos;
        QRect  rect;
        uint_t space;
    } attr;

    struct header {
        QRect   rect;
        QItemR* item;
        QItemT* title;
    } header;

};

#endif
