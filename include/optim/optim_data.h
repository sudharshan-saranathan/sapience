//
// Created by Sudharshan Saranathan on 03/12/24.
//

#ifndef OPTIM_DATA_H
#define OPTIM_DATA_H

#include <QGridLayout>
#include <QTableWidget>

class NodeCtrl;
class Variable;

struct OptimDB {
	static QList<NodeCtrl*> nodeCtrlList;
	static QList<Variable*> variableList;
	static QStringList      nodeEqnsList;
	static QList<int>       deletedSymbols;
};


class OptimData final : public QWidget {

	Q_OBJECT
	Q_DISABLE_COPY_MOVE(OptimData)

public:
	~OptimData() override {}
	explicit
	OptimData(QWidget* parent = nullptr);

private:
	struct _setup_ {
		QGridLayout*  layout;
		QTableWidget* table;
	} setup;
};

#endif //OPTIM_DATA_H