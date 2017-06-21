#include "file.h"
#include "QDebug"
#include <QDataStream>

File::File() :
    QFile()
{
}

File::File(QString name) :
    QFile(name)
{
    this->name = name;
}

void File::writeMatrix(uint8_t hour, uint8_t min, uint8_t data[4][COLUMNS])
{
    QDataStream stream(this);
    if(!open(QIODevice::WriteOnly))
    {
        qDebug() << "Can't open file for writing";
    }
    stream << hour;
    stream << min;
    for(int i = 0 ; i < 4 ; ++i)
    {
        for(int j = 0 ; j < COLUMNS ; ++j)
        {
            stream << data[i][j];
            //qDebug() << data[i][j];
        }
    }
    close();
}
