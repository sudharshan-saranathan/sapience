//
// Created by Sudharshan Saranathan on 03/12/24.
//

#ifndef COMMONEDITOR_H
#define COMMONEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QFileDialog>
#include <QGridLayout>

class CustomEditor final : public QTextEdit {

	Q_OBJECT

public:
	~CustomEditor() override = default;
	explicit
	CustomEditor(QColor, QWidget* parent = nullptr);

public slots:
	void
	open() { open(QFileDialog::getOpenFileName()); }

	void
	save() const { save(QFileDialog::getSaveFileName()); }

	void
	open(const QString &filePath);

	void
	save(const QString &filePath) const;

protected:
	void
	dragEnterEvent(QDragEnterEvent* event) override;

	void
	dropEvent(QDropEvent *event) override;

private:
	struct _attr_ {
		int nrows;
		int ncols;
	};
};

#endif //COMMONEDITOR_H
