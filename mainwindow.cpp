#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rzutowanie.cpp"
#include "przeksztalcenia.cpp"
#include "teksturowanie.cpp"
#include "rysowanie.cpp"
#include "symulacjaruchu.cpp"
#include "wyznaczaniefigur.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    poczatkowyX = ui->ramka->x();
    poczatkowyY = ui->ramka->y();
    wysokosc = ui->ramka->height();
    szerokosc = ui->ramka->width();

    obrazek = QImage(1550, 900, QImage::Format_RGB32);
    czarneTlo(obrazek, true);
    wczytajTekstury();

    wyznaczWierzcholki();
    wyznaczTrojkaty();
    przeksztalc();
    rzutujNa2D();
    teksturuj();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    p.drawImage(poczatkowyX, poczatkowyY, obrazek);
}

void MainWindow::on_pushButton_clicked()
{
    symulujRuch();
}
