//
//  main.h
//  MonteGreen
//
//  Created by Ярослав Жумагулов on 07.12.15.
//  Copyright © 2015 Yaroslav Zhumagulov. All rights reserved.
//

#ifndef main_h
#define main_h

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "constants.h"
#include "setConfiguration.h"
#include "functions.h"
#include "deviation.h"
#include "updates.h"
#include "montecarlo.h"
volatile double wMin,hMin,hMax,wMax1,wMax2,SMin,**greenFuncGrid,gridStep,*realGreen,*tau,T,fullS;
volatile double pAddRemove,pAlterCreate,Dmin,u,gridStart;
volatile int kMax,N,monteStatus,gridMode,kStart,mGrid,numberResults,fullIter,monteStart,monteFull,monteFirst;
volatile int firstPow,secondPow,counter;
volatile struct configuration conf;
volatile struct configuration bestConf;


#endif /* main_h */
