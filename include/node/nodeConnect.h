//
// Created by Sudharshan Saranathan on 25/11/24.
//

#ifndef PATHELEMENT_H
#define PATHELEMENT_H

#include <QWidgetAction>

#include "node/nodeConnect.h"
#include "node/nodeCtrl.h"

#define CONNECTITEM 4

using QStOGI = QStyleOptionGraphicsItem;

class variable {
public:
	virtual ~variable() = default;

protected:
	double  value  = 0.0;
	bool    fixed  = false;
	QString symbol = QString();

public:

	void
	setValue(const double& value) { this->value = value; }

	void
	setFixed(const bool& fixed)   { this->fixed = fixed; }

	void
	setSymbol(const QString& symbol) { this->symbol = symbol; }

	[[nodiscard]] double
	getValue() const { return value; }

	[[nodiscard]] bool
	isFixed() const  { return fixed; }

	[[nodiscard]] QString
	getSymbol() { return symbol; }
};

class nodeConnect final :	public QObject,
							public QGraphicsPathItem,
							public variable {

	Q_OBJECT Q_DISABLE_COPY_MOVE(nodeConnect)
	Q_CLASSINFO("Author", "Sudharshan Saranathan")public:

	~nodeConnect() override;
	explicit
	nodeConnect(const QPen&    pen = QPen(categoryList[0].getColor(), 3.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin),
				QGraphicsItem* parent = nullptr);

	enum { Type = UserType + CONNECTITEM };

private:

	struct {
		QPen    pen    = QPen(categoryList[0].getColor(), 3.0);
		QString symbol = QString();
	} attr;

	struct {
		nodeCtrl* sourceNode   = nullptr;
		nodeCtrl* targetNode   = nullptr;
		nodeHandle*  sourceHandle = nullptr;
		nodeHandle*  targetHandle = nullptr;
	} pointers;

	struct {
		QPainterPath path;
	} curve;

	struct {
		QMenu*         pointer        = nullptr;
		QLineEdit*     createCategory = nullptr;
		QWidgetAction* createAction   = nullptr;
	} menu;

signals:

	void
	pathDeleted(nodeConnect*);

protected slots:

	void
	hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	void
	hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
	void
	contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

public slots:

	void
	clearConnection(const nodeHandle*) const;
	void
	setCategory(const varCategory&);

public:

	[[nodiscard]] int
	type() const override { return Type; }

	[[nodiscard]] nodeCtrl*
	getOriginNode() const { return pointers.sourceNode; }

	[[nodiscard]] nodeCtrl*
	getTargetNode() const { return pointers.targetNode; }

	[[nodiscard]] nodeHandle*
	getOriginVar() const { return pointers.sourceHandle; }

	[[nodiscard]] nodeHandle*
	getTargetVar() const { return pointers.targetHandle; }

	void
	setOriginNode(nodeCtrl* onode) { pointers.sourceNode = onode; }

	void
	setTargetNode(nodeCtrl* tnode) { pointers.targetNode = tnode; }

	void
	setOriginVar(nodeHandle* ovar) { pointers.sourceHandle = ovar; }

	void
	setTargetVar(nodeHandle* tvar) { pointers.targetHandle = tvar; }

	void
	clear() {
		curve.path.clear();
		setPath(QPainterPath());
	}

	void
	connect(QPointF);

	void
	connect(QPointF, QPointF);

	void
	setAttr(nodeCtrl*, nodeHandle*, nodeCtrl*, nodeHandle*);

	void
	refresh();
};

#endif //PATHELEMENT_H
