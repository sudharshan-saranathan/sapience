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
    const QBrush QSSBrush::normal       = QBrush(Qt::black, Qt::SolidPattern);
    const QBrush QSSBrush::circle       = QBrush(Qt::darkGray, Qt::SolidPattern);
    const QBrush QSSBrush::handle       = QBrush(QColor(255, 255, 0), Qt::SolidPattern);
    const QBrush QSSBrush::background   = QBrush(QColor(220, 220, 220), Qt::SolidPattern);
    const QBrush QSSBrush::foreground   = QBrush(Qt::black, Qt::SolidPattern);
    const QBrush QSSBrush::node         = QBrush(Qt::white, Qt::SolidPattern);

//  Static member declaration:
    const QPen QSSPen::normal       = QPen(QSSBrush::normal, 2.0, Qt::SolidLine, Qt::RoundCap);
    const QPen QSSPen::circle       = QPen(QSSBrush::circle, 4.0, Qt::SolidLine, Qt::RoundCap);
    const QPen QSSPen::handle       = QPen(QSSBrush::handle, 4.0, Qt::SolidLine, Qt::RoundCap);
    const QPen QSSPen::background   = QPen(QSSBrush::background, 4.0, Qt::SolidLine, Qt::RoundCap);
    const QPen QSSPen::foreground   = QPen(QSSBrush::foreground, 4.0, Qt::SolidLine, Qt::RoundCap);
    const QPen QSSPen::node         = QPen(QBrush(Qt::black), 2.0, Qt::SolidLine, Qt::RoundCap);
