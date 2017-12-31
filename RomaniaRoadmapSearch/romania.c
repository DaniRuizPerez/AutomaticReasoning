#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domain.h"
#include "search.h"

static char *cityName[NUM_CITIES] =
{
  /*  0 */ "Oradea",
  /*  1 */ "Zerind",
  /*  2 */ "Arad",
  /*  3 */ "Timisoara",
  /*  4 */ "Lugoj",
  /*  5 */ "Mehadia",
  /*  6 */ "Dobreta",
  /*  7 */ "Sibiu",
  /*  8 */ "Rimnicu Vilcea",
  /*  9 */ "Craiova",
  /* 10 */ "Fagaras",
  /* 11 */ "Pitesti",
  /* 12 */ "Giurgiu",
  /* 13 */ "Bucharest",
  /* 14 */ "Neamt",
  /* 15 */ "Urcizeni",
  /* 16 */ "Iasi",
  /* 17 */ "Vaslui",
  /* 18 */ "Hirsova",
  /* 19 */ "Eforie"
};

static int road[NUM_CITIES][NUM_CITIES];

static int straightDistance[]={
380, /*  0 Oradea */
374, /*  1 Zerind */
366, /*  2 Arad */
329, /*  3 Timisoara */
244, /*  4 Lugoj */
241, /*  5 Mehadia */
242, /*  6 Dobreta */
253, /*  7 Sibiu */
193, /*  8 Rimnicu Vilcea */
160, /*  9 Craiova */
178, /* 10 Fagaras */
98 , /* 11 Pitesti */
77 , /* 12 Giurgiu */
0  , /* 13 Bucharest */
234, /* 14 Neamt */
80 , /* 15 Urcizeni */
226, /* 16 Iasi */
199, /* 17 Vaslui */
151, /* 18 Hirsova */
161  /* 19 Eforie */
};

tState *loadDomain(char *fileName) {
  tState *s;
  int i,j;

  for (i=0;i<NUM_CITIES;i++)
    for (j=0;j<NUM_CITIES;j++)
      road[i][j]=NO_ROAD;
  
  road[ORADEA][ZERIND]=71; road[ORADEA][SIBIU]=151;
  road[ZERIND][ARAD]=75;
  road[ARAD][SIBIU]=140; road[ARAD][TIMISOARA]=118;
  road[TIMISOARA][LUGOJ]=111;
  road[LUGOJ][MEHADIA]=70;
  road[MEHADIA][DOBRETA]=75;
  road[DOBRETA][CRAIOVA]=120;
  road[SIBIU][RIMNICU]=80; road[SIBIU][FAGARAS]=99;
  road[RIMNICU][CRAIOVA]=146; road[RIMNICU][PITESTI]=97;
  road[CRAIOVA][PITESTI]=138;
  road[FAGARAS][BUCHAREST]=211;
  road[PITESTI][BUCHAREST]=101;
  road[GIURGIU][BUCHAREST]=90;
  road[BUCHAREST][URZICENI]=85;
  road[NEAMT][IASI]=87;
  road[URZICENI][VASLUI]=142; road[URZICENI][HIRSOVA]=98;
  road[IASI][VASLUI]=92;
  road[HIRSOVA][EFORIE]=86;
  
  /* Symmetric arcs */
  for (i=0;i<NUM_CITIES;i++)
    for (j=0;j<i;j++)
      road[i][j]=road[j][i];

  numOperators=NUM_CITIES;
  s=(tState *)malloc(sizeof(tState));
  s->inCity=ARAD;
  
  return s;
}

void freeDomain() { }

int goalTest(tState *s) {
  return s->inCity==BUCHAREST;
}

int executable(unsigned op,tState *s) {
  return road[s->inCity][op]!=NO_ROAD;
}

tState *successorState(unsigned op,tState *old) {
  int tile;
  tState *result = (tState *)malloc(sizeof(tState));
  result->inCity=op;
  return result;
}

void freeState(tState *s) {
  free(s);
}

int cost(unsigned op,tState *s) {
  return road[s->inCity][op];
}

int h(tSearchNode *n) {
  return straightDistance[n->state->inCity];
}

int stateEqual(tState *s1,tState *s2) {
  return (memcmp(s1,s2,sizeof(tState))==0);
}

/*--- DISPLAY FUNCTIONS -----------------------------------------------*/

void showState(tState *s) {
  printf("%s ",cityName[s->inCity]);
}


void showOperator(unsigned op) {
  printf("go=%s",cityName[op]);
}

/*
int main() {
  int i,j;
  tState *s,*s2;
  s=loadDomain(NULL);
  for (i=0;i<NUM_CITIES;i++)
    for (j=0;j<NUM_CITIES;j++)
      if (road[i][j]!=NO_ROAD) printf("%s to %s = %d\n",cityName[i],cityName[j],road[i][j]);
  
  for (i=0;i<numOperators;i++)
    if (executable(i,s)) {
      showOperator(i);
      s2=successorState(i,s);
      showState(s2);
      printf("\n");
      freeState(s2);
    }
  
}
*/