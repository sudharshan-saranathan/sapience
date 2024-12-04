//
// Created by Sudharshan Saranathan on 04/12/24.
//

#include "node/nodeConstant.h"

nodeConstant::nodeConstant(const QString& name, QGraphicsItem* parent) :
//	Initializer list
//	Base-class constructor
	QGraphicsTextItem(parent),
//	Initialize name:
	attr{name}
{

}