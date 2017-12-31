/*
APELLIDOS: RUIZ PÉREZ
NOMBRE: DANIEL
LOGIN: d.ruiz.perez

APELLIDOS: BARBEITO VÁZQUEZ
NOMBRE: ISMAEL
LOGIN: i.barbeito
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "queue.h"
#include "domain.h"
#include "search.h"

char **paredes;//matriz con las paredes y sobre la que se expandiran los accesibles y los movimientos de las cajas
int** costes;//matriz que almacena la distancia mínima de cada casilla a la meta
int goals; //numero de metas
int* metas; //array con la posicon de las metas
int *cosas_que_cambian;//array con las posiciones que no son paredes
int num_cosas_que_cambian = 0;//numero de las posiciones que no son paredes
int rows;
int cols;

/***********AUX FUNCTIONS*******************/

void barrer(tState *s) {
	//Se recorre la matriz entera y:
	//Se guarda un array con las metas, se actualiza en el estado la posicion de soko y de las cajas.
	//Se guarda en cosas_que_cambian la posicion de todas las cosas que no sean paredes (acceso más eficiente luego en borrados)
	//se eliminan de la matriz las metas y el soko

  int i,j;
  char temp;
  int pos;
  int goals_location_index = 0;
  int box_location_index = 0;
 
  for(i = 0; i<rows; i++)
    for (j = 0; j < cols; j++){
      temp = paredes[i][j];
      pos = POS(i,j);
      if (temp != '#') { //Si es pared ya no hago nada
        if (temp == '.' ||  temp == '*' || temp == '+') { //Marco las metas
          metas[goals_location_index] = pos;
          goals_location_index++;
        }
        if (temp == '+' || temp == '@') //Marco al soko
          s->pos_caja_soko[goals] = pos;
        if (temp == '$' || temp == '*') { //Marco las cajas
          s->pos_caja_soko[box_location_index] = pos;
          box_location_index++;
        }
        paredes[ROW(pos)][COL(pos)] = ' '; //Coloco un blanco
      	cosas_que_cambian[num_cosas_que_cambian] = pos; //indico que es accesible
       num_cosas_que_cambian++;
      }
    }
   num_cosas_que_cambian++;//Si tenia 43 posiciones paredes, esto valdria 42 (n-1)
}

void liberar_accesibles(){
	//Una vez que he llamado a paredes esta todo lleno de @, esta funcion las elimina todas dejando todo en blanco
	int i = 0;
	for(i = 0; i<num_cosas_que_cambian-1; i++){
		//printf("x-> %d y ->%d\n",ROW(cosas_que_cambian[i]),COL(cosas_que_cambian[i]));
		paredes[ROW(cosas_que_cambian[i])][COL(cosas_que_cambian[i])] = ' ';

	}
}

void colocar_elementos (tState *s) {
	//coloca en paredes las cajas y el soko para ejecutar iniaccesibles
	int i;

	for (i = 0; i <goals; i++) 
		paredes[ROW(s->pos_caja_soko[i])][COL(s->pos_caja_soko[i])] = '$';
	paredes[ROW(s->pos_caja_soko[i])][COL(s->pos_caja_soko[i])] = '@';
}

void iniaccesibles (int pos_actual) {
/*Dado un escenario que contega el tablero con paredes, las cajas y el soko, a partir de la posición inicial del operario
se calculan todas las casillas a las que puede acceder el mismo de forma recursiva*/
	int x = ROW(pos_actual);
	int y = COL(pos_actual);
	int i;

	for (i = -1; i <= 1; i+=2) {
		if (paredes[x+i][y] == ' ') {
			paredes[x+i][y] = '@';
			iniaccesibles(POS(x+i,y));
		}
		if (paredes[x][y+i] == ' ') {
			paredes[x][y+i] = '@';
			iniaccesibles(POS(x,y+i));
		}
	}
}


/********LOAD FUNCTIONS*******************/

void readline(FILE *f,char *line, int *goals) {
  int c,i=0;
 
  c=fgetc(f);
  while (c!=EOF && c!='\n') {
    line[i++]=c;
    if (c=='$' || c=='*') (*goals)++;
    c=fgetc(f);
  }
  line[i]=0;
}

