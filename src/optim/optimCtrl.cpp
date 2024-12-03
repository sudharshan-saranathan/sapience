//
// Created by Sudharshan Saranathan on 03/12/24.
//

#include "optim/optimCtrl.h"

#include <QFile>
#include <QMimeData>
#include <QShortcut>
#include <QDragEnterEvent>

optimCtrl::~optimCtrl() {}


optimCtrl::optimCtrl(QWidget* parent) :
/*	Initializer list	*/
//	Base-class constructor:
	QWidget(parent),
//	Virtual Base-class initialization:
	OutputHandler(),
//	Widget:
	widget{new QHBoxLayout(this)},
//	Text Editor:
	editor{
		new customEditor(QColor("#696D7D"), this),
		new QGridLayout,
		{
			new QPushButton(QIcon(":/icons/FontAwesome/svgs/solid/play.svg"), QString(), this),
			new QPushButton(QIcon(":/icons/FontAwesome/svgs/solid/file.svg"), QString(), this),
			new QPushButton(QIcon(":/icons/FontAwesome/svgs/solid/floppy-disk.svg"), QString(), this),
			new QPushButton(QIcon(":/icons/FontAwesome/svgs/solid/eraser.svg"), QString(), this),
			new QPushButton(QIcon(":/icons/FontAwesome/svgs/solid/wrench.svg"), QString(), this)
		}
	},
	workbench{
		new QTabWidget(this),
		new customEditor(QColor("#E9F3E2")),
	},
	optimizer{AMPL(Environment()), "ipopt"}
{
	setAcceptDrops(false);
	setContentsMargins(0, 0, 0, 0);

	optimizer.engine.setOption("Solver", optimizer.solver.toUtf8().constData());
	optimizer.engine.setOutputHandler(this);

	widget.layout->setSpacing(2);
	widget.layout->addWidget(editor.pointer);
	widget.layout->addWidget(workbench.tabs);
	widget.layout->setContentsMargins(0, 0, 0, 0);

	editor.pointer->setPlaceholderText("# Editor for AMPL/GAMS-models");
	editor.pointer->setAcceptDrops(true);
	editor.pointer->setLayout(editor.layout);

	editor.layout->setSpacing(20);
	editor.layout->setContentsMargins(4, 4, 20, 16);
	editor.layout->addWidget(editor.buttons[0], 1, 1, Qt::AlignBottom);
	editor.layout->addWidget(editor.buttons[1], 2, 1, Qt::AlignBottom);
	editor.layout->addWidget(editor.buttons[2], 3, 1, Qt::AlignBottom);
	editor.layout->addWidget(editor.buttons[3], 4, 1, Qt::AlignBottom);
	editor.layout->addWidget(editor.buttons[4], 5, 1, Qt::AlignBottom);
	editor.layout->setRowStretch(0, 5);
	editor.layout->setColumnStretch(0, 5);

	editor.buttons[0]->setFixedSize(QSize(30, 30));
	editor.buttons[1]->setFixedSize(QSize(30, 30));
	editor.buttons[2]->setFixedSize(QSize(30, 30));
	editor.buttons[3]->setFixedSize(QSize(30, 30));
	editor.buttons[4]->setFixedSize(QSize(30, 30));

	workbench.tabs->setMinimumWidth(480);
	workbench.tabs->setTabPosition(QTabWidget::West);
	workbench.tabs->addTab(workbench.display, "Output Log");
	workbench.tabs->addTab(new QWidget, "Widget 1");
	workbench.tabs->addTab(new QWidget, "Widget 2");

	workbench.display->setReadOnly(true);
	workbench.display->setAcceptDrops(false);
	workbench.display->setTextColor(Qt::black);

	const auto graphSwitch = new QShortcut(QKeySequence(Qt::ALT | Qt::Key_Tab), this);

	connect(graphSwitch, &QShortcut::activated, this, &optimCtrl::tabSwitched);
	connect(editor.buttons[0], &QPushButton::clicked, this, &optimCtrl::runOpt);
	connect(editor.buttons[1], &QPushButton::clicked, [&](){ editor.pointer->open(); });
	connect(editor.buttons[2], &QPushButton::clicked, [&](){ editor.pointer->save(); });
	connect(editor.buttons[3], &QPushButton::clicked, [&](){ editor.pointer->clear(); });
}

void optimCtrl::runOpt() {

	qInfo() << __FILE__ << __func__;
	workbench.display->clear();
	optimizer.engine.reset();

	const auto model = editor.pointer->toPlainText().toStdString();

	std::vector<std::string> tokens;
	std::stringstream ss(model);
	std::string token;

	optimizer.engine.setOption("solver", optimizer.solver.toUtf8().constData());
	while (std::getline(ss, token, '\n')) {
		tokens.push_back(token);
		if (!token.empty() && token[0] != '#') {
			try {
				qInfo() << token;
				optimizer.engine.eval(fmt::CStringRef(token));
			}
			catch (AMPLException& exception)		{ qDebug() << exception.what(); }
			catch (std::runtime_error& error)		{ qDebug() << error.what(); }
			catch (std::out_of_range& error)		{ qDebug() << error.what(); }
			catch (std::invalid_argument& error)	{ qDebug() << error.what(); }
			catch (std::logic_error& error)			{ qDebug() << error.what(); }
		}
	}
}