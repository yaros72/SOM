//
//  functions.c
//  MonteGreen
//
//  Created by Ярослав Жумагулов on 27.10.15.
//  Copyright © 2015 Yaroslav Zhumagulov. All rights reserved.
//

#include "functions.h"

//функция-инициализация счетчика генератора случайных чисел
void initRandom(void) { srand((unsigned int)time(NULL)); }

//функция-генератор равномерно распределенных на отрезке [0,1] случайных чисел
double getRandom(void){
    double u;
	u = rand() % 1000000;
	u = u / 1000000;
    return u;
}
//сумма массива размерности [1 х n]
double sum(double *arr,int n){
    double sum=0;
    for (int i=0;i<n;i++) sum+=arr[i];
    return sum;
}
//площадь n прямоугольников (массивы wt и ht размерности [1 x n])
double area(double *wt,double *ht,int n){
    double area=0;
    for (int i=0; i<n; i++) area+=wt[i]*ht[i];
    return area;
}

//функция считывания из файла сетки
double **readGreenGrid(void){
    double **matrix=malloc(N*sizeof(double*));
    for (int i=0; i<N; i++) matrix[i]=malloc(mGrid*sizeof(double));
    FILE *file=fopen("grid.txt", "rb");
    for (int i=0;i<N;i++) for (int j=0; j<mGrid; j++) if (!fscanf(file, "%lf", &matrix[i][j]))break;
    fclose(file);
    return matrix;
}
//функция считывания из файла функции Грина
double *readRealGreen(void){
    double *realGreen=malloc(N*sizeof(double));
    FILE *file=fopen("realGreen.txt", "rb");
    for(int i=0;i<N;i++) if (!fscanf(file, "%lf", &realGreen[i])) break;
    fclose(file);
    return realGreen;
}
//функция считывания из файла сетки по мнимому времени
double *readTau(void){
    double *tau=malloc(N*sizeof(double));
    FILE *file=fopen("tau.txt", "rb");
    for(int i=0;i<N;i++) if (!fscanf(file, "%lf", &tau[i])) break;
    fclose(file);
    return tau;
}
//функция поиска оптимального значения изменения параметра
double getOptim(double D0,double D1,double D2,double param){
    if (D0-2.0*D2+D1) return ((3.0*D0-4.0*D2+D1)*param)/(4.0*(D0-2.0*D2+D1));
    else return param;
}
//функция поиска индекса минимального значения в массиве
int findMinimumIndx(double *arr, int n) {

    int indx_min=0;
    for(int i=1;i<n;++i) if(arr[i]<arr[indx_min]) indx_min=i;
    return indx_min;
}
//функция сохранения результатов
void saveResults(double *ht,double *wt, double *ct, int k){
    double *rSide;
	double *lSide;
	rSide = (double*)malloc(k*sizeof(double));
	lSide = (double*)malloc(k*sizeof(double));
	
    for(int i=0;i<k;i++){
        rSide[i]=ct[i]+wt[i]/2.0;
        lSide[i]=ct[i]-wt[i]/2.0;
    }
    double w[10000];
    double h[10000];
    memset(h,0,sizeof(h));
    for (int i=0; i<10000; i++) w[i]=wMax1+(wMax2-wMax1)/10000.0*i;
    for (int j=0; j<k; j++) for(int i=0;i<10000;i++) if((lSide[j]<w[i])&&(w[i]<rSide[j])) h[i]+=ht[j];
    FILE *file=fopen("result.txt", "w+");
    for (int i=0; i<10000;i++) fprintf(file, "%f    %f\n",h[i],w[i]);
    fclose(file);
}
//функция считывания из файла констант
void readConstants(void){
    FILE *file=fopen("constants.txt", "r");
    char buff[80];
    int i=0;
    while (fgets(buff,80,file)!=NULL){
        switch (i) {
            case  1:
            	sscanf(buff, "%lf", &wMin);
            	printf("wMin=%f\n",wMin);
            	break;
            case  2:
            	sscanf(buff, "%lf", &hMin);
            	printf("hMin=%f\n",hMin);
            	break;
            case  3:
            	sscanf(buff, "%lf", &hMax);
            	printf("hMax=%f\n",hMax);
            	break;
            case  4:
            	sscanf(buff, "%lf", &wMax1);
            	printf("wMax1=%f\n",wMax1);
            	break;
            case  5:
            	sscanf(buff, "%lf", &wMax2);
            	printf("wMax2=%f\n",wMax2);
            	break;
            case  6:
            	sscanf(buff,  "%d", &kMax);
            	printf("kMax=%d\n",kMax);
            	break;
            case  7:
            	sscanf(buff, "%lf", &fullS);
            	printf("fullS=%f\n",fullS);
            	break;
            case 8:
            	sscanf(buff, "%lf", &SMin);
            	printf("SMin=%f\n",SMin);
            	break;
            case 11:
            	sscanf(buff, "%lf", &T);
            	printf("T=%f\n",T);
            	break;
            case 12:
            	sscanf(buff,  "%d", &N);
            	printf("N=%d\n",N);
            	break;
            case 16:
            	sscanf(buff, "%lf", &Dmin);
            	printf("Dmin=%f\n",Dmin);
            	break;
            case 17:
            	sscanf(buff,  "%d", &firstPow);
            	printf("firstPow=%d\n",firstPow);
            	break;
            case 18:
            	sscanf(buff,  "%d", &secondPow);
            	printf("secondPow=%d\n",secondPow);
            	break;
            case 19:
            	sscanf(buff,  "%d", &monteStart);
            	printf("monteStart=%d\n",monteStart);
            	break;
            case 20:
            	sscanf(buff,  "%d", &monteFirst);
            	printf("monteFirst=%d\n",monteFirst);
            	break;
            case 22:
            	sscanf(buff,  "%d", &monteFull);
            	printf("monteFull=%d\n",monteFull);
            	break;
            case 23:
            	sscanf(buff,  "%d", &fullIter);
            	printf("fullIter=%d\n",fullIter);
            	break;
            case 24:
            	sscanf(buff,  "%d", &numberResults);
            	printf("numberResults=%d\n",numberResults);
            	break;
            case 29:
            	sscanf(buff,  "%d", &mGrid);
            	printf("mGrid=%d\n",mGrid);
            	break;
            case 30:
            	sscanf(buff, "%lf", &gridStep);
            	printf("gridStep=%f\n",gridStep);
            	break;
            case 31:
            	sscanf(buff, "%lf", &gridStart);
            	printf("gridStart=%f\n",gridStart);
            	break;
            default: break;
        }
        i++;
    }
}


