#include "tray.h"
#include <QDBusConnection>
#include <QDebug>
#include <QTimer>
#include <QDBusMessage>

#define connectS(method,slot) con.sessionBus().connect(service,path,interface,method,this,slot);

MainClass::MainClass(QObject *parent)
    : QObject(parent),
      prog(new bar),
      timer(new QTimer(this))
{

     service = "org.kubanec.kstlink";
     path = "/qstlink";
    //QString interface = "org.kubanec.kstlink.stlink";
     interface = "org.qtproject.Qt.QStLink";

    tray = new QSystemTrayIcon;
    tray->show();

    QStringList lst;
    lst << "uint";
    QDBusConnection con = QDBusConnection::connectToBus(QDBusConnection::SessionBus,"dbus");

    connectS("CoreHalted",SLOT(CoreHalted(quint32)));
    connectS("CommunicationFailed",SLOT(CommunicationFailed()));
    connectS("CoreRunning",SLOT(CoreRunning()));
    connectS("Verification",SLOT(Verification(bool)));
    connectS("Reading",SLOT(Reading(int)));
    connectS("Flashing",SLOT(Flashing(int)));
    connectS("Erasing",SLOT(Erasing(int)));

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->start(300);

    interface = "org.kubanec.kstlink.stlink";

    connect(tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,
            SLOT(activated(QSystemTrayIcon::ActivationReason)));

    connect(this->timer,SIGNAL(timeout()),this,SLOT(tooLongNic()));
    this->timer->setSingleShot(true);
    this->timer->start(1000);

    prog->show();
}

MainClass::~MainClass()
{

}

void MainClass::tooLongNic()
{
    tray->hide();
}

void MainClass::activated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
        prog->setHidden(prog->isVisible());
}

void MainClass::CoreHalted(quint32 address)
{
    s.StopAddress = address;
    s.run = "Halted";
    tray->setIcon(QIcon(":/tray/pause"));
}

void MainClass::CommunicationFailed()
{
    tray->setIcon(QIcon(":/tray/stop"));
    if (!timer->isActive())
        timer->start(10000);
}

void MainClass::CoreRunning()
{
    s.run = "Running";
    s.StopAddress = 0;
    tray->setIcon(QIcon(":/tray/play"));
}

void MainClass::Verification(bool ok)
{
    if (ok)
        tray->showMessage("Kstlink", "Verification successful",
                          QSystemTrayIcon::Information,3000);
    else
        tray->showMessage("Kstlink","Verification Failure",
                          QSystemTrayIcon::Critical,30000);

    prog->hide();
}

void MainClass::Erasing(int percent)
{
    prog->ShowPercents(percent,"Erasing");
}

void MainClass::Reading(int percent)
{
    prog->ShowPercents(percent,"Reading");
}

void MainClass::Flashing(int percent)
{
    prog->ShowPercents(percent,"Flashing");
}

QDBusMessage MainClass::DbusCallMethod(const QString &method)
{
    QDBusMessage msg = QDBusMessage::createMethodCall(service,path,interface,method);
    QDBusConnection con = QDBusConnection::connectToBus(QDBusConnection::SessionBus,"dbus");
    msg = con.call(msg,QDBus::Block,300);

    return msg;
}

void MainClass::timeout()
{
   bool ok = refreshState();

   if (ok)
   {
        QString tooltip;
        tooltip = QString("<table>\
                          <caption>Kstlink GUI</caption> \
                          <br/>\
                          <tr><td>Core Status</td><td><b>%1</b></td></tr> \
                          <tr><td>Core mode</td><td><b>%5</b></td></tr> \
                          <tr><td>PC address</td><td><b>0x%2</b></td></tr>\
                          <br/>\
                          <tr><td>Core ID</td><td><b>0x%3</b></td></tr>\
                          <tr><td>Chip ID</td><td><b>0x%4</b></td></tr>\
                          <tr><td>MCU name</td><td><b>%6</b></td></tr> \
                          <tr><td>Breakpoint count</td><td><b>%7</b></td></tr>\
                          </table>").
                arg(s.run).arg(s.StopAddress,0,16).arg(s.coreID,0,16).arg(s.chipID,0,16).
                arg(s.coreMode).arg(s.mcuName).arg(s.breakpointCount);

        tray->setToolTip(tooltip);
        tray->show();
        timer->stop();
   }
   else
   {
       tray->setToolTip(QString());
       CommunicationFailed();
   }
}

bool MainClass::refreshState()
{
    QStringList methods;
    methods << "GetChipID" << "GetCoreID" << "GetMcuName"
            << "GetModeString" << "GetBreakpointCount";

    for (int i = 0 ; i < methods.count(); i++)
    {
        QDBusMessage msg;
        QString method = methods[i];

        msg = DbusCallMethod(method);
        if(!msg.arguments().count())
            return false;

        QVariant v = msg.arguments().at(0);
        switch (i)
        {
        case 0: s.chipID = v.toInt(); break;
        case 1: s.coreID = v.toUInt(); break;
        case 2: s.mcuName = v.toString(); break;
        case 3: s.coreMode = v.toString(); break;
        case 4: s.breakpointCount = v.toInt(); break;
        }
    }

    return true;
}
