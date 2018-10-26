//
//  Go.hpp
//  Cboarding Update2
//
//  Created by kevin on 2/25/18.
//  Copyright © 2018 kevin. All rights reserved.
//

#ifndef Go_hpp
#define Go_hpp

#include <stdio.h>
#include "Space.hpp"
namespace Monopoly {
    class Go: public Space{
    public:
        int getsalary(){
            return salary;
        }
        void setsalary(int salary){
            Go::salary = salary;
        }
        Go(){
            salary = 0;
        }
        void activate(std::unique_ptr<Monopoly::Player>&  activationgPlayer){};
    private:
        int salary;
    };
}

#endif /* Go_hpp */


