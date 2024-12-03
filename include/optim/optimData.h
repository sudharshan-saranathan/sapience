//
// Created by Sudharshan Saranathan on 03/12/24.
//

#ifndef OPTIMDATA_H
#define OPTIMDATA_H

#include <QWidget>
#include <QGridLayout>
#include <QTableWidget>

#include "node/nodeCtrl.h"
#include "node/nodeVar.h"

class optimData : public QWidget {

	Q_OBJECT
	Q_DISABLE_COPY_MOVE(optimData)

public:
	~optimData() override {}
	 optimData(QWidget* parent = nullptr);

private:
	struct _setup_ {
		QGridLayout*  layout;
		QTableWidget* table;
	} setup;
};

#endif //OPTIMDATA_H