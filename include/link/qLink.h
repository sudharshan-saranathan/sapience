#ifndef QLINK_H
#define QLINK_H

#include "core/qInclude.h"
#include "link/qBezier.h"

class qNode;
class qVar;

class qLink {
public:
   ~qLink() = default;
    qLink() = default;

protected:
    struct sock {
        qNode* node = nullptr;
        qVar*  var  = nullptr;
    };

    struct conn {
        qBzr* bezier = nullptr;
        bool  create = false;
        sock  origin;
        sock  target;
    } pair;

    QList<sock> sockdb;
    QList<conn> conndb;
};

#endif
