//
// Created by Sudharshan Saranathan on 03/12/24.
//

#include "optim/optimData.h"

optimData::optimData(QWidget* parent) :
//	Initializer list:
//	Base-class constructor:
	QWidget(parent),
//	struct _setup_:
	setup{
		new QGridLayout(this),
		new QTableWidget(this),
	}

//  ------------------
//	Constructor begin:
{

}