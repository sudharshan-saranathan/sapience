/*  -----------------------------------
 *  Project     : sapiens
 *  File        : coreGUI.cpp
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

//  Class header file:
    #include "core/coreGUI.h"

//  Class Constructor: coreGUI
    coreGUI::coreGUI(int xs, int ys, QApplication* app) :
    //  Initialize defaults:
        attr{xs, ys, app},
    //  Initialize parent layout and central widget:
        widget{new QWidget(this), new QGridLayout(widget.objptr)},
    //  Initialize QTabWidget:
        tabs{new QTabWidget(widget.objptr), QList<int>{}},
    //  Initialize groupbox and associated buttons:
        groupbox {
            new QGroupBox, 
            new QHBoxLayout,
            new QLabel,
            new QToolButton,
            new QToolButton,
            false
        },
    //  Initialize class schemaViewer (viewer/schemaViewer.h):
        viewer{new schemaViewer(tabs.objptr)}
    {
    //  Set QObject name for internal reference:
        setObjectName ("Main GUI");

    //  Resize application:
        resize(attr.ws, attr.hs);

    //  Set QWidget object as central widget:
        setCentralWidget(widget.objptr);

    //  Add layout to QWidget object:
        widget.objptr->setLayout(widget.layout);

    //  Add QSplitter and QGroupBox objects to base layout:
        widget.layout->addWidget(tabs.objptr, 0, 0, 4, 3);
        widget.layout->addWidget(groupbox.objptr, 0, 1, 1, 1, Qt::AlignHCenter);
        widget.layout->addWidget(groupbox.label, 1, 1, 1, 1, Qt::AlignHCenter);
        widget.layout->setContentsMargins(4, 4, 4, 4);
        widget.layout->setRowStretch(2, 20);
        widget.layout->setSpacing(2);

    //  Add widgets to QTabWidget and customize:
        tabs.objptr->tabBar()->hide();
        tabs.number.append(tabs.objptr->addTab(viewer.objptr, QIcon(":/icons/drawer-alt.svg"), ""));
        tabs.number.append(tabs.objptr->addTab(new QWidget,  QIcon(":/icons/laptop-code.svg"), ""));

    //  Customize QLabel:
        groupbox.label->setContentsMargins(0, 0, 0, 0);
        groupbox.label->setFont(QFont("Gill Sans", 14));
        #ifdef TARGET_OS_OSX
            groupbox.label->setText("Press <font color='red'>Option</font> + <font color='red'>Tab</font>");
        #else
            groupbox.label->setText("Press <font color='red'>Ctrl</font> + <font color='red'>Tab</font>");
        #endif

    //  Customize QToolButton object (chart):
        groupbox.graph->setIcon(QIcon(":/icons/drawer-alt.svg"));
        groupbox.graph->setIconSize(QSize(40, 20));
        groupbox.graph->setCheckable(true);
        groupbox.graph->setChecked(true);

    //  Customize QToolButton object (setup):
        groupbox.setup->setIcon(QIcon(":/icons/laptop-code.svg"));
        groupbox.setup->setIconSize(QSize(40, 20));
        groupbox.setup->setCheckable(true);

    //  Add QToolButton objects to QGroupBox:
        groupbox.layout->setContentsMargins(4, 4, 4, 4);
        groupbox.layout->addWidget(groupbox.graph);
        groupbox.layout->addWidget(groupbox.setup);
        groupbox.objptr->setLayout(groupbox.layout);

        QObject::connect(groupbox.graph, &QToolButton::clicked, this, [this](){showGraph();});
        QObject::connect(groupbox.setup, &QToolButton::clicked, this, [this](){showSetup();});

    //  Display main Graphical User Interface:
        show();

    //  Emit initialized() signal upon constructor completion:
        emit initialized();
    }

//  Function to handle toggling:
    void coreGUI::showGraph() {
    //  Toggle Chart in QGroupBox:
        groupbox.graph->setChecked(true);
        groupbox.setup->setChecked(false);

    //  Show chart-tab:
        tabs.objptr->setCurrentIndex(tabs.number[0]);
    }

//  Function to handle toggling:
    void coreGUI::showSetup(){
    //  Toggle Setup in QGroupBox:
        groupbox.graph->setChecked(false);
        groupbox.setup->setChecked(true);

    //  Show setup-tab:
        tabs.objptr->setCurrentIndex(tabs.number[1]);
    }

//  Slot to handle key presses:
    void coreGUI::keyPressEvent(QKeyEvent *event) {
        Q_UNUSED(event);

    //  Propagate event to base-class handler:
        QMainWindow::keyPressEvent(event);

    //  Switch-Case block for key-handling:
        switch(event->keyCombination())
        {
        //  Filter Option + Tab:
            case QKeyCombination(Qt::AltModifier, Qt::Key_Tab).toCombined(): {
            //  Toggle tab:
                if(!groupbox.isHidden)
                    groupbox.graph->isChecked() ? showSetup() : showGraph();
                break;
            }

        //  Filter Meta + P:
            case QKeyCombination(Qt::MetaModifier, Qt::Key_P).toCombined(): {
            //  Toggle QGroupBox Visibility:
                groupbox.objptr->setVisible(groupbox.isHidden);
                groupbox.label ->setVisible(groupbox.isHidden);
                groupbox.isHidden = !groupbox.isHidden;
                break;
            }

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
