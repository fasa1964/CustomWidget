#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QColor>
#include <QSettings>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/customwidget.ico"));

    customWidget = new FormCustomWidget(0);


    readSettings();

    connect(ui->timeSlider, &QSlider::valueChanged, this, &MainWindow::timeSliderValueChanged);
    connect(ui->sendTextButton, &QPushButton::clicked, this, &MainWindow::sendMessageButtonClicked);
    connect(ui->countdownButton, &QPushButton::clicked, this, &MainWindow::countdownButtonClicked);
    connect(ui->messageTextEdit , &QLineEdit::textChanged, this, &MainWindow::messageTextEditChanged);

    connect(ui->redSlider , &QSlider::valueChanged, this, &MainWindow::redSliderValueChanged);
    connect(ui->greenSlider , &QSlider::valueChanged, this, &MainWindow::greenSliderValueChanged);
    connect(ui->blueSlider , &QSlider::valueChanged, this, &MainWindow::blueSliderValueChanged);
    connect(ui->alphaSlider , &QSlider::valueChanged, this, &MainWindow::alphaSliderValueChanged);

    connect(ui->textRadioButton , &QRadioButton::clicked , this, &MainWindow::radioButtonStateChanged);
    connect(ui->rectangleRadioButton , &QRadioButton::clicked , this, &MainWindow::radioButtonStateChanged);
    connect(ui->windowRadioButton , &QRadioButton::clicked , this, &MainWindow::radioButtonStateChanged);

    connect(ui->fontSizeSlider , &QSlider::valueChanged, this, &MainWindow::fontSizeSliderValueChanged);
    connect(ui->framlessCheckBox, &QCheckBox::stateChanged, this, &MainWindow::framelessCheckBoxStateChanged);
    connect(ui->onTopCheckBox, &QCheckBox::stateChanged, this, &MainWindow::onTopCheckBoxStateChanged);

    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->infoButton, &QPushButton::clicked, this, &MainWindow::infoButtonClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();

    customWidget->close();

    event->accept();
}

void MainWindow::sendMessageButtonClicked()
{
    customWidget->setMessageText(ui->messageTextEdit->text(), ui->timeBox->value());

    if(customWidget->isHidden())
        customWidget->show();
}

void MainWindow::countdownButtonClicked()
{

    if(ui->countdownBox->value() <= 0){
        customWidget->show();
        customWidget->setMessageText("You have to increase the counter", 8);
        return;
    }

    customWidget->show();
    customWidget->startCountdown(ui->countdownBox->value());
}

void MainWindow::timeSliderValueChanged(int value)
{
    ui->timeBox->setValue(value);
}

void MainWindow::messageTextEditChanged(const QString &text)
{
    if(text.isEmpty())
        ui->sendTextButton->setEnabled(false);
    else
        ui->sendTextButton->setEnabled(true);
}

void MainWindow::redSliderValueChanged(int value)
{
    ui->redBox->setValue(value);
    updateColor();
}

void MainWindow::greenSliderValueChanged(int value)
{
    ui->greenBox->setValue(value);
    updateColor();
}

void MainWindow::blueSliderValueChanged(int value)
{
    ui->blueBox->setValue(value);
    updateColor();
}

void MainWindow::alphaSliderValueChanged(int value)
{
    ui->alphaBox->setValue(value);
    updateColor();
}

void MainWindow::fontSizeSliderValueChanged(int value)
{
    ui->fontSizeBox->setValue(value);
    customWidget->setFontSize(value);
    customWidget->update();
}

void MainWindow::framelessCheckBoxStateChanged(int state)
{
    if(state == 2)
        customWidget->setWindowFlag(Qt::FramelessWindowHint, true);
    else
        customWidget->setWindowFlag(Qt::FramelessWindowHint, false);

    customWidget->update();
    sendMessageButtonClicked();
}

