//
// Created by Sudharshan Saranathan on 25/11/24.
//

#ifndef NODE_CONNECT_H
#define NODE_CONNECT_H

//	QtGUI module:
#include <QLineEdit>
#include <QPen>
#include <QWidgetAction>

//	Project headers:
#include "node_handle.h"

//	Macros:
#define CONNECTITEM 4
#define PEN_DEFAULT QPen(categoryList[0].getColor(), 3.0)
#define PEN_COLOR(color) QPen(color, 3.0)

using q_item = QGraphicsItem;

class Variable
{
public:
	virtual ~Variable() = default;

protected:
	double  value  = 0.0;
	bool    fixed  = false;
	QString symbol = QString();

public:
	void
	setValue(const double& value) { this->value = value; }

	void
	setFixed(const bool& fixed) { this->fixed = fixed; }

	void
	setSymbol(const QString& symbol) { this->symbol = symbol; }

	[[nodiscard]] double
	getValue() const { return value; }

	[[nodiscard]] bool
	isFixed() const { return fixed; }

	[[nodiscard]] QString
	getSymbol() { return symbol; }
};

class NodeConnect final : public QObject,
                          public QGraphicsPathItem,
                          public Variable
{
	Q_OBJECT Q_DISABLE_COPY_MOVE(NodeConnect)
	Q_CLASSINFO("Author", "Sudharshan Saranathan")public:
	~NodeConnect() override;
	explicit
	NodeConnect(const QPen& pen = PEN_DEFAULT, q_item* parent = nullptr);

	enum { Type = UserType + CONNECTITEM };

private:
	struct
	{
		QPen    pen    = QPen(categoryList[0].getColor(), 3.0);
		QString symbol = QString();
	} m_attr;

	struct
	{
		NodeCtrl*   sourceNode   = nullptr;
		NodeCtrl*   targetNode   = nullptr;
		NodeHandle* sourceHandle = nullptr;
		NodeHandle* targetHandle = nullptr;
	} m_pointers;

	struct
	{
		QPainterPath path;
	} m_curve;

	struct
	{
		QMenu*         pointer        = nullptr;
		QLineEdit*     createCategory = nullptr;
		QWidgetAction* createAction   = nullptr;
	} m_menu;

signals:
	void
	pathDeleted(NodeConnect*);

protected slots:
	void
	hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;

	void
	hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

	void
	contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

public slots:
	void
	clearConnection(const NodeHandle*) const;
	void
	setCategory(const varCategory&);

public:
	[[nodiscard]] int
	type() const override { return Type; }

	[[nodiscard]] NodeCtrl*
	getOriginNode() const { return m_pointers.sourceNode; }

	[[nodiscard]] NodeCtrl*
	getTargetNode() const { return m_pointers.targetNode; }

	[[nodiscard]] NodeHandle*
	getOriginVar() const { return m_pointers.sourceHandle; }

	[[nodiscard]] NodeHandle*
	getTargetVar() const { return m_pointers.targetHandle; }

	void
	setOriginNode(NodeCtrl* onode) { m_pointers.sourceNode = onode; }

	void
	setTargetNode(NodeCtrl* tnode) { m_pointers.targetNode = tnode; }

	void
	setOriginVar(NodeHandle* ovar) { m_pointers.sourceHandle = ovar; }

	void
	setTargetVar(NodeHandle* tvar) { m_pointers.targetHandle = tvar; }

	void
	clear()
	{
		m_curve.path.clear();
		setPath(QPainterPath());
	}

	void
	connect(QPointF);

	void
	connect(QPointF, QPointF);

	void
	setAttr(NodeCtrl*, NodeHandle*, NodeCtrl*, NodeHandle*);

	void
	refresh();
};

#endif //PATHELEMENT_H
