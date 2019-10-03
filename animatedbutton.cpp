#include "animatedbutton.h"

AnimatedButton::AnimatedButton (QWidget* parent) : QPushButton(parent)
{

}

void AnimatedButton::enterEvent(QEvent *e)
{
    setCursor(Qt::PointingHandCursor);
    QPropertyAnimation *animation = new QPropertyAnimation(this, "color");
    animation->setDuration(300);
    animation->setStartValue(QColor(255, 255, 255));
    animation->setEndValue(QColor(57, 204, 24));
    animation->start();
    QFont bigFont("MS Shell Dlg 2", 16);
    setFont(bigFont);

    QWidget::enterEvent(e);
}

void AnimatedButton::leaveEvent(QEvent *e)
{
    setCursor(Qt::ArrowCursor);
    QPropertyAnimation *animation = new QPropertyAnimation(this, "color");
    animation->setDuration(300);
    animation->setStartValue(QColor(57, 204, 24));
    animation->setEndValue(QColor(255, 255, 255));
    animation->start();
    QFont smallFont("MS Shell Dlg 2", 12);
    setFont(smallFont);


    QWidget::leaveEvent(e);
}

QColor AnimatedButton::color(){
    return Qt::black; // getter is not really needed for now
}

void AnimatedButton::setColor (QColor color){
    setStyleSheet(QString("#switch_to_vr_button {border:2px solid #39CC18;background-color: rgb(%1, %2, %3);border-radius:25px;font-weight:bold;}    #switch_to_vr_button:pressed {border:none;background-color: rgb(57, 204, 24);border-radius:25px;font-size:12pt;font-weight:bold;} #switch_to_vr_button:visited {border:2px solid #39CC18;background-color: rgb(%1, %2, %3);border-radius:25px;font-weight:bold;}").arg(color.red()).arg(color.green()).arg(color.blue()));
}
