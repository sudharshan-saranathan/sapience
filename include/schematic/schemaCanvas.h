/*  -----------------------------------
 *  Project     : sapiens
 *  File        : schemaCanvas.h
 *  Date        : 18.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

    #ifndef CANVAS_H
    #define CANVAS_H

//  Include Qt Core Classes:
    #include <QKeyEvent>
    #include <QGraphicsScene>
    #include <QGraphicsSceneMouseEvent>

//  Include class schemaGrid:
    #include "schematic/schemaGrid.h"
    #include "node/nodeControl.h"

//  Define enum of graphics objects (node, link, handle, ...):
    enum class ENUM_OBJECT {
        NODE,
        LINK,
        HANDLE
    };

//  Forward declaration of QGraphicsView-Derived Class:
    class schemaViewer;

//  Main Class:
    class schemaCanvas final : public QGraphicsScene {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(schemaCanvas)
        Q_CLASSINFO("Author", "Sudharshan Saranathan")

    public:
        ~schemaCanvas() override = default;
         schemaCanvas()          = default;
         explicit schemaCanvas(const QRect&, QObject* parent = nullptr);

    protected:
        struct _attr_ {
            QRect rect;
            float dist;
        } attr;

        struct _list_ {
            QList<QGraphicsItem*> clipboard;
            QList<nodeControl*>    nodelist;
        } list;

    signals:
        void initialized();

    protected slots:
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;
        void keyReleaseEvent(QKeyEvent *event) override;

    public slots:
        static void createNode(QPointF, schemaCanvas*);
        static void deleteNode(schemaCanvas*);
        static void updateNode(schemaCanvas*);
    };

#endif
