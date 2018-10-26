//
//  Gamestate.cpp
//  Cboarding Update 1
//
//  Created by kevin on 2/16/18.
//  Copyright © 2018 kevin. All rights reserved.
//
/*
 for (int i = 0; i < board.getnum_space(); i++) {
 if (board.getboard().at(i)->getSpaceType() == "FreeParking") {
 static_cast<Monopoly::FreeParking*>(board.getboard().at(i).get())->setmoney_pool(0);
 }
 }

 for (int i = 0; i < board.getnum_space(); i++) {
 if (board.getboard().at(i)->getSpaceType() == "FreeParking") {
 static_cast<Monopoly::FreeParking*>(board.getboard().at(i).get())->setmoney_pool(static_cast<Monopoly::Pay*>(board.getboard().at(loaction).get())->getsum());
 }
 }*/

#include "Gamestate.hpp"


Monopoly::Gamestate::Gamestate(){
    Gamestate::current_player = 0;
    Gamestate::turns = 0;
    Gamestate::current_reroll = 0;
}

void Monopoly::the_play_funtion(char* rule_name, char* board_name, char* ran_name){
    Monopoly::Diceroller dice;
    dice.openfile(ran_name);//create dice

    std::unique_ptr<Monopoly::Rules> rules = std::make_unique<Monopoly::Rules>();
    Monopoly::open_rules(rule_name, rules);//initialize rules

    std::vector <std::unique_ptr<Monopoly::Player> > player;
    Monopoly::setupPlayer(player, rules);// initialize player

    Monopoly::Gamestate gamestate;//initialize gamstate
    
    Monopoly::Board board(board_name);//initialize board
    board.getboard().at(0)->setowner_length(player);

    if (rules->getTurn_limits() == -1) {
        //don't have turn limits
        //main loop
        do {
            Monopoly::a_person_play(board, player, gamestate, dice, rules);
            gamestate.next_palyer();
            if (gamestate.getcurrent_player() == player.at(0)->getPeople_left()) {
                gamestate.set_current(0);
            }
        } while (player.at(0)->getPeople_left() > rules->getPlayers_left_to_win());

        //declare winner
        Monopoly::print_board(board, player, gamestate, 1);
        std::cout << "The winners are" << std::endl;
        std::cout << player.at(0)->getName() << std::endl;
    } else{
        //have turn limits
        while(gamestate.getTurns() < rules->getTurn_limits()){
            if (player.at(0)->getPeople_left() > rules->getPlayers_left_to_win()) {
                Monopoly::a_person_play(board, player, gamestate, dice, rules);
                if (player.at(0)->getPeople_left() <= rules->getPlayers_left_to_win()) {
                    break;
                }
                gamestate.add_turn();
                gamestate.next_palyer();
                if (gamestate.getcurrent_player() >= player.at(0)->getPeople_left()) {
                    gamestate.set_current(0);
                }
            } else{
                break;
            }
        }
        // declare winner
        if (gamestate.getTurns() == rules->getTurn_limits()) {
            Monopoly::print_board(board, player, gamestate, 1);
            Monopoly::muti_winner(board, player, rules);
        } else{
            Monopoly::print_board(board, player, gamestate, 1);
            std::cout << "The winners are" << std::endl;
            for (int i = 0 ; i < player.at(0)->getPeople_left(); i++) {
                std::cout << player.at(i)->getName();
            }
        }

    }
    //clear up
    board.vector_destroy();
    player.clear();
    rules.release();
    dice.closefile();
    //clear up
}

void Monopoly::muti_winner(Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, std::unique_ptr<Monopoly::Rules>& rules){
    std::cout << "The winners are" << std::endl;
    for (int i = 0; i < player.at(0)->getPeople_left(); i++) {
        for (int j = 1; j < board.getnum_space(); j++) {
            if (player.at(i)->getName() == board.getboard().at(j)->getOwner()) {
                player.at(i)->add_money(static_cast<Monopoly::Property*>(board.getboard().at(j).get())->getProperty_cost());
                if (board.getboard().at(j)->getupgrade_house() > 0) {
                    player.at(i)->add_money(board.getboard().at(j)->getupgrade_house() * static_cast<Monopoly::Property*>(board.getboard().at(j).get())->getHouse_cost());
                }
                if (board.getboard().at(j)->getupgrade_hotel() > 0) {
                    player.at(i)->add_money((rules->getmax_double_roll() * static_cast<Monopoly::Property*>(board.getboard().at(j).get())->getHouse_cost() + static_cast<Monopoly::Property*>(board.getboard().at(j).get())->getHotel_cost()) * board.getboard().at(j)->getupgrade_hotel());
                }
            }
        }
    }
    int biggest = 0;
    for (int i = 0; i < player.at(0)->getPeople_left(); i++) {
        if (player.at(i)->getMoney() > biggest) {
            biggest = player.at(i)->getMoney();
        }
    }
    for (int i = 0; i < player.at(0)->getPeople_left(); i++) {
        if (player.at(i)->getMoney() == biggest) {
            std::cout << player.at(i)->getName() << std::endl;
        }
    }
}

void Monopoly::check_reroll(Monopoly::Gamestate& gamestate, int max_double_roll, int& a, int& b) {
    if (max_double_roll > 0) {
        if (a%6 == b%6) {
            if (max_double_roll > gamestate.getcurrent_reroll()) {
                gamestate.add_current_reroll();
            } else {
                gamestate.setcurrent_reroll(0);
            }
        } else {
            gamestate.setcurrent_reroll(0);
        }
    }
}

