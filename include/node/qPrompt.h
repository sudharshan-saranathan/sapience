#ifndef QPROMPT_H
#define QPROMPT_H

#include <map>
#include "core/qFunc.h"
#include "core/qInclude.h"
#include "node/qVar.h"
/*
#ifndef QMATRIX_H
#include "optim/qMatrix.h"
#endif
*/
struct qCmds {
    static const QString add;
    static const QString del;
    static const QString mod;
    static const QString mode;
};

struct qArgs {
    static const QString inp;
    static const QString out;
    static const QString par;
};

class qNode;
class qPrompt : public QEditL, public qDesign {

    Q_OBJECT

public:
   ~qPrompt() = default;
    qPrompt(QSize, QWidget* parent = nullptr);

    typedef enum qMode {
        mandb  = 1,
        math   = 2,
        none   = 3
    } qMode;

    struct attr {
        QSize   size;
        qMode   mode;
        QString last;
        QString help;
    } attr;

signals:
    void add (qEnum, QString, QString, double);
    void del (qEnum, QString);
    void mod (qEnum, QString, QString, QString);
    void eval(QString);

protected slots:
    virtual void on_parse(void);
    virtual void on_mandb(void);
    virtual void on_math (void);

};

#endif
