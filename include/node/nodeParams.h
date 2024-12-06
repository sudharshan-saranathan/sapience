//
// Created by Sudharshan Saranathan on 04/12/24.
//

#ifndef NODECONSTANT_H
#define NODECONSTANT_H

#include "nodeConnect.h"
#include "nodeCtrl.h"

#include <QGraphicsTextItem>


class nodeParams final : public QGraphicsTextItem, public variable {

	Q_OBJECT Q_DISABLE_COPY_MOVE(nodeParams)
	Q_CLASSINFO("Author", "Sudharshan Saranathan")public:

	~nodeParams() override = default;
	explicit
	nodeParams(const QString&, QGraphicsItem* parent = nullptr);

public:

	[[nodiscard]] QString
	name() { return attr.name; }

	[[nodiscard]] QString
	description() { return attr.description; }

private:
	struct {
		QString name;
		QString description;
	} attr;
};

#endif //NODECONSTANT_H
