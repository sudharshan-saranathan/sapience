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
    coreGUI::coreGUI(int xs, int ys, QApp* app) :
    //  GUI metadata:
        attr{xs, ys, app},
    //  Initialize parent layout and central widget:
        widget{new QWidget(this), new QGridLayout(widget.objptr)},
    //  Initialize splitter:
        splitter{new QSplitter(widget.objptr), QList<int>{1920, 0}},
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
        viewer{new schemaViewer(splitter.objptr)}
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
        widget.layout->addWidget(splitter.objptr, 0, 0, 4, 3);
        widget.layout->addWidget(groupbox.objptr, 0, 1, 1, 1, Qt::AlignHCenter);
        widget.layout->addWidget(groupbox.label, 1, 1, 1, 1, Qt::AlignHCenter);
        widget.layout->setContentsMargins(4, 4, 4, 4);
        widget.layout->setRowStretch(2, 20);
        widget.layout->setSpacing(2);

    //  Add widgets to QSplitter and resize:
        splitter.objptr->insertWidget(0, viewer.objptr);
        splitter.objptr->insertWidget(1, new QWidget);
        splitter.widths[0] = 1920;
        splitter.widths[1] = 0;
        splitter.objptr->setSizes(splitter.widths);

    //  Customize QLabel:
        groupbox.label->setContentsMargins(0, 0, 0, 0);
        groupbox.label->setFont(QFont("Gill Sans", 14));
        #ifdef TARGET_OS_OSX
            groupbox.label->setText("Press <font color='red'>Option</font> + <font color='red'>Tab</font>");
        #else
            groupbox.label->setText("Press <font color='red'>Ctrl</font> + <font color='red'>Tab</font>");
        #endif

    //  Customize QToolButton object (chart):
        groupbox.chart->setIcon(QIcon(":/icons/drawer-alt.svg"));
        groupbox.chart->setIconSize(QSize(40, 20));
        groupbox.chart->setCheckable(true);
        groupbox.chart->setChecked(true);

    //  Customize QToolButton object (setup):
        groupbox.setup->setIcon(QIcon(":/icons/laptop-code.svg"));
        groupbox.setup->setIconSize(QSize(40, 20));
        groupbox.setup->setCheckable(true);

    //  Add QToolButton objects to QGroupBox:
        groupbox.layout->setContentsMargins(4, 4, 4, 4);
        groupbox.layout->addWidget(groupbox.chart);
        groupbox.layout->addWidget(groupbox.setup);
        groupbox.objptr->setLayout(groupbox.layout);

        QObject::connect(groupbox.chart, &QToolButton::clicked, this, [this](){showGraph();});
        QObject::connect(groupbox.setup, &QToolButton::clicked, this, [this](){showSetup();});

    //  Display main Graphical User Interface:
        show();

    //  Emit initialized() signal upon constructor completion:
        emit initialized();
    }

//  Function to handle toggling:
    void coreGUI::showGraph() {

    //  Toggle Chart in QGroupBox:
        groupbox.chart->setChecked(true);
        groupbox.setup->setChecked(false);

    //  Resize page and set size:
        splitter.widths[0] = 1920;
        splitter.widths[1] = 0;
        splitter.objptr->setSizes(splitter.widths);
    }

//  Function to handle toggling:
    void coreGUI::showSetup() {

    //  Toggle Setup in QGroupBox:
        groupbox.chart->setChecked(false);
        groupbox.setup->setChecked(true);

    //  Resize page and set size:
        splitter.widths[0] = 0;
        splitter.widths[1] = 1920;
        splitter.objptr->setSizes(splitter.widths);
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
            //  Toggle visible page:
                if(!groupbox.isHidden) 
                    groupbox.chart->isChecked() ? showSetup() : showGraph();
                
                break;
            }

        //  Filter Meta + P:
            case QKeyCombination(Qt::MetaModifier, Qt::Key_P).toCombined(): {
            //  Toggle QGroupBox Visibility:
                groupbox.isHidden = !groupbox.isHidden;
                groupbox.objptr->setVisible(groupbox.isHidden);
                groupbox.label ->setVisible(groupbox.isHidden);
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
