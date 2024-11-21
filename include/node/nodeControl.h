/*  -----------------------------------
 *  Project     : sapience
 *  File        : nodeControl.h
 *  Date        : 19.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef NODECTRL_H
#define NODECTRL_H

/*  Default defines */
#define NODE_WS 300
#define NODE_HS 200
#define HDR_WS  300
#define HDR_HS  200

/*  QtCore module   */
#include <QPen>
#include <QRect>
#include <QBrush>
#include <QPointF>
#include <QString>
#include <QPainter>
#include <QLineEdit>

/*  QtGui module    */
#include <QGraphicsItem>
#include <QGraphicsSvgItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsProxyWidget>

/*  Include project headers */
#include "svgButton.h"
#include "nodeVar.h"

//  Convenience typedefs:
using uint_t = unsigned int;
using QItemG = QGraphicsItem;
using QItemR = QGraphicsRectItem;
using QItemT = QGraphicsTextItem;
using QItemS = QGraphicsSvgItem;
using QSOGI = QStyleOptionGraphicsItem;
using QProxy = QGraphicsProxyWidget;
using QEditL = QLineEdit;

//  Forward declaration of enum class:
enum class GITEM_;

//  Class header:
class nodeControl final : public QObject, public QItemR {
    Q_OBJECT
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
    ~nodeControl() override = default;

    nodeControl() = delete;

    nodeControl(const nodeControl &);

    nodeControl(const QPointF &, const QString &, GITEM_, QItemG *parent = nullptr);

private:
    /*  Node attributes */
    struct _attr_ {
        QPointF cpos;
        QRect rect;
        GITEM_ type;
    } attr;

    /*  Header attributes   */
    struct _hdr_ {
        QRect rect;
        QItemR *hdrptr;
        QItemT *txtptr;
    } hdr;

    /*  SVG icon-buttons */
    struct _svg_ {
        svgButton *addInp;
        svgButton *addOut;
        svgButton *addPar;
        svgButton *delNode;
    } svg;

    /*  Command-prompt  */
    struct _prompt_ {
        QProxy *proxy;
        QEditL *objptr;
    } prompt;

    /*  Lists to store node-variables   */
    struct _list_ {
        QList<nodeVar *> input;
        QList<nodeVar *> output;
        QList<nodeVar *> parameter;
    } list;

signals:
    void initialized(); //  Constructor emits this signal
    void nodeMoved(); //  Signal is emitted when node is moved around

protected slots:
    void handlePrompt() const;
    void paint(QPainter *, const QSOGI *, QWidget *) override;
    QVariant itemChange(QGraphicsItem::GraphicsItemChange, const QVariant &) override;

public slots:
    void addStream(VARITEM_);

public:
    [[nodiscard]] QString getName() const { return (hdr.txtptr->toPlainText()); }
    [[nodiscard]] GITEM_ getType() const { return (attr.type); }

private:
    void init();
};

#endif
