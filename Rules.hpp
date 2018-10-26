//
//  Rules.hpp
//  Cboarding Update 1
//
//  Created by kevin on 2/16/18.
//  Copyright © 2018 kevin. All rights reserved.
//


#ifndef Rules_hpp
#define Rules_hpp

#include <stdio.h>
#include <iostream>
#include <memory>
namespace Monopoly {
    class Rules{
    public: // Mutators
        Rules();
        void setStarting_cash(int starting_cash) {
            Rules::starting_cash = starting_cash;
        }
        void setTurn_limits(int turn_limits) {
            Rules::turn_limits = turn_limits;
        }
        void setPlayers_left_to_win(int players_left_to_win) {
            Rules::players_left_to_win = players_left_to_win;
        }
        void setSet_mupltiper(int set_mupltiper) {
            Rules::set_mupltiper = set_mupltiper;
        }
        void setHouses_before_hotels(int houses_before_hotels) {
            Rules::houses_before_hotels = houses_before_hotels;
        }
        void setBuild_evenly(char build_evenly) {
            Rules::build_evenly = build_evenly;
        }
        void setFree_parking(char free_parking) {
            Rules::free_parking = free_parking;
        }
        void setAuction(char auction) {
            Rules::auction = auction;
        }
        void setLand_on_go(int land_on_go) {
            Rules::land_on_go = land_on_go;
        }
        void setmax_double_roll(int max_double_roll) {
            Rules::max_double_roll = max_double_roll;
        }

    public: // Accessors
        int getStarting_cash() const {
            return starting_cash;
        }
        int getTurn_limits() const {
            return turn_limits;
        }
        int getPlayers_left_to_win() const {
            return players_left_to_win;
        }
        int getSet_mupltiper() const {
            return set_mupltiper;
        }
        int getHouses_before_hotels() const {
            return houses_before_hotels;
        }
        char getBuild_evenly() const {
            return build_evenly;
        }
        char getFree_parking() const {
            return free_parking;
        }
        char getAuction() const {
            return auction;
        }
        int getLand_on_go() const {
            return land_on_go;
        }
        int getmax_double_roll() const {
            return max_double_roll;
        }
    private:
        int starting_cash;
        int turn_limits;
        int players_left_to_win;
        int set_mupltiper;
        int houses_before_hotels;
        char build_evenly;
        char free_parking;
        char auction;
        int land_on_go;
        int max_double_roll;
    };
    void open_rules(char* rule_name, std::unique_ptr < Monopoly::Rules> & rules);
}
#endif /* Rules_hpp */

