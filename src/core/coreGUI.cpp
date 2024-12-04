/*  -----------------------------------
 *  Project     : sapiens
 *  File        : coreGUI.cpp
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

/*  Class header    */
#include "core/coreGUI.h"

/*  QtWidgets module    */
#include <QShortcut>
#include <QTabBar>

/*  Class constructor   */
coreGUI::coreGUI(const int& xs, const int& ys, QApplication* app) :

/*  Initializer list    */
//  Initialize Attribute(s)
	attr{xs, ys, app, QCursor(Qt::ArrowCursor)},

//  Initialize QTabWidget
	tabs{
		//	QList to store the indices of tabbed widgets
		QList<int>{},
		//  QTabWidget manages two children - <graph> and <setup>
		new QTabWidget(this),
		//  QLayout is added onto QTabWidget to arrange buttons
		new QGridLayout(tabs.pointer),
		//  schemaViewer (GUI where user constructs schematics)
		new schemaViewer(tabs.pointer),
		//  optimCtrl (page where user sets up the optimization problem)
		new optimCtrl(tabs.pointer)
	},

//  Initialize groupbox
	groupbox{
		//  QGroupBox contains the buttons for switching tabs
		new QGroupBox(tabs.pointer),
		//  QHBoxLayout arranges the buttons
		new QHBoxLayout(groupbox.pointer),
		//  QToolButton
		new QToolButton(groupbox.pointer),
		//  QToolButton
		new QToolButton(groupbox.pointer),
		//  QLabel displays the shortcut to switch tabs
		new QLabel(groupbox.pointer),
	}

//  -------------------------
//  Constructor (body) begin:
{
	//  Assert pointer allocations:
	Q_ASSERT(attr.app);
	Q_ASSERT(tabs.pointer);
	Q_ASSERT(tabs.layout);
	Q_ASSERT(tabs.graph);
	Q_ASSERT(tabs.setup);
	Q_ASSERT(groupbox.pointer);
	Q_ASSERT(groupbox.layout);
	Q_ASSERT(groupbox.graph);
	Q_ASSERT(groupbox.setup);
	Q_ASSERT(groupbox.label);

	//  Setup GUI properties:
	resize(QSize(attr.ws, attr.hs));
	setObjectName("coreGUI");
	setCentralWidget(tabs.pointer);

	//  Insert schemaViewer and QWidget into QTabWidget:
	tabs.pointer->setLayout(tabs.layout);
	tabs.num.append(tabs.pointer->addTab(tabs.graph, QString()));
	tabs.num.append(tabs.pointer->addTab(tabs.setup, QString()));
	tabs.pointer->tabBar()->hide();

	tabs.layout->setContentsMargins(0, 4, 0, 0);
	tabs.layout->setSpacing(2);
	tabs.layout->addWidget(groupbox.pointer, 0, 1);
	tabs.layout->addWidget(groupbox.pointer, 1, 1);
	tabs.layout->addWidget(groupbox.label, 2, 1);
	tabs.layout->setRowStretch(3, 10);
	tabs.layout->setColumnStretch(0, 10);
	tabs.layout->setColumnStretch(2, 10);

	//  Set label text (shortcut hint) and customize:
	groupbox.label->setContentsMargins(1, 1, 1, 1);
	groupbox.label->setFont(QFont("Gill Sans", 14));
	groupbox.label->setText("Press <font color='red'>Alt</font> + <font color='red'>2</font>");
	groupbox.label->setAlignment(Qt::AlignCenter);

	//  Customize <graph> button appearance and behaviour:
	groupbox.graph->setIcon(QIcon(":/icons/drawer-alt.svg"));
	groupbox.graph->setIconSize(QSize(40, 20));
	groupbox.graph->setCheckable(true);
	groupbox.graph->setChecked(true);

	//	Customize <setup> button appearance and behaviour:
	groupbox.setup->setIcon(QIcon(":/icons/laptop-code.svg"));
	groupbox.setup->setIconSize(QSize(40, 20));
	groupbox.setup->setCheckable(true);

	//  Add tool buttons to groupbox layout and customize:
	groupbox.layout->setContentsMargins(4, 4, 4, 4);
	groupbox.layout->addWidget(groupbox.graph);
	groupbox.layout->addWidget(groupbox.setup);
	groupbox.pointer->setLayout(groupbox.layout);

	const auto graphShortcut = new QShortcut(QKeySequence(Qt::ALT | Qt::Key_1), tabs.pointer);
	const auto setupShortcut = new QShortcut(QKeySequence(Qt::ALT | Qt::Key_2), tabs.pointer);

	//  Connect buttons to event handlers:™¡
	connect(graphShortcut, &QShortcut::activated, [&]() { showGraph(); });
	connect(setupShortcut, &QShortcut::activated, [&]() { showSetup(); });
	connect(groupbox.graph, &QToolButton::clicked, [&]() { showGraph(); });
	connect(groupbox.setup, &QToolButton::clicked, [&]() { showSetup(); });

	//	Show GUI
	show();

	//	Emit initialized() signal:
	emit initialized();
}

void //	Shows the <graph> tab when called
coreGUI::showGraph() {
	//  Toggle checked button, show graph tab:
	groupbox.pointer->show();
	groupbox.label->show();
	groupbox.graph->setChecked(true);
	groupbox.setup->setChecked(false);
	tabs.pointer->setCurrentIndex(tabs.num[0]);
}

void //	Shows the <setup> tab when called
coreGUI::showSetup() {
	//  Toggle checked button, show setup tab:
	groupbox.pointer->hide();
	groupbox.label->hide();
	groupbox.graph->setChecked(false);
	groupbox.setup->setChecked(true);
	tabs.pointer->setCurrentIndex(tabs.num[1]);
}
