//
// Created by Sudharshan Saranathan on 04/12/24.
//

#include "node/nodeParams.h"

nodeParams::nodeParams(const QString& name, QGraphicsItem* parent) :
//	Initializer list
//	Base-class constructor
	QGraphicsTextItem(parent),
//	Initialize string:
	attr{name, QString()}
{
	fixed  = true;			//	Inherited from class variable, parameters and constants are fixed by default
	symbol = name;			//	Inherited from class variable
}