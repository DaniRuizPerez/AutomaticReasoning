Rock, paper, scissors, lizard, Spock (P-log)
============

This Probabilistic Reasoning with Answer Sets assignment is one of the projects that I developed for the Knowledge Representation and Automatic Reasoning course in the junior year of my undergrad in computer science at UDC (Spain). It will calculate the probabilities of different things happening on the Big Bang Theory game Rock, paper, scissors, lizard, Spock. 

## Examplanation of the game:

The rules of the game are as follows:

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

## Probability calculations

With the file bigbang.txt and executing P-log we can calculate:

- The probability of winner(kooth).
- The probability of winner(kooth) conditioned to the observation play(sheldon)=rock.
- The probability of a  tie.
- The probability that someone marks scissors.

The results can be seen in the first part of the file obtained_result.txt.


## Anticipation variant

Suppose that Kooth is sometimes quick enough to see Sheldon making the "paper" sign. In fact, 2 of each 3 times, he is able to foresee Sheldon's "paper". In that case, Kooth always marks "scissors". We modeled this variant and recomputed the  probabilities above. The modeled domain can be seen in bigbang_variant.txt.

The results can be seen in the second part of the file obtained_result.txt.

Also, this is how the domain looks:

```
moves = {paper, scissors, rock, lizard, spock}.
players = {sheldon, kooth}.
#domain players(P1).
#domain players(P2).
#domain moves(X).
tie : boolean.
play:players -> moves.

[r] random(play(sheldon)).
[r1] random(play(kooth)).

defeat(paper,rock).
defeat(paper,spock).
defeat(scissors,paper).
defeat(scissors,lizard).
defeat(rock,lizard).
defeat(rock,scissors).
defeat(lizard,spock).
defeat(lizard,paper).
defeat(spock,scissors).
defeat(spock,rock).

winner=P1 :- play(P1)=X,play(P2)=Y,defeat(X,Y).
tie :- play(P1)=X,play(P2)=X,P1<>P2.

pscissors :- play(P1)=scissors.

[r1] pr(play(kooth) = scissors|play(sheldon)=paper)=2/3.

%?{winner=kooth}.
%?{winner=kooth}|obs(play(sheldon)=rock).
%?{pscissors}.
?{tie}.

%?{winner=kooth}|obs(play(sheldon)=paper).

```

## Tools
You need the following tools

- P-log
- lparse
- smodels
- bison/yacc

And to run the software, just execute  ```plog -t filename.txt```


## Contact

Contact [Daniel Ruiz Perez](mailto:druiz072@fiu.edu) for requests, bug reports and good jokes.


## License

The software in this repository is available under the GNU General Public License, version 3. See the [LICENSE](https://github.com/DaniRuizPerez/TheoryOfComputationImplementations/blob/master/LICENSE) file for more information.
