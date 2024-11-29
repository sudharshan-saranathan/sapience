//
// Created by Sudharshan Saranathan on 26/11/24.
//

#ifndef AMPLSOLVER_H
#define AMPLSOLVER_H

#include <QList>

class nodeCtrl;
class nodeVar;
class pathElement;

class amplSolver {
public:
	~amplSolver() = default;
	 amplSolver() = default;
	 amplSolver(const amplSolver &) = delete;

public:
	static QList<nodeCtrl*>		nodeList;
	static QList<nodeVar*>		variableList;
	static QList<pathElement*>  connectionList;
};

#endif //AMPLSOLVER_H
