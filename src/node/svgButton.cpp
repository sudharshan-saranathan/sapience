//
// Created by Sudharshan Saranathan on 21/11/24.
//

#include "node/svgButton.h"

svgButton::svgButton(const QString &filename, QItemG *parent) :
    /*  Initialize base-class constructor*/
    QGraphicsSvgItem{filename, parent},

    /*  Default attributes    */
    attr{filename, 16, 16, QSize(attr.ws, attr.hs)} {
    /*  Rescale the SVG */
    setAcceptHoverEvents(true);
    setScale(static_cast<double>(attr.ws) / QGraphicsSvgItem::boundingRect().width());
}

void svgButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    QGraphicsSvgItem::hoverEnterEvent(event);

    setOpacity(0.50);
    qInfo() << "hoverEnterEvent";
}

void svgButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QGraphicsSvgItem::hoverLeaveEvent(event);

    setOpacity(1.0);
    qInfo() << "hoverLeaveEvent";
}

void svgButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsSvgItem::mousePressEvent(event);
}

void svgButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsSvgItem::mouseReleaseEvent(event);
}
