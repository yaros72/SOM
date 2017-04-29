//
//  constants.h
//  MonteGreen
//
//  Created by Ярослав Жумагулов on 26.10.15.
//  Copyright © 2015 Yaroslav Zhumagulov. All rights reserved.
//

#ifndef constants_h
#define constants_h
struct configuration{                   //структура конфигурации-решения-прямоугольников
    int k;                              //число прямоугольников
    double ht[500];                     //массив высот прямоугольников
    double wt[500];                     //массив ширин прямоугольников
    double ct[500];                     //массив центров прямоугольников
    double D;                           //отклонение конфигурации
};
extern volatile struct configuration bestConf;

//характеристика прямоугольников
extern volatile double wMin;            //минимальное значение ширины
extern volatile double hMin;            //минимальное значение высоты
extern volatile double hMax;            //максимальное значение высоты
extern volatile double SMin;            //минимальное значение площади
extern volatile double wMax1;           //[wMax1,wMax2]-область определения решения
extern volatile double wMax2;           //
extern volatile int kMax;               //максимальное значение количества прямоугольников
extern volatile double fullS;           //нормировка

//характеристика реальной функции Грина
extern volatile double T;               //значение текущей температуры
extern volatile double *realGreen;      //массив реальной функции Грина
extern volatile double *tau;            //массив сетки по мнимому времени
extern volatile int N;                  //количество значений функции Грина

//параметры процедур [поиска решений]-[монте-карло]
extern volatile double Dmin;            //значение минимального отклонения
extern volatile int monteStatus;        //статус монте-карло (1-да,0-нет; меняется в процессе, не задается)
extern volatile int firstPow;           //первое значение показателя в "мнимом" метрополисе (первые итерации)
extern volatile int secondPow;          //второе значение показателя в "мнимом" метрополисе
extern volatile int monteStart;         //количество "пустых" итераций до запуска монте-карло
extern volatile int monteFirst;         //количество первых итераций монте-карло
extern volatile int monteFull;          //полное количество итераций монте-карло (за один запуск)
extern volatile int fullIter;           //полное количество итераций обновлений конфигурации
extern volatile int numberResults;      //количество решений

//параметры-решения интегралов от прямоугольников (значения гипергеометрической функции)
extern volatile double **greenFuncGrid; //матрица (N)x(M) интегралов (N-количество точек по мнимому времени)
extern volatile int mGrid;              //количество столбцов матрицы
extern volatile double gridStep;        //шаг матрицы по частоте
extern volatile double gridStart;       //левая граница сетки


#endif /* constants_h */
