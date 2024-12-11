//
// Created by Sudharshan Saranathan on 03/12/24.
//

#include <QDebug>
#include "optim/optimEngine.h"

optimEngine::optimEngine() :
settings(Environment(), AMPL(Environment()), "ipopt", nullptr) {

	settings.solver.setOption("Solver", settings.method.toUtf8().constData());

}

void optimEngine::run(const QString& model, bool isCommand) {

	qInfo() << __FILE__ << __func__;
	settings.solver.setOption("Solver", "ipopt");

	std::vector<std::string> tokens;
	std::stringstream stream(model.toStdString());
	std::string token;

	while (std::getline(stream, token, '\n')) {
		tokens.push_back(token);
		if (!token.empty() && token[0] != '#') {
			try {
				settings.solver.eval(fmt::CStringRef(token));
			}
			catch (AMPLException& exception)		{ qDebug() << exception.what(); }
			catch (std::runtime_error& error)		{ qDebug() << error.what(); }
			catch (std::out_of_range& error)		{ qDebug() << error.what(); }
			catch (std::invalid_argument& error)	{ qDebug() << error.what(); }
			catch (std::logic_error& error)			{ qDebug() << error.what(); }
		}
	}
}

void optimEngine::set(QTextEdit* page) {
	if (page != nullptr) {
		settings.logger = page;
		settings.solver.setOption(settings.logger);
}