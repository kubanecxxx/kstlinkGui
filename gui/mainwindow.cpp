#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widgettreepages.h"
#include "info.h"
#include "flash.h"

MainWindow::MainWindow(const s_t & t, QObject *parent) :
    QMainWindow(NULL),
    ui(new Ui::MainWindow),
    s(t)
{
    ui->setupUi(this);
    WidgetTreePages * w = new WidgetTreePages(this);
    setCentralWidget(w);

    Page * p;
    p = new Info(s,parent,this);
    w->AddPage(p);

    p = new Flash();
    w->AddPage(p);
}

MainWindow::~MainWindow()
{
    delete ui;
}
