//
//  main.cpp
//  Cboarding Update2
//
//  Created by kevin on 2/22/18.
//  Copyright © 2018 kevin. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include "Gamestate.hpp"


int main(int argc, const char * argv[]) {
    char rule_name[100];
    char board_name[100];
    char ran_name[100];
    sscanf(argv[1],"%s",rule_name);
    sscanf(argv[2],"%s",board_name);
    sscanf(argv[3],"%s",ran_name);
    Monopoly::the_play_funtion(rule_name, board_name, ran_name);
    return 0;
}

