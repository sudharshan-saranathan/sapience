//
// Created by Sudharshan Saranathan on 26/11/24.
//

#ifndef AMPLDATABASE_H
#define AMPLDATABASE_H

#include <QList>

class nodeCtrl;
class nodeVar;
class nodeConnect;

using uint_t = unsigned int;

class amplDatabase {
public:
	~amplDatabase() = default;
	 amplDatabase() = default;
	 amplDatabase(const amplDatabase &) = delete;

public:
	static QList<nodeCtrl*>	nodeList;
	static QList<nodeVar*> variableList;
	static QStringList equationsList;
	static QList<int>  deletedSymbols;
	static QList<nodeConnect*> connectionList;
};

#endif //AMPLDATABASE_H
