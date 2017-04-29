//
//  deviation.c
//  MonteGreen
//
//  Created by Ярослав Жумагулов on 27.10.15.
//  Copyright © 2015 Yaroslav Zhumagulov. All rights reserved.
//

#include "deviation.h"

//функция поиска значений по сетке
double greenGrid(double x,double t,int i){
    int p=floor((x-gridStart)/gridStep);
    return greenFuncGrid[i][p];
}
//функция расчета отклонения
double deviation(struct configuration conf){
    double D=0;
    double G;
    for(int i=0;i<N;i++){
    	G=0;
    	for(int j=0;j<conf.k;j++){
    		G+=conf.ht[j]*(greenGrid(conf.ct[j]+conf.wt[j]/2.0,tau[i],i)-greenGrid(conf.ct[j]-conf.wt[j]/2.0,tau[i],i)); //цикл генерации функции Грина
    	}
    	D+=pow(G-realGreen[i],2); //цикл подсчета отклонения
    }
    return D;
}
//функция расчета отклонения финального результата

