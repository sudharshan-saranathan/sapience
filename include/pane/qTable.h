#ifndef QTABLE_H
#define QTABLE_H

#include "core/qInclude.h"
#include "node/qVar.h"

using qCell    = QTableWidgetItem;
using qListVar = QList<qCell*>;
using QListEqn = QList<QLabel>;
using QListStr = QList<QString>;

class qNode;
enum  qEnum;

class qTable : public QTableWidget {
public:
   ~qTable() = default;
    qTable(uint_t, uint_t, QWidget* parent = nullptr);

protected:
    struct cell {
        qListVar inp;
        qListVar out;
        qListVar par;
        QListStr tmp;
    } cell;

private:
    void populate(qEnum, qNode*);

public:
    void refresh(qNode*);

};

#endif
