#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    app.setStyle(QStyleFactory::create("Fusion"));
    app.setApplicationName("CustomWidget");
    app.setApplicationDisplayName("CustomWidget");
    app.setApplicationVersion("1.0");

    app.setWindowIcon(QIcon(":/customwidget.ico"));


    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "CustomWidget_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return app.exec();
}
