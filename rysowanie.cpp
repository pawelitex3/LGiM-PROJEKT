#include "mainwindow.h"

void MainWindow::czarneTlo(QImage &obrazek, bool noweTlo)
{
    if(noweTlo){
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

        tlo = obrazek.copy();
    }

    else{
        unsigned char * ptr = obrazek.bits();
        unsigned char * ptr2 = tlo.bits();
        for(int i=0; i<wysokosc; i++){
            for(int j=0; j<szerokosc; j++){
                ptr[4*szerokosc*i + 4*j] = ptr2[4*szerokosc*i + 4*j];
                ptr[4*szerokosc*i + 4*j + 1] = ptr2[4*szerokosc*i + 4*j + 1];
                ptr[4*szerokosc*i + 4*j + 2] = ptr2[4*szerokosc*i + 4*j + 2];
            }
        }
    }
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
