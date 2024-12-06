//
// Created by Sudharshan Saranathan on 05/12/24.
//

#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QGraphicsTextItem>

class customLabel : public QGraphicsTextItem {

	Q_OBJECT
	Q_DISABLE_COPY_MOVE(customLabel)

public:
	~customLabel() override = default;
	explicit
	customLabel(const QString& text = QString(), QGraphicsItem* parent = nullptr);

signals:
	void textChanged();

};

#endif //CUSTOMLABEL_H
