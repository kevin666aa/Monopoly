//
//  Rules.cpp
//  Cboarding Update 1
//
//  Created by kevin on 2/16/18.
//  Copyright © 2018 kevin. All rights reserved.
//

#include "Rules.hpp"


Monopoly::Rules::Rules(){
    Rules::starting_cash = 0;
    Rules::turn_limits = 0;
    Rules::players_left_to_win = 0;
    Rules::set_mupltiper = 0;
    Rules::houses_before_hotels = 0;
    Rules::build_evenly = ' ';
    Rules::free_parking = ' ';
    Rules::auction = ' ';
    Rules::land_on_go = 0;
    Rules::max_double_roll = 0;
    return;
}
void Monopoly::open_rules(char* rule_name, std::unique_ptr < Monopoly::Rules> & rules){
    FILE* fp = fopen(rule_name, "r");
    char str = 'a';
    int num = 0;
    while (str != ':') {
        str = getc(fp);
    }
    fscanf(fp, "%d", &num);
    rules->setStarting_cash(num);
    
    str = getc(fp);
    while (str != ':') {
        str = getc(fp);
    }
    fscanf(fp, "%d", &num);
    rules->setTurn_limits(num);
    
    str = getc(fp);
    while (str != ':') {
        str = getc(fp);
    }
    fscanf(fp, "%d", &num);
    rules->setPlayers_left_to_win(num);
    
    str = getc(fp);
    while (str != ':') {
        str = getc(fp);
    }
    fscanf(fp, "%d", &num);
    rules->setSet_mupltiper(num);
    
    str = getc(fp);
    while (str != ':') {
        str = getc(fp);
    }
    fscanf(fp, "%d", &num);
    rules->setHouses_before_hotels(num);
    
    str = getc(fp);
    while (str != ':') {
        str = getc(fp);
    }
    getc(fp);
    str = getc(fp);
    rules->setBuild_evenly(str);
    
    do{
        str = getc(fp);
    } while(str != ':');
    getc(fp);
    str = getc(fp);
    rules->setFree_parking(str);
    
    do{
        str = getc(fp);
    } while(str != ':');
    getc(fp);
    str = getc(fp);
    rules->setAuction(str);
    
    do{
        str = getc(fp);
    } while(str != ':');
    fscanf(fp, "%d", &num);
    rules->setLand_on_go(num);

    do{
        str = getc(fp);
    } while(str != ':');
    fscanf(fp, "%d", &num);
    rules->setmax_double_roll(num);
    fclose(fp);
}
