//
//  Player.hpp
//  Cboarding Update 1
//
//  Created by kevin on 2/16/18.
//  Copyright © 2018 kevin. All rights reserved.
//


#ifndef Player_hpp
#define Player_hpp

#include <cstdio>
#include <iostream>
#include <string>
#include "Rules.hpp"
#include <vector>
#include <memory>
namespace Monopoly {
    class Player{
    public:
        Player();
        
        int getPeople_left();
        void setpeople_left(int people_left);
        void decrease_people();
        //  getters
        const std::string &getName() const {
            return name;
        }

        int getMoney() const {
            return money;
        }

        int getID() const {
            return ID;
        }
        int getlocation() const {
            return location;
        }
        //  setters
        void setName(const std::string &name) {
            Player::name = name;
        }
        void setMoney(int money) {
            Player::money = money;
        }
        void setID(int ID) {
            Player::ID = ID;
        }
        //  others
        void changelocation(int dice_num){
            Player::location = dice_num;
        }
        void add_money(int cash){
            Player::money += cash;
        }
        void print_player() const{
            std::cout << "[" << name << " : $" << money << "]";
        };
        void buy_something(int cost){
            money -= cost;
        }
        void setturns_in_jail(int turns){
            Player::turns_in_jail = turns;
        }
        int getturns_in_jail(){
            return Player::turns_in_jail;
        }
        void reduce_turns_in_jail(){
            Player::turns_in_jail--;
        }


        void setwhether_in_jail(bool aa){
            Player::whether_in_jail = aa;
        }
        int getwhether_in_jail(){
            return Player::whether_in_jail;
        }
    private:
        int people_left;
        std::string name;
        int money;
        int ID;
        int location;

        int turns_in_jail;
        bool whether_in_jail;
    };

    void setupPlayer(std::vector <std::unique_ptr < Monopoly::Player> >& player, const std::unique_ptr<Monopoly::Rules>& rules);
}
#endif /* Player_hpp */

