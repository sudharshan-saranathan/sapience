/*  -----------------------------------
 *  Project     : sapiens
 *  File        : coreGUI.h
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef COREGUI_H
#define COREGUI_H

//	Include Qt Core Classes:
#include <QApplication>
#include <QSize>
#include <QString>

//	Include Qt Objects:
#include <QLabel>
#include <QSplitter>
#include <QGroupBox>
#include <QToolButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMainWindow>

//  Include QGraphicsView-Derived Class:
#include "schematic/schemaViewer.h"

//  Convenience Typedefs:
using QGridL = QGridLayout;
using QGrBox = QGroupBox;
using QSplit = QSplitter;
using QHBoxL = QHBoxLayout;
using QToolB = QToolButton;

//  Class		:	coreGUI
//  Description	:   Main Graphical User Interface
class coreGUI final : public QMainWindow {

    Q_OBJECT
    Q_DISABLE_COPY_MOVE(coreGUI)
    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
   ~coreGUI() override  = default;
    coreGUI()           = default;
    coreGUI(int, int, QApplication*);

private:
    QApplication *app;

protected:
//  Basic attributes:
    struct _attr_ {
        bool  full = false;     //  Fullscreen
        QSize size;             //  Application size
    } attr;

//  Central Widget:
    struct _widget_ {
        QWidget* item;
        QGridL*  layout;
    } widget;

//  QSplitter Object:
    struct _splitter_ {
        QSplitter* item;
        QList<int> size;
    } splitter;

//  QGroupBox Object:
    struct _group_ {
        QGrBox *item;
        QHBoxL *layout;
        QLabel *label;
        QToolB *chart;
        QToolB *setup;
        bool  visible;
    } group;

//  schemaViewer Object:
    struct _schema_ {
        schemaViewer *item;
    } schema;

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
