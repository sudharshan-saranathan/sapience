//
// Created by Sudharshan Saranathan on 04/12/24.
//

#ifndef NODECONSTANT_H
#define NODECONSTANT_H

#include <QGraphicsTextItem>

class nodeConstant : QGraphicsTextItem {

	Q_OBJECT
	Q_DISABLE_COPY_MOVE(nodeConstant)
	Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
	~nodeConstant() override = default;
	explicit
	nodeConstant(const QString&, QGraphicsItem* parent = nullptr);

private:
	struct {
		QString title;
	} attr;

};

#endif //NODECONSTANT_H
