#include "mainwindow.h"

void MainWindow::przeksztalcPlanete(int i, int j)
{
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

void MainWindow::przeksztalc()
{
    ustawJednostkowa();
    for(int i=0; i<wierzcholkiPlanet3D.size(); i++){

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
