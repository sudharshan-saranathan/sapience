//
// Created by Sudharshan Saranathan on 25/11/24.
//

#ifndef PATHELEMENT_H
#define PATHELEMENT_H

#include <QWidgetAction>

#include "node/nodeVar.h"
#include "node/nodeCtrl.h"

using QStOGI = QStyleOptionGraphicsItem;

class nodeConnect final : public QObject, public QGraphicsPathItem {

	Q_OBJECT
	Q_DISABLE_COPY_MOVE(nodeConnect)
	Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
	~nodeConnect() override;
	explicit nodeConnect(const QPen& pen, QGraphicsItem* parent = nullptr);

public:
	enum { Type = UserType + 4};

private:
	struct _attr_ {
		QPen pen;
		nodeCtrl* sourceNode = nullptr;
		nodeVar * sourceVar  = nullptr;
		nodeCtrl* targetNode = nullptr;
		nodeVar * targetVar  = nullptr;
	} attr;

	struct _curve_ {
		QPainterPath path;
	} curve;

	struct _menu_ {
		QMenu* pointer = nullptr;
		QLineEdit* createCategory = nullptr;
		QWidgetAction* createAction = nullptr;
	} menu;

signals:
	void pathDeleted(nodeConnect*);

protected slots:
	void hoverEnterEvent (QGraphicsSceneHoverEvent *event) override;
	void hoverLeaveEvent (QGraphicsSceneHoverEvent *event) override;
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

public slots:
	void clearConnection (const nodeVar*);
	void categorySelected(varCategory);

public:
	[[nodiscard]] int type() const override		  { return Type; }
	[[nodiscard]] nodeCtrl* getOriginNode() const { return attr.sourceNode; }
	[[nodiscard]] nodeCtrl* getTargetNode() const { return attr.targetNode; }
	[[nodiscard]] nodeVar*  getOriginVar () const { return attr.sourceVar;  }
	[[nodiscard]] nodeVar*  getTargetVar () const { return attr.targetVar;  }

	void setOriginNode(nodeCtrl* onode) { attr.sourceNode = onode; }
	void setTargetNode(nodeCtrl* tnode) { attr.targetNode = tnode; }
	void setOriginVar (nodeVar*  ovar)  { attr.sourceVar  = ovar;  }
	void setTargetVar (nodeVar*  tvar)  { attr.targetVar  = tvar;  }

	void clear  () { curve.path.clear(); setPath(QPainterPath()); }
	void connect(QPointF);
	void connect(QPointF, QPointF);
	void setAttr(nodeCtrl*, nodeVar*, nodeCtrl*, nodeVar*);
	void update ();
};

#endif //PATHELEMENT_H
