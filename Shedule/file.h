#ifndef FILE_H
#define FILE_H

#include <QFile>

//#define COLUMNS 7

class File : public QFile
{

public:
    static const int COLUMNS = 7;

    File();
    File(QString name);

    void writeMatrix(uint8_t hour, uint8_t min, uint8_t data[4][COLUMNS]);

private:
    QString name;

};

#endif // FILE_H
