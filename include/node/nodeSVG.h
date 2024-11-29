//
// Created by Sudharshan Saranathan on 21/11/24.
//

#ifndef SVGBUTTON_H
#define SVGBUTTON_H

#define ICONSIZE 16

//  QtGui module:
#include <QSvgRenderer>
#include <QGraphicsSvgItem>
#include <QGraphicsSceneHoverEvent>

//  Convenience typedefs:
using QItemG = QGraphicsItem;
using QItemS = QGraphicsSvgItem;
using uint_t = unsigned int;

//  Class nodeSVG:
class nodeSVG final : public QGraphicsSvgItem {

    Q_OBJECT
    Q_DISABLE_COPY_MOVE(nodeSVG)
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
    ~nodeSVG() override = default;
    nodeSVG(const QString&, const QSize&, QItemG *parent = nullptr);

public:
    enum { Type = UserType + 3 };

protected:
    //  Default attribute(s):
    struct _attr_ {
        QString file;                   //  SVG filename
        QSize   size;                   //  QSize object
        double  scale;                  //  Store icon's scale
    } attr;

    struct _renderer_ {
        QSvgRenderer *pointer = nullptr;
        QString toggleOffFile = QString();
        bool toggleOn = true;
    } renderer;

signals:
    void leftClicked();                 //  Signal emitted when icon is left-clicked
    void rightClicked();                //  Signal emitted when icon is right-clicked
    void middleClicked();               //  Signal emitted when icon is middle-clicked

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;      //  Hover event-handler
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;      //  Hover event-handler
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;      //  Mouse press event-handler
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;    //  Mouse release event-handler

public:
    [[nodiscard]] int type() const override { return Type; }

    void setToggleFile(const QString& filename) { renderer.toggleOffFile = filename; }
};

#endif //SVGBUTTON_H
