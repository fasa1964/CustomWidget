#ifndef DIALOGINFO_H
#define DIALOGINFO_H

#include <QDialog>


namespace Ui {
class DialogInfo;
}

class DialogInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInfo(QWidget *parent = nullptr);
    ~DialogInfo();


    void setCaptionText(const QString &text);
    void setVersionText(const QString &text);
    void setDescryptionText(const QString &text);

private slots:
    void aboutQtButtonClicked();
    void linkActivate(const QString &link);

private:
    Ui::DialogInfo *ui;
};

#endif // DIALOGINFO_H