void Monopoly::a_person_play(Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, Monopoly::Gamestate& gamestate, Monopoly::Diceroller dice, std::unique_ptr<Monopoly::Rules>& rules){
    int c = gamestate.getcurrent_player(); // assign the index of current player to a shorter variable
    int check_player_left = player.at(0)->getPeople_left();
    player_whether_in_jail(board, player, gamestate, dice, rules, c);
    if (check_player_left != player.at(0)->getPeople_left()) {
        return;
    }
    int command = 0;
    std::cin >> command;
    if (command == 1) {
        if (player.at(c)->getwhether_in_jail()) {
            command_1_in_jail(board, player, gamestate, dice, rules, c);
        } else {
            command_1(board, player, gamestate, dice, rules, c);
        }
    } else if (command == 2){
        if (update_qulification(board, player.at(c)->getName())) {
            int count_hotel = 0, count_property = 0;
            for (int i = 1; i < board.getnum_space(); i++) {
                if (board.getboard().at(i)->getOwner() == player.at(c)->getName()) {
                    count_property++;
                    if (board.getboard().at(i)->getupgrade_hotel() > 0) {
                        count_hotel++;
                    }
                }
            }
            if (count_hotel != count_property) {
                buy_update(board, rules,  player.at(c)->getName(), player, c);
            } else {
                std::cout << "You don't have any properties that you can upgrade" << std::endl;
            }
        } else {
            std::cout << "You don't have any properties that you can upgrade" << std::endl;
        }
        a_person_play(board, player, gamestate, dice, rules);
    } else if (command == 3){
        int temp = 0;
        for (int i = 1; i < board.getnum_space(); i++) {
            if (board.getboard().at(i)->getOwner() == player.at(c)->getName()) {
                if (board.getboard().at(i)->getupgrade_house() > 0 || board.getboard().at(i)->getupgrade_hotel() > 0) {
                    temp++;
                    break;
                }
            }
        }
        if (temp > 0) {
            sell_update(board, rules, player.at(c)->getName(), player, c);
        } else{
             std::cout << "You don't have any upgrades that you can sell" << std::endl;
        }
        Monopoly::a_person_play(board, player, gamestate, dice, rules);
    } else if (command == 4){
        //leave_game
        Monopoly::leave_game(gamestate, board, player, c);
    } else {
        std::string dump;
        std::getline(std::cin, dump);
    }
}

void Monopoly::player_whether_in_jail(Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, Monopoly::Gamestate& gamestate, Monopoly::Diceroller dice, std::unique_ptr<Monopoly::Rules>& rules, int c){
    if (player.at(c)->getwhether_in_jail() && player.at(c)->getturns_in_jail() > 0) {
        print_board(board, player, gamestate, 1);
        std::cout << player.at(c)->getName() << " you are in jail for " << player.at(c)->getturns_in_jail() << " turns." << std::endl;
        int money_to_getout = static_cast<Monopoly::Jail*>(board.getboard().at(player.at(c)->getlocation()).get())->getPayed_to_getout();
        if (player.at(c)->getMoney() >= money_to_getout) {
            std::cout << "Would you like to pay $" << money_to_getout << " to leave jail early?" << std::endl << "y for yes and n for no: ";
            char temp_command = ' ';
            std::cin >> temp_command;
            if (temp_command == 'y' || temp_command == 'Y') {
                player.at(c)->buy_something(money_to_getout);
                player.at(c)->setwhether_in_jail(false);
                player.at(c)->setturns_in_jail(0);
                if (rules->getFree_parking() == 'Y') {
                    for (int i = 0; i < board.getnum_space(); i++) {
                        if (board.getboard().at(i)->getSpaceType() == "FreeParking") {
                            static_cast<Monopoly::Freeparking*>(board.getboard().at(i).get())->setpublic_money(money_to_getout +  static_cast<Monopoly::Freeparking*>(board.getboard().at(i).get())->getpublic_money());
                        }
                    }
                }

            } //if (temp_command == 'y' || temp_command == 'Y')
        }
        std::cout << player.at(gamestate.getcurrent_player())->getName() << " please enter your move" << std::endl << "1 to roll dice" << std::endl << "2 to upgrade a property with a house or hotel" << std::endl << "3 to sell a house or hotel" << std::endl << "4 to leave the game" << std::endl << "Your move: ";
    } else if(player.at(c)->getwhether_in_jail() && player.at(c)->getturns_in_jail() == 0){
        print_board(board, player, gamestate, 1);
        int money_to_getout = static_cast<Monopoly::Jail*>(board.getboard().at(player.at(c)->getlocation()).get())->getPayed_to_getout();
        if (player.at(c)->getMoney() >= money_to_getout) {
            std::cout << player.at(c)->getName() << ", you had to pay $" << money_to_getout << " to get out of jail" << std::endl;
            player.at(c)->setwhether_in_jail(false);
            player.at(c)->buy_something(money_to_getout);
            if (rules->getFree_parking() == 'Y') {
                for (int i = 0; i < board.getnum_space(); i++) {
                    if (board.getboard().at(i)->getSpaceType() == "FreeParking") {
                        static_cast<Monopoly::Freeparking*>(board.getboard().at(i).get())->setpublic_money(money_to_getout  +  static_cast<Monopoly::Freeparking*>(board.getboard().at(i).get())->getpublic_money());
                    }
                }
            }
            std::cout << player.at(gamestate.getcurrent_player())->getName() << " please enter your move" << std::endl << "1 to roll dice" << std::endl << "2 to upgrade a property with a house or hotel" << std::endl << "3 to sell a house or hotel" << std::endl << "4 to leave the game" << std::endl << "Your move: ";
        } else {
            check_anything_to_sell(gamestate, board, player, c, player.at(c)->getlocation(), rules, money_to_getout, 2);
        }
    } else {
        Monopoly::print_board(board, player, gamestate, 0);
    }
}

