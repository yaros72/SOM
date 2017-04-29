//
//  updates.c
//  MonteGreen
//
//  Created by Ярослав Жумагулов on 02.11.15.
//  Copyright © 2015 Yaroslav Zhumagulov. All rights reserved.
//

#include "updates.h"

//функция сдвига прямоугольника (значение изменения параметра - центр прямоугольника)
struct configuration shifting(struct configuration conf,int i){
    if (!monteStatus){                                                                      //условие режима "мнимого" метрополиса
        if (i==-1) i=getRandom()*conf.k;                                                    //выбор случайного прямоугольника
        struct configuration C1=conf;                                                       //генерация конфигурации с полным значением изменения параметра
        C1.ct[i]=(wMax2-wMax1-conf.wt[i])*getRandom()+wMax1+conf.wt[i]/2.0;                 //сдвиг прямоугольника
        if (((C1.ct[i]-C1.wt[i]/2.0)<wMax1)||((C1.ct[i]+C1.wt[i]/2.0)>wMax2)) return conf;  //проверка краевых условий
        C1.D=deviation(C1);                                                                 //рассчет отклонения в случае полного значения изменения параметра
        double param=C1.ct[i]-conf.ct[i];                                                   //рассчет полного значения изменения параметра
        
        struct configuration C2=conf;                                                       //генерация отклониния с половинным значением изменения параметра
        C2.ct[i]=(conf.ct[i]+param/2.0);                                                    //сдвиг прямоугольника
        C2.D=deviation(C2);                                                                 //рассчет отклонения в случае половиного значения изменения параметра
        
        struct configuration COptim=conf;                                                   //генерация оптимального обновления конфигурации
        double optim=getOptim(conf.D,C1.D,C2.D,param);                                      //рассчет оптимального значения изменения параметра
        COptim.ct[i]=conf.ct[i]+optim;                                                      //сдвиг прямоугольника
                                                                                            //рассчет отколения в случае оптмального значения изменения параметра
        if ((wMax1<(COptim.ct[i]-COptim.wt[i]/2.0))&&((COptim.ct[i]+COptim.wt[i]/2.0)<wMax2)) COptim.D=deviation(COptim);     //если значение изменения параметра
        else COptim.D=INFINITY;                                                              //не входит в области определения решения, то отклонение приравнивается бесконечности
        double D[]= {conf.D,C1.D,C2.D,COptim.D};
        int iD=findMinimumIndx(D,4);                                                          //поиск минимального отконения из 4-ех
        switch (iD){                                                                        //принятие обновления с минимальным отклонением
            case 0: return conf;
            case 1: return C1;
            case 2: return C2;
            case 3:	return COptim;
            default:return conf;
        }
    }else{
        i=getRandom()*conf.k;                                                               //выбор случайного прямоугольника
        conf.ct[i]=(wMax2-wMax1-conf.wt[i])*getRandom()+wMax1+conf.wt[i]/2.0;               //сдвиг прямоугольника
        if (((conf.ct[i]-conf.wt[i]/2.0)<wMax1)||((conf.ct[i]+conf.wt[i]/2.0)>wMax2)) return conf;
        conf.D=deviation(conf);                                                             //расчет отклонения
        return conf;
    }
}
//функция изменения высоты прямоугольника (значение изменения параметра - высота)
struct configuration height(struct configuration conf){
    if (!monteStatus){                                                                      //условие режима "мнимого" метрополиса
        int i=getRandom()*conf.k;                                                           //выбор случайного прямоугольника в который будет переноситься вес
        int j=getRandom()*conf.k;                                                           //выбор случайного прямоугольника из которого будет переноситься вес
        if (i==j) return conf;                                                              //если были выбран один и тот же прямоугольник, то обновление не принимается
        double paramMax=conf.ht[j]-SMin/conf.wt[j]*conf.wt[i]/conf.wt[j];                   //рассчет максимального и минимального значения изменения параметра
        double paramMin=SMin/conf.wt[i]-conf.ht[i];
        double param=getRandom()*(paramMax-paramMin)+paramMin;                              //определения значения изменения параметра
        struct configuration C1=conf;                                                       //генерация конфигурации с полным значением изменения параметра
        C1.ht[i]=conf.ht[i]+param;                                                          //перенос веса с одного прямоугольника на другой
        C1.ht[j]=conf.ht[j]-param*conf.wt[i]/conf.wt[j];
        if ((hMax<C1.ht[i])||(C1.ht[i]<hMin)||(hMax<C1.ht[j])||(C1.ht[j]<hMin)) return conf; //проверка краевых условий
        C1.D=deviation(C1);                                                                 //рассчет отклонения в случае полного значения изменения параметра

        struct configuration C2=conf;                                                       //генерация отклониния с половинным значением изменения параметра
        C2.ht[i]=conf.ht[i]+param/2.0;                                                      //перенос веса с одного прямоугольника на другой
        C2.ht[j]=conf.ht[j]-param/2.0*conf.wt[i]/conf.wt[j];
        C2.D=deviation(C2);                                                                 //рассчет отклонения в случае половиного значения изменения параметра
        
        struct configuration COptim=conf;                                                   //генерация оптимального обновления конфигурации
        double optim=getOptim(conf.D, C1.D, C2.D, param);                                   //рассчет оптимального значения изменения параметра
        COptim.ht[i]=conf.ht[i]+optim;                                                      //перенос веса с одного прямоугольника на другой
        COptim.ht[j]=conf.ht[j]-optim*conf.wt[i]/conf.wt[j];
                                                                                            //рассчет отколения в случае оптмального значения изменения параметра
        if ((hMax>COptim.ht[i])&&(COptim.ht[i]>hMin)&&(hMax>COptim.ht[j])&&(COptim.ht[j]>hMin)) COptim.D=deviation(COptim);//если значение изменения параметра
        else COptim.D=INFINITY;                                                             //не входит в области определения решения, то отклонение приравнивается бесконечности
        double D[]= {conf.D,C1.D,C2.D,COptim.D};
        int iD=findMinimumIndx(D,4);                                                          //поиск минимального отконения из 4-ех
        switch (iD){                                                                        //принятие обновления с минимальным отклонением
            case 0:return conf;
            case 1:return C1;
            case 2:return C2;
            case 3:return COptim;
            default:return conf;
        }
    }else{
        int i=getRandom()*conf.k;                                                           //выбор случайного прямоугольника в который будет переноситься вес
        int j=getRandom()*conf.k;                                                           //выбор случайного прямоугольника из которого будет переноситься вес
        if (i==j) return conf;                                                              //если были выбран один и тот же прямоугольник, то обновление не принимается
        struct configuration C=conf;
        double paramMax=C.ht[j]-SMin/C.wt[j]*C.wt[i]/C.wt[j];                			    //расчет максимального и минимального значения изменения параметра
        double paramMin=SMin/C.wt[i]-C.ht[i];
        double param=getRandom()*(paramMax-paramMin)+paramMin;                              //определения значения изменения параметра
        double hBuff=C.ht[i];
        C.ht[i]=C.ht[i]+param;                                                        		//перенос веса с одного прямоугольника на другой
        C.ht[j]=C.ht[j]-(C.ht[i]-hBuff)*C.wt[j]/C.wt[i];
        if ((hMax<C.ht[i])||(C.ht[i]<hMin)||(hMax<C.ht[j])||(C.ht[j]<hMin)) return conf;	//проверка краевых условий
        C.D=deviation(C);                                                            		 //расчет отклонения
        return C;
    }
}
//функция изменения ширины прямоугольника (значение изменения параметра - ширина)
struct configuration width(struct configuration conf){
    if (!monteStatus){                                                                      //условие режима "мнимого" метрополиса
        int i=getRandom()*conf.k;                                                           //выбор случайного прямоугольника
        double S=conf.ht[i]*conf.wt[i];                                                     //расчет площади выбранного прямоугольника
        double wMax=2*fmin(conf.ct[i]-wMax1, wMax2-conf.ct[i]);                             //расчет максимального значения ширины прямоугольника
        
        struct configuration C1=conf;                                                       //генерация конфигурации с полным значением изменения параметра
        C1.wt[i]=getRandom()*wMax+wMin;                                                     //генерация ширины прямоуголька
        C1.ht[i]=S/C1.wt[i];                                                                //расчет высоты прямоугольника
        double param=C1.wt[i]-conf.wt[i];                                                   //расчет значения изменения параметра
        if ((hMax<C1.ht[i])||(C1.ht[i]<hMin)||(wMax1>(C1.ct[i]-C1.wt[i]/2.0))||(C1.wt[i]<wMin)||(wMax2<(C1.ct[i]+C1.wt[i]/2.0)))return conf;//проверка краевых условий
        C1.D=deviation(C1);                                                                 //рассчет отклонения в случае полного значения изменения параметра
        
        struct configuration C2=conf;                                                       //генерация отклониния с половинным значением изменения параметра
        C2.wt[i]=C2.wt[i]+param/2.0;                                                        //расчет ширины прямоугольника
        C2.ht[i]=S/C2.wt[i];                                                                //расчет высоты прямоугольника
        C2.D=deviation(C2);                                                                 //расчет отклонение в случае половинного значения изменения параметра
        
        struct configuration COptim=conf;                                                   //генерация отклонения с оптимальным значением изменения параметра
        double optim=getOptim(conf.D, C1.D, C2.D, param);                                   //расчет оптимального значения изменения параметра
        COptim.wt[i]=COptim.wt[i]+optim;                                                    //расчет ширины прямоугольник
        COptim.ht[i]=S/COptim.wt[i];                                                        //расчет высоты прямоугольника
                                                                                            //рассчет отколения в случае оптмального значения изменения параметра
        if ((hMax>COptim.ht[i])&&(COptim.ht[i]>hMin)&&(wMax2>(COptim.ct[i]+COptim.wt[i]/2.0))&&(COptim.wt[i]>wMin)&&(wMax1<(COptim.ct[i]-COptim.wt[i]/2.0))) COptim.D=deviation(COptim);
        else COptim.D=INFINITY;                                                             //если значение изменения параметра не входит в области определения решения
                                                                                            //то отклонение приравнивается бесконечности
        double D[]={conf.D,C1.D,C2.D,COptim.D};
        int iD=findMinimumIndx(D,4);                                                          //поиск минимального значения из 4-ех
        switch (iD){                                                                        //принятие обновления с минимальным отклонением
            case 0:return conf;
            case 1:return C1;
            case 2:return C2;
            case 3:return COptim;
            default:return conf;
        }
    }else{
    	struct configuration C=conf;
        int i=getRandom()*C.k;                                                         //выбор случайного прямоугольника
        double S=C.ht[i]*C.wt[i];                                                      //расчет площади выбранного прямоугольника
        double wMax=2*fmin(C.ct[i]-wMax1, wMax2-C.ct[i]);                              //расчет максимального значения ширины прямоугольника
        C.wt[i]=getRandom()*(wMax-wMin)+wMin;                                          //генерация ширины прямоугольника
        C.ht[i]=S/C.wt[i];                                                             //расчет высоты прямоугольника
        if ((hMax<C.ht[i])||(C.ht[i]<hMin)||(wMax1>(C.ct[i]-C.wt[i]/2.0))||(C.wt[i]<wMin)||(wMax2<(C.ct[i]+C.wt[i]/2.0)))return conf;//проверка краевых условий
        C.D=deviation(C);                                                              //расчет отклонения
        return C;
    }
}
//функция добавления прямоугольника в конфигурацию
struct configuration add(struct configuration conf){
    if (conf.k>=kMax) return conf;                                                      //в случае если количество прямоугольников достигло максимального значения обновление не принимается
    if (!monteStatus){                                                                  //условие режима "мнимого" метрополиса
        int i=getRandom()*conf.k;                                                       //выбор прямоугольника для переноса веса
        if ((conf.ht[i]*conf.wt[i])<(2*SMin)) return conf;                              //если площадь прямоугольника меньше двух минимальных площадей, то обновление отклоняется
        
        struct configuration C1=conf;                                                   //генерация конфигурации с полным значением изменения параметра
        C1.ct[conf.k]=(wMax1+wMin/2.0)+getRandom()*(wMax2-wMax1-wMin);                  //генерация центра нового прямоугольника
        double wNewMax=2*fmin(wMax2-C1.ct[conf.k], C1.ct[conf.k]-wMax1);                //расчет максимального значения ширины прямоугольника
        double param=(getRandom()*(conf.ht[i]*conf.wt[i]-SMin)+SMin);                   //генерация площади нового прямоугольника
        C1.ht[i]=conf.ht[i]-param/conf.wt[i];                                           //расчет высоты выбранного прямоугольника после переноса веса
        C1.ht[conf.k]=param/wNewMax+getRandom()*(param/wMin-param/wNewMax);             //расчет высоты нового прямоугольника
        C1.wt[conf.k]=param/C1.ht[conf.k];                                              //расчет ширины нового прямоугольника
        C1.k+=1;
        if ((C1.ht[conf.k]>hMax)||(C1.ht[conf.k]<hMin))return conf;                     //проверка краевых условий
        C1.D=deviation(C1);                                                             //рассчет отклонения в случае полного значения изменения параметра
        
        struct configuration C2=conf;                                                   //генерация отклониния с половинным значением изменения параметра
        param/=2.0;
        C2.ht[i]=conf.ht[i]-param/conf.wt[i];                                           //расчет высоты выбранного прямоугольника после переноса веса
        C2.ht[conf.k]=param/wNewMax+getRandom()*(param/wMin-param/wNewMax);             //расчет высоты нового прямоугольника
        C2.wt[conf.k]=param/C2.ht[conf.k];                                              //расчет ширины нового прямоугольника
        C2.ct[conf.k]=C1.ct[conf.k];
        C2.k+=1;
        C2.D=deviation(C2);                                                             //расчет отклонение в случае половинного значения изменения параметра
        
        struct configuration COptim=conf;                                               //генерация отклонения с оптимальным значением изменения параметра
        double optim=getOptim(conf.D, C1.D, C2.D, param);                               //расчет оптимального значения изменения парамета
        COptim.ht[i]=conf.ht[i]-optim/conf.wt[i];                                       //расчет высоты выбранного прямоугольника после переноса веса
        COptim.ht[conf.k]=optim/wNewMax+getRandom()*(optim/wMin-optim/wNewMax);         //расчет высоты нового прямоугольника
        COptim.wt[conf.k]=optim/COptim.ht[conf.k];                                      //расчет ширины нового прямоугольника
        COptim.ct[conf.k]=C1.ct[conf.k];
        COptim.k+=1;
        if ((COptim.ht[conf.k]<hMin)||(COptim.ht[i]<hMin)) COptim.D=INFINITY;           //рассчет отколения в случае оптмального значения изменения параметра
        else COptim.D=deviation(COptim);                                                //если значение изменения параметра не входит в области определения решения
                                                                                        //то отклонение приравнивается бесконечности
        
        double D[]= {conf.D,C1.D,C2.D,COptim.D};
        int iD=findMinimumIndx(D,4);                                                      //поиск минимального значения из 4-ех
        switch (iD){                                                                    //принятие обновления с минимальным отклонением
            case 0: return conf;
            case 1: return C1;
            case 2: return C2;
            case 3: return COptim;
            default:return conf;
        }
    }else{
    	struct configuration C=conf;
        int i=getRandom()*C.k;                                                          //выбор прямоугольника для переноса веса
        if ((C.ht[i]*C.wt[i])<(2*SMin)) return conf;    	                            //если площадь прямоугольника меньше двух минимальных площадей, то обновление отклоняется
        C.ct[C.k]=(wMax1+wMin/2.0)+getRandom()*(wMax2-wMax1-wMin); 		                //генерация центра нового прямоугольника
        double wNewMax=fmin(wMax2-C.ct[C.k], C.ct[C.k]-wMax1); 				            //расчет максимального значения ширины прямоугольника
        double param=(getRandom()*(C.ht[i]*C.wt[i]-SMin)+SMin);		                    //генерация площади нового прямоугольника
        C.ht[i]=C.ht[i]-param/C.wt[i];                                    		        //расчет высоты выбранного прямоугольника после переноса веса
        C.ht[C.k]=param/wNewMax+getRandom()*(param/wMin-param/wNewMax);   		        //расчет высоты нового прямоугольника
        C.wt[C.k]=param/C.ht[C.k];                                    			        //расчет ширины нового прямоугольника
        C.k+=1;
        if ((C.ht[C.k]>hMax)||(C.ht[C.k]<hMin))return conf;  		                    //проверка краевых условий
        C.D=deviation(C);      		                                                    //расчет отклонения
        return C;
    }
}
//функция удаления прямоугольника из концигурации
struct configuration del(struct configuration conf){
    if (conf.k<=1) return conf;                                                         //если количество прямоугольников равно 1, то обновление не принимается
    int i=getRandom()*conf.k;                                                           //выбор случайного прямоугольника для удаления
    double S=conf.ht[i]*conf.wt[i];                                                     //расчет площади удаляемого прямоугольника
    struct configuration C=conf;                                                        //генерация новой конфигурации
    C.k=conf.k-1;                                                                       //удаление прямоугольника
    C.ht[i]=C.ht[C.k];
    C.wt[i]=C.wt[C.k];
    C.ct[i]=C.ct[C.k];
    C.ht[C.k]=0;
    C.wt[C.k]=0;
    C.ct[C.k]=0;
    int j=getRandom()*C.k;                                                              //выбор прямоугольника для прибавления веса удаленного прямоугольника
    C.ht[j]+=S/C.wt[j];                                                                 //расчет высоты прямоугольника с прибавленным весом
    C.D=deviation(C);                                                                   //расчет отклонения
    if (C.ht[j]>hMax) return conf;                                                      //проверка краевых условий
    if (!monteStatus) C=shifting(C, j);                                                 //оптимизация решения через обновление-сдвиг
    if ((C.D<conf.D)&&(!monteStatus))return C;
    else return conf;
}
//функция разделения прямоугольника на два прямоугольника
struct configuration split(struct configuration conf){
    if (conf.k>=kMax) return conf;                                                      //в случае если количество прямоугольников достигло максимального значения обновление не принимается
    int i=getRandom()*conf.k;                                                           //выбор прямоугольника для расщепления
    if ((conf.ht[i]*conf.wt[i]<(2*SMin))||(conf.wt[i]<(2*wMin))) return conf;           //если площадь и ширина выбраного прямоугольника меньше двух минимальных
    struct configuration C=conf;                                                        //генерация новой конфигурации
    C.k=conf.k+1;                                                                       //расщепление прямоугольника
    C.ht[i]=C.ht[C.k-2];
    C.wt[i]=C.wt[C.k-2];
    C.ct[i]=C.ct[C.k-2];
    C.ht[C.k-1]=conf.ht[i];
    C.ht[C.k-2]=conf.ht[i];
    C.wt[C.k-1]=conf.wt[i]/2;
    C.wt[C.k-2]=conf.wt[i]-C.wt[C.k-1];
    C.ct[C.k-1]=conf.ct[i]-C.wt[C.k-1]/2.0;
    C.ct[C.k-2]=conf.ct[i]+C.wt[C.k-2]/2.0;
    C.D=deviation(C);                                                                   //расчет прямоугольника
    if (!monteStatus){                                                                  //оптимизация решения через обновление-сдвиг
        if (C.wt[C.k-1]>=C.wt[C.k-2]) C=shifting(C, C.k-1);
        else C=shifting(C, C.k-2);
    }
    if ((C.D<conf.D)&&(!monteStatus)) return C;
    else return conf;
}
//функция соединения двух прямоугольников в один прямоугольник
struct configuration glue(struct configuration conf){
    if (conf.k<=1) return conf;                                                         //если количество прямоугольников равно 1, то обновление не принимается
    int i=getRandom()*conf.k;                                                           //выбор прямоугольников для объединения
    int j=getRandom()*conf.k;
    if (i==j) return conf;                                                              //если выбран один и тот же прямоугольник, то обновление не принимается
    double iS=(conf.ht[i]*conf.wt[i]);                                                  //расчет площади первого выбранного прямоугольника
    double jS=(conf.ht[j]*conf.wt[j]);                                                  //расчет площади второго выбранного прямоугольника
    double wNew=((conf.wt[i]+conf.wt[j]-wMin)*getRandom()+wMin);                        //генерация площади нового прямоугольника
    double hNew=(iS+jS)/wNew;                                                           //расчет высоты нового прямоугольника
    double cNew=((conf.ct[i]*iS)+(conf.ct[j]*jS))/(iS+jS);                              //расчет центра нового прямоугольника
    if ((hNew>hMax)||(hNew<hMin)||((cNew+wNew/2.0)>wMax2)||((cNew-wNew/2.0)<wMax1)) return conf;                                          //проверка краевых условий
    struct configuration C=conf;                                                        //генерация новой конфигурации
    C.ht[i]=C.ht[C.k-2];                                                                //объединение прямоугольников
    C.wt[i]=C.wt[C.k-2];
    C.ct[i]=C.ct[C.k-2];
    C.ht[j]=C.ht[C.k-1];
    C.wt[j]=C.wt[C.k-1];
    C.ct[j]=C.ct[C.k-1];
    C.ht[C.k-2]=hNew;
    C.wt[C.k-2]=wNew;
    C.ct[C.k-2]=cNew;
    C.ht[C.k-1]=0;
    C.wt[C.k-1]=0;
    C.ct[C.k-1]=0;
    C.k-=1;
    C.D=deviation(C);                                                                   //расчет отклонения
    if (!monteStatus) C=shifting(C, C.k-1);                                             //оптимизация решения через обновление-сдвиг
    if (((area(conf.wt,conf.ht,conf.k))==(area(C.wt,C.ht,C.k)))&&((cNew+wNew/2.0)<wMax2)&&((cNew-wNew/2.0)>wMax1))C.D=deviation(C);              //проверка краевых условий
    else return conf;
    if ((C.D<conf.D)&&(!monteStatus))return C;
    else return conf;
}
