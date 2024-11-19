/*  -----------------------------------
 *  Project     : sapience
 *  File        : nodeControl.cpp
 *  Date        : 19.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#include "node/nodeControl.h"

nodeControl::nodeControl(qreal xpos, qreal ypos, const QString& title, QItemG* parent) :
//  Initialize base-class constructor:
    QGraphicsRectItem(parent),

//  Initialize rectangle attributes:
    attr(QPoint(xpos, ypos), QRect(0, 0, 300, 200), 15),

//  Initialize header attributes:
    header(QRect(0, 0, 400, 60), new QGraphicsRectItem(this), new QGraphicsTextItem(title, this))
{
//  Set rectangle for QGraphicsRectItem:
    setRect(attr.rect);

    auto brush = QBrush(Qt::white, Qt::SolidPattern);
    auto pen   = QPen(QBrush(Qt::black), 2.0, Qt::SolidLine);

//  Set brush and pen:
    setBrush(brush);
    setPen(pen);

//  Set appropriate flags:
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}

