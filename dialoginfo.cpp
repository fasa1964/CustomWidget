#include "dialoginfo.h"
#include "ui_dialoginfo.h"

#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>

DialogInfo::DialogInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInfo)
{
    ui->setupUi(this);

    ui->descriptionLabel->setTextFormat(Qt::RichText);

    connect(ui->descriptionLabel, &QLabel::linkActivated, this, &DialogInfo::linkActivate);
    connect(ui->closeButton, &QPushButton::clicked, this, &DialogInfo::close);
    connect(ui->aboutQtButton, &QPushButton::clicked, this, &DialogInfo::aboutQtButtonClicked);

}

DialogInfo::~DialogInfo()
{
    delete ui;
}

void DialogInfo::setCaptionText(const QString &text)
{
    ui->captionLabel->setText(text);
}

void DialogInfo::setVersionText(const QString &text)
{
    ui->versionLabel->setText(text);
}

void DialogInfo::setDescryptionText(const QString &text)
{
    ui->descriptionLabel->setText(text);
}

void DialogInfo::aboutQtButtonClicked()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void DialogInfo::linkActivate(const QString &link)
{
    QDesktopServices::openUrl(link);
    qDebug() << link;
}