void Monopoly::command_1_in_jail(Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, Monopoly::Gamestate& gamestate, Monopoly::Diceroller dice, std::unique_ptr<Monopoly::Rules>& rules, int c){
    int a = 0, b = 0;
    dice.pick_up_random(a, b);
    Monopoly::check_reroll(gamestate, rules->getmax_double_roll(), a, b);
    int dice_num = a%6 + b%6 + 2;
    std::cout << player.at(c)->getName()<< ", you rolled a " << dice_num << std::endl;
    if (gamestate.getcurrent_reroll() > 0) {
//    goes normal
//        same as command 1
        gamestate.setcurrent_reroll(0);
        player.at(c)->setwhether_in_jail(false);
        if (dice_num + player.at(c)->getlocation() >= board.getnum_space()) {
            int a = (dice_num + player.at(c)->getlocation()) / board.getnum_space();
            player.at(c)->changelocation((dice_num + player.at(c)->getlocation()) % board.getnum_space());
            int mmmoney = static_cast<Monopoly::Go*>(board.getboard().at(0).get())->getsalary();
            //change 1
            if (player.at(c)->getlocation() == 0) {
                player.at(c)->add_money(rules->getLand_on_go() * mmmoney);
                player.at(c)->add_money(mmmoney * (a - 1));
            } else{
                player.at(c)->add_money(mmmoney * a);
            }
        } else{
            player.at(c)->changelocation(dice_num + player.at(c)->getlocation());
        }
        int loaction =  player.at(c)->getlocation(); //assign the index of spaces to a shorter variable

        //      Second, check which type the player landed on
        if (board.getboard().at(loaction)->getSpaceType() == "Property") {
            landed_on_property(board, player, gamestate, dice, rules, c, loaction);

        } else if (board.getboard().at(loaction)->getSpaceType() == "FreeParking"){
            if (static_cast<Monopoly::Freeparking*>(board.getboard().at(loaction).get())->getpublic_money() > 0) {
                std::cout << player.at(c)->getName() <<" got $" <<  static_cast<Monopoly::Freeparking*>(board.getboard().at(loaction).get())->getpublic_money() <<" for landing on " << board.getboard().at(loaction)->getname();
                static_cast<Monopoly::Freeparking*>(board.getboard().at(loaction).get())->activate(player.at(c));
                for (int i = 0; i < board.getnum_space(); i++) {
                    if (board.getboard().at(i)->getSpaceType() == "FreeParking") {
                        static_cast<Monopoly::Freeparking*>(board.getboard().at(i).get())->setpublic_money(0);
                    }
                }
            }

        } else if (board.getboard().at(loaction)->getSpaceType() == "Pay"){
            int temp_sum = static_cast<Monopoly::Pay*>(board.getboard().at(loaction).get())->getsum();
             if (temp_sum > player.at(c)->getMoney()) {
             check_anything_to_sell(gamestate, board, player, c, loaction, rules, temp_sum, 1);
             } else{
                 static_cast<Monopoly::Pay*>(board.getboard().at(loaction).get())->activate(player.at(c));
                 std::cout << player.at(c)->getName() << " paid the bank $"<< temp_sum << " for landing on " << board.getboard().at(loaction)->getname() << std::endl;
                 if (rules->getFree_parking() == 'Y') {
                     for (int i = 0; i < board.getnum_space(); i++) {
                         if (board.getboard().at(i)->getSpaceType() == "FreeParking") {
                             static_cast<Monopoly::Freeparking*>(board.getboard().at(i).get())->setpublic_money(temp_sum + static_cast<Monopoly::Freeparking*>(board.getboard().at(i).get())->getpublic_money());
                         }
                     }
                 }
             }
        } else if (board.getboard().at(loaction)->getSpaceType() == "GoToJail"){

            int temp_jail = static_cast<Monopoly::GoToJail*>(board.getboard().at(loaction).get())->getindex_of_jail();
            player.at(c)->changelocation(temp_jail);
            std::cout << player.at(c)->getName() << ", you were sent to " << static_cast<Monopoly::Jail*>(board.getboard().at(temp_jail).get())->getname() << " for " << static_cast<Monopoly::Jail*>(board.getboard().at(temp_jail).get())->getTurns_spent() << " turns" << std::endl;
            player.at(c)->setwhether_in_jail(true);
            player.at(c)->setturns_in_jail(static_cast<Monopoly::Jail*>(board.getboard().at(temp_jail).get())->getTurns_spent());
        }
    } else {
        player.at(c)->reduce_turns_in_jail();
         std::cout << "You are still stuck in jail" << std::endl;
        /*
        if (player.at(c)->getturns_in_jail() == 0) {
            if (player.at(c)->getMoney() <= static_cast<Monopoly::Jail*>(board.getboard().at(player.at(c)->getlocation()).get())->getPayed_to_getout()){
                check_anything_to_sell(gamestate, board, player, c, player.at(c)->getlocation(), rules, static_cast<Monopoly::Jail*>(board.getboard().at(player.at(c)->getlocation()).get())->getPayed_to_getout(), 3);
            }
        } else{
             std::cout << "You are still stuck in jail" << std::endl;
        }*/

    }
}

