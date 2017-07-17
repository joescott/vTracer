#include <QtGui>
#include <QTranslator>
#include <QtGlobal>
#include <QApplication>
#include <QSplashScreen>

#include "def.h"
#include "mainwindow.h"
#include "util.h"

void MessageOutput(QtMsgType type, const QMessageLogContext &, const QString & str)
{
    const char * msg = str.toStdString().c_str();
    switch((int)type)
    {
        case QtDebugMsg:
            fprintf(stdout, "Debug: %s\n", msg);
            break;
        case QtWarningMsg:
            fprintf(stderr, "Warning: %s\n", msg);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "Critical: %s\n", msg);
            break;
        case QtFatalMsg:
            fprintf(stderr, "Fatal: %s\n", msg);
            abort();
    }
}


int main(int argc, char *argv[])
{
    qInstallMessageHandler(MessageOutput);

    QTextCodec *Codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(Codec);

    QSettings settings( CF_PATH, QSettings::IniFormat );

    QApplication a(argc, argv);

    QTranslator tl;
    if (!tl.load(settings.value(CF_LANGUAGE).toString(),
                         util::directoryOf(LANG_PATH).absolutePath()))
        qDebug() << "Using Default Language";

    QApplication::installTranslator(&tl);

    QPixmap pixmap(":img/splash");
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->setWindowFlags(splash->windowFlags() | Qt::WindowStaysOnTopHint);
    splash->show();
    a.processEvents();
    splash->showMessage(QObject::tr("\n\nLoading ..."),
                        Qt::AlignCenter|Qt::AlignBottom,Qt::blue);

    QFile file(":qss/default");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);

    MainWindow *w = new MainWindow(&settings);
    w->show();


    //util::qSleep(1000);
    splash->finish(w);


    return a.exec();
}
