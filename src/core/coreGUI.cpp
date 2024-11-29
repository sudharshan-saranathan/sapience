/*  -----------------------------------
 *  Project     : sapiens
 *  File        : coreGUI.cpp
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

/*  Class header    */
#include "core/coreGUI.h"

/*  QtWidgets module    */
#include <QTabBar>

/*  Class constructor   */
coreGUI::coreGUI(const int& xs, const int& ys, QApplication* app) :

/*  Initializer list    */
//  struct _attr_
    attr{xs, ys, app, QCursor(Qt::ArrowCursor)},
//  struct _stack_
    stack
    {
        //  struct _center_
        {
            new QWidget(this),                      //  Widget
            new QGridLayout(stack.center.ptr)       //  QGridLayout
        },
        //  struct _tabs_
        {
            QList<int>{},                           //  QList
            new QTabWidget(stack.center.ptr),       //  QTabWidget
            new schemaViewer(stack.tabs.ptr),       //  schemaViewer
            new QWidget(stack.tabs.ptr)},           //  QWidget
        //  struct _groupbox_
        {
            new QGroupBox(stack.center.ptr),        //  QGroupBox
            new QHBoxLayout(stack.groupbox.ptr),    //  QHBoxLayout
            new QToolButton (stack.groupbox.ptr),   //  QToolButton
            new QToolButton (stack.groupbox.ptr),   //  QToolButton
            new QLabel(stack.center.ptr)            //  QLabel
        }
    }

//  -------------------------
//  Constructor (body) begin:
{
    //  Assert pointer allocations:
    Q_ASSERT(attr.app);
    Q_ASSERT(stack.center.ptr);
    Q_ASSERT(stack.center.layout);
    Q_ASSERT(stack.tabs.ptr);
    Q_ASSERT(stack.tabs.graph);
    Q_ASSERT(stack.tabs.setup);
    Q_ASSERT(stack.groupbox.ptr);
    Q_ASSERT(stack.groupbox.layout);
    Q_ASSERT(stack.groupbox.graph);
    Q_ASSERT(stack.groupbox.setup);
    Q_ASSERT(stack.groupbox.label);

    //  Setup GUI properties:
    resize(attr.ws, attr.hs);
    setObjectName("coreGUI");
    setCentralWidget(stack.center.ptr);

    /*  Add QTabWidget and QGroupBox to QGridLayout and customize:
     *  Do not delete or modify values (unless you're sure) */
    stack.center.layout->addWidget(stack.tabs.ptr, 0, 0, 4, 3);
    stack.center.layout->addWidget(stack.groupbox.ptr, 0, 1, 1, 1, Qt::AlignCenter);
    stack.center.layout->addWidget(stack.groupbox.label, 1, 1, 1, 1, Qt::AlignCenter);
    stack.center.layout->setContentsMargins(4, 4, 4, 4);
    stack.center.layout->setRowStretch(2, 20);
    stack.center.layout->setSpacing(2);

    //  Insert schemaViewer and QWidget into QTabWidget:
    stack.tabs.num.append(stack.tabs.ptr->addTab(stack.tabs.graph, QIcon(":/icons/drawer-alt.svg"), ""));
    stack.tabs.num.append(stack.tabs.ptr->addTab(stack.tabs.setup, QIcon(":/icons/laptop-code.svg"), ""));
    stack.tabs.ptr->tabBar()->hide();

    //  Set label text (shortcut hint) and customize:
    stack.groupbox.label->setContentsMargins(1, 1, 1, 1);
    stack.groupbox.label->setFont(QFont("Gill Sans", 14));
    stack.groupbox.label->setText("Press <font color='red'>Alt</font> + <font color='red'>Tab</font>");

    //  Customize tool button appearance and behaviour:
    //  <graph>
    stack.groupbox.graph->setIcon(QIcon(":/icons/drawer-alt.svg"));
    stack.groupbox.graph->setIconSize(QSize(40, 20));
    stack.groupbox.graph->setCheckable(true);
    stack.groupbox.graph->setChecked(true);
    //  <setup>
    stack.groupbox.setup->setIcon(QIcon(":/icons/laptop-code.svg"));
    stack.groupbox.setup->setIconSize(QSize(40, 20));
    stack.groupbox.setup->setCheckable(true);

    //  Add tool buttons to groupbox layout and customize:
    stack.groupbox.layout->setContentsMargins(4, 4, 4, 4);
    stack.groupbox.layout->addWidget(stack.groupbox.graph);
    stack.groupbox.layout->addWidget(stack.groupbox.setup);
    stack.groupbox.ptr->setLayout(stack.groupbox.layout);

    //  Connect buttons to event handlers:
    connections.append(QObject::connect(stack.groupbox.graph, &QToolButton::clicked, this, [this](){showGraph();}));
    connections.append(QObject::connect(stack.groupbox.setup, &QToolButton::clicked, this, [this](){showSetup();}));

    /*  Show GUI    */
    show();

    /*  Emit initialized() signal   */
    emit initialized();
}

//  Event-handler for <graph>
void coreGUI::showGraph()
{
    //  Toggle checked button, show graph tab:
    stack.groupbox.graph->setChecked(true);
    stack.groupbox.setup->setChecked(false);
    stack.tabs.ptr->setCurrentIndex(stack.tabs.num[0]);
}

//  Event-handler for <setup>:
void coreGUI::showSetup()
{
    //  Toggle checked button, show setup tab:
    stack.groupbox.graph->setChecked(false);
    stack.groupbox.setup->setChecked(true);
    stack.tabs.ptr->setCurrentIndex(stack.tabs.num[1]);
}

void coreGUI::keyPressEvent(QKeyEvent* event)
{
    switch(event->keyCombination()) {
        //  Handle Alt (Option on macOS) + Tab key-presses:
        case QKeyCombination(Qt::AltModifier, Qt::Key_Tab).toCombined():
            //  Toggle tabs, accept event:
            stack.groupbox.graph->isChecked() ? showSetup() : showGraph();
            event->accept();
            break;

        default:
            //  Call base-class implementation:
            QMainWindow::keyPressEvent(event);
            break;
    }
}

void coreGUI::keyReleaseEvent(QKeyEvent *event) {
    event->ignore();

    //  Call base-class implementation:
    QMainWindow::keyReleaseEvent(event);
}
