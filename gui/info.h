#ifndef INFO_H
#define INFO_H

#include <QWidget>
#include "page.h"
#include "tray.h"

namespace Ui {
class Info;
}

class Info : public Page
{
    Q_OBJECT

public:
    explicit Info(const s_t & t,QObject* tray, QWidget *parent = 0);
    ~Info();

private:
    Ui::Info *ui;
    const s_t & s;

private slots:
    void timeout(void);
};

#endif // INFO_H
