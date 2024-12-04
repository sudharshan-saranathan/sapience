//
// Created by Sudharshan Saranathan on 29/11/24.
//

#include <QDialog>
#include <QComboBox>
#include <QListView>
#include <QShortcut>
#include <QGridLayout>
#include <QToolButton>
#include <QHeaderView>
#include <QModelIndex>
#include <QTableWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QStringListModel>

#include "node/nodeCtrl.h"


void nodeCtrl::actionSetup() const {

	auto dialog = QDialog(scene()->views()[0]);
	auto layout = QGridLayout();
	auto arrow  = QToolButton(&dialog);

	auto nodeData  = QTableWidget(3, 4, &dialog);
	auto eqnsView  = QListView(&dialog);
	auto textEdit  = QTextEdit(&dialog);
	auto separator = QFrame(&dialog);
	auto namesList = QStringList();

	//	Set the layout on the comboBox:
	dialog.setContentsMargins(4, 4, 4, 4);
	dialog.setFixedSize(720, 480);
	dialog.setLayout(&layout);
	dialog.setWindowTitle("Node Setup");

	//	Add widgets to the layout:
	layout.setContentsMargins(0, 0, 0, 0);
	layout.addWidget(&textEdit, 0, 0, 4, 1, Qt::AlignTop);
	layout.addWidget(&nodeData, 0, 2, Qt::AlignTop);
	layout.addWidget(&separator, 0, 1, 3, 1);
	layout.addWidget(&arrow, 1, 0, Qt::AlignBottom | Qt::AlignHCenter);
	layout.addWidget(&eqnsView, 1, 2, 2, 1,  Qt::AlignBottom);
	layout.setRowStretch(1, 10);
	layout.setSpacing(2);

	//	Customize QTextEditor and QListView objects:
	textEdit.setPlaceholderText("1. Enter equations in residual form\n2. Enter one equation per line \n"
								"3. Press <Enter> to start a new line\n4. Press <Ctrl+Enter> to save equations\n");

	textEdit.setMinimumHeight(470);
	eqnsView.setStyleSheet("QListView {"
								"border: none;"
								"background: white;"
								"color: #187795; }");

	//	Customize arrow button:
	arrow.setIcon(QIcon(":/icons/arrow-right-solid.svg"));
	arrow.setIconSize(QSize(20, 20));
	arrow.raise();
	arrow.setStyleSheet("QToolButton {border: 1px solid black; background: white;}"
		"QToolButton:hover {background: gray;}"
		"QToolButton:pressed {border: 1px solid black; background : #9EE37D;}");

	//	Customize separator:
	separator.setFrameShape(QFrame::VLine);
	separator.setFrameShadow(QFrame::Raised);
	separator.setFixedWidth(1);
	separator.setStyleSheet("QFrame {"
		"border				: none;"
		"border-radius		: 4px;"
		"background-color	: gray;}");

	//	----------------------------------------------------------------------------------------------------------------
	//	Add items to the table:

	nodeData.setHorizontalHeaderLabels({"Symbol", "Name", "Stream", "Category"});
	nodeData.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	nodeData.horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	nodeData.horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	nodeData.horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
	nodeData.horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);

	auto variableList = list.inp + list.out;
	for (int j = 0; j < variableList.size(); j++) {

		if (j == nodeData.rowCount())
			nodeData.insertRow(nodeData.rowCount());

		namesList.append(variableList[j]->symbol());

		nodeData.setItem(j, 1, new QTableWidgetItem(variableList[j]->name()));
		nodeData.setItem(j, 0, new QTableWidgetItem(variableList[j]->symbol()));
		nodeData.setItem(j, 3, new QTableWidgetItem(variableList[j]->getCategoryName()));
		nodeData.setItem(j, 2, new QTableWidgetItem(variableList[j]->getVariableType() == Input  ? "Input"  :
													variableList[j]->getVariableType() == Output ? "Output" : "Parameter"));

		const auto color = variableList[j]->getVariableType() == Input  ? QColor("#91E5F6") :
						   variableList[j]->getVariableType() == Output ? QColor("#ffb703") : QColor(Qt::gray);

		nodeData.item(j, 0)->setBackground(color);
		nodeData.item(j, 0)->setTextAlignment(Qt::AlignCenter);
		nodeData.item(j, 2)->setTextAlignment(Qt::AlignCenter);
	}

	/*	This code section handles auto-completion of variable(s) when the user is typing the equation
	 *	in the text editor. If this feature is needed, uncomment the lines below. However, since the
	 *	equations are typed using the variable's symbolic name (e.g. x1, x2, x3, ...), the auto-complete
	 *	isn't really required.
	 */

	auto itemModel = QStringListModel(namesList);
	auto completer = QCompleter(&itemModel, &textEdit);

	//	Attach the text widget to the auto-completer:
	completer.setCompletionMode(QCompleter::PopupCompletion);
	completer.setCaseSensitivity(Qt::CaseInsensitive);
	completer.setWidget(&textEdit);
	completer.setModel(&itemModel);

	connect(&textEdit, &QTextEdit::textChanged, [&]() {

		auto cursor = textEdit.textCursor();
		auto point  = textEdit.cursorRect(cursor).bottomLeft();

		cursor.select(QTextCursor::WordUnderCursor);
		if (!cursor.selectedText().isEmpty() &&        //	The popup is only displayed after the user has begun typing
		    cursor.selectedText().at(0) == QChar('X')) //	Disable auto-complete for variables (e.g. x1, x2, ...)
		{
			completer.setCompletionPrefix(cursor.selectedText());
			completer.complete(QRect(point.x(), point.y(), 100, 5));
		}
	});
	connect(&completer, QOverload<const QString &>::of(&QCompleter::activated), [&](const QString &text) {
		autoCompletion(text, &textEdit);
		completer.popup()->hide();
	});

	auto shortcut = QShortcut(&textEdit);
	shortcut.setKey(QKeySequence(Qt::CTRL | Qt::Key_Return));

	// Connect the shortcut to a lambda function
	connect(&shortcut, &QShortcut::activated, [&textEdit]() {

		const auto textEditInput = textEdit.toPlainText();
		const auto equationsList = textEditInput.split('\n');

		if (!textEditInput.isEmpty()) {
			for (const auto& equation : equationsList)
				amplDatabase::equationsList.append(equation);
		}
	});

	dialog.exec();
}

void nodeCtrl::autoCompletion(const QString &text, const QTextEdit *editor) {
	QTextCursor cursor = editor->textCursor();
	cursor.select(QTextCursor::WordUnderCursor);
	cursor.insertText(text);
}