#include "formcustomwidget.h"
#include "ui_formcustomwidget.h"

#include <QTimer>
#include <QPainter>
#include <QFont>

#include <QDebug>

FormCustomWidget::FormCustomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCustomWidget)
{
    ui->setupUi(this);

    counter = 0;
    countdown = false;

    setBackgroundColor(Qt::lightGray);
    setFontSize(15);

    //setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_OpaquePaintEvent);

}

FormCustomWidget::~FormCustomWidget()
{
    delete ui;
}

void FormCustomWidget::setMessageText(const QString &text, int seconds)
{
    //ui->messageText->setText(text);
    m_messageText = text;

    if(seconds > 0){
        int msec = seconds * 1000;
        QTimer::singleShot(msec, this, SLOT(close()));
    }
}

void FormCustomWidget::timeout()
{
    counter--;
    if(counter <= 0){
        timer->stop();
        countdown = false;
        close();
    }

    update();
}

const QColor &FormCustomWidget::rectangleColor() const
{
    return m_rectangleColor;
}

void FormCustomWidget::setRectangleColor(const QColor &newRectangleColor)
{
    m_rectangleColor = newRectangleColor;
}

void FormCustomWidget::startCountdown(int seconds)
{
    countdown = true;
    counter = seconds;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FormCustomWidget::timeout);
    timer->start(1000);

}

int FormCustomWidget::fontSize() const
{
    return m_fontSize;
}

void FormCustomWidget::setFontSize(int newFontSize)
{
    m_fontSize = newFontSize;
}

const QColor &FormCustomWidget::backgroundColor() const
{
    return m_backgroundColor;
}

void FormCustomWidget::setBackgroundColor(const QColor &newBackgroundColor)
{
    m_backgroundColor = newBackgroundColor;
}

const QString &FormCustomWidget::messageText() const
{
    return m_messageText;
}

const QColor &FormCustomWidget::textColor() const
{
    return m_textColor;
}

void FormCustomWidget::setTextColor(const QColor &newTextColor)
{
    m_textColor = newTextColor;
}

void FormCustomWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QFont font = painter.font();
    font.setPointSize(fontSize());
    painter.setFont(font);


    painter.setPen(backgroundColor());
    painter.fillRect( painter.window(), backgroundColor() );

    // For text color
    painter.setPen( m_textColor );

    // For background window color
    QBrush brush = painter.background();
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(backgroundColor());
    painter.setBrush(brush);
    painter.setBackground(brush);


    QFontMetrics fm(font);
    int w = fm.horizontalAdvance(messageText());
    int h = fm.height();


    const QRect rect =  QRect(geometry().width()/2-(w/2), geometry().height()/2 - (h/2), geometry().width(), geometry().height());
    QRect boundingRect;
    if(countdown){
        QString sec = QString("%1").arg(counter);
        painter.drawText(rect, 0, sec, &boundingRect);
    }else
        painter.drawText(rect, 0, messageText(), &boundingRect);

    // Drawing a rectangle
    painter.setPen(rectangleColor());
    painter.drawLine(0,0,geometry().width(), 0 );
    painter.drawLine(0, geometry().height(), 0, 0 );
    painter.drawLine(geometry().width(), geometry().height(), 0, geometry().height()-1);
    painter.drawLine(geometry().width(), geometry().height(), geometry().width()-1, 0);
    painter.setPen( m_textColor );

}
