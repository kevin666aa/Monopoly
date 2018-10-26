hoarding.out : main.o Board.o Diceroller.o Gamestate.o Player.o Property.o Rules.o Space.o
	g++ main.o Board.o Diceroller.o Gamestate.o Player.o Property.o Rules.o Space.o -std=c++14 -o  hoarding.out

main.o : main.cpp Board.cpp Diceroller.cpp Gamestate.cpp Player.cpp Property.cpp Rules.cpp Space.cpp Board.hpp Diceroller.hpp Gamestate.hpp Player.hpp Property.hpp Rules.hpp Space.hpp
	g++ -Wall -Werror -std=c++14 -c main.cpp

Board.o : Board.cpp Board.hpp
	g++ -Wall -Werror -std=c++14 -c Board.cpp

Diceroller.o : Diceroller.cpp Diceroller.hpp
	g++ -Wall -Werror -std=c++14 -c Diceroller.cpp

Gamestate.o : Gamestate.cpp Gamestate.hpp
	g++ -Wall -Werror -std=c++14 -c Gamestate.cpp

Player.o : Player.cpp Player.hpp
	g++ -Wall -Werror -std=c++14 -c Player.cpp

Rules.o : Rules.cpp Rules.hpp
	g++ -Wall -Werror -std=c++14 -c Rules.cpp

Space.o : Space.cpp Space.hpp
	g++ -Wall -Werror -std=c++14 -c Space.cpp

Property.o : Property.cpp Property.hpp
	g++ -Wall -Werror -std=c++14 -c Property.cpp

Freeparking.o : FreeParking.cpp FreeParking.hpp
	g++ -Wall -Werror -std=c++14 -c FreeParking.cpp

Jail.o : Jail.cpp Jail.hpp
	g++ -Wall -Werror -std=c++14 -c Jail.cpp

Pay.o : Pay.cpp Pay.hpp
	g++ -Wall -Werror -std=c++14 -c Pay.cpp

GoToJail.o : GoToJail.cpp GoToJail.hpp
	g++ -Wall -Werror -std=c++14 -c GoToJail.cpp

clean:
	rm *.o hoarding.out
