//
//  updates.h
//  MonteGreen
//
//  Created by Ярослав Жумагулов on 02.11.15.
//  Copyright © 2015 Yaroslav Zhumagulov. All rights reserved.
//

#ifndef updates_h
#define updates_h

#include <stdio.h>
#include <math.h>
#include "constants.h"
#include "functions.h"
#include "deviation.h"

struct configuration shifting(struct configuration conf,int i);     //функция сдвига прямоугольника
struct configuration height(struct configuration conf);             //функция изменения высоты прямоугольника
struct configuration width(struct configuration conf);              //функция изменения ширины прямоугольника
struct configuration add(struct configuration conf);                //функция добавления прямоугольника в конфигурацию
struct configuration del(struct configuration conf);                //функция удаления прямоугольника из концигурации
struct configuration split(struct configuration conf);              //функция разделения прямоугольника на два прямоугольника
struct configuration glue(struct configuration conf);               //функция соединения двух прямоугольников в один прямоугольник
#endif /* updates_h */
