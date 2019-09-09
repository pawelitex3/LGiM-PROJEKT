#include "mainwindow.h"

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

                dlugosc = sqrt(S.x*S.x + S.y*S.y + S.z*S.z);
                S.x/=dlugosc;
                S.y/=dlugosc;
                S.z/=dlugosc;

                double iloczyn = N.x*S.x + N.y*S.y + N.z*S.z;

                if(iloczyn >=0) iloczyn=0;
                else iloczyn*=-1;

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
                                x = 0;
                            }
                            if(y<=0){
                                y = 0;
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
