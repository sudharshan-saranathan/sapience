/*  -----------------------------------
 *  Project     : sapiens
 *  File        : main.cpp
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

/*  Default defines */
#define XS 1920
#define YS 1200
#define TARGET_OS_OSX

/*  Include project headers */
#include "core/coreGUI.h"
#include "core/coreQSS.h"

/*  QtCore module   */
#include <QFont>

/*  main()  */
int main(int argc, char *argv[])
{
    /*  Instantiate application and GUI */
    QApp    main_app(argc, argv);
    coreGUI core_gui(3024, 1964, &main_app);

    /*  Customize appearance    */
    QApp::setFont(QFont("Gill Sans", 14));
    main_app.setStyleSheet(coreQSS::readQSS(":/style/sapience.qss"));

    /*  Display GUI */
    core_gui.show();

    /*  Enter execution loop    */
    return(main_app.exec());
}
