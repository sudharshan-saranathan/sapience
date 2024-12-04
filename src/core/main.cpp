/*  -----------------------------------
 *  Project     : sapiens
 *  File        : main.cpp
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

//  App dimensions
#define APP_XS 1920
#define APP_YS 1080

#define TARGET_OS_OSX
#define VERBOSE

//  Include core headers
#include "core/coreGUI.h"
#include "core/coreQSS.h"

//  QtGui module
#include <QFont>
#include <QScreen>

//  Main executable
int
main(int argc, char* argv[]) {
	//  Instantiate application and set font:
	QApp_t main_app(argc, argv);
	QApp_t::setFont(QFont("Gill Sans", 14));

	const auto screen = QGuiApplication::primaryScreen();
	const auto width  = screen->size().width();
	const auto height = screen->size().height();

	qInfo() << "Screen resolution - " << width << height;

	coreGUI core_gui(width, height, &main_app);

	//	Set stylesheets:
	main_app.setStyleSheet(coreQSS::readQSS(":/style/sapience.qss"));

	//	Display GUI:
	core_gui.show();

	//  Enter execution loop:
	return (QApp_t::exec());
}
