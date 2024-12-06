//
// Created by Sudharshan Saranathan on 05/12/24.
//

#include "custom/customDialog.h"

customDialog::customDialog(const QString& text, const QString& hint, QWidget* parent) :
//	Initializer list:
//	Base-class constructor
	QDialog(parent),
//	Initialize layout:
	layout{new QVBoxLayout(this)},
//	Initialize QLineEdit:
	input{new QLineEdit(this), hint},
//	Initialize label:
	label{new QLabel(this), text}
//	Constructor (body) begin:
{
	setAttribute(Qt::WA_OpaquePaintEvent);
	setWindowFlag(Qt::FramelessWindowHint);
	setContentsMargins(0, 0, 0, 0);
	setFixedSize(200, 70);
	setStyleSheet("QDialog {" "padding	: 4px;" "border		: 1px solid #495867;" "border-radius : 10px;"
				  "background	: #495867;}");

	setLayout(layout);

	const auto separator = new QFrame(this);
	separator->setFrameShape(QFrame::HLine);
	separator->setFrameShadow(QFrame::Sunken);
	separator->setFixedHeight(1);
	separator->setFixedWidth(100);
	separator->setGeometry(50, 38, 100, 1);

	layout->setContentsMargins(0, 4, 0, 0);
	layout->setSpacing(2);
	layout->addWidget(label.pointer, 0, Qt::AlignCenter);
	layout->addWidget(separator, 1, Qt::AlignCenter);
	layout->addWidget(input.pointer, 2, Qt::AlignCenter);

	label.pointer->setText(text);
	label.pointer->setAlignment(Qt::AlignCenter);
	label.pointer->setStyleSheet("QLabel { font: 12pt Monaco; border: none; color: white; background: #4C5C68;}");

	input.pointer->setFixedWidth(200);
	input.pointer->setPlaceholderText(hint);
	input.pointer->setStyleSheet("QLineEdit {"
								 "border : 2px solid #495867; font: 12pt Monaco; color: #ffffff; padding: 2px;"
								 "placeholder-text-color: #DDCFCF; background: #4C5C68;}");

	connect(input.pointer, &QLineEdit::returnPressed, this, &customDialog::accept);

}
