//
// Created by Sudharshan Saranathan on 21/11/24.
//

#include "node/nodeVar.h"

/*  Class constructor  */
nodeVar::nodeVar(const QString &name, VARITEM_ type, QGraphicsItem *parent) :
    /*  Initialize base-class constructor   */
    QGraphicsEllipseItem{parent},

    /*  Default attributes  */
    attr{type, QRect(0, 0, 4, 4)} {
    /*  Customize appearance    */
    setBrush(QSSBrush::handle);
    setPen(QSSPen::handle);

    /*  Customize rectangle dimensions and behaviour  */
    setRect(attr.rect);
    setTransformOriginPoint(attr.rect.width() / 2, attr.rect.height() / 2);
}
