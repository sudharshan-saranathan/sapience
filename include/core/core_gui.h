/*  -----------------------------------
 *  Project     : sapience-debug
 *  File        : CoreGui.h
 *  Date        : 23.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef CORE_GUI_H
#define CORE_GUI_H

//  QtCore
#include <QKeyEvent>

//	QtWidgets module
#include <QApplication>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QToolButton>

//  Include class SchemaViewer (schematic/SchemaViewer.h)
#include "optim/optim_ctrl.h"
#include "schematic/schema_viewer.h"

//  Define aliases:
using q_appl = QApplication;
using q_grid = QGridLayout;

/*  -------------------------------------------------
 *  Class       : CoreGui
 *  Description : Main Graphical User Interface (GUI)
 *  -----------------------------------------------*/
class CoreGui final : public QMainWindow
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE(CoreGui)
	Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
	~CoreGui() override = default;
	CoreGui()           = delete;
	CoreGui(const int&, const int&, q_appl*);

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
	struct
	{
		int     ws     = 1920;                        //  GUI width in pixels
		int     hs     = 1080;                        //  GUI height in pixels
		q_appl* app    = nullptr;                     //  Pointer to QApplication object
		QCursor cursor = QCursor(Qt::OpenHandCursor); //  Default cursor
	} m_attr;

	/*  The central widget is a QTabWidget with two child widgets indexed by <indices>: <graph> (QGraphicsView) and
	 *  <setup> (optimization page)	*/
	struct
	{
		QList<int>    indices = QList<int>(); //  List containing tab-indices
		QTabWidget*   pointer = nullptr;      //  Pointer to QTabWidget
		QGridLayout*  layout  = nullptr;      //  Layout added on top of the tab widget
		SchemaViewer* graph   = nullptr;      //  Derived from QGraphicsView (see SchemaViewer.h)
		optimCtrl*    setup   = nullptr;      //  Derived from QWidget
	} m_tab;

	/*  The groupbox contains buttons for switching between the <graph> and <setup> tabs, along
	 *  with a label displaying its shortcut
	 */
	struct
	{
		QGroupBox*   pointer = nullptr; //  Pointer to QGroupBox
		QHBoxLayout* layout  = nullptr; //  Pointer to QHBoxLayout
		QToolButton* graph   = nullptr; //  Button to show the <graph> tab (see showGraph() method)
		QToolButton* setup   = nullptr; //  Button to show the <setup> tab (see showSetup() method)
		QLabel*      label   = nullptr; //  Label that display a keyboard shortcut for switching tabs
	} m_groupbox;
};

#endif