void MainWindow::onTopCheckBoxStateChanged(int state)
{
    if(state == 2)
        customWidget->setAttribute(Qt::WA_AlwaysStackOnTop, true);
    else
       customWidget->setAttribute(Qt::WA_AlwaysStackOnTop, false);


    customWidget->setFocus(Qt::ActiveWindowFocusReason);
    customWidget->update();
    sendMessageButtonClicked();

}

void MainWindow::radioButtonStateChanged(bool /*checked*/)
{
    disconnectSlider();

    if(ui->textRadioButton->isChecked())
    {
        ui->redSlider->setValue( textColor.red() );
        ui->redBox->setValue(textColor.red());

        ui->greenSlider->setValue( textColor.green() );
        ui->greenBox->setValue(textColor.green());

        ui->blueSlider->setValue( textColor.blue() );
        ui->blueBox->setValue(textColor.blue());

        ui->alphaSlider->setValue( textColor.alpha() );
        ui->alphaBox->setValue(textColor.alpha());
    }

    if(ui->windowRadioButton->isChecked())
    {
        ui->redSlider->setValue( windowColor.red() );
        ui->redBox->setValue(windowColor.red());

        ui->greenSlider->setValue( windowColor.green() );
        ui->greenBox->setValue(windowColor.green());

        ui->blueSlider->setValue( windowColor.blue() );
        ui->blueBox->setValue(windowColor.blue());

        ui->alphaSlider->setValue( windowColor.alpha() );
        ui->alphaBox->setValue(windowColor.alpha());
    }

    if(ui->rectangleRadioButton->isChecked())
    {
        ui->redSlider->setValue( rectangleColor.red() );
        ui->redBox->setValue(rectangleColor.red());

        ui->greenSlider->setValue( rectangleColor.green() );
        ui->greenBox->setValue(rectangleColor.green());

        ui->blueSlider->setValue( rectangleColor.blue() );
        ui->blueBox->setValue( rectangleColor.blue());

        ui->alphaSlider->setValue( rectangleColor.alpha() );
        ui->alphaBox->setValue(rectangleColor.alpha());

    }

    connectSlider();

}

void MainWindow::infoButtonClicked()
{
    infoDlg = new DialogInfo(this);
    infoDlg->setCaptionText( QApplication::applicationName());
    infoDlg->setVersionText( QApplication::applicationVersion());

    QString description = "<html>This app is an example for programming a custom widgets in Qt6."
                          "Developed by Farschad Saberi in C++ with Qt 6.0.2<br>"
                          "Feel free to change the sourcecode!<br>"
                          "This app stands under the "
                          "<a href='https://www.gnu.org/licenses/gpl-3.0.en.html'><span style=' text-decoration: underline; color:#1e90ff;'"
                          ">GNU LPG v. 3 License</span></a></p><br>"
                          "You can download the sourcecode from "
                          "<a href='https://github.com/fasa1964/CustomWidget/tree/master'><span style='text-decoration: underline; color:#1e90ff;'>github.</span></a></html>";


    infoDlg->setDescryptionText(description);
    infoDlg->exec();

}

QString MainWindow::convertTo(const QColor &color)
{
    // RGBA
    QString cs =  QString("%1,%2,%3,%4").arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());
    return cs;
}

QColor MainWindow::convertFrom(const QString &color)
{
    QStringList list = color.split(",");
    bool ok;
    int red = list.at(0).toInt(&ok); Q_ASSERT(ok);
    int green = list.at(1).toInt(&ok); Q_ASSERT(ok);
    int blue = list.at(2).toInt(&ok); Q_ASSERT(ok);
    int alpha = list.at(3).toInt(&ok); Q_ASSERT(ok);

    QColor c = QColor(red,green,blue,alpha);

    return c;
}

void MainWindow::disconnectSlider()
{
    disconnect(ui->redSlider , &QSlider::valueChanged, this, &MainWindow::redSliderValueChanged);
    disconnect(ui->greenSlider , &QSlider::valueChanged, this, &MainWindow::greenSliderValueChanged);
    disconnect(ui->blueSlider , &QSlider::valueChanged, this, &MainWindow::blueSliderValueChanged);
    disconnect(ui->alphaSlider , &QSlider::valueChanged, this, &MainWindow::alphaSliderValueChanged);
}

