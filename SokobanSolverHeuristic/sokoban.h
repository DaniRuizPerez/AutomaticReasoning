/*
APELLIDOS: RUIZ PÉREZ
NOMBRE: DANIEL
LOGIN: d.ruiz.perez

APELLIDOS: BARBEITO VÁZQUEZ
NOMBRE: ISMAEL
LOGIN: i.barbeito
*/

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

#define POS(r,c) ((r)*cols+(c)) //Convierte dos valores i j que representan índices de matriz en un entero
#define ROW(p) ((p)/cols)
#define COL(p) ((p) % cols)

#define CODE(o,c) ((o)+(c)*(4)) //Devuelve un código que asocia cada caja y cada acción con un entero
#define OP(co) ((co)%4)
#define BOX(co) ((co)/4)


typedef struct tState_ {
	int *pos_caja_soko; 
	/*Este array tiene exactamente tantas posiciones como cajas+1 (de 0 al número de cajas)
	En la última celda del array se guarda la posición del soko*/
} tState;
