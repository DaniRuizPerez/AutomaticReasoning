import subprocess
import os
import sys

def to_number(note):
	if note == "g":
		return 1
	elif note == "a":
		return 2
	elif note == "b":
		return 3
	elif note == "c'":
		return 4
	elif note == "d'":
		return 5
	elif note == "e'":
		return 6
	elif note == "f'":
		return 7
	elif note == "g'":
		return 8
	elif note == "a'":
		return 9
	elif note == "b'":
		return 10
	elif note == "c''":
		return 11
	elif note == "d''":
		return 12
	elif note == "e''":
		return 13
	elif note == "f''":
		return 14
	elif note == "g''":
		return 15

def to_note(note):
	if note == 1:
		return "g"
	elif note == 2:
		return "a"
	elif note == 3:
		return "b"
	elif note == 4:
		return "c'"
	elif note == 5:
		return "d'"
	elif note == 6:
		return "e'"
	elif note == 7:
		return "f'"
	elif note == 8:
		return "g'"
	elif note == 9:
		return "a'"
	elif note == 10:
		return "b'"
	elif note == 11:
		return "c''"
	elif note == 12:
		return "d''"
	elif note == 13:
		return "e''"
	elif note == 14:
		return "f''"
	elif note == 15:
		return "g''"

#para ordenar los plays
def insertionsort( aList ):
  for i in range( 1, len( aList ) ):
    tmp = aList[i]
    k = i
    while k > 0 and compare_plays(tmp,aList[k - 1]):
        aList[k] = aList[k - 1]
        k -= 1
    aList[k] = tmp

#Necesario para el sort
def compare_plays (play1, play2):
	#ordeno primero por voz y luego por tiempo
	a = play1.replace("play","").replace("(","").split(",")[1]
	b = play2.replace("play","").replace("(","").split(",")[1]
	a = int(a)
	b = int(b)
	if (a < b):
		return True
	elif(a > b):
		return False
	#si la voz es el mismo, ordeno por la tiempo
	a = play1.replace("play","").replace("(","").split(",")[0]
	b = play2.replace("play","").replace("(","").split(",")[0]
	a = int(a)
	b = int(b)
	if (a < b):
		return True
	elif(a > b):
		return False
	return False

def showHelp():
	print """canon.py
	Opciones----------------------------
	-v x : Permite determinar el numero de voces
	-i archivo : Para establecer desde que archivo se obtiene la base del canon
	-p archivo : Permite determinar que archivo utilizar como preferencias
	-l : Permite determinar si se desea pasar la salida al lilypond
	-h : Muestra la ayuda
	Por defecto input = input.txt y preferences = preferences1.txt"""

#Escribe la salida el en fichero output.txt
def output_to_file():
	#Lo intento borrar, y si no existe capturo la excepcion
	try:
		os.remove(os.getcwd()+"/output.txt")
	except:
		pass
	output = open("output.txt","a")

	notes_number_list = []
	j = 0
	while(j < voices):
		notes_list.append("")
		notes_number_list.append("")
		espera = int(wait)*j
		for i in xrange(int(espera)):
			notes_list[j] +=  "-\t"
			notes_number_list[j] +=  "-\t"
		j += 1

	for action in plays:
		voice = action.replace("play","").replace("(","").replace(")","").split(",")[1]
		note = action.replace("play","").replace("(","").replace(")","").split(",")[2]
		notes_list[int(voice)-1] += str(to_note(int(note))+ "\t")
		notes_number_list[int(voice)-1] += note + "\t"

	for i in xrange(voices):
		output.write(notes_list[i] +  "\n")

	output.write("\n\n")

	for i in xrange(voices):
		output.write(notes_number_list[i] + " \n")

def to_lilypond():

	numbers = ["One", "Two", "Three", "Four"]
	instruments = ["voice oohs","Flute", "Clarinet","Ocarina"]

	text = "\\version \"2.14.2\"\n  \score { \n \\new Staff << \n" 

	for voice in xrange(min(4,voices)):
		text += " \\new Voice { \n  \set midiInstrument = #\""+instruments[voice] +"\""" \n  \\voice"+numbers[voice] + "\n"
		text += "  " + notes_list[voice] +  "\n } \n"

	text += ">> \n\layout { } \n\midi { \n \context { \n  \Staff \n  \\remove ""Staff_performer"" } \n\context { " 
	text += "\n  \Voice  \n  \consists ""Staff_performer""  }  \n }\n }"

	text = text.replace("-", "r")
	text = text.replace("	", " ")

	try:
		os.remove(os.getcwd()+"/lilypond.txt")
	except:
		pass
	lilypond = open("lilypond.txt","a")
	lilypond.write(text)
	lilypond.close()
  
  	subprocess.call(["lilypond","lilypond.txt"])

####### PARSEO DE PARAMETROS DE ENTRADA #########

