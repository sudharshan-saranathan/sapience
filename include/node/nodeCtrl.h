/*  -----------------------------------
 *  Project     : sapience
 *  File        : nodeCtrl.h
 *  Date        : 19.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef NODECTRL_H
#define NODECTRL_H

/*  Default defines */
#define NODE_WS 300
#define NODE_HS 200
#define HDR_WS  296
#define HDR_HS  28

/*  QtCore module   */
#include <QRect>
#include <QPointF>
#include <QString>
#include <QPainter>
#include <QLineEdit>

/*  QtGui module    */
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
enum class ITEMTYPE;

//  Class header:
class nodeCtrl final : public QObject, public QItemR {
    Q_OBJECT
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
    ~nodeCtrl() override = default;
    nodeCtrl()           = delete;
    nodeCtrl(const QPointF&, const QString&);
    nodeCtrl(const nodeCtrl&);

private:
    /*  Node attributes */
    struct _attr_ {
        const QPointF origin;
        const QRect bounds;
        const ITEMTYPE type;
    } attr;

    /*  Header attributes   */
    struct _hdr_
    {
        QRect   rect   = QRect(0, 0, HDR_WS, HDR_HS);
        QItemR* hdrPtr = nullptr;
        QItemT* txtPtr = nullptr;
    } hdr;

    /*  SVG icon-buttons */
    struct _svg_ {
        svgButton *addInp  = nullptr;
        svgButton *addOut  = nullptr;
        svgButton *addPar  = nullptr;
        svgButton *delNode = nullptr;
    } svg;

    /*  Command-prompt  */
    struct _prompt_
    {
        QProxy* proxy  = nullptr;
        QEditL* objptr = nullptr;
    } prompt;

    /*  Lists to store node-variables   */
    struct _list_
    {
        QList<nodeVar*>  input  = QList<nodeVar*>{};
        QList<nodeVar *> output = QList<nodeVar *>{};
        QList<nodeVar *> params = QList<nodeVar *>{};
    } list;

signals:
    void initialized(); //  Constructor emits this signal
    void nodeChanged(); //  Signal emitted when node moved
    void nodeDeleted(); //  Signal emitted when node closed

protected slots:
    void handlePrompt() const;
    void paint(QPainter *, const QSOGI *, QWidget *) override;
    QVariant itemChange(QGraphicsItem::GraphicsItemChange, const QVariant &) override;

public slots:
    void addStream(QString, VARTYPE);

public:
    [[nodiscard]] QString  getName() const { return (hdr.txtPtr->toPlainText()); }
    [[nodiscard]] ITEMTYPE getType() const { return (attr.type); }

private:
    void init();
};

#endif
