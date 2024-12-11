//
// Created by Sudharshan Saranathan on 21/11/24.
//

#ifndef NODE_HANDLE_H
#define NODE_HANDLE_H

#define HANDLE_XS 8
#define HANDLE_YS 8
#define FONT_SIZE 12

/*  QtGui module    */
#include <QGraphicsEllipseItem>
#include <QMenu>
#include <QtGlobal>

#define HANDLEITEM 2
#define RANDOMINT QRandomGenerator::system()->generate()
#define RANDOMHEX QString("%1").arg(RANDOMINT & 0xFFFFFF, 6, 16, QChar('0'))

//  Convenience typedefs:
using q_item_g = QGraphicsItem;
using q_item_t = QGraphicsTextItem;
using q_item_r = QGraphicsRectItem;
using QItemE   = QGraphicsEllipseItem;
using uint_t   = unsigned int;

//  Forward declarations of class NodeCtrl, NodeConnect:
class NodeCtrl;
class NodeConnect;

//  Class to define variable categories that respect conservation laws:
class varCategory
{
public:
	varCategory(QString name, const uint_t ID, const QColor& col) :
		typeName(std::move(name)),
		typeID(ID),
		color(col)
	{
	}

	varCategory(const varCategory& other) = default;

	varCategory&
	operator=(const varCategory& other)
	{
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
class NodeHandle final : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT Q_DISABLE_COPY_MOVE(NodeHandle)
	Q_CLASSINFO("Author", "Sudharshan Saranathan")
	Q_PROPERTY(varCategory category READ category WRITE setCategory NOTIFY categoryChanged)

public:
	//  This enum is to distinguish between input & output handles:
	enum StreamType
	{
		INP = 0x01,
		OUT = 0x02,
	};

	Q_ENUM(StreamType)

public:
	~NodeHandle() override;
	explicit
	NodeHandle(const StreamType&, QGraphicsItem* parent = nullptr);

	enum { Type = UserType + HANDLEITEM };

protected:
	//  Default attribute(s):
	struct
	{
		StreamType  type;
		varCategory category;
		QString     handleID;
		QRect       rect = QRect(0, 0, HANDLE_XS, HANDLE_YS);
	} m_attr;

	/*  Struct containing graphical elements and the pointer-address of the conjugate m_handle (if the variable is linked)
	 *  and a bool flag to store the pairing status. The status can be queried using the isPaired() method    */
	struct
	{
		q_item_t* text     = nullptr;
		q_item_t* symbol   = nullptr;
		QItemE*   selector = nullptr;
		double    position = 0.0;

		struct
		{
			bool         connected = false;
			NodeHandle*  conjugate = nullptr;
			NodeConnect* connector = nullptr;
		} state;
	} m_handle;

signals:
	void
	handleRenamed(); //  Signal emitted when the variable is renamed
	void
	handleCreated(); //  Signal emitted after the variable is initialized
	void
	handleShifted(); //  Signal emitted when the m_handle is moved
	void
	handleDeleted(NodeHandle*); //  Signal emitted when variable is deleted
	void
	handleClicked(NodeHandle*); //  Signal emitted when variable is clicked
	void
	categoryChanged();

public:
	[[nodiscard]] QString
	categoryName() const { return m_attr.category.getName(); }

	[[nodiscard]] varCategory
	category() const { return m_attr.category; }

	[[nodiscard]] int
	categoryID() const { return m_attr.category.getID(); }

	[[nodiscard]] QColor
	categoryColor() const { return m_attr.category.getColor(); }

	[[nodiscard]] bool
	isPaired() const { return (m_handle.state.connected); }

	[[nodiscard]] int
	type() const override { return (Type); }

	[[nodiscard]] QString
	name() const { return m_handle.text->toPlainText(); }

	[[nodiscard]] QString
	symbol() const { return m_handle.symbol->toPlainText(); }

	[[nodiscard]] QString
	UID() const { return m_attr.handleID; }

	[[nodiscard]] NodeConnect*
	pair(NodeHandle* vsrc, QColor color = QColor(243, 149, 22)); //  Pair with another variable to this instance

	[[nodiscard]] StreamType
	streamType() const { return (m_attr.type); } //  Stream type (input, output, ...)

	[[nodiscard]] NodeHandle*
	conjugate() const { return (m_handle.state.conjugate); } //  Get paired variable

	void
	free(QColor color = QColor(4, 220, 69)); //  Remove connections from this variable

	void
	showSelector() const
	{
		m_handle.selector->show();
		m_handle.selector->setOpacity(1.0);
	}

	//  Hide radio-button selector:
	void
	hideSelector() const
	{
		m_handle.selector->hide();
		m_handle.selector->setOpacity(0.0);
	}

	void
	setUID(const QString& UID) { m_attr.handleID = UID; }

	void
	setCategory(const varCategory& vCategory)
	{
		m_attr.category = vCategory;
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

//	Register the class with Qt's Meta-Object system:
Q_DECLARE_METATYPE(NodeHandle*)

//	Removing this makes qvariant_cast<NodeParams*>(value) fail, leading to segmentation faults

#endif //NODEVAR_H
