Automatic Reasoning Projects 
============

This is a collection of projets that I developed for the Intelligent System and Knowledge Representation and Automatic Reasoning courses in the sophomore and junior years of my BS in computer science at UDC (Spain). The projects are the following:


- **Automated canon composer with multiple voices using Answer Set Programming** that takes into account many melodic restrictions and preferences. It uses the tools gringo, clasp, python and lilypond. A short example audio file is provided, created with one of the preference files provided. Using Python, clasp, gringo and lilypond.

- **Sokoban solver by heuristic search** that solves the sokoban game. With the help of some code extracted directly from the Russell&Norvig03's book, my partner and I developed the especific domain and a suitable heuristic. Greedy, BSF, DSF and A* can be used to perform the search. The objective is to move the player (@) UP, DOWN, LEFT, and RIGHT to collect the goals (.). The walls (#) can't be moved but the objects ($) can. The selected heuristic is minimum distances to the goals. 

- **Hitori Puzzle Solver** that transforms a simplified version of the Hitori puzzle into a set of CNF boolean clauses based on the rules of the game, calls a propositional satisfiability (SAT) solver and creates the solution. Using Python and picosat.

- **Probabilistic Reasoning with Answer Sets** that calculates the probabilities of different things happening on the Big Bang Theory game Rock, paper, scissors, lizard, Spock. Using P-log.

- **Theorem prover** project that checks whether a conclusion follows from the premises using a theorem prover for Predicate Calculus called Prover9. This software accepts a list of formulas in First Order Logic and decides whether a formula is valid or not by refutation using resolution.

- **8puzzle solver by heuristic search** that finds a solution for the game. With the help of some code extracted directly from the Russell&Norvig03's book, we developed the especific domain and a suitable heuristic. Greedy, BSF, DSF and A* can be used to perform the search. The best heuristic tried was the taxicab distance.

- **Romania Roadmap Search**  that finds a route to Bucharest from Arad (preferably the shortest). With the help of some code extracted directly from the Russell&Norvig03's book, we developed the especific domain and a suitable heuristic. Greedy, BSF, DSF and A* can be used to perform the search. The heuristic used was the straight distance.



## Contact

Contact [Daniel Ruiz Perez](mailto:druiz072@fiu.edu) for requests, bug reports and good jokes.


## License

The software in this repository is available under the GNU General Public License, version 3. See the [LICENSE](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/LICENSE) file for more information.
