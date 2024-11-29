/*  -----------------------------------
 *  Project     : sapience
 *  File        : coreGUI.h
 *  Date        : 23.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef COREGUI_H
#define COREGUI_H

/*  QtCore  */
#include <QObject>
#include <QKeyEvent>

/*	QtWidgets module  */
#include <QApplication>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QToolButton>

/*  Include class schemaViewer (schematic/schemaViewer.h)   */
#include "schematic/schemaViewer.h"

/*  Convenience Typedefs    */
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
    ~coreGUI() override         = default;
     coreGUI()                  = delete;
     coreGUI(const int&, const int&, QApplication*);

private:
    /*  Default attribute(s)    */
    struct _attr_
    {
        int     ws     = 1920;                                  //  GUI width in pixels
        int     hs     = 1080;                                  //  GUI height in pixels
        QApp_t* app    = nullptr;                               //  Pointer to QApplication object
        QCursor cursor = QCursor(Qt::ArrowCursor);              //  Default cursor
    } attr;

    /*  The complete widget stack for QMainWindow   */
    struct _stack_
    {
        /*  Top-level container with layout, added as
         *  the center widget of QMainWindow */
        struct _center_
        {
            QWidget* ptr    = nullptr;              //  Pointer to QWidget
            QGridL*  layout = nullptr;              //  Pointer to QGridLayout
        } center;

        /*  Widget containing two tabs: <graph> (flowchart drawing area)
         *  and <setup> (optimization page) - indexed by <num>  */
        struct _tabs_
        {
            QList<int>    num   = QList<int>();     //  List containing tab-indices
            QTabWidget*   ptr   = nullptr;          //  Pointer to QTabWidget
            schemaViewer* graph = nullptr;          //  Derived from QGraphicsView (see schemaViewer.h)
            QWidget*      setup = nullptr;          //  Derived from QWidget
        } tabs;

        /*  The groupbox contains buttons for switching between the
         *  <graph> and <setup> tabs, along with a label displaying
         *  a keyboard shortcut */
        struct _groupbox_ {
            QGroupBox   *ptr    = nullptr;          //  Pointer to QGroupBox
            QHBoxLayout *layout = nullptr;          //  Pointer to QHBoxLayout
            QToolButton *graph  = nullptr;          //  Button to show the <graph> tab (see showGraph() method)
            QToolButton *setup  = nullptr;          //  Button to show the <setup> tab (see showSetup() method)
            QLabel      *label  = nullptr;          //  Label that display a keyboard shortcut for switching tabs
        } groupbox;

    } stack;

protected:
    QList<QMetaObject::Connection> connections = QList<QMetaObject::Connection>();

signals:
    void initialized();                                         //  Signal emitted upon constructor completion

protected slots:
    void showGraph();                                           //  <graph> button event-handler
    void showSetup();                                           //  <setup> button event-handler

    void keyPressEvent(QKeyEvent* event) override;              //  Application-level shortcut handler
    void keyReleaseEvent(QKeyEvent* event) override;            //  Application-level shortcut handler
};

#endif
