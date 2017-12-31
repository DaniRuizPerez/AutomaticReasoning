#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3
#define NUM_OPERATORS 4

typedef struct tState_ {
  int cells[3][3];
  int r,c;
} tState;
