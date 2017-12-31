8puzzle solver by heuristic search
============

This 8puzzle solver by heuristic search is one of the projects that I developed for the Intelligent Systems course in the sophomore year of my BSc in computer science at UDC (Spain). With the help of some code extracted directly from the Russell&Norvig03's book, my partner and I developed a suitable heuristic and Greedy, BSF, DSF and A* can be used to perform the search. The best heuristic tried was the taxicab distance (distance in rows plus distance in columns). The object of the puzzle is to place the tiles in order by making sliding moves that use the empty space


<p align="center">
<img src="https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/8PuzzleSolverHeuristic/8puzzle.png" width="500">
</p>




/*Ya que en costes almacenamos las distancias mínimas a las metas de casa posición, 
	consideramos una heurística basada en esa matriz, tal que la suma de los costes de
	las posiciones de todas las cajas es el valor de h*/

	

## Code explanation and domain creation

[search.c](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/8PuzzleSolverHeuristic/search.c) contains the generic code for tree search extracted directly from the Russell&Norvig03's Artificial Intelligence: A Modern Approach book. To construct the corresponding domain, it is necessary to define the functions specified in the [search.h](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/8PuzzleSolverHeuristic/search.h) file. The selected heuristic is the taxicab distance (distance in rows plus distance in columns)

[8puzzle.h](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/8PuzzleSolverHeuristic/8puzzle.h) contains the definition of the type tState (description of the state of a problem) and the actions we can execute (UP,DOWN,LEFT,RIGHT). [8puzzle.c](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/8PuzzleSolverHeuristic/8puzzle.c) contains the implementation for the functions described in [search.h](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/8PuzzleSolverHeuristic/search.h).

[search.c](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/8PuzzleSolverHeuristic/search.c) expects the domain definitions from the files domain.h and domain.c (that need to be generated). An option to change form one domain to another is to copy [8puzzle.h](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/8PuzzleSolverHeuristic/8puzzle.h) and [8puzzle.c](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/8PuzzleSolverHeuristic/8puzzle.c) to domain.h and domain.c respectively. With the [Makefile](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/8PuzzleSolverHeuristic/Makefile) we simplify the symbolic link creation process. To establish a domain, we execute:

```
make domain DOM=8puzzle
```
That creates the symbolic link, establishing 8puzzle as the domain. To compile the program we then just execute

```
make
```
Storing the executable in the file search.


## How to execute
The last command (make) will generate a file called "search". We have to execute that file with the following parameters:

- greedy
- depth
- breadth
- a-star
- tree
- graph






## Contact

Contact [Daniel Ruiz Perez](mailto:druiz072@fiu.edu) for requests, bug reports and good jokes.


## License

The software in this repository is available under the GNU General Public License, version 3. See the [LICENSE](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/LICENSE) file for more information.
