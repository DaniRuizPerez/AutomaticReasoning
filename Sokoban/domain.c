#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domain.h"
#include "search.h"

void *stateBlocksHashKey(tState *s) {
  return s->blockLoc;
}

tState *loadDomain(char *fileName) {
  int i,j;
  tState *s = (tState *)malloc(sizeof(tState));

  numBlocks=6; numLocs=numBlocks+1;
  
  numOperators=numBlocks*numLocs;
  stateHashKeySize=numBlocks*sizeof(int);
  stateHashKey=stateBlocksHashKey;
  
  s->blockLoc=(int *) malloc(numBlocks*sizeof(int));

  s->blockLoc[0]=2;
  s->blockLoc[2]=4;
  s->blockLoc[4]=TABLE;
  s->blockLoc[1]=3;
  s->blockLoc[3]=5;
  s->blockLoc[5]=TABLE;
 /* s->blockLoc[9]=8; 
  s->blockLoc[8]=7;
  s->blockLoc[7]=6;
  s->blockLoc[6]=TABLE;*/
    
  s->clear = (char *) calloc(numLocs,sizeof(char));

  for (i=0;i<numBlocks;i++) {
    s->clear[i]=1;
    for (j=0;j<numBlocks;j++)
      if (s->blockLoc[j]==i) {s->clear[i]=0; break;}
  }
  s->clear[TABLE]=1;
  s->inTower=(char *) calloc(numBlocks,sizeof(char));
  
  goalLoc=(int *) malloc(numBlocks*sizeof(int));
  for (i=0;i<numBlocks;i++)
    goalLoc[i]=i+1; /* last is numBlocks=TABLE */
  
	for (i = 0; i <numBlocks; i++)
		s->inTower[i] = towerInitializer(s,i);
  
  return s;
}

void freeDomain() {
  free(goalLoc);
}

int goalTest(tState *s) {
    int i;
    for (i=0;i<numBlocks;i++)
      if (s->blockLoc[i]!=goalLoc[i]) return 0;
    return 1;
}

int executable(unsigned op,tState *s) {
	int b = OP_BLOCK(op);
	int p = OP_LOC(op);

	return b!=p && s->clear[b] && s->clear[p];
}

int towerInitializer (tState *s, int b) {
	if (s->blockLoc[b] == goalLoc[b]) 
		if (s->blockLoc[b]!=TABLE) 
			return isInTower(tState *s, s->blockLoc[b])
		else return 1	
	return 0;
} 

int inTower (tState *s, int b) {
	return goalLoc[b] == s -> blockLoc[b] && s-> inTower[s->blockLoc[b]]
}


tState *successorState(unsigned op,tState *old) {
	int b = OP_BLOCK(op);
	int p = OP_LOC(op);
	tState *result = (tState *) malloc(sizeof(tState));
	result -> blockLoc = (int *)malloc(numBlocks*sizeof(int));
	memcpy(result->blockLoc,old->blockLoc,numBlocks*sizeof(int));
	result -> clear = (char *)malloc(numLocs*sizeof(int));
	memcpy(result->clear,old->clear,numLocs*sizeof(int));
	result -> inTower =(char *)malloc(numBlocks*sizeof(int));
	memcpy(result->inTower,old->clear,numBlocks*sizeof(int));
	
	result -> blockLoc[b] = p;
	if (p != TABLE) result->clear[p]=0;
	result -> clear[old->blockLoc[b]]=1;
	return result;
}

void freeState(tState *s) {
  free(s->blockLoc);
  free(s->clear);
  free(s->inTower);
  free(s);
}

int cost(unsigned op,tState *s) {
  return 1;
}

int stateEqual(tState *s1,tState *s2) {
  int i;
  for (i=0;i<numBlocks;i++)
    if (s1->blockLoc[i]!=s2->blockLoc[i]) return 0;
  return 1;
}

int h(tSearchNode *n) {
  int i,count=0;

  /* How many blocks are not in their place */
  for (i=0;i<numBlocks;i++)
    if (n->state->blockLoc[i]!=goalLoc[i]) count++;
      
    return count;
}


/*--- DISPLAY FUNCTIONS -----------------------------------------------*/

void showState(tState *s) {
  int i,j;
  
  for (i=0;i<numBlocks;i++)
    if (s->clear[i]) {
      for (j=i;j!=TABLE;j=s->blockLoc[j])
        printf(" %d",j);
      printf(";");
    }
  printf("\n");
}

void showOperator(unsigned op) {
  int b=OP_BLOCK(op), l=OP_LOC(op);
  printf("move(%d,",OP_BLOCK(op));
  if (l==TABLE) printf("table)");
  else printf("%d)",l);
}