void Monopoly::command_1(Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, Monopoly::Gamestate& gamestate, Monopoly::Diceroller dice, std::unique_ptr<Monopoly::Rules>& rules, int c){
    int a = 0, b = 0;
    dice.pick_up_random(a, b);
    Monopoly::check_reroll(gamestate, rules->getmax_double_roll(), a, b);
    int dice_num = a%6 + b%6 + 2;
    std::cout << player.at(c)->getName()<< ", you rolled a " << dice_num << std::endl;
    //      First, move the location. During the move, see if the player move over Go. If move
    //      over, add money to the player
    if (dice_num + player.at(c)->getlocation() >= board.getnum_space()) {
        int a = (dice_num + player.at(c)->getlocation()) / board.getnum_space();
        player.at(c)->changelocation((dice_num + player.at(c)->getlocation()) % board.getnum_space());
        int mmmoney = static_cast<Monopoly::Go*>(board.getboard().at(0).get())->getsalary();
        //change 1
        if (player.at(c)->getlocation() == 0) {
            player.at(c)->add_money(rules->getLand_on_go() * mmmoney);
            player.at(c)->add_money(mmmoney * (a - 1));
        } else{
            player.at(c)->add_money(mmmoney * a);
        }
    } else{
        player.at(c)->changelocation(dice_num + player.at(c)->getlocation());
    }
    int loaction =  player.at(c)->getlocation(); //assign the index of spaces to a shorter variable

    //      Second, check which type the player landed on
    if (board.getboard().at(loaction)->getSpaceType() == "Property") {
        landed_on_property(board, player, gamestate, dice, rules, c, loaction);


    } else if (board.getboard().at(loaction)->getSpaceType() == "FreeParking"){
        if (static_cast<Monopoly::Freeparking*>(board.getboard().at(loaction).get())->getpublic_money() > 0) {
            std::cout << player.at(c)->getName() <<" got $" <<  static_cast<Monopoly::Freeparking*>(board.getboard().at(loaction).get())->getpublic_money() <<" for landing on " << board.getboard().at(loaction)->getname();
            static_cast<Monopoly::Freeparking*>(board.getboard().at(loaction).get())->activate(player.at(c));
            for (int i = 0; i < board.getnum_space(); i++) {
                if (board.getboard().at(i)->getSpaceType() == "FreeParking") {
                    static_cast<Monopoly::Freeparking*>(board.getboard().at(i).get())->setpublic_money(0);
                }
            }
        }

        /*
         if (static_cast<Monopoly::FreeParking*>(board.getboard().at(loaction).get())->getmoney_pool() > 0) {
         std::cout << player.at(c)->getName() <<" got $" <<  static_cast<Monopoly::FreeParking*>(board.getboard().at(loaction).get())->getmoney_pool() <<" for landing on " << board.getboard().at(loaction)->getname();
         static_cast<Monopoly::FreeParking*>(board.getboard().at(loaction).get())->activate(player.at(c));

         }
         */
    } else if (board.getboard().at(loaction)->getSpaceType() == "Pay"){
        int temp_sum = static_cast<Monopoly::Pay*>(board.getboard().at(loaction).get())->getsum();
        if (temp_sum > player.at(c)->getMoney()) {
            check_anything_to_sell(gamestate, board, player, c, loaction, rules, temp_sum, 1);
        } else{
            static_cast<Monopoly::Pay*>(board.getboard().at(loaction).get())->activate(player.at(c));
            std::cout << player.at(c)->getName() << " paid the bank $"<< temp_sum << " for landing on " << board.getboard().at(loaction)->getname() << std::endl;
            if (rules->getFree_parking() == 'Y') {
                for (int i = 0; i < board.getnum_space(); i++) {
                    if (board.getboard().at(i)->getSpaceType() == "FreeParking") {
                        static_cast<Monopoly::Freeparking*>(board.getboard().at(i).get())->setpublic_money(temp_sum +static_cast<Monopoly::Freeparking*>(board.getboard().at(i).get())->getpublic_money());
                    }
                }
            }
        }
    } else if (board.getboard().at(loaction)->getSpaceType() == "GoToJail"){

        int temp_jail = static_cast<Monopoly::GoToJail*>(board.getboard().at(loaction).get())->getindex_of_jail();
        player.at(c)->changelocation(temp_jail);
        std::cout << player.at(c)->getName() << ", you were sent to " << static_cast<Monopoly::Jail*>(board.getboard().at(temp_jail).get())->getname() << " for " << static_cast<Monopoly::Jail*>(board.getboard().at(temp_jail).get())->getTurns_spent() << " turns" << std::endl;
        player.at(c)->setwhether_in_jail(true);
        player.at(c)->setturns_in_jail(static_cast<Monopoly::Jail*>(board.getboard().at(temp_jail).get())->getTurns_spent());
    }

    //this works when player reroll
    if (gamestate.getcurrent_reroll() > 0) {
        Monopoly::a_person_play(board, player, gamestate, dice, rules);
    }
}


void Monopoly::landed_on_property(Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, Monopoly::Gamestate& gamestate, Monopoly::Diceroller dice, std::unique_ptr<Monopoly::Rules>& rules, int c, int loaction){
    if (board.getboard().at(loaction)->getOwner() == "None" || board.getboard().at(loaction)->getOwner() == player.at(c)->getName()) {
        //nobody owns the property or oneself owns it
        Monopoly::buy_property(board, rules, player, c, loaction);
    }
    else {
        //somebody owns it and the player pays rent
        Monopoly::pay_rent(gamestate, board, player, c, loaction, rules);
    }
}


