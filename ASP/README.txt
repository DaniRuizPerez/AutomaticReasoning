P2 Answer Set Programming 2013-2014

Daniel Ruiz Pérez - d.ruiz.perez@udc.es
Isidro Alfaro Barbará - isidro.alfaro@udc.es

Introducción

Esta práctica consiste en la realización de un compositor automático de canon usando ASP(Answer Set Programming). 
Para ello se ha realizado un programa en python con el nombre canon.py que crea un canon ayudándose de los programas clasp y gringo.

Ficheros

canon.py : Fichero principal que realiza el canon de forma automática.
canon.txt : Contiene las reglas para la realización del canon.
preferences1.txt : Contiene las preferencias para la realización de un canon melódico.
input.txt : Contiene las voces y las notas que se tomarán de forma determinada para la realización del canon. 
output.txt : Contiene la salida del programa.

Ejecución

Para la ejecución del programa hay que tener instalados python, clasp y gringo. Una vez que se tenga instalados dichos programas podremos 
obtener nuestro canon ejecutando "python canon.py -v x -i archivo_input -p archivo_preferencias" donde x es el número de voces que deseamos obtener en nuestro canon. Si ejecutamos -l y tenemos lilypond en el path, generará el pdf y el midi. Archivo_input es el archivo en el cuál están las voces y las notas que se tomarán como entrada, por defecto a input.txt y archivo_preferencias es el archivo para las preferencias melódicas, por defecto a preferences_all.txt. El programa guardará la salida en el archivo output.txt el cuál contendrá el canon que se haya obtenido, en el caso de que se pueda llegar a alguna solución.
Para consultar las opciones del programa se puede utilizar la opción -h.


Opcional

Se ha realizado la parte opcional que consiste en obtener las notas en el pentagrama y el MIDI que se genera a partir de lo que se ha obtenido 
anteriormente y pasándoselo al lilypond. Para ello hay que utilizar el paramétro -l.
También se han realizado las preferencias melódicas que están contenidas en el fichero preferences1.txt.


Advertencia importante

Se ha considerado como responsabilidad del usuario el poner en el input notas cuando la voz correspondiente todavia no ha empezado a tocar. Esto causará un desplazamiento de la voz igual al numero de notas que el usuario ha decidido obligar a tocar aun que se pierdan las propiedades del canon.

También se ha considerado responsabilidad del usuario el hecho de poner un numero de voces y desplazamientos elevados y una duracion del canon pequeña. Esto ocasiona que a algunas voces nunca les toque empezar a tocar, y que el numero de silencios correspondientes se salga de la duración del canon.