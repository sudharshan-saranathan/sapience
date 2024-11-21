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
}

void svgButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QGraphicsSvgItem::hoverLeaveEvent(event);

    setOpacity(1.0);
}

void svgButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsSvgItem::mousePressEvent(event);

    /*  Switch-case block to handle mouse-press */
    switch(event->button()) {
        /*  Filter left clicks  */
        case Qt::LeftButton: {
            emit leftClicked();
            event->accept();
            break;
        }
        /*  Filter middle clicks  */
        case Qt::MiddleButton: {
            emit middleClicked();
            event->accept();
            break;
        }
        /*  Filter right clicks  */
        case Qt::RightButton: {
            emit rightClicked();
            event->accept();
            break;
        }
        /*  Default case  */
        default:
            event->ignore();
            break;
    }
}

void svgButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsSvgItem::mouseReleaseEvent(event);
}
