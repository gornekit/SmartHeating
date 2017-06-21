#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog();
    Dialog(QString text);

    ~Dialog();

private:
    QString text;
    QLabel * label;
    QPushButton * okButt;
};

#endif // DIALOG_H
