//
// Created by Sudharshan Saranathan on 29/11/24.
//


#include <QGraphicsScene>
#include "node/nodeGroup.h"

#define defaultLabelColor QColor("#CAC4CE")

nodeGroup::nodeGroup(const QPointF& pos, const QString& filename, QItemG* parent) :
/*	Initializer lists	*/
//	Base-class constructor:
	QGraphicsSvgItem(filename, parent),
//	struct _attr_:
	attr{pos, new QGraphicsTextItem("New Folder", this)}
{

	attr.label->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter));
	attr.label->setPos(QGraphicsSvgItem::boundingRect().center() - QPointF(250, 0));
	attr.label->setTextWidth(500);
	attr.label->setFont(QFont("Gill Sans", 100));
	attr.label->setDefaultTextColor(defaultLabelColor);
	attr.label->setFlag(ItemIgnoresParentOpacity);
	attr.label->setTextInteractionFlags(Qt::TextEditorInteraction);

	setScale(0.20);
	setFlags(ItemIsMovable | ItemIsSelectable);

	const auto center = QGraphicsSvgItem::boundingRect().center();
	setPos(attr.origin.x() - center.x() * 0.20, attr.origin.y() - center.y() * 0.20);
}

void nodeGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

	//	Reset node state to remove dashed lines:
	auto modOption(*option);
	modOption.state = QStyle::State_None;

	//	Call base-class event-handler:
	QGraphicsSvgItem::paint(painter, &modOption, widget);
}

QVariant nodeGroup::itemChange(const GraphicsItemChange change, const QVariant &value) {
	/*	Switch-case block to handle item changes	*/
	switch (change) {
		//	If the node was moved, emit signal:
		case ItemSelectedHasChanged: {
			attr.label->setDefaultTextColor(isSelected() ? Qt::white : defaultLabelColor);
			break;
		}

		//	Default block:
		default:
			break;
	}
	return(value);
}

void nodeGroup::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {

	for (int j = 0; j < contents.pointers.size(); j++) {
		contents.pointers[j]->setParentItem(nullptr);
		contents.pointers[j]->show();
		contents.pointers[j]->setPos(contents.position[j] + scenePos() - attr.origin);
	}

	scene()->removeItem(this);
	deleteLater();
}

void nodeGroup::hold(QGraphicsItem* item) {

	contents.pointers.append(item);										//	Store the item pointer
	contents.position.append(item->scenePos());							//	Store the scene position of the item

	item->hide();														//	Hide the node
	item->setParentItem(this);											//	Re-parent the node
	item->setPos(0, 0);
}