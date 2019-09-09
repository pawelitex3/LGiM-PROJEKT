#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QColor>
#include <QRgb>
#include <QTime>
#include <QFutureSynchronizer>
#include <windows.h>
#include <QGenericMatrix>
#include <cmath>
#include <algorithm>
#include <QtConcurrent/QtConcurrent>
#include "wierzcholek.h"
#include "trojkat.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*);
    void czarneTlo(QImage & obrazek, bool noweTlo);

    void rysujOdcinek(int x0, int y0, int x1, int y1);
    void zapalPiksel(int x, int y);
    void zapalPiksel(int x, int y, int red, int green, int blue);
    void rysujBryle();
    void wyznaczWierzcholki();
    void wyznaczTrojkaty();
    void rzutujNa2D();
    void wczytajTekstury();
    void teksturuj();
    void ustawJednostkowa();
    void przeksztalc();
    void przeksztalcPlanete(int i, int j);

    void symulujRuch();

    void obracanieOX(double katObrotuX, int planeta);
    void obracanieOY(double katObrotuY, int planeta);
    void obracanieOZ(double katObrotuZ, int planeta);
    void przesuwanie(int przesuniecieX, int przesuniecieY, int przesuniecieZ, int planeta);

    double liczbaSektorow, liczbaStosow;

    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QImage obrazek, tlo;

    //QVector <Wierzcholek> wierzcholkiKuli;
    //QVector <Trojkat> trojkatyKuli;
    //QVector <Wierzcholek> zrzutowaneWierzcholkiKuli;

    QVector <QGenericMatrix<4, 4, double> > przeksztalcenia;
    QVector <QVector <Wierzcholek> > wierzcholkiPlanet2D;
    QVector <QVector <Wierzcholek> > wierzcholkiPlanet3D;
    QVector <QVector <Wierzcholek> > przeksztalconeWierzcholkiPlanet3D;
    QVector <QVector <Wierzcholek> > wierzcholkiTekstury;
    QVector <QVector <Trojkat> > trojkatyPlanet;
    QVector <QImage> tekstury;


    int szerokosc, wysokosc, poczatkowyX, poczatkowyY;

};

#endif // MAINWINDOW_H
