#include "mainwidget.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QDebug>
#include <QPixmap>
#include <QColor>
#include <QPalette>
#include <QFrame>
#include <QPainter>
#include <QDialog>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent), changedData(false)

{
    //Set up file
    fileName = "/Users/nikita/Desktop/SmartHeating/atmega32A/eeprom/eeprom.txt";
    file = new File(fileName);

    //Create time
    time = new QTime();
    time->start();

    //Quick filling set up
    for(int i = 0 ; i < 4 ; ++i)
    {
        fillData[i] = new QDoubleSpinBox();
        fillData[i]->setRange(0, 99);
        fillData[i]->setDecimals(0);
        fillData[i]->setSingleStep(1);
        fillData[i]->setSuffix(" °C");
        fillButt[i] = new QPushButton("Fill with");
    }

    connect(fillButt[0], SIGNAL(clicked()), SLOT(fillMorning()));
    connect(fillButt[1], SIGNAL(clicked()), SLOT(fillAfternoon()));
    connect(fillButt[2], SIGNAL(clicked()), SLOT(fillEvening()));
    connect(fillButt[3], SIGNAL(clicked()), SLOT(fillNight()));

    //Clear button set up
    clearButt = new QPushButton("Clear");
    connect(clearButt, SIGNAL(clicked()), SLOT(clearTable()));

    //Save button set up
    saveButt = new QPushButton("Save");
    connect(saveButt, SIGNAL(clicked()), SLOT(saveChanges()));

    loadButt = new QPushButton("Load");
    connect(loadButt, SIGNAL(clicked()), SLOT(loadData()));

    //Creating table
    QStringList days;
    days << "Monday" << "Tuesday" << "Wednesday" << "Thursday" << "Friday" << "Saturday" << "Sunday";

    for(int i = 0 ; i < 4 ; ++i)
    {
        table[i] = new QTableWidget(1, COLUMNS, parent);

        for(int j = 0 ; j < COLUMNS ; ++j)
        {
            table[i]->setCellWidget(0, j, createSpinBox());
            table[i]->setHorizontalHeaderLabels(days);
            table[i]->setFixedSize(716, 53);
        }
    }

    //Set up images
    image[0] = new QImage("/Users/nikita/Desktop/SmartHeating/Shedule/images/morning.jpg");
    image[1] = new QImage("/Users/nikita/Desktop/SmartHeating/Shedule/images/afternoon.jpg");
    image[2] = new QImage("/Users/nikita/Desktop/SmartHeating/Shedule/images/evening.jpg");
    image[3] = new QImage("/Users/nikita/Desktop/SmartHeating/Shedule/images/night.jpg");

    QFont * font = new QFont();
    font->setFamily("Helvetica [Cronyx]");
    font->setPointSize(40);
    font->setWeight(QFont::Normal);

    for(int i = 0 ; i < 4 ; ++i)
    {
        label[i] = new QLabel();
        label[i]->setFixedSize(300, 160);
        label[i]->setScaledContents(true);
        label[i]->setPixmap(QPixmap::fromImage(*image[i], Qt::AutoColor));

        text[i] = new QLabel();
        text[i]->setFixedSize(700, 50);
        text[i]->setTextFormat(Qt::RichText);
        text[i]->setFont(*font);
        text[i]->setAlignment(Qt::AlignCenter);
        text[i]->setStyleSheet("color: rgb(0, 150, 0)");
    }

    text[0]->setText("Morning 7:00 - 12:00");
    text[1]->setText("Afternoon 12:00 - 18:00");
    text[2]->setText("Evening 18:00 - 00:00");
    text[3]->setText("Night 00:00 - 7:00");


    //Set up Line Widgets
    QFrame * vLine = new QFrame();
    vLine->setLineWidth(1);
    vLine->setFrameShape(QFrame::VLine);
    vLine->setFrameShadow(QFrame::Raised);
    vLine->setPalette(QPalette(QColor(240, 255, 240)));

    //Set up layout
    QGridLayout * grid = new QGridLayout();

    grid->addWidget(label[0], 0, 0, 2, 2);
    grid->addWidget(table[0], 1, 2, 1, 5);
    grid->addWidget(text[0], 0, 2, 1, 5);
    grid->addWidget(fillButt[0], 0, 7, 1, 1, Qt::AlignBottom);
    grid->addWidget(fillData[0], 1, 7, 1, 1);

    grid->addWidget(label[1], 2, 0, 2, 2);
    grid->addWidget(table[1], 3, 2, 1, 5);
    grid->addWidget(text[1], 2, 2, 1, 5);
    grid->addWidget(fillButt[1], 2, 7, 1, 1, Qt::AlignBottom);
    grid->addWidget(fillData[1], 3, 7, 1, 1);

    grid->addWidget(label[2], 4, 0, 2, 2);
    grid->addWidget(table[2], 5, 2, 1, 5);
    grid->addWidget(text[2], 4, 2, 1, 5);
    grid->addWidget(fillButt[2], 4, 7, 1, 1, Qt::AlignBottom);
    grid->addWidget(fillData[2], 5, 7, 1, 1);

    grid->addWidget(label[3], 6, 0, 2, 2);
    grid->addWidget(table[3], 7, 2, 1, 5);
    grid->addWidget(text[3], 6, 2, 1, 5);
    grid->addWidget(fillButt[3], 6, 7, 1, 1, Qt::AlignBottom);
    grid->addWidget(fillData[3], 7, 7, 1, 1);

    grid->addWidget(vLine, 0, 8, 9, 1);
    grid->addWidget(clearButt, 1, 9, 1, 1);
    grid->addWidget(saveButt, 4, 9, 1, 1);
    grid->addWidget(loadButt, 5, 9, 1, 1);


    setLayout(grid);
    setFixedSize(WEIDTH, HEIGHT);
}

void MainWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(QPen(QColor(0, 100, 0)));
    p.drawLine(15,174,1140,174);
    p.drawLine(15,339,1140,339);
    p.drawLine(15,504,1140,504);
}

QDoubleSpinBox * MainWidget::createSpinBox()
{
    QDoubleSpinBox * spin = new QDoubleSpinBox();
    spin->setRange(0, 99);
    spin->setDecimals(0);
    spin->setSingleStep(1);
    spin->setSuffix(" °C");
    connect(spin, SIGNAL(valueChanged(double)), SLOT(dataChanged()));

    return spin;
}

void MainWidget::setFileName(QString fileName)
{
    this->fileName = fileName;
}

void MainWidget::saveChanges()
{
    for(int i = 0 ; i < 4 ; ++i)
        for(int j = 0 ; j < COLUMNS ; ++j)
            dayPart[i][j] = static_cast<QDoubleSpinBox *> (this->table[i]->cellWidget(0, j))->value();
    file->writeMatrix(time->hour(), time->minute(), dayPart);

    Process * proc = new Process();
    QString res = proc->runConvert();

    delete (proc);

    Dialog * dialog = new Dialog(res);
    dialog->exec();

    delete dialog;

    changedData = false;
}

void MainWidget::loadData()
{
    for(int i = 0 ; i < 4 ; ++i)
        for(int j = 0 ; j < COLUMNS ; ++j)
            dayPart[i][j] = static_cast<QDoubleSpinBox *> (this->table[i]->cellWidget(0, j))->value();
    file->writeMatrix(time->hour(), time->minute(), dayPart);

    Process * proc = new Process();
    QString res = proc->runConvert();
    res += "\n\n";
    res += proc->runLoad();

    delete proc;

    Dialog * dialog = new Dialog(res);
    dialog->exec();

    delete dialog;

    changedData = false;
}

void MainWidget::fillMorning()
{
    for(int i = 0 ; i < COLUMNS ; ++i)
        static_cast<QDoubleSpinBox *> (this->table[0]->cellWidget(0, i))->setValue(fillData[0]->value());
}

void MainWidget::fillAfternoon()
{
    for(int i = 0 ; i < COLUMNS ; ++i)
        static_cast<QDoubleSpinBox *> (this->table[1]->cellWidget(0, i))->setValue(fillData[1]->value());
}

void MainWidget::fillEvening()
{
    for(int i = 0 ; i < COLUMNS ; ++i)
        static_cast<QDoubleSpinBox *> (this->table[2]->cellWidget(0, i))->setValue(fillData[2]->value());
}

void MainWidget::fillNight()
{
    for(int i = 0 ; i < COLUMNS ; ++i)
        static_cast<QDoubleSpinBox *> (this->table[3]->cellWidget(0, i))->setValue(fillData[3]->value());
}

void MainWidget::clearTable()
{
    for(int i = 0 ; i < 4 ; ++i)
        for(int j = 0 ; j < COLUMNS ; ++j)
            static_cast<QDoubleSpinBox *> (this->table[i]->cellWidget(0, j))->setValue(0);
}

void MainWidget::dataChanged()
{
    changedData = true;
}

bool MainWidget::getChangedStatus()
{
    return changedData;
}
