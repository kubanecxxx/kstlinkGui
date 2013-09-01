#ifndef BAR_H
#define BAR_H

#include <QWidget>

namespace Ui {
class bar;
}

class bar : public QWidget
{
    Q_OBJECT

public:
    explicit bar(QWidget *parent = 0);
    ~bar();

private:
    Ui::bar *ui;
    //void mouseMoveEvent(QMouseEvent * evt);
    //void mousePressEvent(QMouseEvent * evt);
    QPoint pos;

public slots:
    void ShowPercents(int percent, const QString & task);
};

#endif // BAR_H
