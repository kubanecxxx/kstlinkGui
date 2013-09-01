#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSystemTrayIcon>
#include <QDBusConnection>
#include "bar.h"

class MainClass :public QObject
{
    Q_OBJECT

public:
    MainClass(QObject *parent = 0);
    ~MainClass();

private:
    QSystemTrayIcon * tray;

    QString service ;
    QString path;
    QString interface;

    QDBusMessage DbusCallMethod(const QString & method);
    bar * prog;
    QTimer * timer;

    struct s
    {
        QString run;
        quint32 StopAddress;
        int chipID;
        quint32 coreID;
        QString mcuName;
        QString coreMode;
        int breakpointCount;
    } s;

    bool refreshState(void);

private slots:
    void CoreHalted(quint32);
    void CommunicationFailed();
    void CoreRunning();
    void Verification(bool ok);
    void Erasing(int);
    void Flashing(int);
    void Reading(int);
    void timeout();

    void activated(QSystemTrayIcon::ActivationReason);
    void tooLongNic(void);
};

#endif // MAINWINDOW_H
