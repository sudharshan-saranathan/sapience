//
// Created by Sudharshan Saranathan on 29/11/24.
//

#ifndef NODE_GROUP_H
#define NODE_GROUP_H

#include "node/node_ctrl.h"

#define GROUPITEM 5

class NodeGroup final : public QGraphicsSvgItem
{

    Q_OBJECT
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
    ~NodeGroup() override = default;
    NodeGroup()           = delete;
    NodeGroup(const QPointF& pos, const QString&, QGraphicsItem* parent = nullptr);

public:

    enum { Type = UserType + GROUPITEM };

private:

    struct
    {
        QPointF origin = QPointF();
        q_text* label  = nullptr;
    } m_attr;

    struct _contents_
    {
        QList<q_item*> pointers = QList<q_item*>();
        QList<QPointF> position = QList<QPointF>();
    } m_contents;

protected slots:

    QVariant
    itemChange(GraphicsItemChange change, const QVariant& value) override;
    void
    paint(QPainter* painter, const q_sogi* option, QWidget* widget) override;
    void
    mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

public:

    void
    hold(q_item* item);

    int
    type() const override { return Type; }

};

#endif //NODEFOLDER_H
