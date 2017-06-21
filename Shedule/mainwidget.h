#ifndef MAINWIDGET
#define MAINWIDGET

#include <QWidget>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QTableWidget>
#include <stdint.h>
#include <QString>
#include <QTime>
#include <QLabel>
#include <QImage>
#include "dialog.h"

#include "file.h"
#include "process.h"

//#define COLUMNS 7

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    void setFileName(QString fileName);
    bool getChangedStatus();

private:
    static const int COLUMNS = 7;
    const int WEIDTH = 1250;
    const int HEIGHT = 680;
    const float picture = 0.12;
    const float box = 0.09;
    const float butt = 0.06;

    QLabel * label[4];
    QLabel * text[4];
    QTableWidget * table[4];
    QPushButton * fillButt[4];
    QDoubleSpinBox * fillData[4];
    QImage * image[4];

    QPushButton * clearButt;
    QPushButton * saveButt;
    QPushButton * loadButt;

    uint8_t dayPart[4][COLUMNS];

    bool changedData;

    QDoubleSpinBox * createSpinBox();
    QString fileName;
    File * file;
    QTime * time;

protected:
    void paintEvent(QPaintEvent *);

public slots:
    void fillMorning();
    void fillAfternoon();
    void fillEvening();
    void fillNight();
    void clearTable();
    void saveChanges();
    void loadData();
    void dataChanged();
};

#endif // MAINWIDGET