void Monopoly::sell_update(Monopoly::Board& board, std::unique_ptr<Monopoly::Rules>& rules, std::string name, std::vector<std::unique_ptr<Monopoly::Player> >& player, int c){
    std::cout << "Which property do you want to downgrade?" << std::endl;
    int big_setid = 0;
    for (int i = 1; i < board.getnum_space(); i++) {
//change 4
        if (static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getsetid() > big_setid) {
            big_setid = static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getsetid();
        }
    } //get the biggest setid for use
    int count_set = 0, count_own = 0;
    std::vector<int> a;
    
    //super long for loop
    for (int k = 0; k <= big_setid; k++) {
        // check which set of properties the player can downgrade
        for (int i = 1; i < board.getnum_space(); i++) {
            if (static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getsetid() == k) {
//change 5
                count_set++;
                if (board.getboard().at(i)->getOwner() == name) {
                    count_own++;
                }
            }
        }
        // if the set can be downgrade
        if (count_set == count_own) {
            // put the set into the vector that will be printed
            for (int m = 0; m <= count_set - 1; m++) {
                for (int i = 1; i < board.getnum_space(); i++) {
                    if (static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getsetid() == k && static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getintrasetid() == m) {
//change 6
                        if (board.getboard().at(i)->getupgrade_house() > 0 || board.getboard().at(i)->getupgrade_hotel() > 0) {
                            a.push_back(i);
                        }
                    }
                }
            }
            // if need to be build evenly
            if (rules->getBuild_evenly() == 'y' || rules->getBuild_evenly() == 'Y' ) {
                // erase the properties that has less upgrades than others from the vector
                int large = 0;
                for (int l = 0; l < (int)a.size(); l++) {
                    int lalala = board.getboard().at(a.at(l))->getupgrade_hotel();
                    if (lalala * rules->getHouses_before_hotels() + lalala + board.getboard().at(a.at(l))->getupgrade_house() > large && static_cast<Monopoly::Property*>(board.getboard().at(a.at(l)).get())->getsetid() == k){
//change 7
                        large = lalala * rules->getHouses_before_hotels() + lalala + board.getboard().at(a.at(l))->getupgrade_house();
                    }
                }  //find the largest numbers
                
                int w = 0;
                do {
                    int lalala = board.getboard().at(a.at(w))->getupgrade_hotel();
                    if (lalala * rules->getHouses_before_hotels() + lalala + board.getboard().at(a.at(w))->getupgrade_house() < large && static_cast<Monopoly::Property*>(board.getboard().at(a.at(w)).get())->getsetid() == k) {
//change 8
                        a.erase(a.begin() + w);
                        w--;
                    }
                    w++;
                } while (w < (int)a.size());

            } //build evenly
            
        } //if (count_set == count_own)
        count_set = 0;
        count_own = 0;
    }
    
    //print
    for (int i = 0; i < (int)a.size(); i++) {
        std::cout << i << ". " << board.getboard().at(a.at(i))->getname() << " [$";
        if (board.getboard().at(a.at(i))->getupgrade_hotel() > 0) {
            int cost = static_cast<Monopoly::Property*>(board.getboard().at(a.at(i)).get())->getHotel_cost() / 2;
            std::cout << cost << "]" <<std::endl;
        } else {
            std::cout << static_cast<Monopoly::Property*>(board.getboard().at(a.at(i)).get())->getHouse_cost() / 2 << "]" <<std::endl;
        }
    }
    std::cout << "Your choice: ";
    int choice = -1;
    std::cin >> choice;
    if (board.getboard().at(a.at(choice))->getupgrade_hotel() > 0) {
        board.getboard().at(a.at(choice))->downgrade(rules->getHouses_before_hotels());
        player.at(c)->add_money(static_cast<Monopoly::Property*>(board.getboard().at(a.at(choice)).get())->getHotel_cost() / 2);
    } else{
        board.getboard().at(a.at(choice))->downgrade(rules->getHouses_before_hotels());
        player.at(c)->add_money(static_cast<Monopoly::Property*>(board.getboard().at(a.at(choice)).get())->getHouse_cost() / 2);
    }
}



void Monopoly::buy_update(Monopoly::Board& board, std::unique_ptr<Monopoly::Rules>& rules, std::string name, std::vector<std::unique_ptr<Monopoly::Player> >& player, int c){
    std::cout << "Which property do you want to upgrade?" << std::endl;
    int big_setid = 0;
    for (int i = 1; i < board.getnum_space(); i++) {
        if (static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getsetid() > big_setid) {
            big_setid = static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getsetid();
        }
    } //get the biggest setid for use
    int count_set = 0, count_own = 0;
    std::vector<int> a;

    //super long for loop
    for (int k = 0; k <= big_setid; k++) {
        // check which set of properties the player can update
        for (int i = 1; i < board.getnum_space(); i++) {
            if (static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getsetid() == k) {
                count_set++;
                if (board.getboard().at(i)->getOwner() == name) {
                    count_own++;
                }
            }
        }
        // if the set can be update
        if (count_set == count_own) {
            // put the set into the vector that will be printed
            for (int m = 0; m <= count_set - 1; m++) {
                for (int i = 1; i < board.getnum_space(); i++) {
                    if (static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getsetid() == k && static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getintrasetid() == m && board.getboard().at(i)->getupgrade_hotel() == 0) {
                        a.push_back(i);
                    }
                }
            }
            // if need to be build evenly
            if (rules->getBuild_evenly() == 'y' || rules->getBuild_evenly() == 'Y' ) {
                // erase the properties that has more upgrades than others from the vector
                int small = 100;
                for (int w = 0; w < (int)a.size(); w++) {
                    if (static_cast<Monopoly::Property*>(board.getboard().at(a.at(w)).get())->getsetid() == k && board.getboard().at(a.at(w))->getupgrade_house() < small) {
                        small = board.getboard().at(a.at(w))->getupgrade_house();
                    }
                }

                int w = 0;
                do {
                    if (board.getboard().at(a.at(w))->getupgrade_house() > small && static_cast<Monopoly::Property*>(board.getboard().at(a.at(w)).get())->getsetid() == k) {
                        a.erase(a.begin() + w);
                        w--;
                    }
                    w++;
                } while (w < (int)a.size());

            } //build evenly

        } //if (count_set == count_own)
        count_set = 0;
        count_own = 0;
    }
    if (a.size() > 0) {
        //print
        for (int i = 0; i < (int)a.size(); i++) {
            std::cout << i << ". " << board.getboard().at(a.at(i))->getname() << " [$";
            if (board.getboard().at(a.at(i))->getupgrade_house() == rules->getHouses_before_hotels()) {
                int cost = static_cast<Monopoly::Property*>(board.getboard().at(a.at(i)).get())->getHotel_cost();
                std::cout << cost << "]" <<std::endl;
            } else {
                std::cout << static_cast<Monopoly::Property*>(board.getboard().at(a.at(i)).get())->getHouse_cost() << "]" <<std::endl;
            }
        }
        std::cout << "Your choice: ";
        int choice = -1;
        std::cin >> choice;
        if (board.getboard().at(a.at(choice))->getupgrade_house() == rules->getHouses_before_hotels()) {
            if (player.at(c)->getMoney() >= static_cast<Monopoly::Property*>(board.getboard().at(a.at(choice)).get())->getHotel_cost()) {
                board.getboard().at(a.at(choice))->from_house_hotel(rules->getHouses_before_hotels());
                player.at(c)->buy_something(static_cast<Monopoly::Property*>(board.getboard().at(a.at(choice)).get())->getHotel_cost());
            }
        } else{
            if (player.at(c)->getMoney() >= static_cast<Monopoly::Property*>(board.getboard().at(a.at(choice)).get())->getHouse_cost()) {

                board.getboard().at(a.at(choice))->from_house_hotel(rules->getHouses_before_hotels());
                player.at(c)->buy_something(static_cast<Monopoly::Property*>(board.getboard().at(a.at(choice)).get())->getHouse_cost());
            }
        }
    } else {
        std::cout << "You don't have any properties that you can upgrade" << std::endl;
    }

}

