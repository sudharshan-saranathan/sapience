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
#include "core/core_gui.h"
#include "core/core_qss.h"

//  QtGui module
#include <QFont>
#include <QScreen>

//  Main executable
int
main(int argc, char* argv[]) {

//	Print file and function name:
	qInfo() << __FILE_NAME__ << __func__;

//  Instantiate application and set font:
	q_appl main_app(argc, argv);
	q_appl::setFont(QFont("Monaco", 14));

//	Set stylesheet:
	main_app.setStyleSheet(CoreQSS::readQSS(":/style/sapience.qss"));

//	Initialize dimensions:
	auto width  = APP_XS;
	auto height = APP_YS;
	auto bounds = QRect(0, 0, width, height);

//	Parse command line arguments:
	auto display = 0;
	auto args = QString(argv[1]).split("=");

//	Get dimensions of external display:
	auto display = QGuiApplication::screens();
	if (display.data()) {

		auto screenIndex = 0;
		auto args = QString(argv[1]).split("=");

		if (args[0] == "--display")
			screenIndex = args.at(1).toInt();

		width  = display[screenIndex]->size().width();
		height = display[screenIndex]->size().height();
		bounds = display[screenIndex]->geometry();
	}

//	Initialize coreGUI:
	CoreGui core_gui(width, height, &main_app);

//	Move GUI to external display and show:
	core_gui.move(bounds.topLeft());
	core_gui.show();

//  Enter execution loop:
	return (q_appl::exec());
}
