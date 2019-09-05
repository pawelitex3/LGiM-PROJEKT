#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    czarneTlo(obrazek);
    wczytajTekstury();

    wyznaczWierzcholki();
    wyznaczTrojkaty();
    przeksztalc();
    rzutujNa2D();
    rysujBryle();
    teksturuj();


    //symulujRuch();


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

void MainWindow::czarneTlo(QImage &obrazek)
{
    unsigned char * ptr = obrazek.bits();

    for(int i=0; i<wysokosc; i++){
        for(int j=0; j<szerokosc; j++){
            ptr[4*szerokosc*i + 4*j] = 0;
            ptr[4*szerokosc*i + 4*j + 1] = 0;
            ptr[4*szerokosc*i + 4*j + 2] = 0;
        }
    }

    for(int s=0; s<500; s++){
        int i = qrand()%(wysokosc-10);
        int j = qrand()%(szerokosc-10);
        if(s%10==0){
            for(int t=0; t<4; t++){
                for(int p=0; p<4; p++){
                    ptr[4*szerokosc*(i+t) + 4*(j+p)] = 255;
                    ptr[4*szerokosc*(i+t) + 4*(j+p) + 1] = 255;
                    ptr[4*szerokosc*(i+t) + 4*(j+p) + 2] = 255;
                }
            }
        }
        else{
            ptr[4*szerokosc*i + 4*j] = 255;
            ptr[4*szerokosc*i + 4*j + 1] = 255;
            ptr[4*szerokosc*i + 4*j + 2] = 255;
        }
    }

}

void MainWindow::symulujRuch()
{
    int j=1;
    Wierzcholek start(0, 0, 0);
    while(1){
        czarneTlo(obrazek);
        przeksztalcenia.clear();
        przeksztalconeWierzcholkiPlanet3D.clear();
        for(int i=0; i<9; i++){
            ustawJednostkowa();
            obracanieOX(90, i);
            if(i==0){
                obracanieOY(2*j, i);
                obracanieOZ(1*j, i);
            }
            else if (i == 1){
                obracanieOY(0.1*j, i);
                przesuwanie(220, 0, 0, i);
                obracanieOY(10*j, i);
                obracanieOX(0.005*j, i);
            }
            else if(i==2){
                obracanieOY(0.02*j, i);
                przesuwanie(259, 0, 0, i);
                obracanieOY(5*j, i);
                obracanieOX(0.005*j, i);
            }
            else if(i==3){
                obracanieOY(5*j, i);
                obracanieOZ(2*j, i);
                przesuwanie(308, 0, 0, i);
                obracanieOY(3*j, i);
                obracanieOX(0.005*j, i);
            }
            else if(i==4){
                obracanieOY(5*j, i);
                przesuwanie(351, 0, 0, i);
                obracanieOY(1.5*j, i);
                obracanieOX(0.005*j, i);
            }
            else if(i==5){
                obracanieOY(2*j, i);
                przesuwanie(429, 0, 0, i);
                obracanieOY(0.2*j, i);
                obracanieOX(0.005*j, i);
            }
            else if(i==6){
                obracanieOY(2*j, i);
                przesuwanie(539, 0, 0, i);
                obracanieOY(0.1*j, i);
                obracanieOX(0.005*j, i);
            }
            else if(i==7){
                obracanieOY(3.5*j, i);
                przesuwanie(629, 0, 0, i);
                obracanieOY(0.05*j, i);
                obracanieOX(0.005*j, i);
            }
            else if(i==8){
                obracanieOY(3*j, i);
                przesuwanie(709, 0, 0, i);
                obracanieOY(0.025*j, i);
                obracanieOX(0.005*j, i);
            }




            //j%=360;
            //obracanieOY(3, i);
        }
        j++;
        //obracanieOY(3, 0);
        wierzcholkiPlanet2D.clear();
        rzutujNa2D();
        rysujBryle();
        teksturuj();
        QTime pause = QTime::currentTime().addMSecs(33);
        while(QTime::currentTime() < pause){
            QCoreApplication::processEvents(QEventLoop::AllEvents, 3);
        }
        update();
    }
}

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
    /*
    promien = 200;
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

            Wierzcholek w(x, y, z);

            wierzcholkiKuli.push_back(w);
        }
    }
    */
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

    /*
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
    */
}

