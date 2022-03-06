#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

#include <formcustomwidget.h>
#include <dialoginfo.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual void closeEvent(QCloseEvent *event) override;

private slots:
    void sendMessageButtonClicked();
    void countdownButtonClicked();
    void timeSliderValueChanged(int value);
    void messageTextEditChanged(const QString &text);

    void redSliderValueChanged(int value);
    void greenSliderValueChanged(int value);
    void blueSliderValueChanged(int value);
    void alphaSliderValueChanged(int value);

    void fontSizeSliderValueChanged(int value);
    void framelessCheckBoxStateChanged(int state);
    void onTopCheckBoxStateChanged(int state);

    void radioButtonStateChanged(bool);
    void infoButtonClicked();

private:
    Ui::MainWindow *ui;

    FormCustomWidget *customWidget;
    DialogInfo *infoDlg;

    QColor textColor;
    QColor rectangleColor;
    QColor windowColor;


    QString convertTo(const QColor &color);
    QColor convertFrom(const QString &color);

    void disconnectSlider();
    void connectSlider();

    void updateColor();
    void readSettings();
    void saveSettings();

};
#endif // MAINWINDOW_H
