/*  -----------------------------------
 *  Project     : sapiens
 *  File        : coreQSS.cpp
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

/*  Class header file   */
#include "core/coreQSS.h"

/*  Static members declaration  */
const QBrush QSSBrush::normal       = QBrush(Qt::black, Qt::SolidPattern);
const QBrush QSSBrush::circle       = QBrush(Qt::darkGray, Qt::SolidPattern);
const QBrush QSSBrush::handle       = QBrush(QColor(243, 146, 55), Qt::SolidPattern);
const QBrush QSSBrush::background   = QBrush(QColor(220, 220, 220), Qt::SolidPattern);
const QBrush QSSBrush::foreground   = QBrush(Qt::black, Qt::SolidPattern);
const QBrush QSSBrush::node         = QBrush(Qt::white, Qt::SolidPattern);

/*  Static members declaration  */
const QPen QSSPen::normal       = QPen(QSSBrush::normal, 2.0, Qt::SolidLine, Qt::RoundCap);
const QPen QSSPen::circle       = QPen(QSSBrush::circle, 4.0, Qt::SolidLine, Qt::RoundCap);
const QPen QSSPen::handle       = QPen(QSSBrush::handle, 4.0, Qt::SolidLine, Qt::RoundCap);
const QPen QSSPen::background   = QPen(QSSBrush::background, 4.0, Qt::SolidLine, Qt::RoundCap);
const QPen QSSPen::foreground   = QPen(QSSBrush::foreground, 4.0, Qt::SolidLine, Qt::RoundCap);
const QPen QSSPen::node         = QPen(QBrush(Qt::black), 2.0, Qt::SolidLine, Qt::RoundCap);

/*  Static members declaration */
const QColor QSSRGB::moonstone      = QColor(100, 166, 189);
const QColor QSSRGB::englishViolet  = QColor(69, 55, 80);
const QColor QSSRGB::lilac          = QColor(194, 151, 184);
const QColor QSSRGB::yaleBlue       = QColor(13, 59, 102);
const QColor QSSRGB::lemonChiffon   = QColor(250, 240, 202);
const QColor QSSRGB::lapisLazuli    = QColor(65, 101, 138);
const QColor QSSRGB::carrotOrange   = QColor(241, 143, 1);
const QColor QSSRGB::cordovan       = QColor(118, 66, 72);
const QColor QSSRGB::darkslateGray  = QColor(59, 96, 100);