//
//  Player.cpp
//  Cboarding Update 1
//
//  Created by kevin on 2/16/18.
//  Copyright © 2018 kevin. All rights reserved.
//

#include "Player.hpp"

Monopoly::Player::Player(){
    Player::location = 0;
}

int Monopoly::Player::getPeople_left() {
    return people_left;
}
void Monopoly::Player::decrease_people(){
    people_left = people_left - 1;
}
void Monopoly::Player::setpeople_left(int people_left){
    Player::people_left = people_left;
}


void Monopoly::setupPlayer(std::vector <std::unique_ptr < Monopoly::Player>>& player, const std::unique_ptr<Monopoly::Rules>& rules){
    int num_player = 0;
    std::cout << "Enter how many players will be playing: ";
    std::cin >> num_player;
    player.resize(num_player);
    std::string name;
    for (int i = 0; i < num_player; i++) {
        std::cout << "Enter the name of player " << i+1 << ": ";
        std::cin >> name;
        player.at(i) = std::make_unique<Monopoly::Player>();
        player.at(i)->setName(name);
        player.at(i)->setID(i+1);
        player.at(i)->setMoney(rules->getStarting_cash());
        player.at(i)->setpeople_left(num_player);
        player.at(i)->setwhether_in_jail(false);
    }
}




