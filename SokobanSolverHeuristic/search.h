typedef struct tSearchNode_ {
  tState *state;
  struct tSearchNode_ *parent;
  unsigned action;
  int pathCost;
  int depth;
} tSearchNode;

tState *initialState();
int goalTest(tState *s);
int executable(unsigned op,tState *s);
tState *successorState(unsigned op,tState *s);
int cost(unsigned op,tState *s);
int h(tSearchNode *n);
void showOperator(unsigned op);
void showState(tState *s);
