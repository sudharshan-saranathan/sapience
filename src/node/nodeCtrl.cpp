/*  -----------------------------------
 *  Project     : sapience
 *  File        : nodeCtrl.cpp
 *  Date        : 19.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

/*  QtCore module   */
#include <QKeyEvent>

/*  Include project headers */
#include "node/nodeCtrl.h"
#include "core/coreQSS.h"
#include "schematic/schemaCanvas.h"

/*  Class constructor   */
nodeCtrl::nodeCtrl(const QPointF &cpos, const QString &name) :
    /*  Default attributes  */
    attr{cpos, QRect(0, 0, NODE_WS, NODE_HS), ITEMTYPE::NODE},
    /*  Header attributes   */
    hdr{QRect(2, 2, 296, 33), new QItemR(this), new QItemT(name)},
/*  Initialize SVG buttons  */
    svg{
        new svgButton(":/icons/circle-down.svg", hdr.hdrPtr),
        new svgButton(":/icons/circle-up.svg", hdr.hdrPtr),
        new svgButton(":/icons/gear-solid.svg", hdr.hdrPtr),
        new svgButton(":/icons/node.close.svg", hdr.hdrPtr)
    },
/*  Initialize QLineEdit attributes */
    prompt{new QGraphicsProxyWidget(this), new QLineEdit},
    /*  Initialize empty lists  */
    list{
        QList<nodeVar *>{},
        QList<nodeVar *>{},
        QList<nodeVar *>{}
    }
/*  Constructor body begin  */
{
    /*  Call initializer    */
    init();
}

/*  Class copy-constructor  */
nodeCtrl::nodeCtrl(const nodeCtrl &source) :
/*  Initialize default attributes   */
attr{source.scenePos() + QPointF(10, 10), source.attr.bounds, ITEMTYPE::NODE},
/*  Initialize header and attributes    */
hdr{
    source.hdr.rect,
    new QItemR(this),
    new QItemT("Node-Copy")
},
/*  Initialize SVG icons    */
svg{
    new svgButton(":/icons/circle-down.svg", hdr.hdrPtr),
    new svgButton(":/icons/circle-up.svg", hdr.hdrPtr),
    new svgButton(":/icons/gear-solid.svg", hdr.hdrPtr),
    new svgButton(":/icons/node.close.svg", hdr.hdrPtr)
},
/*  Initialize  command-prompt and attributes   */
    prompt{new QGraphicsProxyWidget(this), new QLineEdit}
/*  Copy-constructor body begin  */
{
    /*  Call initializer    */
    init();

    /*  Copy input variables */
    for (auto j: source.list.input) {
        addStream(j->getName(), VARTYPE::INPUT);
    }

    /*  Copy output variables */
    for (auto j: source.list.output) {
        addStream(j->getName(), VARTYPE::OUTPUT);
    }

    /*  Copy parameters */
    for (auto j: source.list.params) {
        addStream(j->getName(), VARTYPE::PARAMETER);
    }
}

/*  Initializer */
void nodeCtrl::init()
{
    /*  Set object name for internal reference  */
    setObjectName(tr("nodeCtrl"));

    /*  Set size, position, brush, and pen  */
    setRect(attr.bounds);
    setPos(attr.origin);
    setPen(QSSPen::node);
    setBrush(QSSBrush::node);

    /*  Customize flags */
    setFlags(QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemIsFocusable |
             QGraphicsItem::ItemSendsGeometryChanges |
             QGraphicsItem::ItemSendsScenePositionChanges);

    /*  Customize header    */
    hdr.hdrPtr->setBrush(QBrush(QSSRGB::moonstone, Qt::SolidPattern));
    hdr.hdrPtr->setPen(QPen(QBrush(Qt::white), 0.2, Qt::SolidLine));
    hdr.hdrPtr->setRect(hdr.rect);
    hdr.txtPtr->setParentItem(hdr.hdrPtr);

    /*  Customize command-prompt    */
    prompt.objptr->setFixedSize(296, 28);
    prompt.objptr->setPlaceholderText("Enter cmd or type 'help'");

    /*  Initialize QGraphicsProxyWidget  */
    prompt.proxy->setWidget(prompt.objptr);
    prompt.proxy->setPos(2, rect().bottom() - 30);

    /*  Customize title attributes    */
    hdr.txtPtr->setTextWidth(80);
    hdr.txtPtr->setPos(110, 6);
    hdr.txtPtr->setTextInteractionFlags(Qt::TextEditorInteraction);
    hdr.txtPtr->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter));

    /*  Arrange SVG buttons */
    svg.addInp->setPos(10, 10);
    svg.addOut->setPos(40, 10);
    svg.addPar->setPos(244, 10);
    svg.delNode->setPos(274, 10);

    /*  Connect command-prompt to event-handler */
    auto c1 = QObject::connect(prompt.objptr, &QLineEdit::returnPressed, this, [this]() { handlePrompt(); });
    auto c2 = QObject::connect(svg.addInp, &svgButton::leftClicked, this,
                               [this]() { addStream(QString("Variable"), VARTYPE::INPUT); });
    auto c3 = QObject::connect(svg.addOut, &svgButton::leftClicked, this,
                               [this]() { addStream(QString("Variable"), VARTYPE::OUTPUT); });
    auto c4 = QObject::connect(svg.delNode, &svgButton::leftClicked, this, [this]() { emit nodeDeleted(); });


    /*  Initialization complete */
    emit initialized();
}

/*  Event-handler for command-prompt    */
void nodeCtrl::handlePrompt() const {
    prompt.objptr->clear();
}

void nodeCtrl::addStream(QString name, const VARTYPE type) {
    Q_UNUSED(type)

    /*  Set default parameters  */
    QList<nodeVar*>& lst = (type == VARTYPE::INPUT
                                ? list.input
                                : (type == VARTYPE::OUTPUT ? list.output : list.params));
    const auto offsetPos = (type == VARTYPE::INPUT ? 10 : (type == VARTYPE::OUTPUT ? 286 : 0));

    /*  Create a new variable   */
    lst.append(new nodeVar(name, type, this));

    /*  Get the maximum size    */
    if (const auto max = qMax(list.input.size(), list.output.size()); max >= 4) {
        setRect(QRect(0, 0, attr.bounds.width(), attr.bounds.height() + (max - 3) * 40));
        prompt.proxy->setPos(2, rect().bottom() - 30);
    }

    /*  Set position of variable    */
    lst.last()->setPos(offsetPos, 20 + lst.size() * 40);
}

/*  QGraphicsRectItem::paint() method (overridden)
 *  In this function, the border colour of selected node(s)
 *  has been changed to RED */
void nodeCtrl::paint(QPainter* painter, const QSOGI *option, QWidget *widget) {
    /*  If the node is selected, change border colour to red    */
    setPen(isSelected() ? QPen(Qt::red, 2.0) : QPen(Qt::black, 2.0));

    /*  Propagate event to default handler  */
    QItemR::paint(painter, option, widget);
}

/*  QGraphicsRectItem::itemChange() method (overridden)
 *  In this function, the itemChange() method is modified to emit
 *  signals which are then caught by <schemaCanvas> to redraw the
 *  connections between nodes   */
QVariant nodeCtrl::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    /*  Switch-case block   */
    switch (change) {
        /*  Filter QGraphicsItem::ItemScenePositionHasChanged   */
        case QGraphicsItem::ItemScenePositionHasChanged: {
            emit nodeChanged();
            break;
        }
        /*  Default */
        default:
            break;
    }
    /*  Propagate event to base-class handler and return value  */
    QGraphicsRectItem::itemChange(change, value);
    return (value);
}
