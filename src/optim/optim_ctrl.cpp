//
// Created by Sudharshan Saranathan on 03/12/24.
//

#include "optim/optim_ctrl.h"

#include <QFile>
#include <QMimeData>
#include <QDragEnterEvent>

optimCtrl::~optimCtrl() {}


optimCtrl::optimCtrl(QWidget* parent) :
/*	Initializer list	*/
//	Base-class constructor:
	QWidget(parent),
//	Virtual Base-class initialization:
	OutputHandler(),
//	Widget:
	m_widget{new QHBoxLayout(this)},
//	Text Editor:
	m_editor{
		new CustomEditor(QColor("#696D7D"), this),
		new QGridLayout,
		{
			new QPushButton(QIcon(":/icons/FontAwesome/svgs/solid/play.svg"), QString(), this),
			new QPushButton(QIcon(":/icons/FontAwesome/svgs/solid/file.svg"), QString(), this),
			new QPushButton(QIcon(":/icons/FontAwesome/svgs/solid/floppy-disk.svg"), QString(), this),
			new QPushButton(QIcon(":/icons/FontAwesome/svgs/solid/eraser.svg"), QString(), this),
			new QPushButton(QIcon(":/icons/FontAwesome/svgs/solid/wrench.svg"), QString(), this)
		}
	},
	m_workbench{
		new QTabWidget(this),
		new CustomEditor(QColor("#E9F3E2")),
	},
	m_optimizer{AMPL(Environment()), "ipopt"}
{
	setAcceptDrops(false);
	setContentsMargins(0, 0, 0, 0);

	m_optimizer.engine.setOption("Solver", m_optimizer.solver.toUtf8().constData());
	m_optimizer.engine.setOutputHandler(this);

	m_widget.layout->setSpacing(2);
	m_widget.layout->addWidget(m_editor.pointer);
	m_widget.layout->addWidget(m_workbench.tabs);
	m_widget.layout->setContentsMargins(0, 0, 0, 0);

	m_editor.pointer->setPlaceholderText("# Editor for AMPL/GAMS-models");
	m_editor.pointer->setAcceptDrops(true);
	m_editor.pointer->setLayout(m_editor.layout);

	m_editor.layout->setSpacing(20);
	m_editor.layout->setContentsMargins(4, 4, 20, 16);
	m_editor.layout->addWidget(m_editor.buttons[0], 1, 1, Qt::AlignBottom);
	m_editor.layout->addWidget(m_editor.buttons[1], 2, 1, Qt::AlignBottom);
	m_editor.layout->addWidget(m_editor.buttons[2], 3, 1, Qt::AlignBottom);
	m_editor.layout->addWidget(m_editor.buttons[3], 4, 1, Qt::AlignBottom);
	m_editor.layout->addWidget(m_editor.buttons[4], 5, 1, Qt::AlignBottom);
	m_editor.layout->setRowStretch(0, 5);
	m_editor.layout->setColumnStretch(0, 5);

	m_editor.buttons[0]->setFixedSize(QSize(30, 30));
	m_editor.buttons[1]->setFixedSize(QSize(30, 30));
	m_editor.buttons[2]->setFixedSize(QSize(30, 30));
	m_editor.buttons[3]->setFixedSize(QSize(30, 30));
	m_editor.buttons[4]->setFixedSize(QSize(30, 30));

	m_workbench.tabs->setMinimumWidth(480);
	m_workbench.tabs->setTabPosition(QTabWidget::West);
	m_workbench.tabs->addTab(m_workbench.display, "Output Log");
	m_workbench.tabs->addTab(new QWidget, "Widget 1");
	m_workbench.tabs->addTab(new QWidget, "Widget 2");

	m_workbench.display->setReadOnly(true);
	m_workbench.display->setAcceptDrops(false);
	m_workbench.display->setTextColor(Qt::black);

	connect(m_editor.buttons[0], &QPushButton::clicked, this, &optimCtrl::runOpt);
	connect(m_editor.buttons[1], &QPushButton::clicked, [&](){ m_editor.pointer->open(); });
	connect(m_editor.buttons[2], &QPushButton::clicked, [&](){ m_editor.pointer->save(); });
	connect(m_editor.buttons[3], &QPushButton::clicked, [&](){ m_editor.pointer->clear(); });
}

void optimCtrl::runOpt() {

#ifdef VERBOSE
	qInfo() << __FILE__ << __func__;
#endif

	m_workbench.display->clear();
	m_optimizer.engine.reset();

	const auto model = m_editor.pointer->toPlainText().toStdString();

	std::vector<std::string> tokens;
	std::stringstream ss(model);
	std::string token;

	m_optimizer.engine.setOption("solver", m_optimizer.solver.toUtf8().constData());
	while (std::getline(ss, token, '\n')) {
		tokens.push_back(token);
		if (!token.empty() && token[0] != '#') {
			try {
				qInfo() << token;
				m_optimizer.engine.eval(fmt::CStringRef(token));
			}
			catch (AMPLException& exception)		{ qDebug() << exception.what(); }
			catch (std::runtime_error& error)		{ qDebug() << error.what(); }
			catch (std::out_of_range& error)		{ qDebug() << error.what(); }
			catch (std::invalid_argument& error)	{ qDebug() << error.what(); }
			catch (std::logic_error& error)			{ qDebug() << error.what(); }
		}
	}
}