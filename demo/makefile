all: demo_hand demo_cshand demo_csgmp 

demo_hand: hand_demo.cpp ../src/HandBigInt.hpp
	g++ -fsanitize=address -Wfatal-errors -pedantic --std=c++17 -I../src hand_demo.cpp -o demo_hand

demo_cshand: cs_demo.cpp
	g++ -fsanitize=address -Wfatal-errors -pedantic --std=c++17 -I../src cs_demo.cpp ../src/BigIntegerHand.cpp -o demo_cshand

demo_csgmp: cs_demo.cpp
	g++ -fsanitize=address -Wfatal-errors -pedantic --std=c++17 -I../src cs_demo.cpp ../src/BigIntegerGMP.cpp -o demo_csgmp -lgmp -lgmpxx

clean:
	rm -f demo_*