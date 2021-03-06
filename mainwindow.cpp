#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

double primerNum;
bool noEscibrenumero = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->cero,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->uno,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->dos,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->tres,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->cuatro,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->cinco,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->seis,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->siete,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->ocho,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->nueve,SIGNAL(released()),this,SLOT(digit_pressed()));


    connect(ui->plusmin,SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui->porcentaje,SIGNAL(released()),this,SLOT(unary_operation_pressed()));

    connect(ui->suma,SIGNAL(released()),this,SLOT(binario_operation_pressed()));
    connect(ui->resta,SIGNAL(released()),this,SLOT(binario_operation_pressed()));
    connect(ui->multiplicacion,SIGNAL(released()),this,SLOT(binario_operation_pressed()));
    connect(ui->division,SIGNAL(released()),this,SLOT(binario_operation_pressed()));

    ui->suma->setCheckable(true);
    ui->resta->setCheckable(true);
    ui->multiplicacion->setCheckable(true);
    ui->division->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::digit_pressed()
{
 QPushButton * button = (QPushButton*)sender();

 double labelNumber;
 QString newlabel;
 if ((ui->suma->isChecked() ||ui->resta->isChecked() || ui->multiplicacion->isChecked() || ui->division->isChecked()) && (!noEscibrenumero) )
 {
     labelNumber = button->text().toDouble();
      noEscibrenumero = true ;
      newlabel = QString::number(labelNumber,'g',10);
      ui->lcd->display(newlabel);
 }
 else
 {
     if (ui->label->text().contains('.') && button->text() ==  "0")
     {
         newlabel = ui->label->text() + button->text();
         ui->lcd->display(newlabel);
     }
     else
     {
         labelNumber = (ui->label->text() + button->text()).toDouble();
         newlabel = QString::number(labelNumber,'g',10); // agregando la cantidad de decimales que quiero que muestre
         ui->lcd->display(newlabel);
     }
 }
 ui->label->setText(newlabel);
}


void MainWindow::on_punto_released()
{
    ui->label->setText(ui->label->text() + ".");
    ui->lcd->display(ui->label->text());
}

void MainWindow::unary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();
    double labelNumber;
    QString newlabel;
    if (button->text() == "+/-")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * -1;
        newlabel = QString::number(labelNumber,'g',10);
        ui->label->setText(newlabel);
        ui->lcd->display(newlabel);

    }

    if (button->text() == "%")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01;
        newlabel = QString::number(labelNumber,'g',10);
        ui->label->setText(newlabel);
        ui->lcd->display(newlabel);

    }
}

void MainWindow::on_clear_released()
{
    ui->suma->setChecked(false);
    ui->resta->setChecked(false);
    ui->multiplicacion->setChecked(false);
    ui->division->setChecked(false);

    noEscibrenumero = false;

    ui->label->setText("0");
    double labelnumb;
    QString newlbl;
    labelnumb = 0;
    newlbl = QString::number(labelnumb);
    ui->lcd->display(newlbl);
}

void MainWindow::on_igual_released()
{
    double labelNumber, segundoNum;
    QString newlabel;

    segundoNum = ui->label->text().toDouble();

    if (ui->suma->isChecked())
    {
        labelNumber = primerNum + segundoNum;
        newlabel = QString::number(labelNumber,'g',10);
        ui->label->setText(newlabel);
        ui->lcd->display(newlabel);
        ui->suma->setChecked(false);
        QMessageBox msj;
        msj.setText("Operacion Realizada");
        msj.exec();
    }
    else if (ui->resta->isChecked())
    {
        labelNumber = primerNum - segundoNum;
        newlabel = QString::number(labelNumber,'g',10);
        ui->label->setText(newlabel);
        ui->lcd->display(newlabel);
        ui->resta->setChecked(false);
        QMessageBox msj;
        msj.setText("Operacion Realizada");
        msj.exec();
    }
    else if (ui->multiplicacion->isChecked())
    {
        labelNumber = primerNum * segundoNum;
        newlabel = QString::number(labelNumber,'g',10);
        ui->label->setText(newlabel);
        ui->lcd->display(newlabel);
        ui->multiplicacion->setChecked(false);
        QMessageBox msj;
        msj.setText("Operacion Realizada");
        msj.exec();
    }
    else if (ui->division->isChecked())
    {
        labelNumber = primerNum / segundoNum;
        newlabel = QString::number(labelNumber,'g',10);
        ui->label->setText(newlabel);
        ui->lcd->display(newlabel);
        ui->division->setChecked(false);
        QMessageBox msj;
        msj.setText("Operacion Realizada");
        msj.exec();
    }

    noEscibrenumero = false ;

}

void MainWindow::binario_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();
    primerNum = ui->label->text().toDouble();
    button->setChecked(true);


}

void MainWindow::on_LCD_overflow()
{
  QPushButton * button = (QPushButton*) sender();
  primerNum = ui->label->text().toDouble();
  QString lol;
  lol = primerNum;
  ui->lcd->display(lol);

}
