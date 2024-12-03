/*  -----------------------------------
 *  Project     : sapience-debug
 *  File        : nodeCtrl.h
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef NODECTRL_H
#define NODECTRL_H

/*  Default defines */
#define NODE_WS 300
#define NODE_HS 200
#define HDR_WS  296
#define HDR_HS  33
#define NODE_TEXT_WIDTH 120

/*	QtGui module	*/
#include <QLabel>
#include <QLineEdit>
#include <QStatusBar>
#include <QCompleter>
#include <QStyleOptionGraphicsItem>

//	Include SVG buttons	*/
#include <QTextEdit>

#include "node/nodeSVG.h"
#include "node/nodeVar.h"
#include "ampl/amplDatabase.h"

//	Convenience typedefs:
using QEditL = QLineEdit;
using QItemG = QGraphicsItem;
using QItemL = QGraphicsLineItem;
using QItemR = QGraphicsRectItem;
using QItemT = QGraphicsTextItem;
using QProxy = QGraphicsProxyWidget;
using QStOGI = QStyleOptionGraphicsItem;

enum MessageType {
	Info,
	Error,
	Warning
};

/*	Forward declaration of sub-classed QStatusBar	*/
class status;

class nodeCtrl final : public QObject, public QGraphicsRectItem {
	Q_OBJECT
	Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
	~nodeCtrl() override;
	 nodeCtrl(const nodeCtrl&);
	 nodeCtrl(const QPointF&, const QString&, QGraphicsItem *parent = nullptr);

	 enum { Type = UserType + 1 };

private:
	/*	Default attribute(s)	*/
	struct _attr_ {
		QString name;			//	Node name
		QString itemID;			//	Unique Identifier (UID)
		QPointF origin;			//	Cursor position of created node
		QColor  color;			//	The color of the node's border, default is black
		QRect   rect;			//	Node rectangle
		bool  locked;			//	If the node is locked (i.e. no user interaction)
		bool deleted;			//	Set to true if this item has been deleted by the user:
	} attr;

	/*	Complete QGraphicsItem stack	*/
	struct _stack_ {
		//	Header section:
		struct _header_ {
			QItemR *ptr  = nullptr;
			QRect   rect = QRect();
		} header;

		struct _rails_ {
			QItemL *left  = nullptr;
			QItemL *right = nullptr;
			QItemE *hintL = nullptr;
			QItemE *hintR = nullptr;
		} rails;

		//	Node title:
		struct _title_ {
			QItemT *ptr = nullptr;
		} title;

		//	SVG buttons for variable management:
		struct _svg_ {
			nodeSVG *input  = nullptr; //	Button for adding input variable to the node
			nodeSVG *output = nullptr; //	Button for adding output variable to the node
			nodeSVG *params = nullptr; //	Button for adding parameter/constant
			nodeSVG *close  = nullptr; //	Button to delete the node
			nodeSVG *toggle = nullptr; //	Show/hide node's connections
		} svg;

		//	Lists to store variable pointers and names:
		struct _list_ {
			QList<nodeVar *> inp = QList<nodeVar *>();
			QList<nodeVar *> out = QList<nodeVar *>();
			QList<nodeVar *> par = QList<nodeVar *>();
			QList<QString>   eqn = QList<QString>  ();
		} list;

		//	Struct _prompt_:
		struct _statusBar_ {
			QString message = QString();
			QItemR *board   = nullptr;
			status *pointer = nullptr;
		} statusBar;
	} stack;

	//	Nodal context menu and actions:
	struct _menu_ {
		QMenu *  pointer  = nullptr;
		QAction *save     = nullptr;
		QAction *close    = nullptr;
		QAction *input    = nullptr;
		QAction *output   = nullptr;
		QAction *constant = nullptr;
	} menu;

signals:
	void initialized();									//	Signal emitted upon constructor completion
	void nodeRenamed();
	void nodeShifted();									//	Signal emitted when node is moved around
	void nodeRefresh();									//	Signal emitted when node is moved into or out of a folder
	void nodeDeleted(nodeCtrl *);						//	Signal emitted when node is deleted
	void variableCreated();								//	Signal emitted when a variable is created
	void variableDeleted();								//	Signal emitted when a variable is deleted
	void linkVariable(nodeCtrl *, nodeVar *);			//	Signal emitted when the user wishes to draw a connection

protected slots:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

	void paint(QPainter *, const QStOGI *, QWidget *) override;

	void hoverMoveEvent(QGraphicsSceneHoverEvent *) override;

	void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;

	void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;

	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override { actionSetup(); event->accept(); }

	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

protected:
	void actionSave() {}

	void actionErase() {}

	void actionSetup() const;

public:
	[[nodiscard]] int     type() const override { return (Type); }
	[[nodiscard]] QString name() const { return (attr.name); }
	[[nodiscard]] QString getUID() const { return attr.itemID; }
	[[nodiscard]] QPointF origin() const { return attr.origin; }
	[[nodiscard]] bool isLocked () const { return attr.locked;}

	static void autoCompletion(const QString &, const QTextEdit *);

	void createVariable(const StreamType &, const QString &symbol = QString(), QPointF pos = QPointF());

	void deleteVariable(nodeVar *);

	void onLockToggled(bool);

	void setColor(const QColor& color) const {stack.header.ptr->setBrush(QBrush(color));}
};

class status : public QGraphicsTextItem {
public:
	~status() override = default;

	explicit status(QGraphicsItem *parent = nullptr) : QGraphicsTextItem(parent) {
		document()->setDefaultFont(QFont("Gill Sans", 12, QFont::Light));
		setDefaultTextColor(Qt::white);
	}

public:
	void print(const QString &message, const MessageType type = Info) {

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
