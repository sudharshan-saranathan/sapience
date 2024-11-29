//
// Created by Sudharshan Saranathan on 21/11/24.
//

#ifndef NODEVAR_H
#define NODEVAR_H

#define HANDLE_XS 8
#define HANDLE_YS 8
#define FONT_SIZE 10

/*  QtGui module    */
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QMenu>

enum VariableType {
    None,
    Input,
    Output,
    Constant,
    Parameter
};

//  Convenience typedefs:
using QItemG = QGraphicsItem;
using QItemT = QGraphicsTextItem;
using QItemE = QGraphicsEllipseItem;

//  Forward declaration:
class nodeCtrl;

/*  ------------------------------------------------------------*/
/*  Main Class  */
class nodeVar final : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(nodeVar)
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
    ~nodeVar() override = default;

    nodeVar(const QString &, const QString &, VariableType, QGraphicsItem *parent = nullptr);

public:
    enum { Type = UserType + 2 };

protected:
    //  Default attribute(s):
    struct _attr_ {
        const VariableType type;
        QString            variableID;
        QString            name = QString();
        QRect              rect = QRect(0, 0, HANDLE_XS, HANDLE_YS);
    } attr;

    /*  Struct containing the symbol and selector dot   */
    struct _handle_ {
        QItemT *pointer  = nullptr;
        QItemE *selector = nullptr;
        double  position = 0.0;
    } handle;

    /*  Struct containing the address of the conjugate pair
     *  (when the variable is linked) and a bool flag to
     *  denote pairing status. This state can be queried using
     *  the isPaired() function.    */
    struct _variable_ {
        nodeVar *conjugate = nullptr; //  Pointer to conjugate nodeVar variable
        bool     connected = false;   //  Boolean flag, accessible through setter and getter methods.
        double   data      = 0.0;
    } variable;

signals:
    void variableCreated();          //  Signal emitted after the variable is initialized
    void variableShifted();          //  Signal emitted when the handle is moved
    void variableDeleted(nodeVar *); //  Signal emitted when variable is deleted
    void variableClicked(nodeVar *); //  Signal emitted when variable is clicked

public:
    [[nodiscard]] bool    isPaired() const { return (variable.connected); }
    [[nodiscard]] int     type() const override { return (Type); }
    [[nodiscard]] QString name() const { return (attr.name); }
    [[nodiscard]] QString getUID() const { return attr.variableID; }
    [[nodiscard]] QString symbolName() const { return (handle.pointer->toPlainText()); }

    [[nodiscard]] bool pair(nodeVar *vsrc, QColor color = QColor(243, 149, 22)); //  Pair a variable to this instance
    [[nodiscard]] VariableType getVariableType() const { return (attr.type); }

    nodeVar *conjugate() const { return (variable.conjugate); } //  Get paired variable
    void     free(QColor color = QColor(4, 220, 69));           //  Remove connections from this variable

    //  Show radio-button selector:
    void showSelector() const {
        handle.selector->show();
        handle.selector->setOpacity(1.0);
    }

    //  Hide radio-button selector:
    void hideSelector() const {
        handle.selector->hide();
        handle.selector->setOpacity(0.0);
    }

    //  Set variable name (overloaded function):
    void name(const QString &variableName) {
        attr.name = variableName;
        handle.pointer->setPlainText(variableName);
    }

    //  Set variable UID:
    void setUID(const QString &vUID) {
        attr.variableID = vUID;
    }

protected slots:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
};

#endif //NODEVAR_H
