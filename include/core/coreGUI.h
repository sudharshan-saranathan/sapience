/*  -----------------------------------
 *  Project     : sapience-debug
 *  File        : coreGUI.h
 *  Date        : 23.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef COREGUI_H
#define COREGUI_H

//  QtCore
#include <QKeyEvent>

//	QtWidgets module
#include <QApplication>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QToolButton>

//  Include class schemaViewer (schematic/schemaViewer.h)
#include "optim/optimCtrl.h"
#include "schematic/schemaViewer.h"

//  Define shorthand:
using uint_t = unsigned int;
using QApp_t = QApplication;
using QGridL = QGridLayout;

/*  -------------------------------------------------
 *  Class       : coreGUI
 *  Description : Main Graphical User Interface (GUI)
 *  -----------------------------------------------*/
class coreGUI final : public QMainWindow {
	Q_OBJECT
	Q_DISABLE_COPY_MOVE(coreGUI)
	Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:

	~coreGUI() override = default;
	coreGUI()           = delete;
	coreGUI(const int&, const int&, QApplication*);

signals:

	void
	initialized(); //  Signal emitted upon constructor completion

protected slots:

	void
	showGraph(); //  <graph> button event-handler
	void
	showSetup(); //  <setup> button event-handler

private:

	//  Default Attribute(s):
	struct {
		int     ws     = 1920;                        //  GUI width in pixels
		int     hs     = 1080;                        //  GUI height in pixels
		QApp_t* app    = nullptr;                     //  Pointer to QApplication object
		QCursor cursor = QCursor(Qt::OpenHandCursor); //  Default cursor
	} attr;

	/*  The central widget contains a QTabWidget with two children: <graph> (QGraphicsView)
	 *  and <setup> (optimization page) - indexed by <num>  */
	struct {
		QList<int>    num     = QList<int>(); //  List containing tab-indices
		QTabWidget*   pointer = nullptr;      //  Pointer to QTabWidget
		QGridLayout*  layout  = nullptr;      //  Layout added on top of the tab widget
		schemaViewer* graph   = nullptr;      //  Derived from QGraphicsView (see schemaViewer.h)
		optimCtrl*    setup   = nullptr;      //  Derived from QWidget
	} tabs;

	/*  The groupbox contains buttons for switching between the <graph> and <setup> tabs, along
	 *  with a label displaying its shortcut
	 */
	struct {
		QGroupBox*   pointer = nullptr; //  Pointer to QGroupBox
		QHBoxLayout* layout  = nullptr; //  Pointer to QHBoxLayout
		QToolButton* graph   = nullptr; //  Button to show the <graph> tab (see showGraph() method)
		QToolButton* setup   = nullptr; //  Button to show the <setup> tab (see showSetup() method)
		QLabel*      label   = nullptr; //  Label that display a keyboard shortcut for switching tabs
	} groupbox;
};

#endif
