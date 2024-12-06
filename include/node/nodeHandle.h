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

#define HANDLEITEM 2
#define HEX_RANDOM QString("#%1").arg(QRandomGenerator::global()->generate() & 0xFFFFFF, 6, 16, QChar('0'))

//  Convenience typedefs:
using QItemG = QGraphicsItem;
using QItemT = QGraphicsTextItem;
using QItemR = QGraphicsRectItem;
using QItemE = QGraphicsEllipseItem;
using uint_t = unsigned int;

//  Forward declarations of class nodeCtrl, nodeConnect:
class nodeCtrl;
class nodeConnect;

//  This enum is to distinguish between input & output streams:
enum StreamType { Input, Output };

class sensor final : public QObject, public QItemR {

	Q_OBJECT Q_DISABLE_COPY_MOVE(sensor)
	Q_CLASSINFO("Author", "Sudharshan Saranathan")public:

	~sensor() override = default;
	explicit
	sensor(const double&, QItemG* parent = nullptr);

protected slots:

	void
	hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	void
	hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

};

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
class nodeHandle final : public QObject, public QGraphicsEllipseItem {

	Q_OBJECT Q_DISABLE_COPY_MOVE(nodeHandle)
	Q_CLASSINFO("Author", "Sudharshan Saranathan")
	Q_PROPERTY(varCategory category READ category WRITE setCategory NOTIFY categoryChanged)

public:

	~nodeHandle() override;
	explicit
	nodeHandle(const StreamType&, QGraphicsItem* parent = nullptr);

	enum { Type = UserType + HANDLEITEM };

protected:

	//  Default attribute(s):
	struct {
		StreamType  type;
		varCategory category;
		QString     handleID;
		QRect       rect = QRect(0, 0, HANDLE_XS, HANDLE_YS);
	} attr;

	/*  Struct containing graphical elements and the pointer-address of the conjugate handle (if the variable is linked)
	 *  and a bool flag to store the pairing status. The status can be queried using the isPaired() method    */
	struct {
		QItemT* text     = nullptr;
		QItemT* symbol   = nullptr;
		QItemE* selector = nullptr;
		double  position = 0.0;

		struct {
			bool         connected = false;
			nodeHandle*  conjugate = nullptr;
			nodeConnect* connector = nullptr;
		} state;
	} handle;

signals:

	void
	handleRenamed(); //  Signal emitted when the variable is renamed
	void
	handleCreated(); //  Signal emitted after the variable is initialized
	void
	handleShifted(); //  Signal emitted when the handle is moved
	void
	handleDeleted(nodeHandle*); //  Signal emitted when variable is deleted
	void
	handleClicked(nodeHandle*); //  Signal emitted when variable is clicked
	void
	categoryChanged();

public:

	[[nodiscard]] QString
	categoryName() const { return attr.category.getName(); }

	[[nodiscard]] varCategory
	category() const { return attr.category; }

	[[nodiscard]] int
	categoryID() const { return attr.category.getID(); }

	[[nodiscard]] QColor
	categoryColor() const { return attr.category.getColor(); }

	[[nodiscard]] bool
	isPaired() const { return (handle.state.connected); }

	[[nodiscard]] int
	type() const override { return (Type); }

	[[nodiscard]] QString
	name() const { return handle.text->toPlainText(); }

	[[nodiscard]] QString
	symbol() const { return handle.symbol->toPlainText(); }

	[[nodiscard]] QString
	UID() const { return attr.handleID; }

	[[nodiscard]] nodeConnect*
	pair(nodeHandle* vsrc, QColor color = QColor(243, 149, 22)); //  Pair with another variable to this instance

	[[nodiscard]] StreamType
	streamType() const { return (attr.type); } //  Stream type (input, output, ...)

	[[nodiscard]] nodeHandle*
	conjugate() const { return (handle.state.conjugate); } //  Get paired variable

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

	void
	setUID(const QString& UID) { attr.handleID = UID; }

	void
	setCategory(const varCategory& vCategory) {
		attr.category = vCategory;
		emit categoryChanged();
	}

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
