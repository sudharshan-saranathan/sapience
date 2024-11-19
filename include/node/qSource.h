#ifndef QSOURCE_H
#define QSOURCE_H

#include "qInclude.h"

class qSource : public QObject, public QGraphicsSvgItem {

    Q_OBJECT

public:
   ~qSource() = default;
    qSource(QItemG* parent = nullptr);

    struct attr {
        QString file;
        QSize   size;
    } attr;

} qSource;

#endif
