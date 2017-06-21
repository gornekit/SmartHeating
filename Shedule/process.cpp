#include "process.h"
#include <QVariant>

Process::Process()
{
    workingDir = "/Users/nikita/Desktop/SmartHeating/atmega32A/eeprom/";
    convert = "/usr/local/CrossPack-AVR-20131216/bin/avr-objcopy";
    convertList << "-I" << "binary" << "eeprom.txt" << "-O" << "ihex" << "eeprom.hex";
    load = "/usr/local/CrossPack-AVR//bin/avrdude";
    loadList << "-c" << "usbasp" << "-P" << "usb" << "-p" << "m32" << "-U eeprom:w:eeprom.hex:i";
}

QString Process::runConvert()
{
    QString res = "";
    QProcess * proc = new QProcess();
    proc->setWorkingDirectory(workingDir);
    proc->setProgram(convert);
    proc->setArguments(convertList);
    proc->start();
    res += "Starting program : " + proc->program() + "\nWith arguments : ";
    for(int i = 0; i < convertList.length() ; ++i)
        res += convertList[i] + " ";
    res += "\n";
    bool start = proc->waitForStarted(-1);
    bool finish = proc->waitForFinished(-1);
    QVariant startValue(start);
    QVariant finishValue(finish);
    res += "Started : " + QString(startValue.toString());
    res += "\nFinished : " + QString(finishValue.toString());
    res += proc->readAll();
    delete (proc);

    return res;
}

QString Process::runLoad()
{
    QString res = "";
    QProcess * proc = new QProcess();
    proc->setWorkingDirectory(workingDir);
    proc->setProgram(load);
    proc->setArguments(loadList);
    proc->start();
    res += "Starting program : " + proc->program() + "\nWith arguments : ";
    for(int i = 0; i < loadList.length() ; ++i)
        res += loadList[i] + " ";
    res += "\n";
    bool start = proc->waitForStarted(-1);
    bool finish = proc->waitForFinished(-1);
    QVariant startValue(start);
    QVariant finishValue(finish);
    res += "Started : " + QString(startValue.toString());
    res += "\nFinished : " + QString(finishValue.toString());
    QString output = proc->readAllStandardOutput();
    res += "\nOutput : ";
    if(output == "")
        res += "no output.";
    else
        res += output;
    QString error = proc->readAllStandardError();
    res += "\nError : ";
    if(error == "")
        res += "no error.";
    else
        res += error;

    delete (proc);

    return res;
}

Process::~Process()
{

}
