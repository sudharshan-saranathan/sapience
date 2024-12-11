//
// Created by Sudharshan Saranathan on 21/11/24.
//

#include "node/node_svg.h"

NodeSVG::NodeSVG(const QString &filename, const QSize &size, const bool translate, q_item *parent) :

    /*  Initializer list    */
    //  Base-class constructor:
    QGraphicsSvgItem{
        filename,
        parent
    },
    //  struct _attr_:
    m_attr{
        filename,
        size,
        0.0
    },
    //  struct _renderer_:
    m_renderer{new QSvgRenderer, QString(), true}

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
    m_attr.scale = m_attr.size.width() / QGraphicsSvgItem::boundingRect().width();
    setScale(m_attr.scale);

    m_renderer.pointer->load(m_attr.file);
    setSharedRenderer(m_renderer.pointer);
}

void NodeSVG::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    //  Reduce opacity on hover-enter:
    setOpacity(0.50);

    //  Resolve event handlers of nested item(s):
    QGraphicsSvgItem::hoverEnterEvent(event);
}

void NodeSVG::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    //  Resolve event handlers of nested item(s) first, if any:
    QGraphicsSvgItem::hoverLeaveEvent(event);

    //  Restore opacity on hover-leave:
    setOpacity(1.0);
}

/*  Event-handler for unprocessed mouse clicks  */
void NodeSVG::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    //  Magnify the icon on mouse clicks:
    setScale(m_attr.scale * 1.1);

    /*  Switch-case block   */
    switch(event->button()) {
        //  Notify parent(s) on click through signal:
        case Qt::LeftButton: {
            if (!m_renderer.toggleOffFile.isEmpty()) {
                m_renderer.toggleOn = !m_renderer.toggleOn;
                m_renderer.pointer->load(m_renderer.toggleOn ? m_attr.file : m_renderer.toggleOffFile);
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

void NodeSVG::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    //  De-magnify the icon:
    setScale(m_attr.scale);

    //  Accept the event:
    event->accept();
}