bool Monopoly::update_qulification(Monopoly::Board& board, std::string name){
    bool didadi = false;
    int big_setid = 0;
    for (int i = 1; i < board.getnum_space(); i++) {
        if (board.getboard().at(i)->getSpaceType() == "Property") {
            if (static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getsetid() > big_setid) {
                big_setid = static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getsetid();
            }
        }
    }
//change 7
    int count_set = 0, count_own = 0;
//    int temp = 0;
    for (int k = 0; k <= big_setid; k++) {
        for (int i = 1; i < board.getnum_space(); i++) {
            if (board.getboard().at(i)->getSpaceType() == "Property") {
                if (static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getsetid() == k) {
                    count_set++;
                    if (board.getboard().at(i)->getOwner() == name) {
                        count_own++;
                    }
                }
            }
        }
//        temp = 0;
        if (count_set == count_own) {
            didadi = true;
        } else {
            if (count_own > 0) {
                didadi = false;
                break;
            }
        }
        count_set = 0;
        count_own = 0;
    }
    return didadi;
} //end


void Monopoly::buy_property(Monopoly::Board& board, std::unique_ptr<Monopoly::Rules>& rules, std::vector<std::unique_ptr<Monopoly::Player>>& player, int c, int location){
    // declare temp varible to simplify coding
    int cost_of_proper = static_cast<Monopoly::Property*>(board.getboard().at(location).get())->getProperty_cost();
    std::string property_name = board.getboard().at(location)->getname();
    std::string player_name = player.at(c)->getName();

    if (board.getboard().at(location)->getOwner() == "None") {
        // nobody owns it so see if player owns enough to buy
        if (player.at(c)->getMoney() >= cost_of_proper) {
            // ask player if he/she wants buy it
            std::cout << "Would you like to buy " <<  property_name << " for $" << cost_of_proper << "?" << std::endl << "Rent on " << property_name <<" is $" << static_cast<Monopoly::Property*>(board.getboard().at(location).get())->getRent();
            std::cout << "Enter y for yes or n for no: ";
            char decision = ' ';
            std::cin >> decision;
            if (decision == 'y') {
                // Player buy the house
                std::cout << player_name << " bought " << property_name << " for $" << cost_of_proper << std::endl;
                board.getboard().at(location)->setOwner(player_name);
                player.at(c)->buy_something(cost_of_proper);
            } else {
                if (rules->getAuction() == 'Y') {
                    // the player choose no, so start auction
                    Monopoly::auction(board, player, c, location, property_name, cost_of_proper);
                }
            }
        } else {
            std::cout << player_name << ", you don't have enough money to afford " << property_name << ". " << property_name << " costs $" << cost_of_proper << " but you only have $" <<  player.at(c)->getMoney() <<std::endl ;
            if (rules->getAuction() == 'Y') {
                // the player choose no, so start auction
                Monopoly::auction(board, player, c, location, property_name, cost_of_proper);
            }
        }
    } else {
        std::cout << player_name << ", you landed on " << property_name << " which you already own" << std::endl;
    }
}
//acution needs change
void Monopoly::auction(Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player>>& player, int c, int location, std::string property_name, int cost_of_proper){
    std::cout << "Starting the auction for " << property_name << std::endl;
    std::cout << "No one has bid on " << property_name << " [$ " << cost_of_proper <<  "] yet" << std::endl;
    int current_bid = 0, mayb_valid_bid = 0;
    std::vector<int> player_code;
    for (int i = 0; i < player.at(0)->getPeople_left(); i++) {
        player_code.push_back(i);
    }
    int i = 0;
    do {
        std::cout << player.at(player_code.at(i))->getName() << ", enter a bid of at least $" << current_bid + 1 << " to bid on the property or a value less than that to leave the auction" << std::endl << "Your bid: ";
        std::cin >> mayb_valid_bid;
        if (current_bid == 0 && mayb_valid_bid <= current_bid) {
            player_code.erase(player_code.begin() + i);
            i--;
            if (player_code.size() >= 1) {
                std::cout << "No one has bid on " << property_name << " [$ " << cost_of_proper <<  "] yet" << std::endl;
            } else {
                std::cout << " No one decided to purchase "<< property_name << std::endl;
                break;
            }
        } else {
            if (mayb_valid_bid > current_bid) {
                if (player.at(player_code.at(i))->getMoney() < mayb_valid_bid) {
                    player_code.erase(player_code.begin() + i);
                } else {
                    current_bid = mayb_valid_bid;
                    if (player_code.size() <= 1) {
                        std::cout << player.at(player_code.at(i))->getName() << " won " << property_name  << " for $" << current_bid << std::endl;
                        board.getboard().at(location)->setOwner(player.at(player_code.at(i))->getName());
                        player.at(player_code.at(i))->buy_something(current_bid);
                        break;
                    } else {
                        std::cout << "The current bid for " << property_name << " [$ " << cost_of_proper <<  "] is $" << current_bid << " by " << player.at(player_code.at(i))->getName();
                    }
                }
            } else {
                player_code.erase(player_code.begin() + i);
                i--;

                if (player_code.size() == 1) {
                    std::cout << player.at(player_code.at(0))->getName() << " won " << property_name  << " for $" << current_bid << std::endl;
                    board.getboard().at(location)->setOwner(player.at(player_code.at(0))->getName());
                    player.at(player_code.at(0))->buy_something(current_bid);
                    break;
                } else {
                    int helpme = 0;
                    if (i < 0) {
                        helpme = (int)player_code.size() - 1;
                    } else {
                        helpme = i;
                    }
                    std::cout << "The current bid for " << property_name << " [$ " << cost_of_proper <<  "] is $" << current_bid << " by " << player.at(player_code.at(helpme))->getName();
                }
            }
        }
        i++;
        if (i >= (int)player_code.size()) {
            i = 0;
        }
    } while (player_code.size() > 0);
}



