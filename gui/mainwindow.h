#ifndef MAINWINDOW_H1
#define MAINWINDOW_H1

#include <QMainWindow>
#include "tray.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const s_t & t, QObject *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    const s_t & s;
};

#endif // MAINWINDOW_H
