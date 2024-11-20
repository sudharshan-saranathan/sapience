/*  -----------------------------------
 *  Project     : sapience
 *  File        : nodeControl.h
 *  Date        : 19.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

    #ifndef NODECTRL_H
    #define NODECTRL_H

//  Default definitions:
    #define NODE_WS 300
    #define NODE_HS 200
    #define HDR_WS  300
    #define HDR_HS  200

//  Include Qt Core Classes:
    #include <QPen>
    #include <QRect>
    #include <QBrush>
    #include <QPointF>
    #include <QString>
    #include <QPainter>
    #include <QGraphicsItem>
    #include <QGraphicsRectItem>
    #include <QGraphicsTextItem>

//  Convenience typedefs:
    using uint_t = unsigned int;
    using QItemG = QGraphicsItem;
    using QItemR = QGraphicsRectItem;
    using QItemT = QGraphicsTextItem;
    using QSOGI  = QStyleOptionGraphicsItem;

//  Forward declaration of enum class:
    enum class ENUM_OBJECT;

//  Class header:
    class nodeControl : public QObject, public QItemR {

        Q_OBJECT
        Q_CLASSINFO("Author", "Sudharshan Saranathan")

    public:
        ~nodeControl() override = default;
         nodeControl()          = delete;
         nodeControl(const nodeControl&);
         nodeControl(const QPointF&, const QString&, QItemG* parent = nullptr);

    private:
        struct _attr_ {
            QPointF cpos;
            QRect   rect;
        } attr;

        struct _hdr_ {
            QRect   rect;
            QItemR* hdrptr;
            QItemT* txtptr;
        } hdr;

    protected slots:
        void paint(QPainter*, const QSOGI*, QWidget*) override;

    public:
        [[nodiscard]] QString getName() const {return(hdr.txtptr->toPlainText());}

    };

    #endif
