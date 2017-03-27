#include "util.h"
#include <QtCore>
#include <QApplication>

#ifdef Q_OS_WIN
#include <windows.h> // for Sleep
#endif

util::util()
{
}

QDir util::directoryOf(const QString &subdir)
{

    QDir dir(QApplication::applicationDirPath());
    dir.cd(subdir);
    QString s = dir.absolutePath();
    return dir;
}

void util::qSleep(int ms)
{
#ifdef Q_OS_WIN
    Sleep(uint(ms));
#else
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
#endif
}

QString util::msecToString(int ms)
{
    int secs = ms/1000;
    int mins = (secs / 60) % 60;
    int hours = (secs / 3600);
    return QString("%1:%2:%3")
    .arg(hours, 2, 10, QLatin1Char('0'))
    .arg(mins, 2, 10, QLatin1Char('0'))
    .arg(secs, 2, 10, QLatin1Char('0'));
}
