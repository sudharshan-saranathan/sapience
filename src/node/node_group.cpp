//
// Created by Sudharshan Saranathan on 29/11/24.
//


#include "node/node_group.h"

#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>

#define DEFAULT_LABEL_COLOR QColor("#CAC4CE")

NodeGroup::NodeGroup(const QPointF& pos, const QString& filename, q_item_g* parent) :
/*	Initializer lists	*/
//	Base-class constructor:
	QGraphicsSvgItem(filename, parent),
//	Default attributes:
	m_attr{
		pos,
		new QGraphicsTextItem("New Folder", this)
	}
{

	m_attr.label->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter));
	m_attr.label->setPos(QGraphicsSvgItem::boundingRect().center() - QPointF(250, 0));
	m_attr.label->setTextWidth(500);
	m_attr.label->setFont(QFont("Gill Sans", 100));
	m_attr.label->setDefaultTextColor(DEFAULT_LABEL_COLOR);
	m_attr.label->setFlag(ItemIgnoresParentOpacity);
	m_attr.label->setTextInteractionFlags(Qt::TextEditorInteraction);

	setScale(0.20);
	setFlags(ItemIsMovable | ItemIsSelectable);

	const auto center = QGraphicsSvgItem::boundingRect().center();
	setPos(m_attr.origin.x() - center.x() * 0.20, m_attr.origin.y() - center.y() * 0.20);
}

void NodeGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

	//	Reset node state to remove dashed lines:
	auto modOption(*option);
	modOption.state = QStyle::State_None;

	//	Call base-class event-handler:
	QGraphicsSvgItem::paint(painter, &modOption, widget);
}

QVariant NodeGroup::itemChange(const GraphicsItemChange change, const QVariant &value) {
	/*	Switch-case block to handle item changes	*/
	switch (change) {
		//	If the node was moved, emit signal:
		case ItemSelectedHasChanged: {
			m_attr.label->setDefaultTextColor(isSelected() ? Qt::white : DEFAULT_LABEL_COLOR);
			break;
		}

		//	Default block:
		default:
			break;
	}
	return(value);
}

void NodeGroup::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {

	for (int j = 0; j < m_contents.pointers.size(); j++) {
		m_contents.pointers[j]->setParentItem(nullptr);
		m_contents.pointers[j]->show();
		m_contents.pointers[j]->setPos(m_contents.position[j] + scenePos() - m_attr.origin);
	}

	scene()->removeItem(this);
	deleteLater();
}

void NodeGroup::hold(QGraphicsItem* item) {

	m_contents.pointers.append(item);										//	Store the item pointer
	m_contents.position.append(item->scenePos());							//	Store the scene position of the item

	item->hide();														//	Hide the node
	item->setParentItem(this);											//	Re-parent the node
	item->setPos(0, 0);
}