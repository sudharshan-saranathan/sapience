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
        static const QBrush handle;
        static const QBrush circle;
        static const QBrush background;
        static const QBrush foreground;
        static const QBrush node;
    };

//  Define custom Qt Pens:
    struct QSSPen {
        static const QPen normal;
        static const QPen handle;
        static const QPen circle;
        static const QPen background;
        static const QPen foreground;
        static const QPen node;
    };

//  Define QSS-Parser:
class coreQSS {
public:
    static QString readQSS(const QString& filename){

        QFile   file(filename); file.open(QFile::ReadOnly);
        QString text = QLatin1String(file.readAll());

        file.close();
        return(text);
    }
};

#endif //COREQSS_H
