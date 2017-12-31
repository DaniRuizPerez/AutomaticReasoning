Predicate Calculus Theorem Proving (using Prover9)
============

This 8puzzle solver by heuristic search is one of the projects that I developed for the Intelligent Systems course in the sophomore year of my BSc in computer science at UDC (Spain). With the help of some code extracted directly from the Russell&Norvig03's book, my partner and I developed a suitable heuristic and Greedy, BSF, DSF and A* can be used to perform the search.


photo




<table style="text-align: left;" border="0" cellspacing="2" cellpadding="2">
      <tbody>
        <tr>
          <td style="text-align: center; vertical-align: middle;">
          <table style="width: 78px; height: 79px; text-align: left; margin-left: auto; margin-right: auto;" border="1" cellspacing="2" cellpadding="2">
            <tbody>
              <tr>
                <td style="vertical-align: top;">&nbsp;1 <br>
                </td>
                <td style="vertical-align: top;">&nbsp;2 <br>
                </td>
                <td style="vertical-align: top;">&nbsp;3 <br>
                </td>
              </tr>
              <tr>
                <td style="vertical-align: top;">&nbsp;4 <br>
                </td>
                <td style="vertical-align: top;">&nbsp;5 <br>
                </td>
                <td style="vertical-align: top;">&nbsp;6 <br>
                </td>
              </tr>
              <tr>
                <td style="vertical-align: top;">&nbsp;7 <br>
                </td>
                <td style="vertical-align: top;">&nbsp;8 <br>
                </td>
                <td style="vertical-align: top;"><br>
                </td>
              </tr>
            </tbody>
          </table><br>

          </td>
          <td style="text-align: center; vertical-align: middle;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <br>
          </td>
          <td style="text-align: center; vertical-align: middle;">
          <table style="text-align: left; margin-left: auto; margin-right: auto;" border="1" cellspacing="2" cellpadding="2">
            <tbody>
              <tr>
                <td style="vertical-align: top;">&nbsp;4 <br>
                </td>
                <td style="vertical-align: top;">&nbsp;1 <br>
                </td>
                <td style="vertical-align: top;">&nbsp;3 <br>
                </td>
              </tr>
              <tr>
                <td style="vertical-align: top;">&nbsp;7 <br>
                </td>
                <td style="vertical-align: top;">&nbsp;2 <br>
                </td>
                <td style="vertical-align: top;">&nbsp;5 <br>
                </td>
              </tr>
              <tr>
                <td style="vertical-align: top;"><br>
                </td>
                <td style="vertical-align: top;">&nbsp;8 <br>
                </td>
                <td style="vertical-align: top;">&nbsp;6 <br>
                </td>
              </tr>
            </tbody>
          </table>
          <br>
          </td>
        </tr><tr>
          <td style="text-align: center; vertical-align: middle;">Estado inicial<br>
          </td>
          <td style="text-align: center; vertical-align: middle;"><br>
          </td>
          <td style="text-align: center; vertical-align: middle;">Estado meta<br>
          </td>
        </tr>

      </tbody>
    </table>

Uninformed search.

search.c contains the code for tree search extracted directly from the Russell&Norvig03's Artificial Intelligence: A Modern Approach book. To construct the corresponding domain, it is necesary to define the funtions specified in the search.h file.

8puzzle.h contains the definition of the type tState (description of the state of a problem) and the actions we can execute. 8puzzle.c contains the code for the functions described in search.h.

search.c expects the domain definitions from the files domain.h and domain.c. An option to change form one domain to another is to copy 8puzzle.h and 8puzzle.c to domain.h and domain.c respectively. With the makefile we simplify the symbolic link creation process. To stablish a domain, we execute:

```
make domain DOM=8puzzle
```
That creates the symbolic link, stablishing 8puzzle as the domain. To compile the program we then just execute

```
make
```
Storing the executable in the file search.


8puzzle.c y h son los domain.c y .h
greedy and A* breath depth


h is the heuristic function






## Contact

Contact [Daniel Ruiz Perez](mailto:druiz072@fiu.edu) for requests, bug reports and good jokes.


## License

The software in this repository is available under the GNU General Public License, version 3. See the [LICENSE](https://github.com/DaniRuizPerez/AutomaticReasoning/blob/master/LICENSE) file for more information.
