#include "core/qCustom.h"

qDialog::qDialog(const QString& message, QtMsgType type, QWidget* parent) :
    QMessageBox (parent),
    attr        ("Promod Dialog", 500, true),
    resource    (QString(), QPixmap())
{

    if(message.isEmpty())
        qWarning() << __FILE__ << __LINE__ << "Expected non-empty message";

    switch (type){

        case QtInfoMsg:
            resource.file = ":/icons/msg.info.svg";
            resource.icon = QPixmap(resource.file).scaledToHeight(30, Qt::SmoothTransformation);;
            break;

        case QtWarningMsg:
            resource.file = ":/icons/msg.warn.svg";
            resource.icon = QPixmap(resource.file).scaledToHeight(30, Qt::SmoothTransformation);
            break;

        case QtCriticalMsg:
            resource.file = ":/icons/msg.qsn.svg";
            resource.icon = QPixmap(resource.file).scaledToHeight(30, Qt::SmoothTransformation);;
            break;

        case QtFatalMsg:
            resource.file = ":/icons/msg.err.svg";
            resource.icon = QPixmap(resource.file).scaledToHeight(30, Qt::SmoothTransformation);;
            break;

        default:
            break;
    }

    setText(message);
    setIconPixmap(resource.icon);
    setWindowTitle(attr.title);

    setFixedWidth     (attr.width);
    setDefaultButton  (QMessageBox::Save);
    setStandardButtons(QMessageBox::Save |\
                       QMessageBox::Discard |\
                       QMessageBox::Cancel);

    if(attr.no_icon){
        button(QMessageBox::Save)->setIcon(QIcon());
        button(QMessageBox::Cancel)->setIcon(QIcon());
        button(QMessageBox::Discard)->setIcon(QIcon());
    }
}

qPushB::qPushB(QWidget* parent,\
               const QString& name,\
               const QString& file,\
               const QSize&  isize,\
               const QSize&  bsize)

  : QPushButton(parent),
    attr(isize, bsize),
    resource(name, file, QIcon(resource.file)),
    opacity (new QOpac(this))
{
//  Display warning if filename is empty:
    if(file.isEmpty())
        qWarning() << __FILE__ << __LINE__ << "Expected non-empty filename";

//  Display warning if name is empty:
    if(name.isEmpty())
        qWarning() << __FILE__ << __LINE__ << "Expected non-empty string";

//  Set tool-tip for button:
    setToolTip(resource.name);

//  Set icon of button:
    setIcon(resource.icon);

//  Set geometric properties of button:
    setMaximumSize(QSize(45, 35));
    setIconSize   (attr.isize);
    setFixedSize  (attr.bsize);

//  Set graphics effects:
    opacity.effect->setOpacity(1.0);
    setGraphicsEffect(opacity.effect);
}

void qPushB::enterEvent(QEnterEvent* event){

    if(opacity.effect)
        opacity.effect->setOpacity(0.8);

    QPushButton::enterEvent(event);
}

void qPushB::leaveEvent(QEvent* event){

    if(opacity.effect)
        opacity.effect->setOpacity(1.0);

    QPushButton::leaveEvent(event);
}
