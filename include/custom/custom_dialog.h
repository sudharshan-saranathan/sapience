//
// Created by Sudharshan Saranathan on 05/12/24.
//

#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QLabel>
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QVBoxLayout>

class CustomDialog final : public QDialog {

	Q_OBJECT Q_DISABLE_COPY(CustomDialog)
	Q_CLASSINFO("Author", "Sudharshan Saranathan")public:

	~CustomDialog() override = default;
	CustomDialog(const QString&, const QString&, QWidget* parent = nullptr);

signals:

	void
	paramsInput(QString);

public:

	QString
	parameters() const { return (m_input.pointer->text()); }

private:

	QVBoxLayout* layout = nullptr;

	struct {
		QLineEdit* pointer     = nullptr;
		QString    placeholder = QString();
	} m_input;

	struct {
		QLabel* pointer = nullptr;
		QString text    = QString();
	} m_label;
};

#endif //CUSTOMDIALOG_H
