/*  -----------------------------------
 *  Project     : sapience
 *  File        : coreGUI.h
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  License     : GNU GPL v3.0
 *  -----------------------------------
 */

    #ifndef COREGUI_H
    #define COREGUI_H

//	Include from QtCore module:
    #include <QSize>
    #include <QString>

//	Include from QtWidgets module:
    #include <QLabel>
    #include <QGroupBox>
    #include <QTabBar>
    #include <QTabWidget>
    #include <QToolButton>
    #include <QGridLayout>
    #include <QHBoxLayout>
    #include <QMainWindow>
    #include <QApplication>

//  Include class schemaViewer (schematic/schemaViewer.h):
    #include "schematic/schemaViewer.h"

//  Convenience Typedefs:
    using uint_t = unsigned int;
    using QApp   = QApplication;
    using QGridL = QGridLayout;
    using QGrBox = QGroupBox;
    using QHBoxL = QHBoxLayout;
    using QToolB = QToolButton;

//  -------------------------------------------------
//  Class       : coreGUI
//  Description : Main Graphical User Interface (GUI)
//  -------------------------------------------------
    class coreGUI final : public QMainWindow {

        Q_OBJECT
        Q_DISABLE_COPY_MOVE(coreGUI)
        Q_CLASSINFO("Author", "Sudharshan Saranathan")

    public:
        ~coreGUI() override  = default;
         coreGUI(int, int, QApplication*);

    protected:
    //  Default attributes:
        struct _attr_ {
            int    ws;
            int    hs;
            QApp* app;
        } attr{};

        struct _widget_ {
            QWidget* objptr;
            QGridL*  layout;
        } widget{};

        struct _tabs_ {
            QTabWidget* objptr;
            QList<int>  number;
        } tabs;

        struct _groupbox_ {
            QGrBox *objptr;
            QHBoxL *layout;
            QLabel *label;
            QToolB *graph;
            QToolB *setup;
            bool isHidden;
        } groupbox;

        struct _viewer_ {
            schemaViewer *objptr;
        } viewer;

    signals:
        void initialized();

    protected slots:
        void showGraph();
        void showSetup();
        void quitClicked();

    public slots:
        void keyPressEvent(QKeyEvent*) override;
        void keyReleaseEvent(QKeyEvent*) override;
    };

    #endif
