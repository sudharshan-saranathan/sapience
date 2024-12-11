//
// Created by Sudharshan Saranathan on 05/12/24.
//

#include "custom/custom_dialog.h"

#define DIALOG_WS 200
#define DIALOG_HS 75

CustomDialog::CustomDialog(const QString& text, const QString& hint, QWidget* parent) :
//	Initializer list:
//	Base-class constructor
	QDialog(parent),
//	Initialize layout:
	layout{new QVBoxLayout(this)},
//	Initialize QLineEdit:
	m_input{new QLineEdit(this), hint},
//	Initialize label:
	m_label{new QLabel(this), text}
//	Constructor (body) begin:
{
	setAttribute(Qt::WA_OpaquePaintEvent);
	setWindowFlag(Qt::FramelessWindowHint);
	setContentsMargins(0, 0, 0, 0);
	setFixedSize(DIALOG_WS, DIALOG_HS);
	setStyleSheet("QDialog {padding: 4px; border: 1px solid #495867; border-radius: 10px; background: #495867;}");

	setLayout(layout);

	const auto separator = new QFrame(this);
	separator->setFrameShape(QFrame::HLine);
	separator->setFrameShadow(QFrame::Sunken);
	separator->setFixedHeight(1);
	separator->setFixedWidth(150);
	separator->setGeometry(25, 40, 100, 1);

	layout->setContentsMargins(0, 8, 0, 0);
	layout->setSpacing(0);
	layout->addWidget(m_label.pointer, 0, Qt::AlignCenter);
	layout->addWidget(separator, 1, Qt::AlignCenter);
	layout->addWidget(m_input.pointer, 2, Qt::AlignCenter);

	m_label.pointer->setText(text);
	m_label.pointer->setAlignment(Qt::AlignCenter);
	m_label.pointer->setStyleSheet("QLabel { font: 12pt Monaco; border: none; color: white; background: #4C5C68;}");

	m_input.pointer->setContentsMargins(0, 0, 0, 0);
	m_input.pointer->setFixedWidth(DIALOG_WS);
	m_input.pointer->setPlaceholderText(hint);
	m_input.pointer->setStyleSheet("QLineEdit {"
								   "font: 12pt Monaco;"
								   "color: #ffffff;"
								   "margin: 0px;"
								   "border: 2px solid #495867;"
								   "padding: 2px;"
								   "background: #4C5C68;"
								   "placeholder-text-color: #DDCFCF;}");

	connect(m_input.pointer, &QLineEdit::returnPressed, this, &CustomDialog::accept);
}
