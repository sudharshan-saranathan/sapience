//
// Created by Sudharshan Saranathan on 18/11/24.
//

#include "schematic/schemaGrid.h"

schemaGrid::schemaGrid(QRect rect, QItemG* parent) :
/*  Initialize base-class constructor   */
    QGroup(parent),
/*  Initialize QGraphicsItemGroup   */
    group(rect, 50),
/*  Initialize grid point attributes    */
    point(nullptr, 1.0)
{
//  Create QGraphicsEllipseItem objects and add to group:
    for(int x = rect.left(); x <= rect.right(); x += static_cast<int>(group.space)){
        for(int y = rect.top(); y <= rect.bottom(); y += static_cast<int>(group.space)){
            point.item = new QItemE(x-1, y-1, point.size, point.size);
            point.item->setBrush(QSSBrush::circle);
            point.item->setPen  (QSSPen::circle);
            addToGroup(point.item);
        }
    }
}