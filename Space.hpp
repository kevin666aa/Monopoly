//
//  Space.hpp
//  Cboarding Update 1
//
//  Created by kevin on 2/16/18.
//  Copyright © 2018 kevin. All rights reserved.
//

#ifndef Space_hpp
#define Space_hpp

#include <cstdio>
#include<string>
#include <iomanip>
#include <iostream>
#include "Player.hpp"

namespace Monopoly {
    class Space{
    public:
        Space(); //default constructor
        //        setters
        void setupgrade_house(int upgrade_house);
        void setupgrade_hotel(int upgrade_hotel);
        void setname(std::string name);
        void setOwner(const std::string &owner);
        void setSpaceType(const std::string &type);
        //getters
        const std::string &getSpaceType() const{
            return spacetype;
        }
        const std::string &getOwner() const {
            return owner;
        }
        const std::string &getname() const{
            return name;
        }
        int getupgrade_house() const;
        int getupgrade_hotel() const;
        //
        void from_house_hotel(int rules_before_hotel);
        void downgrade(int rules_before_hotel);
        // static max space name length
        void setmax_length(int a);
        int getmax_length();

        // static max player name length
        void setowner_length(std::vector <std::unique_ptr<Monopoly::Player> >& player);
        int getowner_length();


        void display();
        virtual void activate(std::unique_ptr<Monopoly::Player>&  activationgPlayer) = 0;
        
    private:
        static int max_length;
        static int owner_length;
        std::string spacetype;
        std::string name;
        std::string owner;
        int upgrade_house;
        int upgrade_hotel;
    };
}
#endif /* Space_hpp */