void MainWindow::connectSlider()
{
    connect(ui->redSlider , &QSlider::valueChanged, this, &MainWindow::redSliderValueChanged);
    connect(ui->greenSlider , &QSlider::valueChanged, this, &MainWindow::greenSliderValueChanged);
    connect(ui->blueSlider , &QSlider::valueChanged, this, &MainWindow::blueSliderValueChanged);
    connect(ui->alphaSlider , &QSlider::valueChanged, this, &MainWindow::alphaSliderValueChanged);
}

void MainWindow::updateColor()
{
    QColor color(ui->redBox->value(), ui->greenBox->value(), ui->blueBox->value(), ui->alphaBox->value());

    if(ui->textRadioButton->isChecked()){
        customWidget->setTextColor(color);
        textColor = color;
    }

    if(ui->windowRadioButton->isChecked()){
        customWidget->setBackgroundColor(color);
        windowColor = color;
    }

    if(ui->rectangleRadioButton->isChecked()){
        customWidget->setRectangleColor(color);
        rectangleColor = color;
    }

    customWidget->update();
}

void MainWindow::readSettings()
{
    bool ok;
    QSettings settings( "customwidget@qt6.com", QApplication::applicationName());
    setGeometry( settings.value("geometrie", QRect(200,200,600,400)).toRect() );
    ui->textRadioButton->setChecked( settings.value("textchecked", true).toBool()  );
    ui->windowRadioButton->setChecked( settings.value("windowchecked", false).toBool()  );
    ui->rectangleRadioButton->setChecked( settings.value("rectanglechecked", false).toBool()  );
    ui->messageTextEdit->setText( settings.value("messagetext", "Enter your message text").toString());
    ui->framlessCheckBox->setChecked( settings.value("frameless", false).toBool());

    int fontsize = settings.value("fontsize", 15).toInt(&ok); Q_ASSERT(ok);

    ui->fontSizeSlider->setValue( fontsize );
    ui->fontSizeBox->setValue( fontsize );

    QString tc = settings.value("textcolor", "106,51,0,255").toString();
    textColor =  convertFrom( tc );

    QString rc = settings.value("rectanglecolor", "0,0,0,255").toString();
    rectangleColor =  convertFrom( rc );

    QString wc = settings.value("windowcolor", "255,80,255,255").toString();
    windowColor =  convertFrom( wc );

    customWidget->setTextColor( textColor );
    customWidget->setRectangleColor( rectangleColor );
    customWidget->setBackgroundColor( windowColor );
    customWidget->setFontSize( fontsize );

    if(ui->framlessCheckBox->isChecked())
        customWidget->setWindowFlag(Qt::FramelessWindowHint, true);
    else
        customWidget->setWindowFlag(Qt::FramelessWindowHint, false);

    if(!ui->messageTextEdit->text().isEmpty())
        ui->sendTextButton->setEnabled(true);

}

void MainWindow::saveSettings()
{
    QSettings settings( "customwidget@qt6.com", QApplication::applicationName());

    settings.setValue("geometrie", geometry());
    settings.setValue("textchecked", ui->textRadioButton->isChecked());
    settings.setValue("windowchecked", ui->windowRadioButton->isChecked());
    settings.setValue("rectanglechecked", ui->rectangleRadioButton->isChecked());
    settings.setValue("textcolor",   convertTo( textColor ));
    settings.setValue("windowcolor", convertTo( windowColor ));
    settings.setValue("rectanglecolor", convertTo( rectangleColor ));
    settings.setValue("messagetext", ui->messageTextEdit->text());
    settings.setValue("frameless", ui->framlessCheckBox->isChecked());
    settings.setValue("fontsize", ui->fontSizeBox->value());
}

