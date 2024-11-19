/*  -----------------------------------
 *  Project     : sapiens
 *  File        : coreQSS.cpp
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

//  Class header file:
    #include "core/coreQSS.h"

//  Static member declaration:
    const QBrush QSSBrush::normal = QBrush(QColor(255, 149, 0));
    const QBrush QSSBrush::socket = QBrush(QColor(255, 255, 0), Qt::SolidPattern);
    const QBrush QSSBrush::gridxy = QBrush(Qt::darkGray, Qt::SolidPattern);
    const QBrush QSSBrush::backgr = QBrush(QColor(220, 220, 220), Qt::SolidPattern);
    const QBrush QSSBrush::foregr = QBrush(Qt::black);
    const QBrush QSSBrush::nodebg = QBrush(Qt::white, Qt::SolidPattern);

//  Static member declaration:
    const QPen QSSPen::normal = QPen(QSSBrush::normal , 4.0, Qt::SolidLine, Qt::RoundCap);
    const QPen QSSPen::socket = QPen(QSSBrush::socket , 4.0, Qt::SolidLine, Qt::RoundCap);
    const QPen QSSPen::gridxy = QPen(QSSBrush::gridxy , 4.0, Qt::SolidLine, Qt::RoundCap);
    const QPen QSSPen::backgr = QPen(QSSBrush::backgr , 4.0, Qt::SolidLine, Qt::RoundCap);
    const QPen QSSPen::foregr = QPen(QSSBrush::foregr , 4.0, Qt::SolidLine, Qt::RoundCap);
    const QPen QSSPen::nodebg = QPen(QBrush(Qt::black), 2.0, Qt::SolidLine, Qt::RoundCap);