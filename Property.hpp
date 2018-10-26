//
//  Property.hpp
//  Cboarding Update 1
//
//  Created by kevin on 2/16/18.
//  Copyright © 2018 kevin. All rights reserved.
//

#ifndef Property_hpp
#define Property_hpp

#include <stdio.h>
#include "Space.hpp"

namespace Monopoly {
    class Property :public Space{
    public:
        int getsetid() const{
            return setid;
        }
        int getintrasetid() const{
            return intrasetid;
        }
        int getProperty_cost() const {
            return property_cost;
        }
        int getHouse_cost() const {
            return house_cost;
        }
        int getHotel_cost() const {
            return hotel_cost;
        }
        int getRent() const {
            return rent;
        }
        int getRent_house() const {
            return rent_house;
        }
        int getRent_hotel() const {
            return rent_hotel;
        }
        
    public:
        void setsetid(int setid){
            Property::setid = setid;
        }
        void setintrasetid(int intrasetid){
            Property::intrasetid = intrasetid;
        }
        void setProperty_cost(int property_cost) {
            Property::property_cost = property_cost;
        }
        void setHouse_cost(int house_cost) {
            Property::house_cost = house_cost;
        }
        void setHotel_cost(int hotel_cost) {
            Property::hotel_cost = hotel_cost;
        }
        void setRent(int rent) {
            Property::rent = rent;
        }
        void setRent_house(int rent_house) {
            Property::rent_house = rent_house;
        }
        void setRent_hotel(int rent_hotel) {
            Property::rent_hotel = rent_hotel;
        }
        void activate(std::unique_ptr<Monopoly::Player>&  activationgPlayer){};
    private:
        int setid;
        int intrasetid;
        int property_cost;
        int house_cost;
        int hotel_cost;
        int rent;
        int rent_house;
        int rent_hotel;
    };
}
#endif /* Property_hpp */
