/*  -----------------------------------
 *  Project     : sapience
 *  File        : nodeControl.cpp
 *  Date        : 19.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

/*  QtCore module   */
#include <QKeyEvent>

/*  Include project headers */
#include "node/nodeControl.h"
#include "core/coreQSS.h"
#include "schematic/schemaCanvas.h"

/*  Class constructor   */
nodeControl::nodeControl(const QPointF &cpos, const QString &name, const GITEM_ type, QItemG *parent) :

    /*  Base-class constructor  */
    QItemR{parent},

    /*  Default attributes  */
    attr{cpos, QRect(0, 0, 300, 200), type},

    /*  Header attributes   */
    hdr{
        QRect(2, 2, 296, 33),
        new QItemR(this),
        new QItemT(name, hdr.hdrptr)
    },

    /*  Initialize SVG buttons  */
    svg{
        new svgButton(":/icons/circle-down.svg", hdr.hdrptr),
        new svgButton(":/icons/circle-up.svg", hdr.hdrptr),
        new svgButton(":/icons/var.par.svg", hdr.hdrptr),
        new svgButton(":/icons/node.close.svg", hdr.hdrptr)
    },

    /*  Initialize QLineEdit attributes */
    prompt{new QGraphicsProxyWidget(this), new QLineEdit} {
    /*  Call initializer    */
    init();
}

/*  Class copy-constructor  */
nodeControl::nodeControl(const nodeControl &source) :

    /*  Initialize base-class constructor   */
    QItemR(source.parentItem()),

    /*  Initialize default attributes   */
    attr{source.scenePos() + QPointF(20, 20), source.attr.rect, source.attr.type},

    /*  Initialize header and attributes    */
    hdr{
        source.hdr.rect,
        new QItemR(this),
        new QItemT("Node-Copy", hdr.hdrptr)
    },

    /*  Initialize SVG icons    */
    svg{
        new svgButton(":/icons/circle-down.svg", hdr.hdrptr),
        new svgButton(":/icons/circle-up.svg", hdr.hdrptr),
        new svgButton(":/icons/var.par.svg", hdr.hdrptr),
        new svgButton(":/icons/node.close.svg", hdr.hdrptr)
    },

    /*  Initialize  command-prompt and attributes   */
    prompt{new QGraphicsProxyWidget(this), new QLineEdit}

/*  Copy-constructor body begin  */
{
    /*  Call initializer    */
    init();
}

/*  Initializer */
void nodeControl::init() {
    /*  Set object name for internal reference  */
    /*  Do not delete this                      */
    setObjectName(tr("NodeControl"));

    /*  Set size, position, brush, and pen  */
    setRect(attr.rect);
    setPos(attr.cpos);
    setPen(QSSPen::node);
    setBrush(QSSBrush::node);

    /*  Customize flags */
    setFlags(QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemIsFocusable |
             QGraphicsItem::ItemSendsGeometryChanges |
             QGraphicsItem::ItemSendsScenePositionChanges);

    /*  Customize header    */
    hdr.hdrptr->setBrush(QBrush(QSSRGB::moonstone, Qt::SolidPattern));
    hdr.hdrptr->setPen(QPen(QBrush(Qt::white), 0.2, Qt::SolidLine));
    hdr.hdrptr->setRect(hdr.rect);

    /*  Customize command-prompt    */
    prompt.objptr->setFixedSize(296, 28);
    prompt.objptr->setPlaceholderText("Enter cmd or type 'help'");

    /*  Initialize QGraphicsProxyWidget  */
    prompt.proxy->setWidget(prompt.objptr);
    prompt.proxy->setPos(2, 200 - 30);

    /*  Customize title attributes    */
    hdr.txtptr->setTextWidth(80);
    hdr.txtptr->setPos(110, 6);
    hdr.txtptr->setTextInteractionFlags(Qt::TextEditorInteraction);
    hdr.txtptr->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter));

    /*  Arrange SVG buttons */
    svg.addInp->setPos(15, 10);
    svg.addOut->setPos(50, 10);
    svg.addPar->setPos(229, 10);
    svg.delNode->setPos(269, 10);

    /*  Connect command-prompt to event-handler */
    auto connection = QObject::connect(prompt.objptr, &QLineEdit::returnPressed, this, [this]() { handlePrompt(); });

    /*  Initialization complete */
    emit initialized();
}

/*  Event-handler for command-prompt    */
void nodeControl::handlePrompt() const {
    prompt.objptr->clear();
}

/*  QGraphicsRectItem::paint() method (overridden)
 *  In this function, the border colour of selected node(s)
 *  has been changed to RED */
void nodeControl::paint(QPainter *painter, const QSOGI *option, QWidget *widget) {
    /*  If the node is selected, change border colour to red    */
    setPen(isSelected() ? QPen(Qt::red, 2.0) : QPen(Qt::black, 2.0));

    /*  Propagate event to default handler  */
    QItemR::paint(painter, option, widget);
}

/*  QGraphicsRectItem::itemChange() method (overridden)
 *  In this function, the itemChange() method is modified to emit
 *  signals which are then caught by <schemaCanvas> to redraw the
 *  connections between nodes   */
QVariant nodeControl::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    /*  Switch-case block   */
    switch (change) {
        /*  Filter QGraphicsItem::ItemScenePositionHasChanged   */
        case QGraphicsItem::ItemScenePositionHasChanged: {
            emit updateLink();
            qInfo() << "itemScenePositionHasChanged" << value;
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
