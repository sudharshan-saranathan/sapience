//
// Created by Sudharshan Saranathan on 21/11/24.
//

#ifndef NODEVAR_H
#define NODEVAR_H

/*  QtGui module    */
#include <QGraphicsEllipseItem>

/*  Include project headers */
#include "core/coreQSS.h"
#include "core/coreEnum.h"

/*  Main Class  */
class nodeVar final : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(nodeVar)
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
    ~nodeVar() override = default;
     nodeVar(const QString&, VARTYPE, QGraphicsItem *parent = nullptr);

public:
    enum { Type = UserType + 2 };

protected:
    struct _attr_ {
        QString name = QString();
        VARTYPE type = VARTYPE::NONE;
        QRect   rect = QRect(0, 0, 4, 4);
    } attr;

public:
    [[nodiscard]] QString  getName() const { return(attr.name); }
    [[nodiscard]] VARTYPE getType() const { return(attr.type); }
};

#endif //NODEVAR_H
