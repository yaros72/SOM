//
//  setConfiguration.c
//  MonteGreen
//
//  Created by Ярослав Жумагулов on 27.10.15.
//  Copyright © 2015 Yaroslav Zhumagulov. All rights reserved.
//


#include "setConfiguration.h"

//функция генерации случайной конфигурации в виде структуры configuration
struct configuration setConf(void){
    struct configuration conf;
    conf.k=(int)(getRandom()*(kMax/2)+(kMax/4));                       //генерация числа прямоугольников в конфигурации
    for (int i=0;i<conf.k;i++){                                 //цикл генерации параметров прямоугольников
        conf.ht[i]=hMin+(hMax-hMin)*getRandom();
        conf.wt[i]=wMin+getRandom()*(wMax2-wMax1-wMin);
        conf.ct[i]=wMax1+(wMax2-wMax1-conf.wt[i])*getRandom()+conf.wt[i]/2.0;
    }
    double A=area(conf.wt, conf.ht, conf.k);
    for (int i=0;i<conf.k;i++) conf.ht[i]*=fullS/A;             //нормировка прямоугольников
    for (int i=0;i<conf.k;i++) if ((SMin>(conf.ht[i]*conf.wt[i])&&(hMin<conf.ht[i]))) conf=setConf();    //проверка краевых условий
    return conf;
}

