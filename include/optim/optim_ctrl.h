//
// Created by Sudharshan Saranathan on 03/12/24.
//

#ifndef OPTIMCTRL_H
#define OPTIMCTRL_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

#include "ampl/ampl.h"
#include "custom/custom_editor.h"
#include "node/node_ctrl.h"

using namespace ampl;

class optimCtrl final : public QWidget, public OutputHandler {

	Q_OBJECT
	Q_DISABLE_COPY_MOVE(optimCtrl)
	Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
	~optimCtrl() override;
	 optimCtrl(QWidget* parent = nullptr);

signals:
	void tabSwitched();

public slots:
	void runOpt();
	void output(output::Kind kind, const char* msg) override { m_workbench.display->append(msg); }

private:
	struct _attr_ {
	} attr;

	struct _widget_ {
		QHBoxLayout* layout;
	} m_widget;

	struct _editor_ {
		CustomEditor* pointer = nullptr;
		QGridLayout*  layout = nullptr;
		QPushButton*  buttons[5] = {nullptr};
	} m_editor;

	struct _workbench_ {
		QTabWidget*   tabs    = nullptr;
		CustomEditor* display = nullptr;
	} m_workbench;

	struct _optimizer_ {
		AMPL    engine;
		QString solver;
	} m_optimizer;
};

#endif //OPTIMCTRL_H
