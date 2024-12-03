//
// Created by Sudharshan Saranathan on 21/11/24.
//

#include "node/nodeSVG.h"

nodeSVG::nodeSVG(const QString &filename, const QSize &size, const bool translate, QItemG *parent) :

    /*  Initializer list    */
    //  Base-class constructor:
    QGraphicsSvgItem{
        filename,
        parent
    },
    //  struct _attr_:
    attr{
        filename,
        size,
        0.0
    },
    //  struct _renderer_:
    renderer{new QSvgRenderer, QString(), true}

//  ------------------------
//  Constructor (body) begin
{
    /*  Accept hover events (required for changing opacity when mouse
     *  hovers on the icon), set transformation point to icon center
     *  and translate to parent-origin. Do not delete or modify.  */
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);

    //  If translate is set to true, shift the SVG to its rectangle center:
    if (translate) {
        setTransformOriginPoint(QGraphicsSvgItem::boundingRect().center());
        setPos(-QGraphicsSvgItem::boundingRect().width() / 2.0, -QGraphicsSvgItem::boundingRect().height() / 2.0);
    }

    //  Resize icon and store the current scale:
    attr.scale = attr.size.width() / QGraphicsSvgItem::boundingRect().width();
    setScale(attr.scale);

    renderer.pointer->load(attr.file);
    setSharedRenderer(renderer.pointer);
}

void nodeSVG::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    //  Reduce opacity on hover-enter:
    setOpacity(0.50);

    //  Resolve event handlers of nested item(s):
    QGraphicsSvgItem::hoverEnterEvent(event);
}

void nodeSVG::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    //  Resolve event handlers of nested item(s) first, if any:
    QGraphicsSvgItem::hoverLeaveEvent(event);

    //  Restore opacity on hover-leave:
    setOpacity(1.0);
}

/*  Event-handler for unprocessed mouse clicks  */
void nodeSVG::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    //  Magnify the icon on mouse clicks:
    setScale(attr.scale * 1.1);

    /*  Switch-case block   */
    switch(event->button()) {
        //  Notify parent(s) on click through signal:
        case Qt::LeftButton: {
            if (!renderer.toggleOffFile.isEmpty()) {
                renderer.toggleOn = !renderer.toggleOn;
                renderer.pointer->load(renderer.toggleOn ? attr.file : renderer.toggleOffFile);
                update();
            }

            emit leftClicked();
            event->accept();
            break;
        }
        /*  Default case  */
        default:
            break;
    }

    //  Accept the event:
    event->accept();
}

void nodeSVG::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    //  De-magnify the icon:
    setScale(attr.scale);

    //  Accept the event:
    event->accept();
}
