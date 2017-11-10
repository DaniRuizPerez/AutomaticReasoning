Answer Set Proramming Canon composer
============

The ASP Canon Composer is one of the projects that I developed for the Knowledge Representation and Automatic Reasoning course in the junior year of my undergrad in computer science at UDC (Spain). It is an automated canon composer with multiple voices using Answer Set Programming that takes into account many melodic restrictions and preferences. It uses the tools gringo, clasp, python and lilypond. A short example audio file is provided, created with one of the preference files provided.


## Canon and melodic restrictions and preferences

A canon is a technique for composing musical pieces with two or more simultaneous voices or melodies (polyphony). In a canon, an initial melody (called the leader or dux) is imitated by the other voices (called the followers or comes) that enter into play after a given duration or delay

- Restricted to the C major tonality
- 15 pitches from from g to g'' allowed
- All notes will have the same douration (quarter notes)
- 2 voices simple canon (leader and follower)
- The delay will be specified

It will have the following harmonic restrictions:
- notes played by the voices can't from a dissonance. The following combinations are forbiden: c-d, d-e, e-f, f-g, g-a, a-b, b-c 
- Leader and follower can't perform two consecutive  fifth intervals (when the distance between the lower higher pitch is 5)

And the following melodic preferences (if posible). Degrees for preferences can be varied for generating different solutions:
- Avoid unisons (both voices playing same note)
- Avoid repeating the last note
- Smaller melodic jumps are prefered
- The follower should play a lower pitch than the leader

## Input

First line of the input file is the length and the second line the delay for the second voice. Then a partial description of each voice with fixed notes and the composer will fill in the blanks (it can be completelly blank). Example:

```
8
4
c' -  e' -  -  -  -  g'
-  -  -  -  -  -  -  c' 
```

## Output

The output is an ASCI file like this:
```
8
4
c' d' e' c' e' f' g' g'
-  -  -  -  c' d' e' c' 
```
Also, the software Lilypond can be used to generate a music file that can be listened to.


## How to execute

The following software is needed:
- Python
- clasp
- gringo
- lilypond (optional)

The pythong file canon.py can be executed with the following commands:

	-v x : Determine x number of voices
	-i file : To stablish the base file for the canon
	-p file : To stablish the preference file
	-l : To stablish if Lilypond should be called to generate the audio file
	-h : Shows help
As default, input = input.txt and preferences = preferences1.txt"""


## Contact

Contact [Daniel Ruiz Perez](mailto:druiz072@fiu.edu) for requests, bug reports and good jokes.


## License

The software in this repository is available under the GNU General Public License, version 3. See the [LICENSE](https://github.com/DaniRuizPerez/TheoryOfComputationImplementations/blob/master/LICENSE) file for more information.
