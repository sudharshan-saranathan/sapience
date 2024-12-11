//
// Created by Sudharshan Saranathan on 04/12/24.
//

#ifndef NODEPARAMS_H
#define NODEPARAMS_H

#include <QListView>

class NodeParams final : public QListView {

	Q_OBJECT Q_DISABLE_COPY_MOVE(NodeParams)
	Q_CLASSINFO("Author", "Sudharshan Saranathan")public:

	~NodeParams() override = default;
	NodeParams();

};

#endif //NODEPARAMS_H
