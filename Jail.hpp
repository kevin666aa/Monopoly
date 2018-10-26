//
//  Jail.hpp
//  Cboarding Update2
//
//  Created by kevin on 2/25/18.
//  Copyright © 2018 kevin. All rights reserved.
//

#ifndef Jail_hpp
#define Jail_hpp

#include <stdio.h>
#include "Space.hpp"
namespace Monopoly {
    class Jail: public Space{
    public:
        int getTurns_spent() const {
            return turns_spent;
        }

        int getPayed_to_getout() const {
            return payed_to_getout;
        }

        void setTurns_spent(int turns_spent) {
            Jail::turns_spent = turns_spent;
        }

        void setPayed_to_getout(int payed_to_getout) {
            Jail::payed_to_getout = payed_to_getout;
        }
        
        void activate(std::unique_ptr<Monopoly::Player>&  activationgPlayer){};

    private:
        int turns_spent;
        int payed_to_getout;
    };
}
#endif /* Jail_hpp */
