/*  -----------------------------------
 *  Project     : sapience-debug
 *  File        : nodeCtrl.h
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef NODECTRL_H
#define NODECTRL_H

/*	QtGui module	*/
#include <QCompleter>
#include <QLabel>
#include <QLineEdit>
#include <QStatusBar>
#include <QStyleOptionGraphicsItem>

//	Include SVG buttons	*/
#include <QTextEdit>
#include "ampl/amplDatabase.h"
#include "node/nodeSVG.h"
#include "node/nodeVar.h"

/*  Default defines */
#define NODEITEM 1
#define NODE_WS 300
#define NODE_HS 200
#define HDR_WS  296
#define HDR_HS  33
#define NODE_TEXT_WIDTH 120
#define RANDOMID ("N#" + QString::number(QRandomGenerator::global()->bounded(0x1000)))

//	Convenience typedefs:
using QEditL = QLineEdit;
using QItemG = QGraphicsItem;
using QItemL = QGraphicsLineItem;
using QItemR = QGraphicsRectItem;
using QItemT = QGraphicsTextItem;
using QProxy = QGraphicsProxyWidget;
using QStOGI = QStyleOptionGraphicsItem;

enum MessageType { Info, Error, Warning };

//	Forward declaration of subclassed status bar
class status;

class nodeCtrl final : public QObject, public QGraphicsRectItem {

	Q_OBJECT Q_CLASSINFO("Author", "Sudharshan Saranathan")public:

	~nodeCtrl() override;
	nodeCtrl(const nodeCtrl&);
	nodeCtrl(const QPointF&, const QString&, QGraphicsItem* parent = nullptr);

	enum { Type = UserType + NODEITEM };

private:

	//  Node attributes:
	struct {
		QString name;    //	Node name
		QString itemID;  //	Unique Identifier (UID)
		QPointF origin;  //	Cursor position of created node
		QColor  color;   //	The color of the node's border, default is black
		QRect   rect;    //	Node rectangle
		bool    locked;  //	If the node is locked (i.e. no user interaction)
		bool    deleted; //	Set to true if this item has been deleted by the user:
	} attr;

	//	Header
	struct {
		QItemR* ptr  = nullptr;
		QRect   rect = QRect();
	} header;

	//	Rails (anchors the variable handles)
	struct {
		QItemL* west	 = nullptr;
		QItemL* east	 = nullptr;
		QItemE* hintWest = nullptr;
		QItemE* hintEast = nullptr;
	} rails;

	//	Title
	struct {
		QItemT* ptr = nullptr;
	} title;

	//	SVG Buttons
	struct {
		nodeSVG* input  = nullptr; //	Button for adding input variable to the node
		nodeSVG* output = nullptr; //	Button for adding output variable to the node
		nodeSVG* params = nullptr; //	Button for adding parameter/constant
		nodeSVG* close  = nullptr; //	Button to delete the node
		nodeSVG* toggle = nullptr; //	Show/hide node's connections
	} svg;

	//	Lists to store variable pointers and names:
	struct {
		QList<nodeVar*> inp = QList<nodeVar*>();
		QList<nodeVar*> out = QList<nodeVar*>();
		QList<nodeVar*> par = QList<nodeVar*>();
		QList<QString>  eqn = QList<QString>();
	} list;

	//	Struct _prompt_:
	struct {
		QString message = QString();
		QItemR* board   = nullptr;
		status* pointer = nullptr;
	} statusbar;

	//	Nodal context menu and actions:
	struct {
		QMenu*   pointer  = nullptr;
		QAction* save     = nullptr;
		QAction* close    = nullptr;
		QAction* input    = nullptr;
		QAction* output   = nullptr;
		QAction* constant = nullptr;
	} menu;

signals:

	void
	initialized(); //	Signal emitted upon constructor completion
	void
	nodeRenamed();
	void
	nodeShifted(); //	Signal emitted when node is moved around
	void
	nodeRefresh(); //	Signal emitted when node is moved into or out of a folder
	void
	nodeDeleted(nodeCtrl*); //	Signal emitted when node is deleted
	void
	variableCreated(); //	Signal emitted when a variable is created
	void
	variableDeleted(); //	Signal emitted when a variable is deleted
	void
	linkVariable(nodeCtrl*, nodeVar*); //	Signal emitted when the user wishes to draw a connection

protected slots:

	QVariant
	itemChange(GraphicsItemChange change, const QVariant& value) override;
	void
	paint(QPainter*, const QStOGI*, QWidget*) override;
	void
	hoverMoveEvent(QGraphicsSceneHoverEvent*) override;
	void
	hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
	void
	hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
	void
	mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void
	mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override {
		actionSetup();
		event->accept();
	}
	void
	mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	void
	contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

protected:

	void
	actionSave() {}
	void
	actionErase() {}
	void
	actionSetup() const;

public:

	[[nodiscard]] int
	type() const override { return (Type); }

	[[nodiscard]] QString
	name() const { return (attr.name); }

	[[nodiscard]] QString
	getUID() const { return attr.itemID; }

	[[nodiscard]] QPointF
	origin() const { return attr.origin; }

	[[nodiscard]] bool
	isLocked() const { return attr.locked; }

	[[nodiscard]] nodeVar*
	variableAt(const QPointF&);

	static void
	autoCompletion(const QString&, const QTextEdit*);

	nodeVar*
	createVariable(const StreamType&, const QString& symbol = QString(), QPointF pos = QPointF());

	void
	deleteVariable(nodeVar*);

	void
	onLockToggled(bool);

	void
	setColor(const QColor& color) const { header.ptr->setBrush(QBrush(color)); }

	void
	setUID(const QString& ID) { attr.itemID = ID; }

	void
	randomize() { attr.itemID = RANDOMID; }

	void
	reconnect();

	void
	print(StreamType);

};

class status final : public QGraphicsTextItem {
public:
	~status() override = default;
	explicit
	status(QGraphicsItem* parent = nullptr) :
		QGraphicsTextItem(parent) {
		document()->setDefaultFont(QFont("Gill Sans", 12, QFont::Light));
		setDefaultTextColor(Qt::white);
	}

public:

	void
	print(const QString& message, const MessageType type = Info) {

		auto prefix = QString();
		if (type == Info)
			prefix = QString("[I]: ");
		else if (type == Error)
			prefix = QString("[E]: ");
		else
			prefix = QString("[W]: ");

		setPlainText(prefix + message);
	}

};

#endif
