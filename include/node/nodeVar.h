//
// Created by Sudharshan Saranathan on 21/11/24.
//

#ifndef NODEVAR_H
#define NODEVAR_H

/*  QtCore module   */
#include <QObject>

/*  QtGui module    */
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>

/*  Include project headers */
#include "core/coreQSS.h"

enum class VARITEM_ {
    INPUT,
    OUTPUT,
    PARAMETER
};

/*  Main Class  */
class nodeVar final : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(nodeVar)
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
    ~nodeVar() override = default;

    nodeVar(const QString &, VARITEM_, QGraphicsItem *parent = nullptr);

protected:
    struct _attr_ {
        VARITEM_ type;
        QRect rect;
    } attr;
};

#endif //NODEVAR_H
