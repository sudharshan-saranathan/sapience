//
// Created by Sudharshan Saranathan on 26/11/24.
//

#include "ampl/amplDatabase.h"
#include "node/nodeCtrl.h"
#include "node/nodeVar.h"
#include "node/nodeConnect.h"

QList<nodeCtrl*>	amplDatabase::nodeList		 = QList<nodeCtrl*>();
QList<nodeVar *>	amplDatabase::variableList	 = QList<nodeVar *>();
QStringList			amplDatabase::equationsList  = QStringList();
QList<int>			amplDatabase::deletedSymbols = QList<int>();
QList<nodeConnect*> amplDatabase::connectionList = QList<nodeConnect*>();
