#include "tray.h"
#include <QApplication>
#include <QDBusConnection>

int main(int argc, char *argv[])
{
    //single instance
    QDBusConnection * con;
    if (argc==2)
    {
        QString str (argv[1]);
        QString bdak = QString("tcp:host=%1,port=6668").arg(str);
        QDBusConnection con2 = QDBusConnection::connectToBus(bdak,"bus");
        con = &con2;
    }
    else
    {
        QDBusConnection con3 = QDBusConnection::connectToBus(QDBusConnection::SessionBus,"bus");
        con = &con3;
    }

    bool ok = con->registerService("org.kubanec.kstlinkGui");
    if (!ok)
    {
        qFatal("Application already running...");
    }

    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    new MainClass(*con,&a);


    return a.exec();
}