void Monopoly::pay_rent(Monopoly::Gamestate& gamestate, Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, int c, int location, std::unique_ptr<Monopoly::Rules>& rules){
    int temp_rent = static_cast<Monopoly::Property*>(board.getboard().at(location).get())->getRent();
    if (board.getboard().at(location)->getupgrade_house() > 0) {
        int num_house = board.getboard().at(location)->getupgrade_house();
        temp_rent = static_cast<Monopoly::Property*>(board.getboard().at(location).get())->getRent_house() * pow(2, num_house - 1);
    } else if(board.getboard().at(location)->getupgrade_hotel() > 0){
        int num_hotel = board.getboard().at(location)->getupgrade_hotel();
        temp_rent = static_cast<Monopoly::Property*>(board.getboard().at(location).get())->getRent_house() * pow(2, num_hotel - 1);
    } else{
        int whether_mutiply = Monopoly::if_mutiply_rent(board, player, c, location);
        if (whether_mutiply == 1) {
            temp_rent *= rules->getSet_mupltiper();
        }
    }
    if (player.at(c)->getMoney() >= temp_rent) {
        //can afford the rent so paid it
        player.at(c)->buy_something(temp_rent);
        for (int i = 0; i < player.at(0)->getPeople_left(); i++) {
            if (player.at(i)->getName() == board.getboard().at(location)->getOwner()) {
                player.at(i)->add_money(temp_rent);
                std::cout << player.at(c)->getName() << " paid " << player.at(i)->getName() << " $" << temp_rent << " for landing on " << board.getboard().at(location)->getname() << std::endl;
                break;
            }
        }
    } else{
        check_anything_to_sell(gamestate, board, player, c, location, rules, temp_rent, 0);
    }

}


void Monopoly::check_anything_to_sell(Monopoly::Gamestate& gamestate, Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, int c, int location, std::unique_ptr<Monopoly::Rules>& rules, int temp_rent, int player_or_bank){
    int temp = 0;
    //first check if there is any upgrades to sell
    for (int i = 1; i < board.getnum_space(); i++) {
        if (board.getboard().at(i)->getOwner() == player.at(c)->getName()) {
            if (board.getboard().at(i)->getupgrade_house() > 0 || board.getboard().at(i)->getupgrade_hotel() > 0) {
                temp++;
                break;
            }
        }
    }
    //if there is something to sell
    if (temp > 0) {
        std::cout << "You have $" << player.at(c)->getMoney() << " but you owe $" << temp_rent << std::endl <<"Pick an upgrade to sell to make up the difference" << std::endl;
        int big_setid = 0;
        for (int i = 1; i < board.getnum_space(); i++) {
            int temp_setid = static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getsetid();
            if (temp_setid > big_setid) {
                //change 2
                big_setid = temp_setid;
            }
        } //get the biggest setid for use
        int count_set = 0, count_own = 0;
        std::vector<int> a;

        //super long for loop
        for (int k = 0; k <= big_setid; k++) {
            // check which set of properties the player can downgrade
            for (int i = 1; i < board.getnum_space(); i++) {
                if (static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getsetid() == k) {
                    //change 3
                    count_set++;
                    if (board.getboard().at(i)->getOwner() == player.at(c)->getName()) {
                        count_own++;
                    }
                }
            }

            // if the set can be downgrade
            if (count_set == count_own) {
                // put the set into the vector that will be printed
                for (int m = 0; m <= count_set - 1; m++) {
                    for (int i = 1; i < board.getnum_space(); i++) {
                        if (static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getsetid() == k && static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getintrasetid() == m) {
                            //change 4
                            if (board.getboard().at(i)->getupgrade_house() > 0 || board.getboard().at(i)->getupgrade_hotel() > 0) {
                                a.push_back(i);
                            }
                        }
                    }
                }

                // if need to be build evenly
                if (rules->getBuild_evenly() == 'y' || rules->getBuild_evenly() == 'Y' ) {
                    // erase the properties that has less upgrades than others from the vector
                    int smallest = 0;
                    for (int l = 0; l < (int)a.size(); l++) {
                        if (board.getboard().at(a.at(l))->getupgrade_hotel() * rules->getHouses_before_hotels() + board.getboard().at(a.at(l))->getupgrade_house() > smallest){
                            smallest = board.getboard().at(a.at(l))->getupgrade_hotel() * rules->getHouses_before_hotels() + board.getboard().at(a.at(l))->getupgrade_house();
                        }
                    }  //find the largest numbers

                    for (int l = 0; l < (int)a.size(); l++) {
                        if (board.getboard().at(a.at(l))->getupgrade_hotel() * rules->getHouses_before_hotels() + board.getboard().at(a.at(l))->getupgrade_house() == smallest){
                            a.erase(a.begin() + l);
                        }
                    }  //erase the smallest numbers
                } //build evenly

            } //if (count_set == count_own)
            count_set = 0;
            count_own = 0;
        }

        //print
        for (int i = 0; i < (int)a.size(); i++) {
            std::cout << i << ". " << board.getboard().at(a.at(i))->getname() << " [$";
            if (board.getboard().at(a.at(i))->getupgrade_house() == rules->getHouses_before_hotels()) {
                int cost = static_cast<Monopoly::Property*>(board.getboard().at(a.at(i)).get())->getHotel_cost() / 2;
                std::cout << cost << "]" <<std::endl;
            } else {
                std::cout << static_cast<Monopoly::Property*>(board.getboard().at(a.at(i)).get())->getHouse_cost() / 2 << "]" <<std::endl;
            }
        }
        std::cout << "Your choice: ";
        int choice = -1;
        std::cin >> choice;
        int current = player.at(c)->getMoney() + static_cast<Monopoly::Property*>(board.getboard().at(a.at(choice)).get())->getHouse_cost() / 2;
        board.getboard().at(a.at(choice))->downgrade(rules->getHouses_before_hotels());
        if (current >= temp_rent) {
            player.at(c)->setMoney(0);
            if (player_or_bank == 0) {
                //pay to player
                for (int i = 0; i < player.at(0)->getPeople_left(); i++) {
                    if (player.at(i)->getName() == board.getboard().at(location)->getOwner()) {
                        player.at(i)->add_money(temp_rent);
                        std::cout << player.at(c)->getName() << " paid " << player.at(i)->getName() << " $" << temp_rent << " for landing on " << board.getboard().at(location)->getname() << std::endl;
                        break;
                    }
                }
            } else if (player_or_bank == 1){
                //pay to bank
                std::cout << player.at(c)->getName() << " paid bank $" << temp_rent << " for landing on " << board.getboard().at(location)->getname() << std::endl;
                static_cast<Monopoly::Pay*>(board.getboard().at(location).get())->activate(player.at(c));
            } else if(player_or_bank == 2){
                player.at(c)->setturns_in_jail(0);
                player.at(c)->setwhether_in_jail(false);
                std::cout << player.at(c)->getName() << " paid jail $" << temp_rent << " for landing on " << board.getboard().at(location)->getname() << std::endl;
            }
        } else if (current < temp_rent) {
            player.at(c)->setMoney(current);
            check_anything_to_sell(gamestate, board, player, c, location, rules, temp_rent, player_or_bank);
        }
    } else {
        //second part
        //nothing to sell
        //or after the selling still can't afford the rent so bankrupt
        if (player_or_bank == 0) {
            // pay to player
            for (int i = 0; i < player.at(0)->getPeople_left(); i++) {
                if (player.at(i)->getName() == board.getboard().at(location)->getOwner()) {
                    std::cout << player.at(c)->getName() << " went bankrupt to " << player.at(i)->getName() << " for landing on " << board.getboard().at(location)->getname() << std::endl;
                    player.at(i)->add_money(player.at(c)->getMoney());
                }
            }
            for (int i = 1; i < board.getnum_space(); i++) {
                if (board.getboard().at(i)->getOwner() == player.at(c)->getName()) {
                    board.getboard().at(i)->setOwner(board.getboard().at(location)->getOwner());
                }
            }

        } else if (player_or_bank == 1){
            //pay to bank
            std::cout << player.at(c)->getName() << " went bankrupt by landing on " << board.getboard().at(location)->getname() << std::endl;
        } else if (player_or_bank == 2){
            std::cout << player.at(c)->getName() << " went bankrupt when paying to leave jail"<< std::endl;
        }

        Monopoly::leave_game(gamestate, board, player, c);
    }
}

