/*  -----------------------------------
 *  Project     : sapiens
 *  File        : coreGUI.h
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef COREQSS_H
#define COREQSS_H

/*  QtCore module   */
#include <QPen>
#include <QFile>
#include <QBrush>
#include <QString>

/*  Custom QBrush objects   */
struct QSSBrush {
    static const QBrush normal;
    static const QBrush handle;
    static const QBrush circle;
    static const QBrush background;
    static const QBrush foreground;
    static const QBrush node;
};

/*  Custom QPen objects */
struct QSSPen {
    static const QPen normal;
    static const QPen handle;
    static const QPen circle;
    static const QPen background;
    static const QPen foreground;
    static const QPen node;
};

/*  Custom QColor objects   */
struct QSSRGB {
    static const QColor moonstone;
    static const QColor englishViolet;
    static const QColor lilac;
    static const QColor yaleBlue;
    static const QColor lemonChiffon;
    static const QColor lapisLazuli;
    static const QColor carrotOrange;
    static const QColor cordovan;
    static const QColor darkslateGray;
};

/*  Class to parse stylesheets   */
class coreQSS {

    Q_CLASSINFO("Author", "Sudharshan Saranathan")

public:
    /*  Function to parse stylesheets   */
    static QString readQSS(const QString& filename)
    {
        /*  Read stylesheet */
        QFile   file(filename); file.open(QFile::ReadOnly);
        QString text = QLatin1String(file.readAll());

        /*  Close file and return parsed text   */
        file.close();
        return(text);
    }
};

#endif //COREQSS_H
