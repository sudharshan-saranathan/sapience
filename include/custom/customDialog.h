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

class customDialog : public QDialog {

	Q_OBJECT Q_DISABLE_COPY(customDialog)
	Q_CLASSINFO("Author", "Sudharshan Saranathan")public:

	~customDialog() override = default;
	customDialog(const QString&, const QString&, QWidget* parent = nullptr);

signals:

	void
	paramsInput(QString);

public:

	QString
	parameters() const { return (input.pointer->text()); }

private:

	QVBoxLayout* layout = nullptr;

	struct {
		QLineEdit* pointer     = nullptr;
		QString    placeholder = QString();
	} input;

	struct {
		QLabel* pointer = nullptr;
		QString text    = QString();
	} label;
};

#endif //CUSTOMDIALOG_H
