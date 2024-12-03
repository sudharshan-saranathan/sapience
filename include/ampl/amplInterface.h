//
// Created by Sudharshan Saranathan on 01/12/24.
//

#pragma once

#ifndef AMPLINTERFACE_H
#define AMPLINTERFACE_H

#include <QEvent>
#include <QMovie>
#include <QToolBar>
#include <QMimeData>
#include <iostream>
#include <QDropEvent>
#include <QPushButton>
#include <QGridLayout>
#include <QGraphicsView>
#include <QDialogButtonBox>
#include <QListView>
#include <QTableWidget>
#include <ampl/ampl.h>

#include "node/nodeCtrl.h"
#include "node/nodeVar.h"

using namespace ampl;
using QButtons = QDialogButtonBox;

class amplInterface final : public QWidget, public OutputHandler {
	Q_OBJECT
	Q_DISABLE_COPY_MOVE(amplInterface)

	Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
	explicit amplInterface(QWidget *parent = nullptr);

	void open(const QString &) const;

protected slots:
	void dragEnterEvent(QDragEnterEvent *event) override;

	void dropEvent(QDropEvent *event) override;

	void runAMPL() const;

	void output(const QString &) const;

	void output(output::Kind, const char *) override;

private:
	struct _attr_ {
	} attr;

	struct _layout_ {
		QGridLayout *pointer = nullptr;
	} layout;

	struct _editor_ {
		QTextEdit *  pointer = nullptr;
		QGridLayout *layout  = nullptr;
		QButtons *   toolbar = nullptr;
		QPushButton *run     = nullptr;
		QPushButton *opt     = nullptr;
		QPushButton *load    = nullptr;
		QPushButton *save    = nullptr;
		QPushButton *clear   = nullptr;
	} editor;

	struct _settings_ {
		QTabWidget * pointer    = nullptr;
		QWidget *    varGrapher = nullptr;
		QGridLayout *layout     = nullptr;
		QTabBar *    pageSelect = nullptr;
	} settings;

	struct _setup_ {
		QWidget *     pointer      = nullptr;
		QGridLayout * layout       = nullptr;
		QListView *   categoryView = nullptr;
		QListView *   nodeView     = nullptr;
		QTableWidget *dataTable    = nullptr;
	} setup;

	struct _ampl_ {
		Environment env;
		AMPL *      engine;
		QString     solver;
	} ampl;

	struct _result_ {
		QTextEdit *display = nullptr;
	} result;

signals:
	void tabSwitched();

	void modelLoaded();
};

#endif //AMPLINTERFACE_H
