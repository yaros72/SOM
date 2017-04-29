//
//  montecarlo.conf
//  MonteGreen
//
//  Created by Ярослав Жумагулов on 06.12.15.
//  Copyright © 2015 Yaroslav Zhumagulov. All rights reserved.
//

#include "montecarlo.h"

//функция Монте-Карло (переключатель градиентного спуска и "мнимого" метрополиса)

//функция обновлений
struct configuration nextUpdate(struct configuration conf) {
    int update = floor(getRandom() * 7);
    switch (update) {
        case 0:
            conf = shifting(conf, -1);
            break;
        case 1:
            conf = height(conf);
            break;
        case 2:
            conf = width(conf);
            break;
        case 3:
            conf = add(conf);
            break;
        case 4:
            conf = del(conf);
            break;
        case 5:
            conf = split(conf);
            break;
        case 6:
            conf = glue(conf);
            break;
        default:
            break;
    }
    return conf;
}
