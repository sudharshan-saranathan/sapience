/*  -----------------------------------
 *  Project     : sapience
 *  File        : coreGUI.h
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef COREGUI_H
#define COREGUI_H

/*	QtWidgets module  */
#include <QLabel>
#include <QTabBar>
#include <QGroupBox>
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
     coreGUI(const uint_t&, const uint_t&, QApplication*);

private:
    /*  Default attributes  */
    struct _attr_ {
        uint_t  ws     = 0;                                     //  GUI width in pixels
        uint_t  hs     = 0;                                     //  GUI height in pixels
        QApp*   app    = nullptr;                               //  Pointer to QApplication object
        QCursor cursor = QCursor(Qt::ArrowCursor);              //  Default cursor
    } attr;

    /*  QWidget and QGridLayout  */
    struct _widget_ {
        QWidget*     objptr = nullptr;                          //  QWidget pointer
        QGridLayout* layout = nullptr;                          //  QGridLayout to be added to QWidget
    } widget;

    /*  QTabWidget and child index counter  */
    struct _tabs_ {
        QTabWidget*   objptr    = nullptr;
        QList<uint_t> number    = QList<uint_t>{};
    } tabs;

    /*  QGroupBox and child widgets  */
    struct _groupbox_ {
        QGroupBox   *objptr = nullptr;                          //  Pointer to QGroupBox object
        QHBoxLayout *layout = nullptr;                          //  Pointer to QHBoxLayout object
        QToolButton *graph  = nullptr;                          //  Pointer to QToolButton object
        QToolButton *setup  = nullptr;                          //  Pointer to QToolButton object
        QLabel      *label  = nullptr;                          //  Pointer to QLabel object
    } groupbox;

    /*  Class schemaViewer (schematic/schemaViewer.h)   */
    struct _viewer_ {
        schemaViewer *objptr = nullptr;                         //  Pointer to schemaViewer object
    } viewer;

signals:
    void initialized();                                         //  Constructor emits this signal upon completion

protected slots:
    void showGraph();                                           //  Tool button event-handler
    void showSetup();                                           //  Tool button event-handler

protected slots:
    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override {}
};

#endif
