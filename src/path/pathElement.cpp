//
// Created by Sudharshan Saranathan on 25/11/24.
//

#include <cmath>
#include <QThread>

#include "schematic/schemaCanvas.h"
#include "path/pathElement.h"

pathElement::pathElement(const QPen& pen, QGraphicsItem* parent) :
/*	Initializer list	*/
//	Base-class constructor:
	QGraphicsPathItem(parent),
//	struct _attr_:
	attr{pen, nullptr, nullptr, nullptr, nullptr},
//	struct _curve_:
	curve{QPainterPath()}

//	-------------------------
//	Constructor (body) begin:
{
	setZValue(-1);
	setPen(attr.pen);
	setAcceptHoverEvents(true);
}

void pathElement::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	Q_UNUSED(event)
	setOpacity(0.6);
}

void pathElement::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	Q_UNUSED(event)
	setOpacity(1.0);
}

void pathElement::clearConnection(const nodeVar* var){
	Q_UNUSED(var)

	qInfo() << "pathElement::clearConnection: Triggered by variableDeleted()";
	attr.sourceVar  = nullptr;
	attr.targetVar  = nullptr;
	attr.sourceNode = nullptr;
	attr.targetNode = nullptr;

	clear();
}

void pathElement::connect(const QPointF tpos) {

	if (attr.sourceNode && attr.sourceVar) {
		const auto spos = attr.sourceVar->scenePos() + attr.sourceVar->rect().center();
		connect(spos, tpos);
	}
}

//	Method that draws a QGraphicsPathItem between two positions on the scene:
void pathElement::connect(const QPointF spos, const QPointF tpos) {

	//	Clear current path:
	curve.path.clear();

	//	Define coordinates:
	const double xi = spos.x();
	const double yi = spos.y();
	const double xf = tpos.x();
	const double yf = tpos.y();

	const double xm = (xi + xf) / 2.0;
	const double dx = 0.25 * (xf - xi);
	const double ep = 0.45 * dx;

	//	Construct path;
	curve.path.moveTo(spos);
	curve.path.lineTo(xm - dx - ep, yi);
	curve.path.cubicTo(xm, yi, xm, yf, xm + dx + ep, yf);
	curve.path.lineTo(xf, yf);
	setPath(curve.path);
}

void pathElement::setAttr(nodeCtrl* srcn , nodeVar* srcv, nodeCtrl* tarn, nodeVar* tarv) {

	attr.sourceNode = srcn;
	attr.targetNode = tarn;
	attr.sourceVar  = srcv;
	attr.targetVar  = tarv;
}

void pathElement::update() {

	if (attr.sourceNode != nullptr && \
		attr.targetNode != nullptr && \
		attr.sourceVar  != nullptr && \
		attr.targetVar  != nullptr)
	{
		const auto spos = attr.sourceVar->scenePos() + attr.sourceVar->rect().center();
		const auto tpos = attr.targetVar->scenePos() + attr.targetVar->rect().center();
		connect(spos, tpos);
	}
}
