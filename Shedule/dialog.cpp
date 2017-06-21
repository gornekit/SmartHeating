#include "dialog.h"
#include <QVBoxLayout>
#include <QPalette>

Dialog::Dialog()
    :QDialog()
{

}

Dialog::Dialog(QString text)
    :QDialog()
{
    this->text = text;
    label = new QLabel(text);

    QPalette pal;
    pal.setColor(this->backgroundRole(), QColor(250, 255, 250));

    okButt = new QPushButton("OK");
    connect(okButt, SIGNAL(clicked()), SLOT(close()));

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(okButt);
    setLayout(layout);
    setPalette(pal);
}

Dialog::~Dialog()
{

}
