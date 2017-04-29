//
//  deviation.h
//  MonteGreen
//
//  Created by Ярослав Жумагулов on 27.10.15.
//  Copyright © 2015 Yaroslav Zhumagulov. All rights reserved.
//

#ifndef deviation_h
#define deviation_h

#include <stdlib.h>
#include <math.h>
#include "constants.h"

double deviation(struct configuration conf);                  //функция расчета отклонения
double greenGrid(double x, double t, int i);                    //функция поиска значений по сетке
#endif /* deviation_h */
