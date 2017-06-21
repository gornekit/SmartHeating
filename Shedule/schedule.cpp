#include "schedule.h"
#include "mainwidget.h"
#include <QPalette>
#include <QColor>
#include <QMessageBox>
#include <QCloseEvent>

Schedule::Schedule(QWidget *parent) :
    QMainWindow(parent)
{
    mainWidget = new MainWidget();

    this->setCentralWidget(mainWidget);

    QPalette pal;
    pal.setColor(this->backgroundRole(), QColor(245, 255, 245));
    move(10, 15);

    setPalette(pal);
    setFixedSize(mainWidget->size());

}

void Schedule::closeEvent(QCloseEvent * event)
{
    if(mainWidget->getChangedStatus())
    {
        QMessageBox msgBox;

        msgBox.setText("Warning!");

        msgBox.setInformativeText("Data wasn't saved. Exit?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setFixedSize(1200, 1000);
        int res = msgBox.exec();

        if(res == QMessageBox::Ok)
            event->accept();
        else
            event->ignore();
    }
    else
        event->accept();
}

Schedule::~Schedule()
{

}
