//
// Created by Sudharshan Saranathan on 01/12/24.
//

#include <QFile>
#include <QShortcut>

#include "ampl/amplInterface.h"
#include "core/coreGUI.h"

#include "ampl/ampl.h"
#include <iostream>
#include <QHeaderView>
#include <QStringListModel>
#include <QThread>
#include <string>
#include <fmt/core.h>

#define RUN_DEFAULT ":/icons/FontAwesome/svgs/solid/play.svg"
#define RUN_BUSY    ":/icons/FontAwesome/svgs/solid/play.svg"
#define RUN_DONE    ":/icons/FontAwesome/svgs/solid/play.svg"

amplInterface::amplInterface(QWidget* parent) :
/*	Initializer list	*/
//	Base-class constructor
	QWidget(parent),
//	Struct elements:
	layout{new QGridLayout},
//	struct _modelEditor_:
	editor{
		new QTextEdit,
		new QGridLayout,
		new QDialogButtonBox,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
	},
//	struct _toolSettings_:
	settings{
		new QTabWidget,
		new QWidget(settings.pointer),
		new QGridLayout,
		new QTabBar
	},
//	struct _setup_:
	setup{
		new QWidget, new QGridLayout,
		new QListView(setup.pointer),
		new QListView(setup.pointer),
		new QTableWidget(50, 6, setup.pointer)
	},
//	struct _amplSettings_:
	ampl{
		Environment("/Applications/AMPL/"),
		new AMPL(ampl.env),
		"ipopt",
	},
//	struct _amplOutput_:
	result{new QTextEdit}
{
	//	Initialize AMPL amplSettings:
	ampl.engine->setOption("solver", ampl.solver.toUtf8().constData());
	ampl.engine->setOutputHandler(this);

	//	Customize appearance and accept drop events:
	setContentsMargins(0, 0, 0, 0);
	setLayout(layout.pointer);
	setAcceptDrops(true);											//	For accepting file-drops into the editor

	layout.pointer->setSpacing(2);
	layout.pointer->setContentsMargins(0, 0, 0, 0);
	layout.pointer->addWidget(editor.pointer, 0, 0, 4, 1);
	layout.pointer->addWidget(settings.pointer, 0, 1, 4, 1);

	editor.pointer->installEventFilter(this);
	editor.pointer->setAcceptDrops(false);
	editor.pointer->setPlaceholderText("# AMPL Model Editor");

	editor.pointer->setLayout(editor.layout);
	editor.layout->setContentsMargins(4, 4, 4, 4);
	editor.layout->addWidget(editor.toolbar, 1, 0, Qt::AlignRight | Qt::AlignBottom);

	editor.toolbar->setContentsMargins(4, 4, 12, 4);
	editor.toolbar->setOrientation(Qt::Vertical);

	editor.run   = editor.toolbar->addButton(QString(), QDialogButtonBox::NoRole);
	editor.load  = editor.toolbar->addButton(QString(), QDialogButtonBox::NoRole);
	editor.save  = editor.toolbar->addButton(QString(), QDialogButtonBox::NoRole);
	editor.clear = editor.toolbar->addButton(QString(), QDialogButtonBox::NoRole);
	editor.opt   = editor.toolbar->addButton(QString(), QDialogButtonBox::NoRole);

	editor.run->setFixedSize(QSize(30, 30));
	editor.opt->setFixedSize(QSize(30, 30));
	editor.save->setFixedSize(QSize(30, 30));
	editor.load->setFixedSize(QSize(30, 30));
	editor.clear->setFixedSize(QSize(30, 30));

	editor.run->setIcon(QIcon(":/icons/FontAwesome/svgs/solid/play.svg"));
	editor.load->setIcon(QIcon(":/icons/FontAwesome/svgs/solid/file.svg"));
	editor.save->setIcon(QIcon(":/icons/FontAwesome/svgs/solid/floppy-disk.svg"));
	editor.clear->setIcon(QIcon(":/icons/FontAwesome/svgs/solid/eraser.svg"));
	editor.opt->setIcon(QIcon(":/icons/FontAwesome/svgs/solid/wrench.svg"));

	result.display->setReadOnly(true);
	ampl.engine->setOutputHandler(this);

	settings.pointer->setTabPosition(QTabWidget::West);
	settings.pointer->setContentsMargins(0, 0, 0, 0);
	settings.pointer->addTab(setup.pointer, "Optimization Setup");
	settings.pointer->addTab(settings.varGrapher, "Graph");
	settings.pointer->addTab(result.display,   "AMPL log");

	setup.dataTable->setHorizontalHeaderLabels({"Variable", "Name", "Initial Value", "Minimum", "Maximum", "Result"});
	setup.dataTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setup.dataTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	setup.dataTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	setup.dataTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
	setup.dataTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
	setup.dataTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
	setup.dataTable->horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);

	setup.pointer->setContentsMargins(0, 0, 0, 0);
	setup.pointer->setLayout(setup.layout);

	setup.layout->setContentsMargins(0, 0, 0, 0);
	setup.layout->setSpacing(1);
	setup.layout->setColumnStretch(1, 20);
	setup.layout->addWidget(setup.categoryView, 0, 0);
	setup.layout->addWidget(setup.nodeView, 0, 1);
	setup.layout->addWidget(setup.dataTable, 2, 0, 1, 2);

	//	Install shortcuts for different UI elements:
	const auto tabSwitch = new QShortcut(QKeySequence(Qt::ALT | Qt::Key_Tab), this);			//	To switch back to graph-mode

	connect(tabSwitch , &QShortcut::activated, [&](){emit tabSwitched(); });
	connect(editor.run, &QPushButton::pressed, this, &amplInterface::runAMPL);
	connect(editor.clear, &QPushButton::pressed, [this]() {
		ampl.engine->reset();
		editor.pointer->clear();
		result.display->clear();
	});

	auto model = new QStringListModel();
	auto slist = QList<QString>();
	setup.categoryView->setModel(model);

	for (auto item : categoryList) {
		slist.append(item.getName());
	}

	model->setStringList(QStringList(slist));
	setup.categoryView->show();
}