#Inicializo las variables
help = False
input = "input.txt"
voices = 0
lilypond = False
preferences = "preferences_all.txt"

#Leo los parametros de entrada
for i in range(len(sys.argv)):
	if sys.argv[i] == "-v":
		voices = int(sys.argv[i+1])
		i += 1
	elif sys.argv[i] == "-l":
		lilypond = True
	elif sys.argv[i] == "-i":
		input = sys.argv[i+1]
		i += 1
	elif sys.argv[i] == "-h":
		help = True
		i += 1
	elif sys.argv[i] == "-p":
		preferences = sys.argv[i+1]
		i += 1

if help:
	showHelp()
	exit()

if voices <= 0:
	print "Introduzca numero de voces correcto"
	showHelp()
	exit()

####### FIN PARSEO DE PARAMETROS DE ENTRADA #########


####### LEEMOS FICHERO ENTRADA #######

try:
	inputf = open(input)
except:
	print "no existe el fichero de entrada"
	showHelp()
	exit()
	
inputLines = inputf.readlines()
inputf.close()
duration = inputLines[0]
wait = inputLines[1]
voicesInput = []

for i in xrange(voices):
	voicesInput.append(inputLines[i+2].replace("\n","").split(" "))

####### FIN LEEMOS FICHERO ENTRADA #######


####### ANNADIMOS LAS COSAS PARA LAS OTRAS VOCES #######

try:
	os.remove(os.getcwd()+"/otherVoices.txt")
except:
	pass
otherVoices = open("otherVoices.txt","a")

addToVoices = ""

i = 2
while i < voices:
	addToVoices += "\n% ******* Codigo para generar la voz " +  str(i) + " ******* \n "
	addToVoices += "#domain followerTime"+str(i)+"(FT"+str(i)+").\n"
	addToVoices += "followerTime"+str(i)+"(wait*"+str(i)+"..duration-1).\n"
	addToVoices += "voice("+str(i+1)+").\n"
	addToVoices += "1 {play(FT"+str(i)+","+str(i+1)+",W) : note(W)}1.\n"
	addToVoices += "play(T+"+str(i)+"*wait,"+str(i+1)+",N) :- play(T,1,N), T+"+str(i)+"*wait<duration.\n"
	i+=1

otherVoices.write(addToVoices)
otherVoices.close()

####### FIN ANNADIMOS LAS COSAS PARA LAS OTRAS VOCES #######


####### ANNADIMOS LOS PLAYS DEL FICHERO DE ENTRADA AL CANON #######

addPlayToCannon = ""
j = 0
for notes in voicesInput:
	j += 1
	for i in range(len(notes)):
		note = notes[i]
		if (note != "-" and note != "" and note != " " and note != "\n"):
			note = to_number(note)
			addPlayToCannon += "play(" + str(i) + "," + str(j)+ "," + str(note) +  ").\n"
try:
	os.remove(os.getcwd()+"/plays.txt")
except:
	pass

plays = open("plays.txt","a")
plays.write(addPlayToCannon)
plays.close()

####### FIN ANNADIMOS LOS PLAYS DEL FICHERO DE ENTRADA AL CANON #######


####### ELIMINAMOS FICHEROS Y EJECUTAMOS LOS COMANDOS #######
try:
	os.remove(os.getcwd()+"/gringo.txt")
	os.remove(os.getcwd()+"/clasp.txt")
except:
	pass
gringo = open("gringo.txt","a")
clasp = open("clasp.txt","a")
subprocess.call(["gringo", "-c", "duration="+duration, "-c", "wait="+wait, "canon.txt" , "plays.txt", preferences, "otherVoices.txt"], stdout=gringo)
subprocess.call(["clasp","gringo.txt"],stdout=clasp)

####### FIN ELIMINAMOS FICHEROS Y EJECUTAMOS LOS COMANDOS #######

####### COMPROBAMOS SALIDA ######
clasp.close()
clasp = open("clasp.txt")
claspLines = clasp.readlines()
clasp.close()
if (claspLines[3] == "UNSATISFIABLE\n" or claspLines[2] == "UNSATISFIABLE\n"):
	print "\nUNSATISFIABLE\n\n\n"
	exit()
if (claspLines[len(claspLines)-5].startswith("SATISFIABLE")):
	plays = claspLines[len(claspLines)-6].replace("\n","").split(" ")
elif (claspLines[len(claspLines)-9].startswith("Optimization")):
	plays = claspLines[len(claspLines)-10].replace("\n","").split(" ")
else:
	print "error al leer el clasp"
	exit()

insertionsort(plays)

for action in plays:
	print action

####### FIN COMPROBAMOS SALIDA ######

####### ESCRIBIMOS LA SALIDA EN EL FICHERO #######

notes_list = []
output_to_file()

####### FIN ESCRIBIMOS LA SALIDA EN EL FICHERO #######

if lilypond:
	to_lilypond()
