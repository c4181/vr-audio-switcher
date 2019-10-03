#ifndef ANIMATEDBUTTON_H
#define ANIMATEDBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>


class AnimatedButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

protected:
    virtual void enterEvent( QEvent* e );
    virtual void leaveEvent( QEvent* e );

public:
    AnimatedButton(QWidget* parent = nullptr);
    void setColor (QColor color);
    QColor color();
};

#endif // ANIMATEDBUTTON_H
