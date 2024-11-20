/*  -----------------------------------
 *  Project     : sapience
 *  File        : nodeControl.cpp
 *  Date        : 19.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

//  Include project hdrs:
    #include "node/nodeControl.h"

#include <QKeyEvent>
    #include <core/coreQSS.h>

//  Class constructor:
    nodeControl::nodeControl(const QPointF& cpos, const QString& name, QItemG* parent) :
    //  Initialize base-class constructor:
        QGraphicsRectItem{parent},
    //  Initialize rectangle attributes:
        attr{cpos, QRect(0, 0, 300, 200)},
    //  Initialize hdr attributes:
        hdr{QRect(0, 0, 296, 60), new QItemR(this), new QItemT(name, hdr.hdrptr)}
    {
    //  Set rectangle for QGraphicsRectItem:
        setPos (attr.cpos);
        setRect(attr.rect);
        setData(0, 0);

    //  Set object name (node, link, handle, ...)
        setObjectName(tr("NodeControl"));

    //  Set brush and pen:
        setBrush(QSSBrush::node);
        setPen(QSSPen::node);

    //  Set appropriate flags:
        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
    }

    nodeControl::nodeControl(const nodeControl& source) :
    //  Initialize base-class constructor:
        QGraphicsRectItem(source.parentItem()),
    //  Initialize rectangle attributes:
        attr{source.scenePos() + QPointF(20, 20), source.attr.rect},
    //  Initialize hdr attributes:
        hdr{
            source.hdr.rect,
            new QItemR(source.parentItem()),
            new QItemT("Node-Copy", this)
        }
    {
    //  Set rectangle for QGraphicsRectItem:
        setPos (attr.cpos);
        setRect(attr.rect);
        setData(0, 0);

    //  Set object name (node, link, handle, ...)
        setObjectName(tr("NodeControl"));

    //  Set brush and pen:
        setBrush(QSSBrush::node);
        setPen  (QSSPen::node);

    //  Set appropriate flags:
        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
    }

    void nodeControl::paint(QPainter* painter, const QSOGI* option, QWidget* widget) {
    //  Change border style for selected nodes:
        setPen(isSelected() ? QPen(Qt::red, 2.0) : QPen(Qt::black, 2.0));

    //  Call default paint-event handler:
        QItemR::paint(painter, option, widget);
    }
