//
// Created by Sudharshan Saranathan on 03/12/24.
//

#include "optim/optim_data.h"

//	Database
QList<NodeCtrl*> OptimDB::nodeCtrlList	 = QList<NodeCtrl*>();
QList<Variable*> OptimDB::variableList	 = QList<Variable*>();
QStringList		 OptimDB::nodeEqnsList	 = QStringList();
QList<int>		 OptimDB::deletedSymbols = QList<int>();

OptimData::OptimData(QWidget* parent) :
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