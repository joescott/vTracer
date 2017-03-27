#ifndef ACTIONINTERFACE_H
#define ACTIONINTERFACE_H

#include <QString>
#include <QtGui>

class ActionInterface
{
public:
    virtual ~ActionInterface() {}
    virtual void doAction() = 0;
};


QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(ActionInterface, "com.trolltech.Plugin.ActionInterface/1.0")
QT_END_NAMESPACE

#endif // ACTIONINTERFACE_H
