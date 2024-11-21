/*  -----------------------------------
 *  Project     : sapiens
 *  File        : coreGUI.cpp
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

/*  Class header file   */
#include "core/coreGUI.h"

/*  Class constructor   */
coreGUI::coreGUI(const int& xs, const int& ys, QApplication* app) :

/*  GUI attributes      */
attr{xs, ys, app},

/*  Central widget and layout   */
widget{new QWidget(this), new QGridLayout(widget.objptr)},

/*  Initialize QTabWidget   */
tabs{new QTabWidget(widget.objptr), QList<int>{}},

/*  Initialize QGroupBox and its children   */
groupbox {
    new QGroupBox(widget.objptr),
    new QHBoxLayout(groupbox.objptr),
    new QLabel(widget.objptr),
    new QToolButton(groupbox.objptr),
    new QToolButton(groupbox.objptr)
},

/*  Initialize schemaViewer */
viewer{new schemaViewer(tabs.objptr)}

/*  Constructor body begin  */
{
    /*  Set object name for internal reference  */
    setObjectName ("Main GUI");

    /*  Resize GUI  */
    resize(attr.ws, attr.hs);

    /*  Set central widget  */
    setCentralWidget(widget.objptr);

    /*  Add grid-layout to central widget   */
    widget.objptr->setLayout(widget.layout);

    /*  Add child widgets to layout and customize   */
    widget.layout->addWidget(tabs.objptr, 0, 0, 4, 3);
    widget.layout->addWidget(groupbox.objptr, 0, 1, 1, 1, Qt::AlignHCenter);
    widget.layout->addWidget(groupbox.label, 1, 1, 1, 1, Qt::AlignHCenter);
    widget.layout->setContentsMargins(4, 4, 4, 4);
    widget.layout->setRowStretch(2, 20);
    widget.layout->setSpacing(2);

    /*  Add schemaViewer and optimization widgets as tabs to QTabWidget, but hide tab-bar   */
    tabs.objptr->tabBar()->hide();
    tabs.number.append(tabs.objptr->addTab(viewer.objptr, QIcon(":/icons/drawer-alt.svg"), ""));
    tabs.number.append(tabs.objptr->addTab(new QWidget,  QIcon(":/icons/laptop-code.svg"), ""));

    /*  Display label and customize */
    groupbox.label->setContentsMargins(0, 0, 0, 0);
    groupbox.label->setFont(QFont("Gill Sans", 14));
#ifdef TARGET_OS_OSX
    groupbox.label->setText("Press <font color='red'>Option</font> + <font color='red'>Tab</font>");
#else
    groupbox.label->setText("Press <font color='red'>Ctrl</font> + <font color='red'>Tab</font>");
#endif

    /*  Initialize tool button, set icon and customize  */
    groupbox.graph->setIcon(QIcon(":/icons/drawer-alt.svg"));
    groupbox.graph->setIconSize(QSize(40, 20));
    groupbox.graph->setCheckable(true);
    groupbox.graph->setChecked(true);               //  The graph button is checked by default

    /*  Initialize tool button, set icon and customize  */
    groupbox.setup->setIcon(QIcon(":/icons/laptop-code.svg"));
    groupbox.setup->setIconSize(QSize(40, 20));
    groupbox.setup->setCheckable(true);

    /*  Arrange tool buttons in layout and set layout   */
    groupbox.layout->setContentsMargins(4, 4, 4, 4);
    groupbox.layout->addWidget(groupbox.graph);
    groupbox.layout->addWidget(groupbox.setup);
    groupbox.objptr->setLayout(groupbox.layout);

    /*  Connect buttons to event handlers   */
    auto connection_1 = QObject::connect(groupbox.graph, &QToolButton::clicked, this, [this](){showGraph();});
    auto connection_2 = QObject::connect(groupbox.setup, &QToolButton::clicked, this, [this](){showSetup();});

    /*  Show GUI    */
    show();

    /*  Emit initialized() signal   */
    emit initialized();
}

/*  Tool button event-handler   */
void coreGUI::showGraph()
{
    /*  Show graph  */
    groupbox.graph->setChecked(true);
    groupbox.setup->setChecked(false);
    tabs.objptr->setCurrentIndex(tabs.number[0]);
}

/*  Tool button event-handler   */
void coreGUI::showSetup()
{
    /*  Show setup  */
    groupbox.graph->setChecked(false);
    groupbox.setup->setChecked(true);
    tabs.objptr->setCurrentIndex(tabs.number[1]);
}

/*  Key-press event-handler */
void coreGUI::keyPressEvent(QKeyEvent *event)
{
    /*  Propagate event to base-class handler   */
    QMainWindow::keyPressEvent(event);

    /*  Switch-case block for event handling    */
    switch(event->keyCombination())
    {
        /*  Filter <Alt+Tab>    */
        case QKeyCombination(Qt::AltModifier, Qt::Key_Tab).toCombined(): {
            groupbox.graph->isChecked() ? showSetup() : showGraph();
            event->accept();
            break;
        }
        /*  Default */
        default: {
            event->ignore();
            break;
        }
    }
}