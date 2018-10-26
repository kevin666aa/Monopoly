//
//  Pay.hpp
//  Cboarding Update2
//
//  Created by kevin on 2/25/18.
//  Copyright © 2018 kevin. All rights reserved.
//

#ifndef Pay_hpp
#define Pay_hpp

#include <stdio.h>
#include "Player.hpp"
#include "Space.hpp"

namespace Monopoly {
    class Pay: public Space {
    public:
        int getsum(){
            return sum;
        }
        void setsum(int sum){
            Pay::sum = sum;
        }
        void activate(std::unique_ptr<Monopoly::Player>& player){
            player->buy_something(Pay::sum);
        }
    private:
        int sum;
    };

 
}



#endif /* Pay_hpp */
