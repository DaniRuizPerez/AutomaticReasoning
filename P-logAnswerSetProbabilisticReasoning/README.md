Rock, paper, scissors, lizard, Spock (P-log)
============

This theorem proving assignment is one of the projects that I developed for the Knowledge Representation and Automatic Reasoning course in the junior year of my undergrad in computer science at UDC (Spain). It will check whether a conclusion follows from the premises using uses a theorem prover for Predicate Calculus called Prover9. This software accepts a list of formulas in First Order Logic and decides whether a formula is valid or not by refutation using resolution.


## Example theorems to prove:

- Scissors cut paper
- Paper covers rock
- Rock crushes lizard
- Lizard poisons Spock
- Spock smashes scissors
- Scissors decapitate lizard
- Lizard eats paper
- Paper disproves Spock
- Spock vaporizes rock
- Rock crushes scissors


Each of the player play in completely random ways.



## Example solution
For example, the shark problem looks like this:

```
formulas(assumptions).

all x (shark(x) -> -herb(x)).
exists x (fish(x)).
all x all y (shark(x) & fish(y) -> eats(x,y)).
all x (fish(x) -> animal(x)).
all x all y (herb(x) & animal(y) -> -eats(x,y)).

end_of_list.

formulas(goals).

all x (shark(x) -> -herb(x)).

end_of_list.
```

## Contact

Contact [Daniel Ruiz Perez](mailto:druiz072@fiu.edu) for requests, bug reports and good jokes.


## License

The software in this repository is available under the GNU General Public License, version 3. See the [LICENSE](https://github.com/DaniRuizPerez/TheoryOfComputationImplementations/blob/master/LICENSE) file for more information.
