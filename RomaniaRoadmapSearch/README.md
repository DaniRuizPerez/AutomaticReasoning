Romania Roadmap Search
============

This Romania roadmap search by heuristic is one of the projects that I developed for the Intelligent Systems course in the sophomore year of my BSc in computer science at UDC (Spain). With the help of some code extracted directly from the Russell&Norvig03's book, my partner and I developed a suitable heuristic and Greedy, BSF, DSF and A* can be used to perform the search. The objective is to find a route to Bucharest from Arad (preferably the shortest). The heuristic used was the straight distance.

<p align="center">
<img src="https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/RomaniaRoadmapSearch/romania.png" width="700">
</p>



## Code explanation and domain creation

[search.c](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/RomaniaRoadmapSearch/search.c) contains the generic code for tree search extracted directly from the Russell&Norvig03's Artificial Intelligence: A Modern Approach book. To construct the corresponding domain, it is necessary to define the functions specified in the [search.h](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/RomaniaRoadmapSearch/search.h) file. The selected heuristic is the straight distance.

[romania.h](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/RomaniaRoadmapSearch/romania.h) contains the definition of the type tState (description of the state of a problem) and the actions we can execute. [romania.c](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/RomaniaRoadmapSearch/romania.c) contains the implementation for the functions described in [search.h](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/RomaniaRoadmapSearch/search.h).

[search.c](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/RomaniaRoadmapSearch/search.c) expects the domain definitions from the files domain.h and domain.c (that need to be generated). An option to change form one domain to another is to copy [romania.h](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/RomaniaRoadmapSearch/romania.h) and [romania.c](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/RomaniaRoadmapSearch/romania.c) to domain.h and domain.c respectively. With the [Makefile](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/RomaniaRoadmapSearch/Makefile) we simplify the symbolic link creation process. To establish a domain, we execute:

```
make domain DOM=romania
```
That creates the symbolic link, establishing romania as the domain. To compile the program we then just execute

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
