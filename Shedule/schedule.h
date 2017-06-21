#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QMainWindow>
#include "mainwidget.h"

class Schedule : public QMainWindow
{
   Q_OBJECT

public:
    explicit Schedule(QWidget *parent = 0);

    ~Schedule();

private:
    MainWidget * mainWidget;

protected:
    virtual void closeEvent(QCloseEvent * event);

};


#endif // SCHEDULE_H
