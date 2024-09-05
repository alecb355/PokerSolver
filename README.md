# PokerSolver

## About
This project (for now) is a limit head's up post-flop Texas Hold 'Em solver. Limit means there are set bet sizes (you dont have the option to bet $5, $5.01, ..., but instead only higher increments like $5, $10, ...). Heads up means there are only two players in the hand, the hero and the villain. Post-flop means it only analyzes after the first 3 cards of board are dealt. 

I hope to eventually expand to no-limit Texas Hold 'Em, as well as other poker variants such as Pot Limit Omaha and 2-7 Draw.

## Motivation
I've always been interested in poker theory and what optimal actions are in certain spots. Although this project isn't based around poker theory, I think it's really cool to find the optimal strategy and then reason why the strategy distribution is the way it is at a certain spot.

## Design Choices
Some of what we implemented could have just been usages of libraries, but I wanted to try writing (almost) everything from scratch. For example, we could have used a library to determine whether the hero or villain won the poker hand, but it was actually a very interesting problem, and I enjoyed coming up with my own efficient solution.

The algorithm we are using is Monte Carlo Counterfactual Regret Minimization
## Usage

### Currently not fully implemented, but eventially:

Navigate to /exec-PokerSolver (or tests if you want to run tests) and run 'make.' Run the executable with the flop as an arg. Example:
```bash
./solver AsKdQs
```

To modify ranges, go to /exec-PokerSolver/main.cpp, and modify the lines below the comment:
```c++
// Change line below to modify player ranges
```

## Project Layout
Layout generally follows Boris Kolpackov's template (https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1204r0.html)