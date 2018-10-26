//
//  Gamestate.hpp
//  Cboarding Update 1
//
//  Created by kevin on 2/16/18.
//  Copyright © 2018 kevin. All rights reserved.
//
#ifndef Gamestate_hpp
#define Gamestate_hpp

#include <iomanip>
#include <stdio.h>
#include "Player.hpp"
#include "Rules.hpp"
#include "Board.hpp"
//#include "FreeParking.hpp"
#include <map>
#include <math.h>
//#include "Space.hpp"
#include "Diceroller.hpp"
//#include "Property.hpp"

namespace Monopoly {
    class Gamestate{
    public:
        //setters
        void set_current(int k){
            Gamestate::current_player = k;
        }
        void setTurns(int turns) {
            Gamestate::turns = turns;
        }
        void setcurrent_reroll(int current_reroll) {
            Gamestate::current_reroll = current_reroll;
        }
        //getters
        int getTurns() const {
            return turns;
        }
        int getcurrent_player(){
            return current_player;
        }
        int getcurrent_reroll(){
            return current_reroll;
        }
        //others
        void next_palyer(){
            Gamestate::current_player++;
        }
        void add_turn(){
            turns++;
        }
        void add_current_reroll(){
            current_reroll++;
        }
        Gamestate();
    private:
        int current_player;
        int turns;
        int current_reroll;
    };
/*The program starts at the fuction "the_play_funtion".
it reads rules file into class rules, board file into class board, initialize the player class vector, the diceroller class, the gamestate class,
 then there is a main for loop do the main circulation from one player to another*/
    void the_play_funtion(char* rule_name, char* board_name, char* ran_name);
    //this function check if there will be several winners
    void muti_winner(Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, std::unique_ptr<Monopoly::Rules>& rules);


//Inside the loop, there are two fuctions: 1."print_board" : print the board
    void print_board(Monopoly::Board& board, std::vector <std::unique_ptr<Monopoly::Player> >& player, Monopoly::Gamestate& gamestate, int declare = 0);



//and 2."a_person_play", this one is the next main function does all the things a player may do, this one almost contain every functions
    void a_person_play(Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, Monopoly::Gamestate& gamestate, Monopoly::Diceroller dice, std::unique_ptr<Monopoly::Rules>& rules);
    void player_whether_in_jail(Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, Monopoly::Gamestate& gamestate, Monopoly::Diceroller dice, std::unique_ptr<Monopoly::Rules>& rules, int c);
    void command_1_in_jail(Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, Monopoly::Gamestate& gamestate, Monopoly::Diceroller dice, std::unique_ptr<Monopoly::Rules>& rules, int c);
    void command_1(Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, Monopoly::Gamestate& gamestate, Monopoly::Diceroller dice, std::unique_ptr<Monopoly::Rules>& rules, int c);
    void landed_on_property(Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, Monopoly::Gamestate& gamestate, Monopoly::Diceroller dice, std::unique_ptr<Monopoly::Rules>& rules, int c, int loaction);

    //-------------------------------------------------------------------
    // when the player enters 1, there will be a dice roll, and checking maybe the numbers are same so the player can roll again
    void check_reroll(Monopoly::Gamestate& gamestate, int max_double_roll, int& a, int& b);
    //then maybe he lands on an place where nobody owned, comes the function "buy_property", which ask player to buy property
    void buy_property(Monopoly::Board& board, std::unique_ptr<Monopoly::Rules>& rules, std::vector<std::unique_ptr<Monopoly::Player> >& player, int c, int location);
        // if the player chooses no, there will be an auction on that land for all players,
        // comes "auction" function
        void auction(Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player>>& player, int c, int location, std::string property_name, int cost_of_proper);
    //or he lands on a place another player owned, he will pay the rent
    void pay_rent(Monopoly::Gamestate& gamestate, Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, int c, int location, std::unique_ptr<Monopoly::Rules>& rules);
        //there are some rules about pay the rent, competled buy the function "if_mutiply_rent"
        int if_mutiply_rent(Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, int c, int location);


    //-------------------------------------------------------------------
    //if the player enters 2, first check if he can upgrade, then do the upgrade
    void buy_update(Monopoly::Board& board, std::unique_ptr<Monopoly::Rules>& rules, std::string name, std::vector<std::unique_ptr<Monopoly::Player> >& player, int c);
    bool update_qulification(Monopoly::Board& board, std::string name);




    //-------------------------------------------------------------------
    //if the player enters 3, first check if he can sell anty upgrade, if he can, the the next
    void check_anything_to_sell(Monopoly::Gamestate& gamestate, Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, int c, int location, std::unique_ptr<Monopoly::Rules>& rules, int temp_rent, int player_or_bank);
    void sell_update(Monopoly::Board& board, std::unique_ptr<Monopoly::Rules>& rules, std::string name, std::vector<std::unique_ptr<Monopoly::Player> >& player, int c);





    //-------------------------------------------------------------------
    //if the player enters 4, the player leaves the game
    void leave_game(Monopoly::Gamestate& gamestate, Monopoly::Board& board, std::vector<std::unique_ptr<Monopoly::Player> >& player, int c);



} //namespace
#endif /* Gamestate_hpp */

