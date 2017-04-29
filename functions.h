//
//  functions.h
//  MonteGreen
//
//  Created by Ярослав Жумагулов on 27.10.15.
//  Copyright © 2015 Yaroslav Zhumagulov. All rights reserved.
//

#ifndef functions_h
#define functions_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"

double getRandom(void);                     //функция-генератор равномерно распределенных на отрезке [0,1] случайных чисел
void initRandom(void);                      //функция-инициализация счетчика генератора случайных чисел
double sum(double *arr,int n);              //сумма массива размерности [1 х n]
double area(double *wt,double *ht,int n);   //площадь n прямоугольников (массивы wt и ht размерности [1 x n])
double **readGreenGrid(void);               //функция считывания из файла сетки
double *readRealGreen(void);                //функция считывания из файла функции Грина
double *readTau(void);                      //функция считывания из файла сетки по мнимому времени
double getOptim(double D0,double D1,double D2,double param);    //функция поиска оптимального значения изменения параметра
void saveResults(double *ht,double *wt, double *ct, int k);     //функция сохранения результатов
void readConstants(void);                                       //функция считывания из файла констант
int findMinimumIndx(double *arr, int n);                          //функция поиска индекса минимального значения в массиве [1 x 4]
#endif /* functions_h */