void Monopoly::leave_game(Monopoly::Gamestate& gamestate, Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, int c){
    for (int i = 1; i < board.getnum_space(); i++) {
        if (player.at(c)->getName() == board.getboard().at(i)->getOwner()) {
            board.getboard().at(i)->setOwner("None");
            board.getboard().at(i)->setupgrade_hotel(0);
            board.getboard().at(i)->setupgrade_house(0);
        }
    }
    player.erase(player.begin() + c);
    for (int i = 0; i < player.at(0)->getPeople_left(); i++) {
        player.at(i)->decrease_people();
    }
    gamestate.set_current(gamestate.getcurrent_player() - 1);
}


int Monopoly::if_mutiply_rent(Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, int c, int location){
    int k = 0, num = 0, whether_mutiply = 0;
    for (int i = 1; i < board.getnum_space(); i++) {
        if (static_cast<Monopoly::Property*>(board.getboard().at(i).get())->getsetid() == static_cast<Monopoly::Property*>(board.getboard().at(location).get())->getsetid()) {
            k++;
            if (board.getboard().at(location)->getOwner() == board.getboard().at(i)->getOwner()){
                num++;
            }
        }
    }
    if(k == num){
        whether_mutiply = 1;
    }
    return whether_mutiply;
}


//print board

void Monopoly::print_board(Monopoly::Board& board, std::vector <std::unique_ptr<Monopoly::Player> >& player, Monopoly::Gamestate& gamestate, int declare){
    int temp = 0;
    std::cout << "Space Number | "<< std::setw(board.getboard().at(0)->getmax_length()) << std::left << "Space Name" <<  " | " << std::setw(board.getboard().at(0)->getowner_length()) << std::left << "Owner" << " | Upgrades | Players " << std::endl;

    for (int i = 0; i < board.getnum_space(); i++) {
        temp = 0;
        std::cout << std::setw(13) << std::left << i;

        board.getboard().at(i)->display();

        for (int k = 0; k < player.at(0)->getPeople_left(); k++) {
            if (player.at(k)->getlocation() == i) {
                temp++;
                if (temp > 1) {
                    std::cout << ", ";
                }
                player.at(k)->print_player();
            }
        }
        std::cout << std::endl;
    }
    if (declare == 0) {
        std::cout << player.at(gamestate.getcurrent_player())->getName() << " please enter your move" << std::endl << "1 to roll dice" << std::endl << "2 to upgrade a property with a house or hotel" << std::endl << "3 to sell a house or hotel" << std::endl << "4 to leave the game" << std::endl << "Your move: ";
    }
}


