/*  -----------------------------------
 *  Project     : sapiens
 *  File        : CoreGui.cpp
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

/*  Class header    */
#include "core/core_gui.h"

/*  QtWidgets module    */
#include <QShortcut>
#include <QTabBar>

/*  Class constructor   */
CoreGui::CoreGui(const int& xs, const int& ys, QApplication* app) :

/*  Initializer list    */
//  Initialize attribute(s)
	m_attr{xs, ys, app, QCursor(Qt::ArrowCursor)},

//  Initialize QTabWidget
	m_tab{
		//	QList to store the indices of tabbed widgets:
		QList<int>{},
		//  QTabWidget manages two children - <graph> and <setup>:
		new QTabWidget(this),
		//  QLayout is added onto QTabWidget to arrange buttons:
		new QGridLayout(m_tab.pointer),
		//  SchemaViewer (GUI where user constructs schematics):
		new SchemaViewer(m_tab.pointer),
		//  optimCtrl (page where user sets up the optimization problem):
		new optimCtrl(m_tab.pointer)
	},

//  Initialize m_groupbox
	m_groupbox{
		//  Qm_groupbox contains the buttons for switching m_tab
		new QGroupBox(m_tab.pointer),
		//  QHBoxLayout arranges the buttons
		new QHBoxLayout(m_groupbox.pointer),
		//  QToolButton
		new QToolButton(m_groupbox.pointer),
		//  QToolButton
		new QToolButton(m_groupbox.pointer),
		//  QLabel displays the shortcut to switch m_tab
		new QLabel(m_groupbox.pointer),
	}

//  -------------------------
//  Constructor (body) begin:
{
	//  Setup GUI properties:
	resize(QSize(m_attr.ws, m_attr.hs));
	setObjectName("CoreGui");
	setCentralWidget(m_tab.pointer);

	//  Insert SchemaViewer and QWidget into QTabWidget:
	m_tab.pointer->setLayout(m_tab.layout);
	m_tab.indices.append(m_tab.pointer->addTab(m_tab.graph, QString()));
	m_tab.indices.append(m_tab.pointer->addTab(m_tab.setup, QString()));
	m_tab.pointer->tabBar()->hide();

	m_tab.layout->setContentsMargins(0, 4, 0, 0);
	m_tab.layout->setSpacing(2);
	m_tab.layout->addWidget(m_groupbox.pointer, 0, 1);
	m_tab.layout->addWidget(m_groupbox.pointer, 1, 1);
	m_tab.layout->addWidget(m_groupbox.label, 2, 1);
	m_tab.layout->setRowStretch(3, 10);
	m_tab.layout->setColumnStretch(0, 10);
	m_tab.layout->setColumnStretch(2, 10);

	//  Set label text (shortcut hint) and customize:
	m_groupbox.label->setContentsMargins(1, 1, 1, 1);
	m_groupbox.label->setFont(QFont("Gill Sans", 14));
	m_groupbox.label->setText("Press <font color='red'>Alt</font> + <font color='red'>2</font>");
	m_groupbox.label->setAlignment(Qt::AlignCenter);

	//  Customize <graph> button appearance and behaviour:
	m_groupbox.graph->setIcon(QIcon(":/icons/drawer-alt.svg"));
	m_groupbox.graph->setIconSize(QSize(40, 20));
	m_groupbox.graph->setCheckable(true);
	m_groupbox.graph->setChecked(true);

	//	Customize <setup> button appearance and behaviour:
	m_groupbox.setup->setIcon(QIcon(":/icons/laptop-code.svg"));
	m_groupbox.setup->setIconSize(QSize(40, 20));
	m_groupbox.setup->setCheckable(true);

	//  Add tool buttons to m_groupbox layout and customize:
	m_groupbox.layout->setContentsMargins(4, 4, 4, 4);
	m_groupbox.layout->addWidget(m_groupbox.graph);
	m_groupbox.layout->addWidget(m_groupbox.setup);
	m_groupbox.pointer->setLayout(m_groupbox.layout);

	const auto graphShortcut = new QShortcut(QKeySequence(Qt::ALT | Qt::Key_1), m_tab.pointer);
	const auto setupShortcut = new QShortcut(QKeySequence(Qt::ALT | Qt::Key_2), m_tab.pointer);

	//  Connect buttons to event handlers:™¡
	connect(graphShortcut, &QShortcut::activated, [&]() { showGraph(); });
	connect(setupShortcut, &QShortcut::activated, [&]() { showSetup(); });
	connect(m_groupbox.graph, &QToolButton::clicked, [&]() { showGraph(); });
	connect(m_groupbox.setup, &QToolButton::clicked, [&]() { showSetup(); });

	//	Show GUI
	show();

	//	Emit initialized() signal:
	emit initialized();
}

void //	Shows the <graph> tab when toggled by the user:
CoreGui::showGraph() {
	//  Toggle checked button, show graph tab:
	m_groupbox.pointer->show();
	m_groupbox.label->show();
	m_groupbox.graph->setChecked(true);
	m_groupbox.setup->setChecked(false);
	m_tab.pointer->setCurrentIndex(m_tab.indices[0]);
}

void //	Shows the <setup> tab when toggled by the user:
CoreGui::showSetup() {
	//  Toggle checked button, show setup tab:
	m_groupbox.pointer->hide();
	m_groupbox.label->hide();
	m_groupbox.graph->setChecked(false);
	m_groupbox.setup->setChecked(true);
	m_tab.pointer->setCurrentIndex(m_tab.indices[1]);
}
