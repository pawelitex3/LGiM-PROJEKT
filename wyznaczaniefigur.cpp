#include "mainwindow.h"


void MainWindow::wyznaczWierzcholki()
{
    double promien, x, y, z, xy;
    double krokSektora, krokStosu, katSektora, katStosu;
    double s, t;
    int szerokoscTekstury, wysokoscTekstury;

    for(int k=0; k<tekstury.size(); k++){
        QVector <Wierzcholek> wierzcholkiKuli;
        QVector <Wierzcholek> wierzcholkiT;

        szerokoscTekstury = tekstury[k].width();
        wysokoscTekstury = tekstury[k].height();

        if(k==0){
            promien = 190;
        }
        else if (k==1){
            promien = 10;
        }
        else if (k==2){
            promien = 19;
        }
        else if (k==3){
            promien = 20;
        }
        else if (k==4){
            promien = 13;
        }
        else if (k==5){
            promien = 55;
        }
        else if (k==6){
            promien = 45;
        }
        else if (k==7){
            promien = 30;
        }
        else if (k==8){
            promien = 30;
        }

        liczbaSektorow = 36;
        liczbaStosow = 18;

        krokSektora = 2*M_PI/liczbaSektorow;
        krokStosu = M_PI/liczbaStosow;

        for(int i=0; i <= liczbaStosow; i++){
            katStosu = M_PI/2 - i*krokStosu;

            xy = promien * cos(katStosu);
            z = promien * sin(katStosu);

            for(int j=0; j <= liczbaSektorow; j++){
                katSektora = j*krokSektora;

                x = xy*cos(katSektora);
                y = xy*sin(katSektora);

                wierzcholkiKuli.push_back(Wierzcholek(x, y, z));

                s = (double)j/liczbaSektorow;
                t = (double)i/liczbaStosow;

                wierzcholkiT.push_back(Wierzcholek(s*szerokoscTekstury, t*wysokoscTekstury, 0));


            }
        }
        wierzcholkiPlanet3D.push_back(wierzcholkiKuli);
        wierzcholkiTekstury.push_back(wierzcholkiT);
    }
}

void MainWindow::wyznaczTrojkaty()
{
    int k1, k2;
    for(int t=0; t<9; t++){
        QVector <Trojkat> trojkatyKuli;

        for(int i=0; i < liczbaStosow; i++){
            k1 = i*(liczbaSektorow+1);
            k2 = k1+liczbaSektorow+1;
            for(int j=0; j<liczbaSektorow; j++, k1++, k2++){
                if(i != 0){
                    Trojkat t(k1, k2, k1+1);
                    trojkatyKuli.push_back(t);
                }

                if(i != liczbaStosow-1){
                    Trojkat t2(k1+1, k2, k2+1);
                    trojkatyKuli.push_back(t2);
                }
            }
        }

        trojkatyPlanet.push_back(trojkatyKuli);
    }
}

void MainWindow::ustawJednostkowa()
{
    QGenericMatrix<4, 4, double> jednostkowa;
    jednostkowa.fill(0);
    for(int i=0; i<4; i++){
        jednostkowa(i, i)=1;
    }
    for(int i=0; i<9; i++){
        przeksztalcenia.push_back(jednostkowa);
    }
}
