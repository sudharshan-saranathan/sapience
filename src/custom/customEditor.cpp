//
// Created by Sudharshan Saranathan on 03/12/24.
//

#include <QFile>
#include <QMimeData>
#include <QDragEnterEvent>

#include "custom/customEditor.h"


customEditor::customEditor(QColor backgroundColor, QWidget *parent) :
/*	Initializer list	*/
//	Base-class constructor:
	QTextEdit(parent)
{
	setAcceptDrops(true);
	setStyleSheet("background: " + backgroundColor.name() + ";");
}

void customEditor::open(const QString &filePath) {
	if (QFile file(filePath); file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		const auto text = file.readAll();
		setText(text);
		file.close();
	}
}

void customEditor::save(const QString &filePath) const {

	const auto contents = toPlainText();
	if (QFile file(filePath); file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		file.write(contents.toUtf8().data());
		file.close();
	}
}

void customEditor::dragEnterEvent(QDragEnterEvent* event) {

	if (event->mimeData()->hasUrls())
		event->acceptProposedAction();
}

void customEditor::dropEvent(QDropEvent* event) {

	if (event->mimeData()->hasUrls()) {
		if (const auto urls = event->mimeData()->urls(); !urls.isEmpty()) {
			qInfo() << __FILE__ << __func__;
			qDebug() << "\t- File: " << urls.first().toLocalFile();
			const auto filePath = urls.first().toLocalFile();
			if (auto file = QFile(filePath); file.open(QIODevice::ReadOnly | QIODevice::Text)) {
				const auto richText = QString(file.readAll());
				setText(richText);
			}
		}
	}
}