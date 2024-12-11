//
// Created by Sudharshan Saranathan on 03/12/24.
//

#pragma once

#include <cstring>
#include <QThread>
#include <QTextEdit>
#include <fmt/core.h>
#include <ampl/ampl.h>

#ifndef OPTIMENGINE_H
#define OPTIMENGINE_H

using namespace ampl;

class OptimEngine final : public AMPL {
public:
	OptimEngine();

public:
	void run(const QString&, bool isCommand = false);
	void set(QTextEdit*);

private:
	struct _settings_ {
		Environment environment;
		AMPL		solver;
		QString		method;
		QTextEdit*	logger = nullptr;
	} settings;
};

#endif //OPTIMENGINE_H