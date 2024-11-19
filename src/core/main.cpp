/*  -----------------------------------
 *  Project     : sapiens
 *  File        : main.cpp
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

//  Define app dimensions:
#define XS 1920
#define YS 1200
#define TARGET_OS_OSX

//  Include UI/UX Objects:
#include "core/coreGUI.h"
#include "core/coreQSS.h"

//  Include Qt Font:
#include <QFont>

//  Main executable function:
int main(int argc, char *argv[]){

    QApplication::setFont(QFont("Gill Sans", 14, QFont::Light));
    QApplication main_app(argc, argv);
    coreGUI      core_gui(3024, 1964, &main_app);

    main_app.setStyleSheet(coreQSS::readQSS(":/style/sapience.qss"));
    core_gui.show();

//  Executable application loop:
    return(main_app.exec());
}
