//
// Created by Sudharshan Saranathan on 26/11/24.
//

#include "ampl/amplSolver.h"
#include "node/nodeCtrl.h"
#include "node/nodeVar.h"
#include "path/pathElement.h"

QList<nodeCtrl*>	amplSolver::nodeList		= QList<nodeCtrl*>();
QList<nodeVar *>	amplSolver::variableList	= QList<nodeVar *>();
QList<pathElement*> amplSolver::connectionList  = QList<pathElement*>();