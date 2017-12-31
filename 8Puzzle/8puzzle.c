#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domain.h"
#include "search.h"

static int domain[2*N][N]; /* first N rows = initial; last N rows = goal */

static tState *goal = NULL;

tState *getState(int firstRow) {
  tState *s = (tState *)malloc(sizeof(tState));
  int i,j,c;
  
  for (i=0;i<N;i++)
    for (j=0;j<N;j++) {
      c=s->cells[i][j]=domain[firstRow+i][j];
      s->row[c]=i;
      s->col[c]=j;
    }
  return s;
}

tState *loadDomain(char *fileName) {
  FILE *f;
  int i,j,c;
  tState *s;

  numOperators=4;
  
  if (fileName==NULL || (f=fopen(fileName,"r"))==NULL) {
    printf("Could not open input file %s\n",fileName); exit(1);
  }
  for (i=0;i<2*N;i++) {
    for (j=0;j<N;j++)  {
      if (fscanf(f,"%d",&c)==EOF || c<0 || c>=N*N) {
        printf("File %s input error: line %d %d\n",fileName,i+1,c); exit(1);
      }
      domain[i][j]=c;
      if (j<N-1)
        if (fscanf(f,",")!=0) {
          printf("File %s input error: expected ',' in line %d\n",fileName,i+1); exit(1);
        }
    }
    if (fscanf(f,"\n")!=0) {
      printf("File %s input error: line %d\n",fileName,i+1); exit(1);
    }
  }
  fclose(f);
    
  s = getState(0);
  goal = getState(N);
  return s;
}

void freeDomain() { }

int goalTest(tState *s) {
  int i,j;
  
  for (i=0;i<N;i++)
    for (j=0;j<N;j++)
      if (s->cells[i][j]!=domain[i+N][j]) return 0;
  return 1;
}

int executable(unsigned op,tState *s) {
  switch(op) {
    case UP:    return s->row[0]>0;
    case DOWN:  return s->row[0]<2;
    case LEFT:  return s->col[0]>0;
    case RIGHT: return s->col[0]<2;
  }
}

tState *successorState(unsigned op,tState *old) {
  int tile;
  tState *result = (tState *)malloc(sizeof(tState));
  
  /* Copy result from old */
  memcpy(result,old,sizeof(tState));
 
  switch(op) {
    case UP: result->row[0]--; break;
    case DOWN: result->row[0]++; break;
    case LEFT: result->col[0]--; break;
    case RIGHT: result->col[0]++; break;
  }
  
  /* Get the moved tile */
  tile=old->cells[result->row[0]][result->col[0]];
  
  /* Put a 0 in the new position of the hole */
  result->cells[result->row[0]][result->col[0]]=0;
  
  /* Put the tile in the old position of the hole */
  result->cells[old->row[0]][old->col[0]]=tile;
  
  /* Update row and col for the tile */
  result->row[tile]=old->row[0];
  result->col[tile]=old->col[0];
  
  return result;
}

void freeState(tState *s) {
  free(s);
}

int cost(unsigned op,tState *s) {
  return 1;
}


int h(tSearchNode *n) {
  int sum=0,c;
  tState *s=n->state;

  for (c=1;c<N*N;c++)
    sum += abs(s->row[c]-goal->row[c]) + abs(s->col[c]-goal->col[c]);
    
  return sum;
}

int stateEqual(tState *s1,tState *s2) {
  return (memcmp(s1,s2,sizeof(tState))==0);
}

/*--- DISPLAY FUNCTIONS -----------------------------------------------*/

void showState(tState *s) {
  int i,j;
  for (i=0; i<N; i++) {
    for (j=0; j<N; j++)
      printf("%d",s->cells[i][j]);
    printf(";");
  }
}


void showOperator(unsigned op) {
  switch(op) {
    case UP:    printf("UP");break;
    case DOWN:  printf("DOWN");break;
    case LEFT:  printf("LEFT");break;
    case RIGHT: printf("RIGHT");break;
  }
}
