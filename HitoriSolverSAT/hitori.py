import os
import subprocess
 # que la variable sea POSITIVA significa que esta en NEGRO
#nuestra matriz de CNF siempre tiene 3 columnas, las dos variables y un 0 (delimitador)
# la variable no puede valer 0, de manera que la posicion 0,0 se corrresponde con la variable 1


#Macros

def to_variable(y, x, n):
	return ((x + n*y)+1)

def from_variable(x, n):
	fila = x/ n
	if (x % n == 0):
		fila = fila -1
	columna = (x-1) % n 
	return (fila, columna)


try:
	f = open("9x9.txt")
except:
	print "\n\nfichero hitori no encontrado\n\n"
	sys.exit()

# leemos la primera linea y definimos la matriz de n*n siendo n el numero de 
# elementos de la linea, y la rellenamos con los datos del fichero
# cuando hay mas de 10 elementos, necesitamos espacios para separarlos, por lo que
# se leen de forma diferente 

i = 0	
for linea in f:
	if i == 0:
		n = len(linea) -1
		n_aux = len(linea.split(" "))
		if n_aux > 10:
			n = n_aux
		matriz = [[0 for x in xrange(n)] for x in xrange(n)]
		matriz_primera_aprox = [[0 for x in xrange(n)] for x in xrange(n)]

	if (n <10):
		for j in range(len(linea)-1):
			matriz[i][j] = linea[j]
	else:
		linea_aux = linea.split(" ")
		for j in range(n_aux):
			matriz[i][j] = linea_aux[j]		
	i= i+1


print("\n\n    MATRIZ ENTRADA\n")
for i in range(len(matriz[0])):
	print matriz[i]


#eliminamos el fichero antiguo y creamos uno nuevo

try:
	os.remove(os.getcwd()+"/cnf.txt")
except:
	pass
CNF = open("cnf.txt","a")

#lo mismo con el fichero en el que escribimos la solicion
try:
	os.remove(os.getcwd()+"/solution.txt")
except:
	pass
f_solution = open("solution.txt","a")




############### PRIMERA APROX: BUCLE DE NO REPETIDOS EN FILAS Y COLUMNAS ##############
# En este bucle comprobamos para cada elemento si alguno de su columna y fila son
# iguales a el, en ese caso, marcamos los dos como negros en la matriz de la 2 aprox

file = ""
lines = 0
for y in xrange(n):
	for x in xrange(n):
		elem = matriz[y][x]
		for ax in xrange(n-x-1):
			elem_comprobar = matriz[y][x+ax+1]
			if (elem == elem_comprobar):
				lines = lines +1
				matriz_primera_aprox[y][x] = "*"
				matriz_primera_aprox[y][x+ax+1] = "*"
				file = file + ""+str(to_variable(y,x,n)) + " " + str(to_variable(y,x+ax+1,n))+" 0 \n"
		for ay in xrange(n-y-1):
			elem_comprobar = matriz[y+ay+1][x]
			if (elem == elem_comprobar):
				lines = lines +1
				matriz_primera_aprox[y][x] = "*"
				matriz_primera_aprox[y+ay+1][x] = "*"
				file = file + ""+str(to_variable(y,x,n)) + " " + str(to_variable(y+ay+1,x,n))+" 0 \n"


#
#print("\n\n   MATRIZ_PRIMERA_APROX")
#for i in range(len(matriz[0])):
#	for j in range(len(matriz[0])):
#		if matriz_primera_aprox[i][j] == 0:
#			matriz_primera_aprox[i][j] = "0"
#	print matriz_primera_aprox[i]
#print("\n\n")

#########################SEGUNDA APROX: NO NEGROS ADYACENTES ####################
# Dos bucles, uno para mirar horizontalmente y otro verticalmente, si hay un negro,
# y su adyacente tambien es negro, annade una linea al cnf 


#Recorrido en horizontal	
for y in xrange(n):
	for x in xrange(n):
		elem = matriz_primera_aprox[y][x]
		#si hay negro en el elemento
		if (elem == "*"):
			#si no estoy en el limite de la derecha
			if x+1 != n:
				elem_siguiente = matriz_primera_aprox[y][x+1]
				#si el siguiente elemento tambien es negro, uno de los dos no tiene que serlo
				if (elem_siguiente == "*"):
					lines = lines +1
					file = file + "-"+str(to_variable(y,x,n)) + " -" + str(to_variable(y,x+1,n))+" 0 \n"		

#recorrido en vertical
for x in xrange(n):
	for y in xrange(n):
		elem = matriz_primera_aprox[y][x]
		#si hay negro en el elemento
		if (elem == "*"):
			#si no estoy en el limite de abajo
			if y+1 != n:
				elem_siguiente = matriz_primera_aprox[y+1][x]
				#si el siguiente elemento tambien es negro, uno de los dos no tiene que serlo
				if (elem_siguiente == "*"):
					lines = lines +1
					file = file + "-"+str(to_variable(y,x,n)) + " -" + str(to_variable(y+1,x,n))+" 0 \n"		


#escribimos en el archivo cnf las lineas, siendo la primera la cabecera
file = "p cnf " + str(n*n) +" " + str(lines) + "\n" + file
CNF.write(file)
CNF.close()



# llamamos al solver SAT y guardamos en el fichero output.txt la salida

try:
	subprocess.call(["picosat", "cnf.txt", "-o", "output.txt"])
	fresponse = open("output.txt")
	response = fresponse.readlines()
	fresponse.close()
except:
	print "\n\n fallo al llamar al sat \n\n"
	sys.exit()



# si nos ha devuelto que es satisfactible, guardamos lo que nos devuelve 
# y marcamos con un * donde hay que poner un negro

string_matrix_solved = ""
if response[0].split(" ")[1] == "SATISFIABLE\n":
	print ("\n    SATISFIABLE")
	i =0;
	variables_response = []
	#este bucle esta por si la salida tiene mas de una linea
	while (1):
		i = 1+i
		try:
			variables_response = variables_response + response[i].replace("\n", "").split(" ")[1:n*n+1]
		except:
			#si el ultimo elemento acaba en 0, lo borramos
			if variables_response[len(variables_response)-1] == "0":
				variables_response = variables_response[0:len(variables_response)-1]
			break

	#una vez que tenemos el resultado en una lista, creamos como quedaria al final
	
	#print (variables_response)
	for y in xrange(n):
		line = ""
		for x in xrange(n):
			if variables_response[y*n +x][0] == "-":
				tupla = from_variable(-1*int(variables_response[y*n+x]),n)
				actual = " " + str(matriz[tupla[0]][tupla[1]]) + " "
			else:
				actual = " * "
			line = line + actual
		string_matrix_solved = string_matrix_solved +"\n" + line
else:
	print("Insatisfiable")
	f_solution.write("Insatisfiable")


print string_matrix_solved
f_solution.write(string_matrix_solved)


