#ifndef PROCESS_H
#define PROCESS_H

#include <QProcess>
#include <QStringList>

class Process
{
public:
    explicit Process();
    QString runConvert();
    QString runLoad();

    ~Process();

private:
    QString workingDir;
    QString convert;
    QString load;
    QStringList convertList;
    QStringList loadList;
};

#endif // PROCESS_H
