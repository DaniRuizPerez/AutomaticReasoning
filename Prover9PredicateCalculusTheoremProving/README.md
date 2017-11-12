Predicate Calculus Theorem Proving (using Prover9)
============

This theorem proving assignment is one of the projects that I developed for the Knowledge Representation and Automatic Reasoning course in the junior year of my undergrad in computer science at UDC (Spain). It will check whether a conclusion follows from the premises using uses a theorem prover for Predicate Calculus called Prover9. This software accepts a list of formulas in First Order Logic and decides whether a formula is valid or not by refutation using resolution.


## Example theorems to prove:
For every theorem, we have the file formatted in First Order Logic and another with the same name and with format .out that is the output of Prover9.

- Every poor man has a rich father. Thus, there is a rich man whose grandfather is rich. (file richman)
- An equivalence relation eq(x,y) satisfies the axioms of reflexivity, symmetry and transitivity. Prove that for two elements x, y that are not equivalent, there is no third element that is equivalent to both x and y.(file equivalence)
- Workers in a company dislike all rival companies. There is a worker whose boss likes everything. Then try to conclude that there is some company without rival companies. (file worker)
- An herbivore never eats animals. The shark eats fishes and, obviously, fishes are animals. Then, the shark cannot be an herbivore.(file shark)

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