void MainWindow::rysujBryle()
{

    for(int j=0; j<trojkatyPlanet.size(); j++){
        ui->label->setNum(wierzcholkiPlanet3D.size());
        QVector <Trojkat> trojkatyKuli = trojkatyPlanet[j];
        //QVector <Wierzcholek> zrzutowaneWierzcholkiKuli = wierzcholkiPlanet2D[j];
/*
        for(int i=0; i<trojkatyKuli.size(); i++){
            Wierzcholek p1(zrzutowaneWierzcholkiKuli[trojkatyKuli[i].wierzcholki[0]]), p2(zrzutowaneWierzcholkiKuli[trojkatyKuli[i].wierzcholki[1]]), p3(zrzutowaneWierzcholkiKuli[trojkatyKuli[i].wierzcholki[2]]);

            double det = (p2.x-p1.x)*(p3.y-p1.y) - (p2.y-p1.y)*(p3.x-p1.x);
            if(det >=0){
                rysujOdcinek((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);
                rysujOdcinek((int)p1.x, (int)p1.y, (int)p3.x, (int)p3.y);
                rysujOdcinek((int)p3.x, (int)p3.y, (int)p2.x, (int)p2.y);
            }

        }
        */
    }
}

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
        //wierzcholkiPlanet3D[j] = przeksztalconeWierzcholki;

        for(int i=0; i<wierzcholkiKuli.size(); i++){



            double x, y;
            //x = 600*wierzcholkiKuli[i].x/(wierzcholkiKuli[i].z+600);
            //y = 600*wierzcholkiKuli[i].y/(wierzcholkiKuli[i].z+600);

            x = -1500*przeksztalconeWierzcholki[i].x/(przeksztalconeWierzcholki[i].z-1500);
            y = -1500*przeksztalconeWierzcholki[i].y/(przeksztalconeWierzcholki[i].z-1500);
            x+=szerokosc/2;
            y+=wysokosc/2;
/*

            if(j==0){
                x+=szerokosc/2;
                y+=wysokosc/2;
            }
            else if(j==1){
                x+=szerokosc/2+220;
                y+=wysokosc/2;
            }
            else if(j==2){
                x+=szerokosc/2+259;
                y+=wysokosc/2;
            }
            else if(j==3){
                x+=szerokosc/2+308;
                y+=wysokosc/2;
            }
            else if(j==4){
                x+=szerokosc/2+351;
                y+=wysokosc/2;
            }
            else if(j==5){
                x+=szerokosc/2+429;
                y+=wysokosc/2;
            }
            else if(j==6){
                x+=szerokosc/2+539;
                y+=wysokosc/2;
            }
            else if(j==7){
                x+=szerokosc/2+629;
                y+=wysokosc/2;
            }
            else if(j==8){
                x+=szerokosc/2+709;
                y+=wysokosc/2;
            }
*/

            zrzutowaneWierzcholkiKuli.push_back(Wierzcholek(x, y, 0.0));
        }
        wierzcholkiPlanet2D.push_back(zrzutowaneWierzcholkiKuli);
    }



/*
    for(int i=0; i<8; i++){
        rzutowanie[i][0] = d*tmp[i][0]/(tmp[i][2]+d);
        rzutowanie[i][1] = d*tmp[i][1]/(tmp[i][2]+d);
        rzutowanie[i][0] += szerokosc/2;
        rzutowanie[i][1] += wysokosc/2;
       }
       */
}

void MainWindow::obracanieOX(double katObrotuX, int planeta)
{
    QGenericMatrix<4, 4, double> obrot;
    obrot.fill(0);
    for(int i=0; i<4; i++){
        obrot(i, i)=1;
    }

    double alfa = katObrotuX;
    alfa = alfa*M_PI/180.0;
    obrot(1, 1) = cos(alfa);
    obrot(1, 2) = -sin(alfa);
    obrot(2, 1) = sin(alfa);
    obrot(2, 2) = cos(alfa);

    przeksztalcenia[planeta] = obrot*przeksztalcenia[planeta];

    //double wynik[4][4];


/*
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            wynik[i][j] = obroc[0][i]*przeksztalcenie[j][0] + obroc[1][i]*przeksztalcenie[j][1] + obroc[2][i]*przeksztalcenie[j][2] + obroc[3][i]*przeksztalcenie[j][3];
        }
    }

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            przeksztalcenie[i][j] = wynik[i][j];
        }
    }
    */
}

