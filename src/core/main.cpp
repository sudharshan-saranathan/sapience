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

//	Print file and function name:
	qInfo() << __FILE_NAME__ << __func__;

//  Instantiate application and set font:
	QApp_t main_app(argc, argv);
	QApp_t::setFont(QFont("Monaco", 14));

//	Set stylesheet:
	main_app.setStyleSheet(coreQSS::readQSS(":/style/sapience.qss"));

//	Initialize dimensions:
	auto width  = APP_XS;
	auto height = APP_YS;
	auto bounds = QRect(0, 0, width, height);

//	Get dimensions of external display:
	auto display = QGuiApplication::screens();
	if (display.data()) {
		width  = display.last()->size().width();
		height = display.last()->size().height();
		bounds = display.last()->geometry();
	}

//	Initialize coreGUI:
	coreGUI core_gui(width, height, &main_app);

//	Move GUI to external display and show:
	core_gui.move(bounds.topLeft());
	core_gui.show();

//  Enter execution loop:
	return (QApp_t::exec());
}
