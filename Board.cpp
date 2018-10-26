//
//  Board.cpp
//  Cboarding Update2
//
//  Created by kevin on 2/25/18.
//  Copyright © 2018 kevin. All rights reserved.
//
//            std::cout << "check 2 begin" << std::endl;
//            std::cout << "check 2 end" << std::endl;
//            std::cout << "check 1 begin" << std::endl;
//            std::cout << "check 1 end" << std::endl;
#include "Board.hpp"

Monopoly::Board::Board(char* board_name){
    std::ifstream a;
    a.open(board_name);
    std::unique_ptr<Property> temp;
    std::unique_ptr<Freeparking> freeparking;
    std::unique_ptr<Pay> pay;

    std::unique_ptr<Go> go = std::make_unique<Go>();
    std::string line;
    std::getline(a, line, ',');std::getline(a, line, ',');
    int num = std::stoi(line);
    Monopoly::Board::setnum_space(num);
    std::getline(a, line);std::getline(a, line);std::getline(a, line);std::getline(a, line);
    std::getline(a, line, ',');std::getline(a, line, ',');
    go->setsalary(std::stoi(line));
    std::getline(a, line, ',');
    go->setname(line);
    Monopoly::Board::board.push_back(std::move(go));

    std::getline(a, line);
    //    Type,SetId,IntrasetId,Name,PropertyCost,HouseCost,Hotel
    //    Cost,Rent,Rent with House,Rent With Hotel
    for (int i = 1; i < num; i++) {
        std::getline(a, line, ',');
        if (line == "Property") {
            temp = std::make_unique<Monopoly::Property>();
            temp->setSpaceType(line);

            std::getline(a, line, ',');
            temp->setsetid(std::stoi(line));

            std::getline(a, line, ',');
            temp->setintrasetid(std::stoi(line));

            std::getline(a, line, ',');
            temp->setname(line);

            std::getline(a, line, ',');
            temp->setProperty_cost(std::stoi(line));

            std::getline(a, line, ',');
            temp->setHouse_cost(std::stoi(line));

            std::getline(a, line, ',');
            temp->setHotel_cost(std::stoi(line));

            std::getline(a, line, ',');
            temp->setRent(std::stoi(line));

            std::getline(a, line, ',');
            temp->setRent_house(std::stoi(line));

            std::getline(a, line);
            temp->setRent_hotel(std::stoi(line));

            Monopoly::Board::board.push_back(std::move(temp));
        } else if (line == "FreeParking"){
            freeparking = std::make_unique<Monopoly::Freeparking>();
            freeparking->setSpaceType(line);

            std::getline(a, line, ',');
            freeparking->setname(line);

            Monopoly::Board::board.push_back(std::move(freeparking));

            std::getline(a, line);
        } else if (line == "Pay"){
            pay = std::make_unique<Monopoly::Pay>();
            pay->setSpaceType(line);

            std::getline(a, line, ',');
            pay->setname(line);

            std::getline(a, line, ',');

            pay->setsum(std::stoi(line));
            Monopoly::Board::board.push_back(std::move(pay));

            std::getline(a, line);
        } else if (line == "Jail") {
            std::unique_ptr<Jail> jail = std::make_unique<Jail>();
            jail->setSpaceType(line);

            std::getline(a, line, ',');
            jail->setname(line);

            std::getline(a, line, ',');
            jail->setTurns_spent(std::stoi(line))
            ;
            std::getline(a, line, ',');
            jail->setPayed_to_getout(std::stoi(line));

            Monopoly::Board::board.push_back(std::move(jail));

            std::getline(a, line);
        } else if (line == "GoToJail") {
            std::unique_ptr<GoToJail> gotojail = std::make_unique<GoToJail>();
            gotojail->setSpaceType(line);

            std::getline(a, line, ',');
            gotojail->setname(line);

            std::getline(a, line, ',');
            gotojail->setindex_of_jail(std::stoi(line));

            Monopoly::Board::board.push_back(std::move(gotojail));

            std::getline(a, line);
        }
    }
    for (int i = 0; i < Monopoly::Board::num_space; i++) {
        if (static_cast<int>(Monopoly::Board::board.at(i)->getname().length()) > Monopoly::Board::board.at(i)->getmax_length()) {
            Monopoly::Board::board.at(i)->setmax_length(static_cast<int>(Monopoly::Board::board.at(i)->getname().length())) ;
        }
    }
    a.close();
}


void Monopoly::Board::vector_destroy(){
    for (int i = 0; i < num_space; i++) {
        board.at(i).release();
    }
    board.clear();
}

