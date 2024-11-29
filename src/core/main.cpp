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
    QApp_t  main_app(argc, argv);
    QApp_t::setFont(QFont("Gill Sans", 14));
    coreGUI core_gui(APP_XS, APP_YS, &main_app);

    //	Set stylesheets:
    main_app.setStyleSheet(coreQSS::readQSS(":/style/sapience.qss"));

    //	Display GUI:
    core_gui.show();

    /*  Enter execution loop    */
    return(QApp_t::exec());
}
