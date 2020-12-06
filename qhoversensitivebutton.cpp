#include "qhoversensitivebutton.h"
#include "mainwindow.h"
#include <QDebug>

QHoverSensitiveButton::QHoverSensitiveButton(QWidget *parent) : QPushButton(parent)
{
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
}

void QHoverSensitiveButton::hoverEnter(QHoverEvent *)
{
    qDebug() << "Hovering enter";
}

void QHoverSensitiveButton::hoverLeave(QHoverEvent *)
{
    qDebug() << "Hovering leave";

}

void QHoverSensitiveButton::hoverMove(QHoverEvent *)
{
    qDebug() << "Hovering move";

}

bool QHoverSensitiveButton::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::HoverEnter:
        hoverEnter(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverMove:
        hoverMove(static_cast<QHoverEvent*>(event));
        return true;
        break;
    default:
        break;
    }
    return QWidget::event(event);
}
