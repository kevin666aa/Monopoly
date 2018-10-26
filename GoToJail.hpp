//
//  GoToJail.hpp
//  Cboarding Update2
//
//  Created by kevin on 2/25/18.
//  Copyright © 2018 kevin. All rights reserved.
//

#ifndef GoToJail_hpp
#define GoToJail_hpp

#include <stdio.h>
#include "Space.hpp"
namespace Monopoly {
    class GoToJail: public Space{
    public:
        int getindex_of_jail() const{
            return index_of_jail;
        }
        void setindex_of_jail(int index_of_jail){
            GoToJail::index_of_jail = index_of_jail;
        }
        void activate(std::unique_ptr<Monopoly::Player>&  activationgPlayer){
             activationgPlayer->changelocation(index_of_jail);
        };
    private:
        int index_of_jail;
    };
}
#endif /* GoToJail_hpp */