void MainWindow::obracanieOY(double katObrotuY, int planeta)
{
    QGenericMatrix<4, 4, double> obrot;
    obrot.fill(0);
    for(int i=0; i<4; i++){
        obrot(i, i)=1;
    }


    double alfa = katObrotuY;
    alfa = alfa*M_PI/180.0;
    obrot(0, 0) = cos(alfa);
    obrot(0, 2) = sin(alfa);
    obrot(2, 0) = -sin(alfa);
    obrot(2, 2) = cos(alfa);

    przeksztalcenia[planeta] = obrot*przeksztalcenia[planeta];

   // double wynik[4][4];
/*
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            wynik[i][j] = obroc[0][i]*przeksztalcenie[j][0] + obroc[1][i]*przeksztalcenie[j][1] + obroc[2][i]*przeksztalcenie[j][2] + obroc[3][i]*przeksztalcenie[j][3];
        }
    }

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            przeksztalcenie[i][j] = wynik[i][j];
        }
    }
    */
}

void MainWindow::obracanieOZ(double katObrotuZ, int planeta)
{
    QGenericMatrix<4, 4, double> obrot;
    obrot.fill(0);
    for(int i=0; i<4; i++){
        obrot(i, i)=1;
    }

    double alfa = katObrotuZ;
    alfa = alfa*M_PI/180.0;
    obrot(0, 0) = cos(alfa);
    obrot(0, 1) = -sin(alfa);
    obrot(1, 0) = sin(alfa);
    obrot(1, 1) = cos(alfa);

    przeksztalcenia[planeta] =  obrot*przeksztalcenia[planeta];

/*
    double wynik[4][4];

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            wynik[i][j] = obroc[0][i]*przeksztalcenie[j][0] + obroc[1][i]*przeksztalcenie[j][1] + obroc[2][i]*przeksztalcenie[j][2] + obroc[3][i]*przeksztalcenie[j][3];
        }
    }

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            przeksztalcenie[i][j] = wynik[i][j];
        }
    }
    */
}

void MainWindow::przesuwanie(int przesuniecieX, int przesuniecieY, int przesuniecieZ, int planeta)
{
    QGenericMatrix<4, 4, double> przesuniecie;
    przesuniecie.fill(0);
    for(int i=0; i<4; i++){
        przesuniecie(i, i)=1;
    }
    przesuniecie(0, 3) = przesuniecieX;
    przesuniecie(1, 3) = przesuniecieY;
    przesuniecie(2, 3) = przesuniecieZ;

    przeksztalcenia[planeta] = przesuniecie*przeksztalcenia[planeta];
}


void MainWindow::rysujOdcinek(int x0, int y0, int x1, int y1)
{
    double a, b, x, y;

            a = static_cast<double>(y1-y0)/static_cast<double>(x1-x0);
            b = y1 - a*x1;

            if(x1 != x0){
                if(x1 < x0){
                    for(x=x0; x>x1; x--){
                        y = (a*x) + b;
                        zapalPiksel(x, y);
                    }
                }
                else{
                    for(x=x0; x<x1; x++){
                        y = (a*x) + b;
                        zapalPiksel(x, y);
                    }
                }
                if(y1 < y0){
                    for(y=y0; y>y1; y--){
                        x = static_cast<double>(y-b)/a;
                        zapalPiksel(x, y);
                    }
                }
                else{
                    for(y=y0; y<y1; y++){
                        x = static_cast<double>(y-b)/a;
                        zapalPiksel(x, y);
                    }
                }

            }
            else{
                if(y1 < y0){
                    for(y0; y0>y1; y0--){
                        zapalPiksel(x0, y0);
                    }
                }
                else{


                    for(y0; y0<y1; y0++){
                        zapalPiksel(x0, y0);
                    }
                }
            }
}

void MainWindow::zapalPiksel(int x, int y)
{
    unsigned char * ptr = obrazek.bits();

    if(x>=0 && x<szerokosc && y>=0 && y<wysokosc){
        ptr[4*szerokosc*y + 4*x] = 255;
        ptr[4*szerokosc*y + 4*x + 1] = 255;
        ptr[4*szerokosc*y + 4*x + 2] = 255;
    }
}

