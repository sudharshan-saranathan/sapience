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
#include <QRandomGenerator>
#include <QGraphicsItem>
#include <QMenu>
#include <utility>

#define VARITEM 2
#define HEX_RANDOM QString("#%1").arg(QRandomGenerator::global()->generate() & 0xFFFFFF, 6, 16, QChar('0'))

//  Convenience typedefs:
using QItemG = QGraphicsItem;
using QItemT = QGraphicsTextItem;
using QItemE = QGraphicsEllipseItem;
using uint_t = unsigned int;

//  Forward declarations of class nodeCtrl, nodeConnect:
class nodeCtrl;
class nodeConnect;

//  This enum is to distinguish between input & output streams:
enum StreamType { Input, Output, Constant, Parameter };

//  Class to define variable categories that respect conservation laws:
class varCategory {
public:

	varCategory(QString name, const uint_t ID, const QColor& col) :
		typeName(std::move(name)),
		typeID(ID),
		color(col) {}

	varCategory(const varCategory& other) = default;

	varCategory&
	operator=(const varCategory& other) {
		if (this == &other)
			return *this;

		typeName = other.typeName;
		typeID   = other.typeID;
		color    = other.color;
		return *this;
	}

	[[nodiscard]] QString
	getName() const { return typeName; }

	[[nodiscard]] uint_t
	getID() const { return typeID; }

	[[nodiscard]] QColor
	getColor() const { return color; }

private:

	QString typeName;
	uint_t  typeID;
	QColor  color;
};

static QList categoryList = {
	varCategory("Default", 0, Qt::gray),
	varCategory("Mass", 1, QColor(82, 178, 207)),
	varCategory("Energy", 2, QColor(243, 149, 22))
};

/*  -------------------------------------------------------------*/
/*  Main Class  */
class nodeVar final : public QObject, public QGraphicsEllipseItem {
	Q_OBJECT Q_DISABLE_COPY_MOVE(nodeVar)
	Q_CLASSINFO("Author", "Sudharshan Saranathan")public:

	~nodeVar() override;
	nodeVar(const QString&, const QString&, StreamType, QGraphicsItem* parent = nullptr);

public:

	enum { Type = UserType + VARITEM };

protected:

	//  Default attribute(s):
	struct {
		StreamType  type;
		varCategory category;
		QString     variableID;
		QString     name = QString();
		QRect       rect = QRect(0, 0, HANDLE_XS, HANDLE_YS);
	} attr;

	/*  Struct containing the symbol and selector dot   */
	struct {
		QItemT* pointer  = nullptr;
		QItemE* selector = nullptr;
		double  position = 0.0;
	} handle;

	/*  Struct containing the address of the conjugate pair
	 *  (when the variable is linked) and a bool flag to
	 *  denote pairing status. This state can be queried using
	 *  the isPaired() function.    */
	struct {
		bool     connected = false;		//  Boolean flag, accessible through setter and getter methods.
		nodeVar* conjugate = nullptr;	//	Pointer to this variable's conjugate (when connected)
	} variable;

signals:

	void
	variableRenamed(); //  Signal emitted when the variable is renamed
	void
	variableCreated(); //  Signal emitted after the variable is initialized
	void
	variableShifted(); //  Signal emitted when the handle is moved
	void
	variableDeleted(nodeVar*); //  Signal emitted when variable is deleted
	void
	variableClicked(nodeVar*); //  Signal emitted when variable is clicked

public:

	[[nodiscard]] QString
	getCategoryName() const { return attr.category.getName(); }

	[[nodiscard]] varCategory
	getCategory() const { return attr.category; }

	[[nodiscard]] int
	getCategoryID() const { return attr.category.getID(); }

	[[nodiscard]] QColor
	getCategoryColor() const { return attr.category.getColor(); }

	[[nodiscard]] bool
	isPaired() const { return (variable.connected); }

	[[nodiscard]] int
	type() const override { return (Type); }

	[[nodiscard]] QString
	name() const { return (attr.name); }

	[[nodiscard]] QString
	getUID() const { return attr.variableID; }

	[[nodiscard]] QString
	symbol() const { return (handle.pointer->toPlainText()); }

	[[nodiscard]] nodeConnect*
	pair(nodeVar* vsrc, QColor color = QColor(243, 149, 22)); //  Pair with another variable to this instance

	[[nodiscard]] StreamType
	getVariableType() const { return (attr.type); } //  Stream type (input, output, ...)

	[[nodiscard]] nodeVar*
	conjugate() const { return (variable.conjugate); } //  Get paired variable

	void
	free(QColor color = QColor(4, 220, 69)); //  Remove connections from this variable

	void
	showSelector() const {
		handle.selector->show();
		handle.selector->setOpacity(1.0);
	}

	//  Hide radio-button selector:
	void
	hideSelector() const {
		handle.selector->hide();
		handle.selector->setOpacity(0.0);
	}

	//  Set variable name (overloaded function):
	void
	name(const QString& variableName) {
		attr.name = variableName;
		handle.pointer->setPlainText(variableName);
	}

	//  Set variable UID:
	void
	setUID(const QString& vUID) { attr.variableID = vUID; }

	void
	setCategory(const varCategory& vCategory) { attr.category = vCategory; }

protected slots:

	QVariant
	itemChange(GraphicsItemChange change, const QVariant& value) override;

	void
	hoverEnterEvent(QGraphicsSceneHoverEvent*) override;

	void
	hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;

	void
	mousePressEvent(QGraphicsSceneMouseEvent* event) override;

	void
	mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

	void
	contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
};

#endif //NODEVAR_H
