/*  -----------------------------------
 *  Project     : sapiens
 *  File        : coreGUI.cpp
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

//  Include Class Header:
#include "core/coreGUI.h"
#include <iostream>

//  Class Constructor:
coreGUI::coreGUI(int xs, int ys, QApplication* application) : app(application),

//  Initializer list for the GUI's attributes:
    attr{false, QSize(xs, ys)},

//  Initialize parent layout and central widget:
    widget(new QWidget, new QGridLayout),

//  Initialize splitter:
    splitter(new QSplitter(widget.item), QList<int>(1920, 0)),

//  Initialize groupbox and associated buttons:
    group(new QGroupBox, new QHBoxLayout, new QLabel, new QToolButton, new QToolButton, true),

//  Initialize QGraphicsView object and QGraphicsScene:
    schema(new schemaViewer(splitter.item))

{
//  Set QObject name for internal reference:
    setObjectName ("Core GUI");

//  Resize the application to pre-defined size:
    resize(attr.size);

//  Set QWidget object as central widget:
    setCentralWidget(widget.item);

//  Add layout to QWidget object:
    widget.item->setLayout(widget.layout);

//  Add QSplitter and QGroupBox objects to base layout:
    widget.layout->addWidget(splitter.item, 0, 0, 4, 3);
    widget.layout->addWidget(group.item, 0, 1, 1, 1, Qt::AlignHCenter);
    widget.layout->addWidget(group.label, 1, 1, 1, 1, Qt::AlignHCenter);
    widget.layout->setContentsMargins(4, 4, 4, 4);
    widget.layout->setRowStretch(2, 20);
    widget.layout->setSpacing(2);

//  Add widgets to QSplitter and resize:
    splitter.item->insertWidget(0, schema.item);
    splitter.item->insertWidget(1, new QWidget);
    splitter.size[0] = 1920;
    splitter.size[1] = 0;
    splitter.item->setSizes(splitter.size);

//  Customize QLabel object, set prompt:
    group.label->setContentsMargins(0, 0, 0, 0);
    group.label->setFont(QFont("Gill Sans", 14));

//  Define appropriate shortcut:
#ifdef TARGET_OS_OSX
    group.label->setText("Press <font color='red'>Option</font> + <font color='red'>Tab</font>");
#else
    group.label->setText("Press <font color='red'>Ctrl</font> + <font color='red'>Tab</font>");
#endif

//  Customize QToolButton object (chart):
    group.chart->setIcon(QIcon(":/icons/drawer-alt.svg"));
    group.chart->setIconSize(QSize(40, 20));
    group.chart->setCheckable(true);
    group.chart->setChecked(true);

//  Customize QToolButton object (setup):
    group.setup->setIcon(QIcon(":/icons/laptop-code.svg"));
    group.setup->setIconSize(QSize(40, 20));
    group.setup->setCheckable(true);

//  Add QToolButton objects to QGroupBox:
    group.layout->setContentsMargins(4, 4, 4, 4);
    group.layout->addWidget(group.chart);
    group.layout->addWidget(group.setup);
    group.item  ->setLayout(group.layout);

    auto connectChart = connect(group.chart, &QToolButton::clicked, this, [this](){showGraph();});
    auto connectSetup = connect(group.setup, &QToolButton::clicked, this, [this](){showSetup();});

//  Display main Graphical User Interface:
    show();

//  Emit initialized() signal upon constructor completion:
    emit initialized();
}

//  Function to handle toggling:
void coreGUI::showGraph() {

//  Toggle Chart in QGroupBox:
    group.chart->setChecked(true);
    group.setup->setChecked(false);

//  Resize page and set size:
    splitter.size[0] = 1920;
    splitter.size[1] = 0;
    splitter.item->setSizes(splitter.size);
}

//  Function to handle toggling:
void coreGUI::showSetup() {

//  Toggle Setup in QGroupBox:
    group.chart->setChecked(false);
    group.setup->setChecked(true);

//  Resize page and set size:
    splitter.size[0] = 0;
    splitter.size[1] = 1920;
    splitter.item->setSizes(splitter.size);
}

//  Slot to handle key presses:
void coreGUI::keyPressEvent(QKeyEvent *event) {
    Q_UNUSED(event);

//  Propagate event to base-class handler:
    QMainWindow::keyPressEvent(event);

//  Switch-Case block for key-handling:
    switch(event->keyCombination())
    {
    //  Filter Option+Tab, or Ctrl+Tab key combinations:
        case QKeyCombination(Qt::AltModifier, Qt::Key_Tab).toCombined():
        //  Toggle visible page:
            if(group.visible) {
                group.chart->isChecked() ? showSetup() : showGraph();
            }
            break;

        case QKeyCombination(Qt::MetaModifier, Qt::Key_P).toCombined():
        //  Toggle QGroupBox Visibility:
            group.visible = !group.visible;
            group.item ->setVisible(group.visible);
            group.label->setVisible(group.visible);
            break;

    //  Default:
        default:
            break;
    }

    event->accept();
}

//  Slot to handle key releases:
void coreGUI::keyReleaseEvent(QKeyEvent *event) {
    Q_UNUSED(event);

    QMainWindow::keyReleaseEvent(event);
}

//  Slot to handle quit button:
void coreGUI::quitClicked() {

}
