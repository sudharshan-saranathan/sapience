/*  -----------------------------------
 *  Project     : sapiens
 *  File        : coreGUI.h
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef COREQSS_H
#define COREQSS_H

//  Include Core Qt Classes:
#include <QPen>
#include <QFile>
#include <QBrush>
#include <QString>

//  Define custom Qt Brushes:
struct QSSBrush {
    static const QBrush normal;
    static const QBrush socket;
    static const QBrush gridxy;
    static const QBrush backgr;
    static const QBrush foregr;
    static const QBrush nodebg;
};

//  Define custom Qt Pens:
struct QSSPen {
    static const QPen normal;
    static const QPen socket;
    static const QPen gridxy;
    static const QPen backgr;
    static const QPen foregr;
    static const QPen nodebg;
};

//  Define QSS-Parser:
class coreQSS {
public:
    static const QString readQSS(const QString& filename){

        QString sheet;
        QFile   file(filename);

        file.open(QFile::ReadOnly);
        sheet = QLatin1String(file.readAll());
        file.close();

        return(sheet);
    }
};

#endif //COREQSS_H
