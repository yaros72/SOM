//
//  montecarlo.h
//  MonteGreen
//
//  Created by Ярослав Жумагулов on 06.12.15.
//  Copyright © 2015 Yaroslav Zhumagulov. All rights reserved.
//

#ifndef montecarlo_h
#define montecarlo_h

#include <stdio.h>
#include <math.h>
#include "constants.h"
#include "updates.h"
#include "deviation.h"
#include "functions.h"
extern volatile int counter;                                            //счетчик "промахов" обновлений (промахи - обновления с отрицательным исходом)
struct configuration nextUpdate(struct configuration conf);             //функция обновлений
#endif /* montecarlo_h */