void MainWindow::zapalPiksel(int x, int y, int r, int g, int b)
{
    unsigned char * ptr = obrazek.bits();

    if(x>=0 && x<szerokosc && y>=0 && y<wysokosc){
        ptr[4*szerokosc*y + 4*x] = b;
        ptr[4*szerokosc*y + 4*x + 1] = g;
        ptr[4*szerokosc*y + 4*x + 2] = r;
    }
}

void MainWindow::wczytajTekstury()
{
    tekstury.push_back(QImage(":/new/prefix1/slonce.jpg"));
    tekstury.push_back(QImage(":/new/prefix1/merkury.jpg"));
    tekstury.push_back(QImage(":/new/prefix1/wenus.jpg"));
    tekstury.push_back(QImage(":/new/prefix1/ziemia.jpg"));
    tekstury.push_back(QImage(":/new/prefix1/mars.jpg"));
    tekstury.push_back(QImage(":/new/prefix1/jowisz.jpg"));
    tekstury.push_back(QImage(":/new/prefix1/saturn.jpg"));
    tekstury.push_back(QImage(":/new/prefix1/uran.jpg"));
    tekstury.push_back(QImage(":/new/prefix1/neptun.jpg"));
}

void MainWindow::teksturuj()
{
    QVector <Wierzcholek> pary;
    for(int i=0; i<tekstury.size(); i++){
        pary.push_back(Wierzcholek(przeksztalconeWierzcholkiPlanet3D[i][0].z, i, 0));
    }

    for(int i=0; i<pary.size(); i++){
        for(int j=i+1; j<pary.size(); j++){
            if(pary[i].x > pary[j].x) std::swap(pary[i], pary[j]);
        }
    }

    for(int p=0; p<tekstury.size(); p++){
        int i = (int) pary[p].y;
        for(int j=0; j<trojkatyPlanet[i].size(); j++){
            double minX, minY, maxX, maxY;
            Trojkat t(trojkatyPlanet[i][j]);
            Wierzcholek p0(wierzcholkiPlanet2D[i][t.wierzcholki[0]]), p1(wierzcholkiPlanet2D[i][t.wierzcholki[1]]), p2(wierzcholkiPlanet2D[i][t.wierzcholki[2]]);
            Wierzcholek p3d0(przeksztalconeWierzcholkiPlanet3D[i][t.wierzcholki[0]]), p3d1(przeksztalconeWierzcholkiPlanet3D[i][t.wierzcholki[1]]), p3d2(przeksztalconeWierzcholkiPlanet3D[i][t.wierzcholki[2]]);
            Wierzcholek pt0(wierzcholkiTekstury[i][t.wierzcholki[0]]), pt1(wierzcholkiTekstury[i][t.wierzcholki[1]]), pt2(wierzcholkiTekstury[i][t.wierzcholki[2]]);

            minX = std::min(p0.x, std::min(p1.x, p2.x));
            minY = std::min(p0.y, std::min(p1.y, p2.y));

            maxX = std::max(p0.x, std::max(p1.x, p2.x));
            maxY = std::max(p0.y, std::max(p1.y, p2.y));

            double u, v, w, mianownik;

            double det = (p1.x-p0.x)*(p2.y-p0.y) - (p1.y-p0.y)*(p2.x-p0.x);

            mianownik = ((p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x));
            if(det >=0){

                Wierzcholek A(p3d1.x-p3d0.x, p3d1.y-p3d0.y, p3d1.z-p3d0.z), B(p3d2.x-p3d0.x, p3d2.y-p3d0.y, p3d2.z-p3d0.z);
                Wierzcholek N(A.y*B.z-A.z*B.y, A.z*B.x-A.x*B.z, A.x*B.y-A.y*B.x);

                double dlugosc = sqrt(N.x*N.x + N.y*N.y + N.z*N.z);
                N.x/=dlugosc;
                N.y/=dlugosc;
                N.z/=dlugosc;

                Wierzcholek S;
                S.x = (p3d1.x+p3d2.x+p3d0.x)/3;
                S.y = (p3d1.y+p3d2.y+p3d0.y)/3;
                S.z = (p3d1.z+p3d2.z+p3d0.z)/3;
                /*
                if(i==1){
                    //S.x = 308;
                    //S.x = (p3d1.x+p3d2.x+p3d0.x)/3-220;
                    //S.y = (p3d1.y+p3d2.y+p3d0.y)/3-220;
                    //S.z = (p3d1.z+p3d2.z+p3d0.z)/3-220;


                }
                else if(i==2){
                    S.x = 259;
                }
                else if(i==3){
                    S.x = 308;

                }
                else if(i==4){
                    S.x = 351;
                }
                else if(i==5){
                    S.x = 429;
                }
                else if(i==6){
                    S.x = 539;
                }
                else if(i==7){
                    S.x = 629;
                }
                else if(i==8){
                    S.x = 709;
                }
*/
                //Wierzcholek S(szerokosc/2, 0, 0);
                dlugosc = sqrt(S.x*S.x + S.y*S.y + S.z*S.z);
                S.x/=dlugosc;
                S.y/=dlugosc;
                S.z/=dlugosc;

                double iloczyn = N.x*S.x + N.y*S.y + N.z*S.z;
                ui->label->setNum(p1.z);
                ui->label_4->setNum(p2.x-p0.x);
                ui->label_2->setNum(p1.y-p0.y);
                ui->label_3->setNum(p2.y-p0.y);
                ui->label_5->setNum(p1.z-p0.z);
                ui->label_6->setNum(p2.z-p0.z);

                if(iloczyn >=0) iloczyn=0;
                else iloczyn*=-1;
                ui->label->setNum(iloczyn);

                for(int k=minX; k<=maxX; k++){
                    for(int l=minY; l<=maxY; l++){
                        v = ((k-p0.x)*(p2.y-p0.y)-(l-p0.y)*(p2.x-p0.x))/mianownik;
                        w = ((p1.x-p0.x)*(l-p0.y)-(p1.y-p0.y)*(k-p0.x))/mianownik;
                        u = 1-v-w;

                        if(u>=0 && v>=0 && w>=0 && u<=1 && v<=1 && w<=1){
                            int r, g, b;
                            double x, y;
                            x = u*pt0.x + v*pt1.x + w*pt2.x;
                            y = u*pt0.y + v*pt1.y + w*pt2.y;

                            if(x>=2048){
                                x = 2047;
                            }
                            if(y>=1024){
                                y = 1023;
                            }
                            if(x<=0){
                                x = 100;
                            }
                            if(y<=0){
                                y = 100;
                            }

                            QColor color = tekstury[i].pixel((int)x, (int)y);
                            r = color.red();
                            g = color.green();
                            b = color.blue();

                            if(i!=0){
                                zapalPiksel(k, l, std::max(r*iloczyn, r*0.1), std::max(g*iloczyn, g*0.1), std::max(b*iloczyn, b*0.1));
                            }
                            else{
                                zapalPiksel(k, l, r, g, b);
                            }



                        }

                    }
                }
            }


        }


    }
}

void MainWindow::ustawJednostkowa()
{
    QGenericMatrix<4, 4, double> jednostkowa;
    jednostkowa.fill(0);
    for(int i=0; i<4; i++){
        jednostkowa(i, i)=1;
    }
    przeksztalcenia.push_back(jednostkowa);
}

void MainWindow::przeksztalc()
{
    for(int i=0; i<wierzcholkiPlanet3D.size(); i++){
        ustawJednostkowa();
        obracanieOX(90, i);

        if(i==1){
            przesuwanie(220, 0, 0, i);
        }
        else if(i==2){
            przesuwanie(259, 0, 0, i);
        }
        else if(i==3){
            przesuwanie(308, 0, 0, i);
        }
        else if(i==4){
            przesuwanie(351, 0, 0, i);
        }
        else if(i==5){
            przesuwanie(429, 0, 0, i);
        }
        else if(i==6){
            przesuwanie(539, 0, 0, i);
        }
        else if(i==7){
            przesuwanie(629, 0, 0, i);
        }
        else if(i==8){
            przesuwanie(709, 0, 0, i);
        }

    }
}

void MainWindow::on_pushButton_clicked()
{
    symulujRuch();
}
