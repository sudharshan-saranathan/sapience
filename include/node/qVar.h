#ifndef QVAR_H
#define QVAR_H

#include "core/qFunc.h"
#include "core/qInclude.h"

typedef enum qEnum {
    inp = 0,
    out = 1,
    par = 2
} qEnum;

//------------------------------------------------------------------------------
class qNode;
class qLabel : public QItemT {

    Q_OBJECT

public:
   ~qLabel() = default;
    qLabel(qEnum, QString, QItemG* parent = nullptr);

protected:
    struct attr {
        uint_t  width;
        QString label;
        QString tip;
        QOption option;
    } attr;

signals:
    void label_update(const QString&);

public:
    void verify_text();

protected:
    virtual void focusInEvent(QFocusEvent*);
    virtual void focusOutEvent(QFocusEvent*);
    virtual void keyPressEvent(QKeyEvent*);
    virtual void keyReleaseEvent(QKeyEvent*);

};

//------------------------------------------------------------------------------

class qVar : public QObject, public QItemE, qDesign {

    Q_OBJECT

public:
   ~qVar() = default;
    qVar(qEnum, QString, QString, float, QItemG* parent);

protected:
    struct attr {
        QBool paired;
        qreal radius;
    } attr;

    struct label {
        qLabel *item;
    } label;

    struct var {
        qEnum   type;
        QString name;
        QString unit;
        double  value;
    } var;

signals:
    void enroll_sock(qNode*,  qVar*);
    void create_link(qNode*,  qVar*);
    void adjust_link(qNode*,  qVar*);
    void update_var (qNode*,  qVar*);
    void delete_var (qNode*,  qVar*);
    void replace_var(QString, qVar*);

protected slots:
    virtual QVariant  itemChange  (QChange, const QVariant& );
    virtual void hoverEnterEvent  (QGraphicsSceneHoverEvent*);
    virtual void hoverLeaveEvent  (QGraphicsSceneHoverEvent*);
    virtual void mousePressEvent  (QGraphicsSceneMouseEvent*);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
    virtual void on_label_update  (const QString&);

protected:
    void update();

public:
    qEnum   type () { return(var.type);  }
    QString name () { return(var.name);  }
    QString unit () { return(var.unit);  }
    double& value() { return(var.value); }

public:
    void name(QString name) {
        var.name = name;
        label.item->setPlainText(name);
        label.item->verify_text();
    }
    void unit  (QString unit) { var.unit  = unit;  }
    void value (double value) { var.value = value; }

public:
    void set_paired(bool value) { attr.paired = value; }
    bool get_paired(void)       { return(attr.paired); }
};

#endif
