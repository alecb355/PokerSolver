# PokerSolver

## About
This project (for now) is a no-limit heads up post-flop Texas Hold 'Em solver. No-Limit means there aren't set bet sizes (you have the option to bet $1.00, $1.01, $2.43, etc). Heads up means there are only two players in the hand, the hero and the villain. Post-flop means it only analyzes after the first 3 cards of board are dealt. 

I hope to eventually expand to no-limit Texas Hold 'Em, as well as other poker variants such as Pot Limit Omaha and 2-7 Draw.

## Motivation
I've always been interested in poker theory and what optimal actions are in certain spots. Although this project isn't based around poker theory, I think it's really cool to find the optimal strategy and then reason why the strategy distribution is the way it is at a certain spot.

## Design Choices
Some of what we implemented could have just been usages of libraries, but I wanted to try writing (almost) everything from scratch. For example, we could have used a library to determine whether the hero or villain won the poker hand, but instead I wanted to write my own solution.

The algorithm we are using is Monte Carlo Counterfactual Regret Minimization
## Usage

### Currently not fully implemented, but eventually:

Run make to build the project. Then run the executable with the flop as an arg. Example:
```bash
./build/solver AsKdQs
```

To modify ranges, go to /src/main.cpp, and modify the lines below the comment:
```c++
// Change line below to modify player ranges
```