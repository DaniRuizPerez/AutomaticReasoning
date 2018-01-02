Sokoban solver by heuristic search
============

This sokoban puzzle solver by heuristic search is one of the projects that I developed for the Intelligent Systems course in the sophomore year of my BSc in computer science at UDC (Spain). With the help of some code extracted directly from the Russell&Norvig03's book, my partner and I developed the especific domain and a suitable heuristic. Greedy, BSF, DSF and A* can be used to perform the search. The objective is to move the player (@) UP, DOWN, LEFT, and RIGHT to collect the goals (.). The walls (#) can't be moved but the objects ($) can. The selected heuristic is minimum distances to the goals. This is a representation of one game:

							#####
							#   #####
							# # $ $ #
							# ..#   #
							## . $ ##
							 #  # @#
							 #######
	

## Code explanation and domain creation

[search.c](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/SokobanSolverHeuristic/search.c) contains the generic code for tree search extracted directly from the Russell&Norvig03's Artificial Intelligence: A Modern Approach book. To construct the corresponding domain, it is necessary to define the functions specified in the [search.h](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/SokobanSolverHeuristic/search.h) file. The selected heuristic is minimum distances to the goals.

[sokoban.h](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/SokobanSolverHeuristic/sokoban.h) contains the definition of the type tState (description of the state of a problem) and the actions we can execute (UP,DOWN,LEFT,RIGHT). [sokoban.c](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/SokobanSolverHeuristic/sokoban.c) contains the implementation for the functions described in [search.h](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/SokobanSolverHeuristic/search.h).

[search.c](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/SokobanSolverHeuristic/search.c) expects the domain definitions from the files domain.h and domain.c (that need to be generated). An option to change form one domain to another is to copy [sokoban.h](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/SokobanSolverHeuristic/sokoban.h) and [sokoban.c](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/SokobanSolverHeuristic/sokoban.c) to domain.h and domain.c respectively. With the [Makefile](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/SokobanSolverHeuristic/Makefile) we simplify the symbolic link creation process. To establish a domain, we execute:

```
make domain DOM=sokoban
```
That creates the symbolic link, establishing sokoban as the domain. To compile the program we then just execute

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
