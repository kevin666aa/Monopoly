//
//  Diceroller.hpp
//  Cboarding Update 1
//
//  Created by kevin on 2/16/18.
//  Copyright © 2018 kevin. All rights reserved.
//

#ifndef Diceroller_hpp
#define Diceroller_hpp

#include <cstdio>
namespace Monopoly {
    class Diceroller{
    public:
        void openfile(char* random_name){
            random = fopen(random_name, "r");
        } //open the file, initialize random pointer

        void pick_up_random(int& a, int& b){
            fscanf(random, "%d", &a);
            fscanf(random, "%d", &b);
        } //pick up random nums

        void closefile(){
            fclose(random);
            random = nullptr;
        } //close the file

    private:
        FILE* random;
    };
}
#endif /* Diceroller_hpp */
