#ifndef QPANE_H
#define QPANE_H

#include "core/qFunc.h"
#include "core/qCustom.h"
#include "core/qInclude.h"
#include "pane/qTable.h"

using QListStr = QStringList;
using QListEqn = QList<QLabel>;

class qNode;
class qPane : public QWidget, public qDesign {

    Q_OBJECT
    Q_DISABLE_COPY_MOVE(qPane)

public:
   ~qPane() = default;
    qPane(QWidget* parent = nullptr);

protected:
    struct attr {
        QSize  size;
        QGrid *layout;
    } attr;

    struct label {
        QLabel* item;
        QString text;
    } label;

    struct table {
        uint_t   rows;
        uint_t   cols;
        qTable*  item;
        QListStr head;
    } table;

public:
    void refresh(qNode*);

};

#endif
