//
// Created by Sudharshan Saranathan on 29/11/24.
//

#ifndef NODEFOLDER_H
#define NODEFOLDER_H

#include "node/nodeCtrl.h"

#define GROUPITEM 5

class nodeGroup final : public QGraphicsSvgItem
{

    Q_OBJECT
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:

    ~nodeGroup() override = default;
    nodeGroup()           = delete;
    nodeGroup(const QPointF& pos, const QString&, QGraphicsItem* parent = nullptr);

public:

    enum { Type = UserType + GROUPITEM };

private:

    struct _attr_
    {
        QPointF origin = QPointF();
        QItemT* label  = nullptr;
    } attr;

    struct _contents_
    {
        QList<QItemG*> pointers = QList<QItemG*>();
        QList<QPointF> position = QList<QPointF>();
    } contents;

protected slots:

    QVariant
    itemChange(GraphicsItemChange change, const QVariant& value) override;
    void
    paint(QPainter* painter, const QStOGI* option, QWidget* widget) override;
    void
    mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

public:

    void
    hold(QGraphicsItem* item);

    int
    type() const override { return Type; }

};

#endif //NODEFOLDER_H
