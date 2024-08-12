all:
	clang++ -std=c++20 -o test test.cpp
	clang++ -std=c++20 -o test_best_hand test_best_hand.cpp
clean:
	rm -rf test
	rm -rf test_best_hand