char **loadFile(char *fileName, int *rows, int *cols, int *goals) {
  FILE *f;
  char line[512], *s;
  int i,l;
  QUEUE lines=qEMPTY;
  char **array;
 
  *goals=0;
  *cols=-1;
  if (fileName==NULL || (f=fopen(fileName,"r"))==NULL) {
    printf("Could not open input file %s\n",fileName); exit(1);
  }
  readline(f,line,goals);
  while ((l=strlen(line))!=0) {
    if (l>*cols) *cols=l;
    s=(char *)malloc((l+1)*sizeof(char));
    strcpy(s,line);
    qInsertLast(&lines,&s,sizeof(char *));
    readline(f,line,goals);
  }
  fclose(f);
 
  array=(char **)Queue2Array(lines,sizeof(char *),rows);
  qFree(&lines);
 
  for (i=0;i<*rows;i++) {
    l=strlen(array[i]);
    s=(char *)malloc(sizeof(char)* (*cols));
    memcpy(s,array[i],sizeof(char)* (*cols));
    free(array[i]);
    array[i]=s;
  }
 
  return array;
}

void *stateArrayHashKey(tState *s) {
  return s->pos_caja_soko;  
} 

void crear_costes() {
	//reserva espacio para la matriz costes
	int i;
	costes = malloc(sizeof(int*)*rows);
	for (i = 0; i < rows; i++)
		costes[i] = malloc(sizeof(int)*cols);
}

int sale_rango(int pos, int limite){
	//indica si la posicion dada esta dentro o fuera del rango de la matriz
	return !(pos >= 0 && pos <limite);
}

void expandir (int pos_actual, int coste) {
	//pone en cada posicion de costes la distancia mímina a la meta indicada
	int i;
	int x = ROW(pos_actual);
	int y = COL(pos_actual);

	for (i = -1; i <= 1; i+=2) {
		if (!sale_rango(x+i,rows))
			if (costes[x+i][y] > coste) {
				costes[x+i][y] = coste;
				expandir(POS(x+i,y),1+coste);
			}
		if (!sale_rango(y+i,cols))
			if (costes[x][y+i] > coste) {
				costes[x][y+i] = coste;
				expandir(POS(x,y+i),1+coste);
			}
	}
}

void interf_expandir () {
	//llama a la funcion expandir una vez por cada meta despues de haber inicializado costes a int_max

	crear_costes();
	int i,j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			costes[i][j] = INT_MAX; //Así al comparar por menor sustituimos siempre
	for (i = 0; i < goals; i++) {
		costes[ROW(metas[i])][COL(metas[i])] = 0; //Pongo el valor de la meta
		expandir (metas[i],1);//y la expando
	}
}


tState *loadDomain(char *fileName) {
	tState *state = (tState *)malloc(sizeof(tState));
	paredes = loadFile(fileName, &rows, &cols, &goals);
	metas = malloc(sizeof(int)*goals);
  	state->pos_caja_soko = malloc(sizeof(int)*(goals+1));
  	cosas_que_cambian = malloc(sizeof(int)*rows*cols);
 	barrer(state);
	interf_expandir();
  	cosas_que_cambian = realloc(cosas_que_cambian, sizeof(int)*num_cosas_que_cambian);
 	stateHashKeySize = (1+goals)*sizeof(int);   
	stateHashKey=stateArrayHashKey;   
	numOperators = 4*goals;       
	return state;
}
/***********************************************/

/*********FREE & DISPLAY FUNCTIONS**************/

void liberar_matriz (void ** matriz){
	int i;
	for (i = 0; i<rows; i++)
		free (matriz[i]);
	free (matriz);
}

void freeDomain(){ 
	free(metas);
	free(cosas_que_cambian);
	liberar_matriz((void **)paredes);
	liberar_matriz((void**)costes);
}

void freeState(tState *s){
	free(s->pos_caja_soko);
	free(s);
}

