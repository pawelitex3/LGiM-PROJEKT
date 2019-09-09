#include "mainwindow.h"

void MainWindow::symulujRuch()
{
    int j=1;
    Wierzcholek start(0, 0, 0);
    while(1){
        czarneTlo(obrazek, false);
        przeksztalcenia.clear();
        przeksztalconeWierzcholkiPlanet3D.clear();

        QFutureSynchronizer<void> synch;

        ustawJednostkowa();

        for(int i=0; i<9; i++){
            synch.addFuture(QtConcurrent::run(this, &MainWindow::przeksztalcPlanete, i, j));

        }
        synch.waitForFinished();
        j++;
        wierzcholkiPlanet2D.clear();
        rzutujNa2D();
        //rysujBryle();
        teksturuj();
        QTime pause = QTime::currentTime().addMSecs(10);
        while(QTime::currentTime() < pause){
            QCoreApplication::processEvents(QEventLoop::AllEvents, 3);
        }
        update();
    }
}
