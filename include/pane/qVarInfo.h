#ifndef QVARINFO_H
#define QVARINFO_H

#include "core/qInclude.h"
#include "node/qVar.h"

class qVarInfo : public QListWidget {

    Q_OBJECT

public:
   ~qVarInfo() = default;
    qVarInfo(QWidget* parent = nullptr);

};

#endif
