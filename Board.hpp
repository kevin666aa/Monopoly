//
//  Board.hpp
//  Cboarding Update 1
//
//  Created by kevin on 2/16/18.
//  Copyright © 2018 kevin. All rights reserved.
//

/*#include "Space.hpp"
 #include "Property.hpp"
 #include "Go.hpp"
 #include "FreeParking.hpp"
 #include "Pay.hpp"
 #include "Jail.hpp"
 #include "GoToJail.hpp"*/

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Space.hpp"
#include "Property.hpp"
#include "Go.hpp"
#include "Freeparking.hpp"
#include "Pay.hpp"
#include "Jail.hpp"
#include "GoToJail.hpp"
#include <vector>
#include <memory>
namespace Monopoly {
    class Board{
    public:
        Board();
        Board(char* board_name);//initialize

        int getnum_space() const{
            return Board::num_space;
        }
        void setnum_space(int num){
            Board::num_space = num;
        }
        std::vector<std::unique_ptr<Space> >& getboard(){
            return Board::board;
        }
        void vector_destroy();
    private:
        int num_space;
        std::vector<std::unique_ptr<Space> > board;
    };
}
#endif /* Board_hpp */
