//
//  main.c
//  MonteGreen
//
//  Created by Ярослав Жумагулов on 26.10.15.
//  Copyright © 2015 Yaroslav Zhumagulov. All rights reserved.
//
#include "main.h"

int main(int argc, const char *argv[]) {
    clock_t begin, end;
    double time_spent;
    initRandom();                               //инициализация счетчика случайных чисел
    begin = clock();                            //запуск счетчика времени



    int kAll = 0, point = 0, R = 0, numThreads;
    double *ht, *wt, *ct;

    printf("Loading input files...\n");
    readConstants();                            //считываение констант
    realGreen = readRealGreen();                  //считывание функции Грина
    tau = readTau();                              //считывание сетки по минимому времени
    greenFuncGrid = readGreenGrid();              //считывание сетки
    printf("Loading finished\n");


    ht = (double *) malloc(numberResults * kMax * sizeof(double));
    wt = (double *) malloc(numberResults * kMax * sizeof(double));
    ct = (double *) malloc(numberResults * kMax * sizeof(double));
    numThreads = omp_get_num_threads();                        //количество потоков


#pragma omp parallel for shared(R,realGreen,tau,greenFuncGrid,N,kMax,hMin,wMin,wMax1,wMax2,hMax,gridStep,gridStart,SMin,fullS,ht,wt,ct,kAll,point,numberResults,T) private(conf,bestConf)
    for (int j = 0; j < numberResults; j++) {                            //цикл генерации решений
        conf = setConf();                                            //генерация начальной конфигурации
        numThreads = omp_get_num_threads();                        //количество потоков
        kStart = conf.k;
        conf.D = deviation(conf);                                //расчет начального отклонения
        for (int i = 0; i < fullIter; i++) {
            conf = nextUpdate(conf);    //цикл Монте-Карло (обновлений)
        }

#pragma omp critical
        printf("N=%d D=%f k=%d S=%f\n", R++, conf.D, conf.k,
               area(conf.wt, conf.ht, conf.k));//вывод номера решения и его отклонения
#pragma omp critical

        for (int ii = point; ii < (point + conf.k); ii++) {              //запись решения
            ht[ii] = conf.ht[ii - point];
            wt[ii] = conf.wt[ii - point];
            ct[ii] = conf.ct[ii - point];
        }
        point += conf.k;
        kAll += conf.k;

    }
    double S = area(wt, ht, kAll);
    for (int i = 0; i < kAll; i++) ht[i] *= fullS / S;                  //нормировка решений
    end = clock();
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;        //подсчет времени генерации решений
    printf("t=%f\n", time_spent / numThreads);                                //вывод времени генерации решений
    saveResults(ht, wt, ct, kAll);                                 //сохранение результата
    return 0;
}
