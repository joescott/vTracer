#ifndef UTIL_H
#define UTIL_H

#include <QtCore>

class util
{
public:
    util();
    static QDir directoryOf(const QString &subdir);
    static void qSleep(int ms);
    static QString msecToString(int ms);
};

#endif // UTIL_H
