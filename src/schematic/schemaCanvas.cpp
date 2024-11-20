/*  -----------------------------------
 *  Project     : sapience
 *  File        : schemaCanvas.cpp
 *  Date        : 18.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

//  Include Qt Core Classes:
    #include <QPointF>

//  Include project headers:
    #include "core/coreIOF.h"
    #include "node/nodeControl.h"
    #include "schematic/schemaCanvas.h"

//  Constructor:
    schemaCanvas::schemaCanvas(const QRect& rect, QObject* parent) :
    //  Initialize base-class constructor:
        QGraphicsScene(parent),
    //  Initialize attributes:
        attr{rect, 1.0},
    //  Initialize clipboard:
        list{QList<QGraphicsItem*>{}, QList<nodeControl*>{}}
    {
    //  Add gridpoints to the scene:
        addItem(new schemaGrid(attr.rect));

    //  Emit initialized() signal upon Constructor completion:
        emit initialized();
    }

    void schemaCanvas::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
        Q_UNUSED(event)
        QGraphicsScene::mouseMoveEvent(event);
    }

    void schemaCanvas::mousePressEvent(QGraphicsSceneMouseEvent* event) {
        Q_UNUSED(event)
        QGraphicsScene::mousePressEvent(event);

        switch(event->button()) {
            case Qt::LeftButton: {
                mouse::is_pressed_lmb = true;
                break;
            }
            case Qt::MiddleButton: {
            //  Create a new node and add it to scene:
                schemaCanvas::createNode(event->scenePos(), this);
                mouse::is_pressed_mmb = true;
                break;
            }
            case Qt::RightButton: {
                mouse::is_pressed_rmb = true;
                break;
            }
            default:
                break;
        }
    }

    void schemaCanvas::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
        Q_UNUSED(event)
        QGraphicsScene::mouseReleaseEvent(event);

        mouse::is_pressed_lmb = false;
        mouse::is_pressed_mmb = false;
        mouse::is_pressed_rmb = false;
    }

    void schemaCanvas::keyPressEvent(QKeyEvent* event) {
        Q_UNUSED(event)
        QGraphicsScene::keyPressEvent(event);

        if(event->matches(QKeySequence::Copy)) {
            if(!list.clipboard.isEmpty())
                qWarning() << "Warning! Discarding clipboard";

            list.clipboard = selectedItems();
            event->accept();
        }

        if(event->matches(QKeySequence::Paste)) {
            if(!list.clipboard.isEmpty()) {
                for(auto j : list.clipboard) {
                    const auto node = qgraphicsitem_cast<nodeControl*>(j);
                    const auto copy = new nodeControl(*node);

                    addItem(copy);
                }
            }
            event->accept();
        }
    }

    void schemaCanvas::keyReleaseEvent(QKeyEvent* event) {
        Q_UNUSED(event)
        QGraphicsScene::keyReleaseEvent(event);

        event->accept();
    }

    void schemaCanvas::createNode(QPointF cpos, schemaCanvas* scenePtr) {
        Q_UNUSED(cpos)

        auto node = new nodeControl(cpos, "Node");
        scenePtr->list.nodelist.append(node);
        scenePtr->addItem(node);
    }

    void schemaCanvas::deleteNode(schemaCanvas* scenePtr) {
        Q_UNUSED(scenePtr)
    }

    void schemaCanvas::updateNode(schemaCanvas* scenePtr) {
        Q_UNUSED(scenePtr)
    }