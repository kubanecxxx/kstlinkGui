#ifndef FLASH_H
#define FLASH_H

#include <QWidget>
#include "page.h"

namespace Ui {
class Flash;
}

class Flash : public Page
{
    Q_OBJECT

public:
    explicit Flash(QWidget *parent = 0);
    ~Flash();

private:
    Ui::Flash *ui;
};

#endif // FLASH_H
