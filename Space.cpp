//
//  Space.cpp
//  Cboarding Update 1
//
//  Created by kevin on 2/16/18.
//  Copyright © 2018 kevin. All rights reserved.
//

#include "Space.hpp"

Monopoly::Space::Space(){
    Space::name = " ";
    Space::owner  = "None";
    Space::upgrade_hotel = 0;
    Space::upgrade_house = 0;
}
//        setters
void Monopoly::Space::setupgrade_house(int upgrade_house){
    Space::upgrade_house =upgrade_house;
}
void Monopoly::Space::setupgrade_hotel(int upgrade_hotel){
    Space::upgrade_hotel = upgrade_hotel;
}
void Monopoly::Space::setname(std::string name){
    Space::name = name;
}
void Monopoly::Space::setOwner(const std::string &owner) {
    Space::owner = owner;
}
void Monopoly::Space::setSpaceType(const std::string &type){
    Space::spacetype = type;
}
//getters
int Monopoly::Space::getupgrade_house() const{
    return upgrade_house;
}
int Monopoly::Space::getupgrade_hotel() const{
    return upgrade_hotel;
}

void Monopoly::Space::from_house_hotel(int rules_before_hotel){
    upgrade_house++;
    if (upgrade_house > rules_before_hotel) {
        upgrade_house = 0;
        upgrade_hotel ++;
    }
}
void Monopoly::Space::downgrade(int rules_before_hotel) {
    if (upgrade_hotel > 0) {
        upgrade_hotel--;
        upgrade_house = rules_before_hotel;
    } else if(upgrade_house > 0){
        upgrade_house--;
    }
}

void Monopoly::Space::display(){
    std::cout << "| " << std::setw(max_length) << std::left << name << " | "<<  std::setw(owner_length) << std::left << owner << " | ";
    for (int k = 0; k < upgrade_hotel; k++) {
        std::cout << "H";
    }
    for (int m = 0; m < upgrade_house; m++) {
        std::cout << "h";
    }
    for (int l = 0; l < 8 - upgrade_house - upgrade_hotel; l++) {
        std::cout << " ";
    }
    std::cout << " | ";
}

int Monopoly::Space::max_length = 10;
void Monopoly::Space::setmax_length(int a){
    Space::max_length = a;
}
int Monopoly::Space::getmax_length(){
    return Space::max_length;
}

int Monopoly::Space::owner_length = 5;
void Monopoly::Space::setowner_length(std::vector <std::unique_ptr<Monopoly::Player> >& player){
    for (int i = 0; i < player.at(0)->getPeople_left(); i++) {
        if (static_cast<int>(player.at(i)->getName().length()) > owner_length) {
            owner_length = static_cast<int>(player.at(i)->getName().length());
        }
    }
}
int Monopoly::Space::getowner_length(){
    return owner_length;
}














