#ifndef FORMCUSTOMWIDGET_H
#define FORMCUSTOMWIDGET_H

#include <QWidget>
#include <QColor>
#include <QPaintEvent>


namespace Ui {
class FormCustomWidget;
}

class FormCustomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FormCustomWidget(QWidget *parent = nullptr);
    ~FormCustomWidget();

    const QColor &textColor() const;
    void setTextColor(const QColor &newTextColor);

    const QString &messageText() const;

    const QColor &backgroundColor() const;
    void setBackgroundColor(const QColor &newBackgroundColor);

    int fontSize() const;
    void setFontSize(int newFontSize);

    const QColor &rectangleColor() const;
    void setRectangleColor(const QColor &newRectangleColor);

    void startCountdown(int seconds);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

public slots:
    void setMessageText(const QString &text, int seconds);

private slots:
    void timeout();

private:
    Ui::FormCustomWidget *ui;

    QTimer *timer;

    QString m_messageText;
    QColor m_textColor;
    QColor m_backgroundColor;
    QColor m_rectangleColor;

    int m_fontSize;
    int counter;
    bool countdown;
};

#endif // FORMCUSTOMWIDGET_H
