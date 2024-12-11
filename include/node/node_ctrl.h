/*  -----------------------------------
 *  Project     : sapience-debug
 *  File        : NodeCtrl.h
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef NODE_CTRL_H
#define NODE_CTRL_H

/*  QtGui module  */
#include <QCompleter>
#include <QLabel>
#include <QLineEdit>
#include <QStatusBar>

//  Include SVG buttons */
#include <QTextEdit>

#include "node_handle.h"
#include "node_params.h"
#include "node_svg.h"
#include "optim/optim_data.h"

/*  Default defines */
#define NODEITEM 1
#define NODE_WS 300
#define NODE_HS 200
#define HDR_WS 296
#define HDR_HS 33
#define NODE_TEXT_WIDTH 120
#define RANDOMID QRandomGenerator::global()->bounded(0x1000)

//  Convenience typedefs:
using q_edit  = QLineEdit;
using q_item  = QGraphicsItem;
using q_line  = QGraphicsLineItem;
using q_rect  = QGraphicsRectItem;
using q_text  = QGraphicsTextItem;
using q_circ  = QGraphicsEllipseItem;
using q_proxy = QGraphicsProxyWidget;
using q_sogi  = QStyleOptionGraphicsItem;

enum message_type { info, error, warning };

//  Forward declaration of subclassed status bar
class status;
class NodeParams;

class NodeCtrl final : public QObject, public QGraphicsRectItem
{
	Q_OBJECT Q_CLASSINFO("Author", "Sudharshan Saranathan")

public :
	~NodeCtrl() override;

	explicit
	NodeCtrl(const NodeCtrl&);

	NodeCtrl(const QPointF&, const QString&, QGraphicsItem* parent = nullptr);

	enum { Type = UserType + NODEITEM };

private:
	//  Node attributes:
	struct
	{
		QString name;    // Node name
		QString item_id; // Unique Identifier (UID)
		QPointF origin;  // Cursor position of created node
		QColor  color;   // The color of the node's border, default is black
		QRect   rect;    // Variable stores the geometry of the node
		bool    locked;  // If the node is locked (i.e. no user interaction)
		bool    deleted; // Set to true if this item has been deleted by the user:
	} m_attr;

	//	Header, displayed as a rectangle at the top of the node. It houses buttons and the node's title:
	struct
	{
		q_rect* pointer = nullptr;	//	QGraphicsRectItem (displayed at the top) as the header
		QRect   rect    = QRect();	//	Variable to store the geometry of the header
	} m_header;

	/*  Rails, displayed as textured vertical lines at the node's left and right edges. Input and output handles can be
	 *  moved only along the rails:	*/
	struct
	{
		q_line* west      = nullptr;
		q_line* east      = nullptr;
		q_circ* hint_west = nullptr;
		q_circ* hint_east = nullptr;
	} m_rails;

	//  Title
	struct
	{
		q_item_t* pointer = nullptr;
	} m_title;

	//  SVG Buttons:
	struct
	{
		NodeSVG* input  = nullptr; //  Button for adding input variable to the node
		NodeSVG* output = nullptr; //  Button for adding output variable to the node
		NodeSVG* params = nullptr; //  Button for adding parameter/constant
		NodeSVG* close  = nullptr; //  Button to delete the node
		NodeSVG* toggle = nullptr; //  Show/hide node's connections
	} m_svg;

	//  Lists to store useful stuff (handle pointers, parameters, equations):
	struct
	{
		QList<NodeHandle*> inp = QList<NodeHandle*>();
		QList<NodeHandle*> out = QList<NodeHandle*>();
		QList<NodeParams*> par = QList<NodeParams*>();
		QList<QString>     eqn = QList<QString>();
	} m_list;

	//  Statusbar displays notifications when the user interacts with the node:
	struct
	{
		QString   message = QString();
		q_item_r* board   = nullptr;
		status*   pointer = nullptr;
	} m_statusbar;

	//	Nodal context menu and actions:
	struct
	{
		QMenu*   pointer  = nullptr;
		QAction* save     = nullptr;
		QAction* close    = nullptr;
		QAction* input    = nullptr;
		QAction* output   = nullptr;
		QAction* constant = nullptr;
	} m_menu;

signals:
	void
	initialized();							//	Signal emitted upon constructor completion

	void
	nodeRenamed();							//	Signal emitted when the node is renamed

	void
	nodeShifted();							//	Signal emitted when node is moved around

	void
	nodeRefresh();							//	Signal emitted when node is moved into or out of a folder

	void
	nodeDeleted(NodeCtrl*);					//	Signal emitted when node is deleted

	void
	handleCreated();						//	Signal emitted when a variable is created

	void
	handleDeleted();						//	Signal emitted when a variable is deleted

	void
	connectHandle(NodeCtrl*, NodeHandle*);	//	Signal emitted when the user clicks a handle (to start a connection)

protected slots:
	QVariant
	itemChange(GraphicsItemChange change, const QVariant& value) override;

	void
	paint(QPainter*, const q_sogi*, QWidget*) override;

	void
	hoverMoveEvent(QGraphicsSceneHoverEvent*) override;

	void
	hoverEnterEvent(QGraphicsSceneHoverEvent*) override;

	void
	hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;

	void
	mousePressEvent(QGraphicsSceneMouseEvent* event) override;

	void
	mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override { actionSetup(); }

	void
	mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

	void
	contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

protected:
	void
	actionSetup() const;

public:
	[[nodiscard]] int
	type() const override { return (Type); }

	[[nodiscard]]
	QString name() const { return (m_attr.name); }

	[[nodiscard]]
	QString UID() const { return m_attr.item_id; }

	[[nodiscard]]
	QPointF origin() const { return m_attr.origin; }

	[[nodiscard]]
	bool isLocked() const { return m_attr.locked; }

	[[nodiscard]] NodeHandle*
	handleAt(const QPointF&);

	static void
	autoCompletion(const QString&, const QTextEdit*);

	NodeHandle*
	createHandle(const NodeHandle::StreamType&, QPointF pos = QPointF());

	QList<NodeParams*>
	createParams();

	void
	deleteHandle(NodeHandle*);

	void
	deleteParameter(NodeParams*);

	void
	onLockToggled(bool);

	void
	setColor(const QColor& color) const { m_header.pointer->setBrush(QBrush(color)); }

	void
	reconnect();
};

class status final : public QGraphicsTextItem
{
public:
	~status() override = default;
	explicit
	status(q_item* parent = nullptr) : q_text(parent)
	{
		document()->setDefaultFont(QFont("Gill Sans", 12, QFont::Light));
		setDefaultTextColor(Qt::white);
	}

public:
	void print(const QString& message, const message_type type = info)
	{
		auto prefix = QString();
		if (type == info)
			prefix = QString("[I]: ");
		else if (type == error)
			prefix = QString("[E]: ");
		else
			prefix = QString("[W]: ");

		setPlainText(prefix + message);
	}
};

//	Register the class with Qt's Meta-Object system:
Q_DECLARE_METATYPE(NodeCtrl)

#endif