void imprimir_paredes (tState s){
/*Función para mostrar de forma visual el tablero con la opción -v*/
	int i,j;;
	colocar_elementos(&s);

	for (i = 0; i < goals; ++i){
		if (paredes[ROW(metas[i])][COL(metas[i])] == ' ')
			paredes[ROW(metas[i])][COL(metas[i])] = '.';
		else if (paredes[ROW(metas[i])][COL(metas[i])] == '@')
			paredes[ROW(metas[i])][COL(metas[i])]= '+';
		else if (paredes[ROW(metas[i])][COL(metas[i])] == '$')
			paredes[ROW(metas[i])][COL(metas[i])]= '*';
	}
	for (i = 0; i<rows; i++){
		for (j = 0; j<cols; j++)
			printf ("%c",paredes[i][j]);
		printf("\n");		
	}
	liberar_accesibles();
}

void showOperator(unsigned op){
	int box = BOX(op);
	switch(OP(op)){
		case UP:    printf("BOX %d UP",box);break;
	    case DOWN:  printf("BOX %d DOWN",box);break;
	    case LEFT:  printf("BOX %d LEFT",box);break;
    	case RIGHT: printf("BOX %d RIGHT",box);break;
	}
}

void showState(tState *s){
	int i = 0;
	printf("soko is at -> %d,%d\n",ROW(s->pos_caja_soko[goals]),COL(s->pos_caja_soko[goals]));
	for (i = 0; i < goals; ++i)
		printf("box %d at %d,%d\n",i,ROW(s->pos_caja_soko[i]),COL(s->pos_caja_soko[i]));
	imprimir_paredes(*s);
}

/******************************************************/

/************NEXT STATE*******************************/

int es_esquina_mala (tState s, int box, int i, int j){ // i y j son las variables que se usan en succesorstate
/*Devuelve 1 si la posición es una esquina que impide encontrar una solución*/

	int k;
	for (k = 0; k < goals; ++k) //Si la caja va a una esquina, pero dicha esquina es una meta, no es una posición inválida
		if (POS(ROW(s.pos_caja_soko[box])+i,COL(s.pos_caja_soko[box]+j) == metas[k]))
			return 0;
	
	char arriba = paredes[ROW(s.pos_caja_soko[box])+i-1][COL(s.pos_caja_soko[box])+j];
	char abajo = paredes[ROW(s.pos_caja_soko[box])+i+1][COL(s.pos_caja_soko[box])+j];
	if (arriba == '#' || abajo == '#'){
		char izquierda = paredes[ROW(s.pos_caja_soko[box])+i][COL(s.pos_caja_soko[box])-1+j];
		char derecha = paredes[ROW(s.pos_caja_soko[box])+i][COL(s.pos_caja_soko[box])+1+j];
		if (izquierda == '#' || derecha == '#')
			return 1;
	}
	return 0;
}

unsigned accion_contraria(unsigned accion) {
/*Las acciones están numeradas de tal forma que dos
acciones contrarias (UP/DOWN y RIGHT/LEFT) se diferencian
en uno una de la otra. Así, para obtener la acción contraria
a la dada, basta con ver si es par o no y en función de eso
sumarle o restarle uno*/	
	if (!(accion%2))
		return (++accion);
	return (--accion);
}

int executable (unsigned op, tState *s) {
/*Una acción es ejecutable (podemos mover una caja) hacia un lado si:
	a) El soko puede llegar al lado contrario (puedo mover a derecha si el soko puede empujar desde izquierda)
	b) El lado al que quiero mover está libre*/
	int accion = OP(op);
	int box = BOX(op);
	int x = ROW(s->pos_caja_soko[box]);
	int y = COL(s->pos_caja_soko[box]);
	char pos_accion; //Almaceno lo que hay en el lugar al que quiero mover
	char pos_contraria; //Almaceno lo que hay en el lugar en el que empujará el soko

	colocar_elementos(s);
	iniaccesibles(s->pos_caja_soko[goals]);
	/*Curioso: si aquí le paso la caja actual en lugar del soko, expande la caja y halla siempre la solución óptima
	si consideramos que el soko puede "saltar" por encima de las cajas*/
	int colindantes[4] = {paredes[x-1][y], //UP
						  paredes[x+1][y], //DOWN
						  paredes[x][y+1], //RIGHT
						  paredes[x][y-1]  //LEFT
						 };
	pos_accion = colindantes[accion];
	pos_contraria = colindantes[accion_contraria(accion)];			 
 	liberar_accesibles();
	if (pos_contraria =='@' && (pos_accion == ' ' || pos_accion == '@')) 
	/*Como lleno la matriz paredes de @, una pos_accion accesible puede contener o blanco o arroba*/ 
			return (!es_esquina_mala (*s,box,x,y)); //Si es accesible, devuelve true si no está en una esquina
	return 0;
}

