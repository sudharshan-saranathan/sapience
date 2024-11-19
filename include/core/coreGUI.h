/*  -----------------------------------
 *  Project     : sapiens
 *  File        : coreGUI.h
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

    #ifndef COREGUI_H
    #define COREGUI_H

//	Include QtCore:
    #include <QApplication>
    #include <QSize>
    #include <QString>

//	Include QtWidgets:
    #include <QLabel>
    #include <QSplitter>
    #include <QGroupBox>
    #include <QToolButton>
    #include <QGridLayout>
    #include <QHBoxLayout>
    #include <QMainWindow>

//  Include derived UI element:
    #include "schematic/schemaViewer.h"

//  Convenience Typedefs:
    using uint_t = unsigned int;
    using QApp   = QApplication;
    using QGridL = QGridLayout;
    using QGrBox = QGroupBox;
    using QSplit = QSplitter;
    using QHBoxL = QHBoxLayout;
    using QToolB = QToolButton;

//  -------------------------------------------------
//  Name        : CoreGUI
//  Description : Main Graphical User Interface (GUI)
//  -------------------------------------------------
    class coreGUI final : public QMainWindow {

        Q_OBJECT
        Q_DISABLE_COPY_MOVE(coreGUI)
        Q_CLASSINFO("Author", "Sudharshan Saranathan")

    public:
        ~coreGUI() override  = default;
         coreGUI()           = default;
         coreGUI(int, int, QApplication*);

    protected:

        struct _attr_ {
            int    ws;
            int    hs;
            QApp* app;
        } attr;

        struct _widget_ {
            QWidget* objptr;
            QGridL*  layout;
        } widget;

        struct _splitter_ {
            QSplitter* objptr;
            QList<int> widths;
        } splitter;

        struct _groupbox_ {
            QGrBox *objptr;
            QHBoxL *layout;
            QLabel *label;
            QToolB *chart;
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

    public slots:
        static void quitClicked();
        void keyPressEvent(QKeyEvent*) override;
        void keyReleaseEvent(QKeyEvent*) override;
    };

    #endif
