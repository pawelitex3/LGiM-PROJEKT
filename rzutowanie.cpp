#include "mainwindow.h"

void MainWindow::rzutujNa2D()
{

    for(int j=0; j<wierzcholkiPlanet3D.size(); j++){
        QVector <Wierzcholek> wierzcholkiKuli = wierzcholkiPlanet3D[j];
        QVector <Wierzcholek> zrzutowaneWierzcholkiKuli;
        QVector <Wierzcholek> przeksztalconeWierzcholki;
        QGenericMatrix<4, 4, double> macierzp = przeksztalcenia[j];
        for(int i=0; i<wierzcholkiKuli.size(); i++){
            Wierzcholek w;
            w.x = wierzcholkiKuli[i].x*macierzp(0, 0) + wierzcholkiKuli[i].y*macierzp(0, 1) + wierzcholkiKuli[i].z*macierzp(0, 2) + macierzp(0, 3);
            w.y = wierzcholkiKuli[i].x*macierzp(1, 0) + wierzcholkiKuli[i].y*macierzp(1, 1) + wierzcholkiKuli[i].z*macierzp(1, 2) + macierzp(1, 3);
            w.z = wierzcholkiKuli[i].x*macierzp(2, 0) + wierzcholkiKuli[i].y*macierzp(2, 1) + wierzcholkiKuli[i].z*macierzp(2, 2) + macierzp(2, 3);
            przeksztalconeWierzcholki.push_back(w);
        }

        przeksztalconeWierzcholkiPlanet3D.push_back(przeksztalconeWierzcholki);

        for(int i=0; i<wierzcholkiKuli.size(); i++){
            double x, y;

            x = -1500*przeksztalconeWierzcholki[i].x/(przeksztalconeWierzcholki[i].z-1500);
            y = -1500*przeksztalconeWierzcholki[i].y/(przeksztalconeWierzcholki[i].z-1500);
            x+=szerokosc/2;
            y+=wysokosc/2;

            zrzutowaneWierzcholkiKuli.push_back(Wierzcholek(x, y, 0.0));
        }
        wierzcholkiPlanet2D.push_back(zrzutowaneWierzcholkiKuli);
    }
}
