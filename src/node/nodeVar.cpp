//
// Created by Sudharshan Saranathan on 21/11/24.
//

#include "node/nodeVar.h"

/*  Class constructor  */
nodeVar::nodeVar(const QString &name, VARTYPE type, QGraphicsItem *parent) :
/*  Initialize base-class constructor   */
    QGraphicsEllipseItem{parent},
/*  Default attributes  */
    attr{name, type, QRect(0, 0, 4, 4)}
/*  Constructor body-begin  */
{
    /*  Customize appearance    */
    setBrush(QBrush(QSSRGB::spaceCadet, Qt::SolidPattern));
    setPen  (QPen(QSSRGB::spaceCadet));

    /*  Customize rectangle dimensions and behaviour  */
    setRect(attr.rect);
    setTransformOriginPoint(static_cast<qreal>(attr.rect.width())/2.0, static_cast<qreal>(attr.rect.height())/2.0);
}