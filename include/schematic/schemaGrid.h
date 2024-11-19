/*  -----------------------------------
 *  Project     : sapiens
 *  File        : viewer.h
 *  Date        : 18.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef SCHEMAGRID_H
#define SCHEMAGRID_H

//  Include Qt Core Classes:
#include <QGraphicsItemGroup>
#include <QGraphicsEllipseItem>

//  Include Qt Styling Header:
#include "core/coreQSS.h"

//  Convenience typedefs:
using uint_t = unsigned int;
using QGroup = QGraphicsItemGroup;
using QItemG = QGraphicsItem;
using QItemE = QGraphicsEllipseItem;

class schemaGrid final : public QGroup {
public:
   ~schemaGrid() override = default;
    schemaGrid()          = default;
    schemaGrid(QRect, QItemG* parent = nullptr);

private:
    struct _group_ {
        QRect  rect;
        uint_t space;
    } group;

    struct _point_ {
        QItemE *item;
        double  size;
    } point;

public:
    QRect  rect   () { return(group.rect); }
    uint_t spacing() { return(group.space);}
};

#endif
