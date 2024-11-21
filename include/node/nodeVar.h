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

/*  Main Class  */
class nodeVar : public QObject, public QGraphicsEllipseItem {

    Q_OBJECT
    Q_DISABLE_COPY_MOVE(nodeVar)
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
    ~nodeVar() override = default;
     nodeVar();

};

#endif //NODEVAR_H
