/*  -----------------------------------
 *  Project     : sapience
 *  File        : nodeControl.cpp
 *  Date        : 19.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

//  Include Qt Core Module:
    #include <QKeyEvent>

//  Include project hdrs:
    #include "node/nodeControl.h"
    #include "core/coreQSS.h"

//  Class constructor:
    nodeControl::nodeControl(const QPointF& cpos, const QString& name, QItemG* parent) :
    //  Initialize base-class constructor:
        QGraphicsRectItem{parent},
    //  Initialize rectangle attributes:
        attr{cpos, QRect(0, 0, 300, 200)},
    //  Initialize hdr attributes:
        hdr{QRect(2, 2, 296, 33), new QItemR(this), new QItemT(name, hdr.hdrptr)},
    //  Initialize QLineEdit object:
        prompt{new QGraphicsProxyWidget(this), new QLineEdit}
    {
    //  Set rectangle for QGraphicsRectItem:
        setPos (attr.cpos);
        setRect(attr.rect);

    //  Set object name (node, link, handle, ...)
        setObjectName(tr("NodeControl"));

    //  Set brush and pen:
        setBrush(QSSBrush::node);
        setPen(QSSPen::node);

    //  Set appropriate flags:
        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);

    //  Customize header appearance:
        hdr.hdrptr->setBrush(QBrush(QSSRGB::moonstone, Qt::SolidPattern));
        hdr.hdrptr->setPen  (QPen  (QSSRGB::moonstone, Qt::SolidLine));
        hdr.hdrptr->setRect (hdr.rect);

    //  Customize QLineEdit:
        prompt.objptr->setFixedSize(296, 28);
        prompt.objptr->setPlaceholderText("Enter cmd or type 'help'");

    //  Initialize QGraphicsProxyWidget:
        prompt.proxy->setWidget(prompt.objptr);
        prompt.proxy->setPos(2, 200 - 30);

    //  Customize node title:
        hdr.txtptr->setTextWidth(80);
        hdr.txtptr->setPos(110, 6);
        hdr.txtptr->setTextInteractionFlags(Qt::TextEditorInteraction);
        hdr.txtptr->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter));

    //  Connect QLineEdit to event-handler:
        QObject::connect(prompt.objptr, &QLineEdit::returnPressed, this, [this](){handlePrompt();});
    }

    nodeControl::nodeControl(const nodeControl& source) :
    //  Initialize base-class constructor:
        QGraphicsRectItem(source.parentItem()),
    //  Initialize rectangle attributes:
        attr{source.scenePos() + QPointF(20, 20), source.attr.rect},
    //  Initialize hdr attributes:
        hdr{
            source.hdr.rect,
            new QItemR(this),
            new QItemT("Node-Copy", hdr.hdrptr)
        },
    //  Initialize QLineEdit object:
        prompt{new QGraphicsProxyWidget(this), new QLineEdit}
    {
    //  Set rectangle for QGraphicsRectItem:
        setPos (attr.cpos);
        setRect(attr.rect);

    //  Set object name (node, link, handle, ...)
        setObjectName(tr("NodeControl"));

    //  Set brush and pen:
        setBrush(QSSBrush::node);
        setPen(QSSPen::node);

    //  Set appropriate flags:
        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);

    //  Customize header appearance:
        hdr.hdrptr->setBrush(QBrush(QSSRGB::moonstone, Qt::SolidPattern));
        hdr.hdrptr->setPen  (QPen  (QSSRGB::moonstone, Qt::SolidLine));
        hdr.hdrptr->setRect (hdr.rect);

    //  Customize QLineEdit:
        prompt.objptr->setFixedSize(296, 28);
        prompt.objptr->setPlaceholderText("Enter cmds or type 'help'");

    //  Initialize QGraphicsProxyWidget:
        prompt.proxy->setWidget(prompt.objptr);
        prompt.proxy->setPos(2, 200 - 30);

    //  Customize node title:
        hdr.txtptr->setTextWidth(80);
        hdr.txtptr->setPos(110, 6);
        hdr.txtptr->setTextInteractionFlags(Qt::TextEditorInteraction);
        hdr.txtptr->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter));

    //  Connect QLineEdit to event-handler:
        auto connection = QObject::connect(prompt.objptr, &QLineEdit::returnPressed, this, [this](){handlePrompt();});
    }

    void nodeControl::handlePrompt() const {
        prompt.objptr->clear();
    }

    void nodeControl::paint(QPainter* painter, const QSOGI* option, QWidget* widget) {
    //  Change border style for selected nodes:
        setPen(isSelected() ? QPen(Qt::red, 2.0) : QPen(Qt::black, 2.0));

    //  Call default paint-event handler:
        QItemR::paint(painter, option, widget);
    }
