/*  -----------------------------------
 *  Project     : sapiens
 *  File        : main.cpp
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

/*  Default defines */
#define APP_XS 1920
#define APP_YS 1200
#define TARGET_OS_OSX

/*  Include project headers */
#include "core/coreGUI.h"
#include "core/coreQSS.h"

/*  QtGui module  */
#include <QFont>

/*  main executable  */
int main(int argc, char *argv[])
{
    /*  Instantiate application and GUI */
    QApp    main_app(argc, argv);
    coreGUI core_gui(APP_XS, APP_YS, &main_app);

    /*  Customize appearance    */
    QApp::setFont(QFont("Gill Sans", 14));
    main_app.setStyleSheet(coreQSS::readQSS(":/style/sapience.qss"));

    /*  Display GUI */
    core_gui.show();

    /*  Enter execution loop    */
    return(main_app.exec());
}
