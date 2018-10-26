//
//  Freeparking.hpp
//  Cboarding Update2
//
//  Created by kevin on 2/28/18.
//  Copyright © 2018 kevin. All rights reserved.
//

#ifndef Freeparking_hpp
#define Freeparking_hpp

#include <stdio.h>
#include "Space.hpp"
#include "Player.hpp"

namespace Monopoly {
    class Freeparking: public Space{
    public:
        int getpublic_money(){
            return public_money;
        }
        void setpublic_money(int testmoney){
            Freeparking::public_money = testmoney;
        }
        void activate(std::unique_ptr<Monopoly::Player>&  activationgPlayer){
            activationgPlayer->add_money(public_money);
        }
        Freeparking(){
            public_money = 0;
        }
    private:
        int public_money;
    };

}

#endif /* Freeparking_hpp */
