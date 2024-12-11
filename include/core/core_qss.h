/*  -----------------------------------
 *  Project     : sapiens
 *  File        : coreGUI.h
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef COREQSS_H
#define COREQSS_H

//  QtCore module
#include <QFile>
#include <QPen>
#include <QRandomGenerator>
#include <QString>

//  Custom QBrush
struct QSSBrush {
	static const QBrush normal;
	static const QBrush handle;
	static const QBrush circle;
	static const QBrush background;
	static const QBrush foreground;
	static const QBrush node;
};

//  Custom QPen
struct QSSPen {
	static const QPen normal;
	static const QPen handle;
	static const QPen circle;
	static const QPen background;
	static const QPen foreground;
	static const QPen node;
};

//  Custom QColor named objects
struct QSSRGB {
	static const QColor moonstone;
	static const QColor spaceCadet;
	static const QColor englishViolet;
	static const QColor lilac;
	static const QColor yaleBlue;
	static const QColor lemonChiffon;
	static const QColor lapisLazuli;
	static const QColor carrotOrange;
	static const QColor cordovan;
	static const QColor darkslateGray;
};

//  Static function to parse QSS stylesheets
class CoreQSS {
	Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:

	//  Function to parse stylesheets
	static QString
	readQSS(const QString& qssFilePath) {
		//	Open stylesheet and parse contents:
		QFile file(qssFilePath);
		file.open(QFile::ReadOnly);
		QString text = QLatin1String(file.readAll());

		//	Close file and return parsed text:
		file.close();
		return (text);
	}

	//  Function to generate a random color (hexadecimal value)
	static QColor
	colorGenerator() {
		const auto color = QRandomGenerator::global()->bounded(0x1000000);
		const auto hex   = QColor(QString("#%1").arg(color, 6, 16, QLatin1Char('0')));

		return (hex);
	}
};

#endif //COREQSS_H
