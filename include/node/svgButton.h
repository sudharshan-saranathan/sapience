//
// Created by Sudharshan Saranathan on 21/11/24.
//

#ifndef SVGBUTTON_H
#define SVGBUTTON_H

#include <QObject>
#include <QString>
#include <QGraphicsItem>
#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>

using QItemG = QGraphicsItem;
using QItemS = QGraphicsSvgItem;
using uint_t = unsigned int;

class svgButton final : public QGraphicsSvgItem {

    Q_OBJECT
    Q_DISABLE_COPY_MOVE(svgButton)
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
    ~svgButton() override = default;
     explicit svgButton(const QString &, QItemG *parent = nullptr);

protected:
    struct _attr_ {
        QString file;
        uint_t ws;
        uint_t hs;
        QSize size;
    } attr;

signals:
    void lclicked();
    void rclicked();
    void mclicked();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;
};

#endif //SVGBUTTON_H
