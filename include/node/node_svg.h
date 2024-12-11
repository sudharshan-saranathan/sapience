//
// Created by Sudharshan Saranathan on 21/11/24.
//

#ifndef NODE_SVG_H
#define NODE_SVG_H

#define SVGITEM 3
#define ICONSIZE 16

//  QtGui module:
#include <QSvgRenderer>
#include <QGraphicsSvgItem>
#include <QGraphicsSceneHoverEvent>

//  Convenience typedefs:
using q_item = QGraphicsItem;
using QItemS = QGraphicsSvgItem;
using uint_t = unsigned int;

//  Class NodeSVG:
class NodeSVG final : public QGraphicsSvgItem
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(NodeSVG)
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
    ~NodeSVG() override = default;
    NodeSVG(const QString&, const QSize&, bool translate, q_item* parent = nullptr);

public:
    enum { Type = UserType + SVGITEM };

protected:
    //  Default attribute(s):
    struct
    {
        QString file;  //  SVG filename
        QSize   size;  //  QSize object
        double  scale; //  Store icon's scale
    } m_attr;

    struct
    {
        QSvgRenderer* pointer       = nullptr;
        QString       toggleOffFile = QString();
        bool          toggleOn      = true;
    } m_renderer;

signals:
    void leftClicked();   //  Signal emitted when icon is left-clicked
    void rightClicked();  //  Signal emitted when icon is right-clicked
    void middleClicked(); //  Signal emitted when icon is middle-clicked

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;   //  Hover event-handler
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;   //  Hover event-handler
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;   //  Mouse press event-handler
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override; //  Mouse release event-handler

public:
    [[nodiscard]] int
    type() const override { return Type; }

    void
    setToggleFile(const QString& filename) { m_renderer.toggleOffFile = filename; }
};

#endif //SVGBUTTON_H
