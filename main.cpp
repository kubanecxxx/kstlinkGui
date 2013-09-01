#include "tray.h"
#include <QApplication>
#include <QDBusConnection>

int main(int argc, char *argv[])
{
    //single instance
    QDBusConnection con = QDBusConnection::connectToBus(QDBusConnection::SessionBus,"bus");
    bool ok = con.registerService("org.kubanec.kstlinkGui");
    if (!ok)
    {
        qFatal("Application already running...");
    }

    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    new MainClass(&a);

    return a.exec();
}