tState *successorState(unsigned op,tState *s){

	int accion = OP(op);
	int box = BOX(op);
	int i = 0,j = 0,k; //variables que indican el desplazamiento en la matriz

  	tState *result = (tState *)malloc(sizeof(tState));
  	result->pos_caja_soko = malloc(sizeof(int)*(goals+1));

  	for ( k= 0;  k< goals; k++)
  		result->pos_caja_soko[k] = s->pos_caja_soko[k]; //se copia todo menos la ultima posición para ganar eficiencia

	switch (accion) {
		case UP:	i = -1; break;
		case DOWN: i = 1;break;
		case RIGHT: j = 1; break;
		case LEFT: j= -1; break;
	}
	result->pos_caja_soko[goals] = s->pos_caja_soko[box]; //se actualiza la posicion de soko 
	result->pos_caja_soko[box] = POS(ROW(s->pos_caja_soko[box])+i,COL(s->pos_caja_soko[box])+j); //y la posicion de la caja movida
	return result;
}

int cost(unsigned op,tState *s){
	return 1;
}

int h(tSearchNode *n){ 
	/*Ya que en costes almacenamos las distancias mínimas a las metas de casa posición, 
	consideramos una heurística basada en esa matriz, tal que la suma de los costes de
	las posiciones de todas las cajas es el valor de h*/

	int i = 0;
	int sum = 0;
	int pos_temp;
	for (i = 0; i < goals; ++i) {
		pos_temp = n->state->pos_caja_soko[i];
		sum+= costes[ROW(pos_temp)][COL(pos_temp)];
	}
	return sum;
}

/******************************************************/

/****************COMPARAR ESTADOS***************/

int goalTest(tState *s){
	//te dice si es el estado final en funcion de si todas las cajas tienen distancia a la meta mas cercana 0
	int i;
	for (i = 0; i < goals; i++) 
		if (costes[ROW(s->pos_caja_soko[i])][COL(s->pos_caja_soko[i])] != 0)
			return 0;
	return 1;
}

void intercambiar (int* a, int* b) {
        int temp = *a;
        *a = *b;
        *b = temp;
} 

int stateEqual(tState *s1,tState *s2) {
	int i, j, escape, copy_goals = goals;
	/*Este algoritmo se basa en la idea de que el orden de las cajas es irrelevante en el estado.
	Para que dos estados sean iguales, tienen que tener para cualquier caja x de s1 en una posición,
	su correspondiente caja y en s2 en la misma posición. Una forma de comprobar esto es, sabiendo que
	en los vectores tengo las cajas entre 0 y goals-1, comprobar si alguna caja en ese rango de s2 coincide
	con la primera de s1 en posición. Si si, disminuyo en 1 el limite superior ((goals-1)-1) y pongo la caja
	de s2 al final de su rango.

	Visualmente:
	s1 = 8, 4, 5
	s2 = 1, 8, 4
	goals = 3
	copy_goals = 3

	al acabar el segundo for, quedaría algo así

	s1 = 8, 4, 5
	s2 = 1, 4, 8
	goals = 3
	copy_goals = 2	
	*/
	for (i = 0; i < goals; i++) {
		escape = copy_goals;
	    for (j = 0; j < copy_goals; j++ )
	        if (s1->pos_caja_soko[i] == s2->pos_caja_soko[j]) {
	            intercambiar(&s2->pos_caja_soko[j], &s2->pos_caja_soko[goals-1]);
	            copy_goals--;
	            break;
	        }
	     if (j == escape)
	    	return 0;
	}
	return 1;
}