void amplInterface::dragEnterEvent(QDragEnterEvent* event) {
	if (event->mimeData()->hasUrls()) {
		event->acceptProposedAction();
	}
}

void amplInterface::dropEvent(QDropEvent* event) {
	if (event->mimeData()->hasUrls()) {
		if (const auto urls = event->mimeData()->urls(); !urls.isEmpty()) {
			qInfo() << __FILE__ << __func__;
			qDebug() << "\t- File: " << urls.first().toLocalFile();

			const auto filename = urls.first().toLocalFile();
			open(filename);
		}
	}
}

void amplInterface::open(const QString& filePath) const {

	qInfo() << __FILE__ << __func__;									// Print file and function name
	QFile file(filePath);

	// Open the file in read-only mode
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		const auto textStream(&file);									// Create a text stream
		const auto contents = textStream->readAll();					// Read the contents

		editor.pointer->setText(contents);								// Display the contents on the QTextEdit
		file.close();													// Close the file after reading
	}
}

void amplInterface::runAMPL() const {

	qInfo() << __FILE__ << __func__;
	result.display->clear();
	ampl.engine->reset();

	const auto model = editor.pointer->toPlainText().toStdString();

	std::vector<std::string> tokens;
	std::stringstream ss(model);
	std::string token;

	while (std::getline(ss, token, '\n')) {
		tokens.push_back(token);
		if (!token.empty() && token[0] != '#') {
			try {
				ampl.engine->eval(fmt::CStringRef(token));
			}
			catch (AMPLException& exception)		{ qDebug() << exception.what(); }
			catch (std::runtime_error& error)		{ qDebug() << error.what(); }
			catch (std::out_of_range& error)		{ qDebug() << error.what(); }
			catch (std::invalid_argument& error)	{ qDebug() << error.what(); }
			catch (std::logic_error& error)			{ qDebug() << error.what(); }
		}
	}
}

void amplInterface::output(output::Kind kind, const char* msg) {

	result.display->append(msg);
}

void amplInterface::output(const QString& entityName) const {

	qInfo() << __FILE__ << __func__;
	const auto entityNameCString = fmt::CStringRef(entityName.toStdString());
	try {
		std::cout << ampl.engine->getVariable(entityNameCString).value() << std::endl;
	}
	catch (ampl::AMPLException& exception)		{ qDebug() << exception.what(); }
	catch (std::runtime_error& error)			{ qDebug() << error.what(); }
	catch (std::out_of_range& error)			{ qDebug() << error.what(); }
	catch (std::invalid_argument& error)		{ qDebug() << error.what(); }
	catch (std::logic_error& error)				{ qDebug() << error.what(); }
	catch (...) { qDebug() << "Unknown error occured"; }
}
