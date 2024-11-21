/*  -----------------------------------
 *  Project     : sapience
 *  File        : coreGUI.h
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef COREGUI_H
#define COREGUI_H

/* Include from Qt core */
#include <QSize>
#include <QString>

/*	Include from QtWidgets module  */
#include <QLabel>
#include <QGroupBox>
#include <QTabBar>
#include <QTabWidget>
#include <QToolButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QApplication>

/*  Include class schemaViewer (schematic/schemaViewer.h)   */
#include "schematic/schemaViewer.h"

/*  Convenience Typedefs    */
using uint_t = unsigned int;
using QApp   = QApplication;
using QGridL = QGridLayout;
using QGrBox = QGroupBox;
using QHBoxL = QHBoxLayout;
using QToolB = QToolButton;

/*  -------------------------------------------------
 *  Class       : coreGUI
 *  Description : Main Graphical User Interface (GUI)
 *  -----------------------------------------------*/
class coreGUI final : public QMainWindow {

    Q_OBJECT
    Q_DISABLE_COPY_MOVE(coreGUI)
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
    ~coreGUI() override  = default;
     coreGUI()           = delete;
     coreGUI(const int&, const int&, QApplication*);

    protected:
    /*  Default attributes  */
    struct _attr_ {
        int    ws;      //  GUI width in pixels
        int    hs;      //  GUI height in pixels
        QApp* app;      //  Pointer to QApplication object
    } attr;

    /*  QWidget */
    struct _widget_ {
        QWidget* objptr;    //  Pointer to QWidget object
        QGridL*  layout;    //  Pointer to QGridLayout object
    } widget;

    /*  QTabWidget  */
    struct _tabs_ {
        QTabWidget* objptr;
        QList<int>  number;
    } tabs;

    /*  Groupbox containing tool buttons and a label    */
    struct _groupbox_ {
        QGrBox *objptr;     //  Pointer to QGroupBox object
        QHBoxL *layout;     //  Pointer to QHBoxLayout object
        QLabel *label;      //  Pointer to QLabel object
        QToolB *graph;      //  Pointer to QToolButton object
        QToolB *setup;      //  Pointer to QToolButton object
    } groupbox;

    /*  Class schemaViewer: Derived from QGraphicsView (schematic/schemaViewer.h)   */
    struct _viewer_ {
        schemaViewer *objptr;   //  Pointer to schemaViewer object
    } viewer;

signals:
    void initialized();         //  Constructor emits this signal upon completion

protected slots:
    void showGraph();           //  Tool button event-handler
    void showSetup();           //  Tool button event-handler

protected slots:
    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override {}
};

#endif
