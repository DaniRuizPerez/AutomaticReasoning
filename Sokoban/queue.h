/***************************************************************************** 
 * QUEUE.h 
 * Pedro Cabalar 15/10/2004
 *
 * A QUEUE is a single connected round list. The QUEUE itself is a pointer
 * used to point at any moment the last element in the list.
 *****************************************************************************/

struct qNode {
  struct qNode *next;
  int data[0];
};

typedef struct qNode *QUEUE;

/* qEMPTY: returns the empty queue (represented as the NULL pointer) */
#define qEMPTY NULL

/* qIsEmpty(QUEUE q);
 * Decides whether QUEUE q is empty or not. It is equivalent to 
 * the expression q==qEMPTY
 */
#define qIsEmpty(q) ((q)==NULL)

/* qIsNotEmpty(QUEUE q);
 * The opposite to qIsEMPTY. It is equivalent to the expression q!=qEMPTY
 */
#define qIsNotEmpty(q) ((q)!=NULL)

/* qFirst(QUEUE q,type);
 * Returns a pointer to the data of the first element in the list, assuming
 * that the element type is 'type'.
 * EXAMPLE: 
 *   printf("%d\n",*qFirst(q,int));  
 *   will print the first element of q, assuming it is an integer number.
 * REQUIRES: q must be non-empty.
 */
#define qFirst(q,type) ((type *)(q)->next->data)

/* qNext(QUEUE q,type);
 * Returns a QUEUE pointer to the next element from q.
 * Remember that the end of the list is not a NULL pointer, but is connected
 * instead to the first element (it is a round list).
 * REQUIRES: q must be non-empty.
 */
#define qNext(q) ((q)->next)

/* qInsertAt(QUEUE *pq,QUEUE pos,void *e,unsigned int size);
 * Inserts an element of size 'size' whose address is pointer 'e' at the 
 * position pointed by QUEUE pointer 'pos'. 
 * REQUIRES: 'pos' must be one of the pointers inside the queue *pq.
 * MODIFIES: the queue elements and (possibly) the queue pointer *pq.
 */
#define qInsertAt(pq,pos,e,size) ((*pq)==(pos))?qInsertFirst(pq,e,size):qInsertFirst(&p,e,size)

/* qPUSH(QUEUE *pq,void *e,type)
 * Pushes element of type 'type' whose address is pointer 'e' at the 
 * top of the queue pointed by 'pq'. Note that 'pq' must be of type (QUEUE *),
 * since the queue pointer can be modified.
 * MODIFIES: the queue elements and (possibly) the queue pointer *pq.
 */
#define qPUSH(pq,e,type) qInsertFirst(pq,(void *)e,sizeof(type))

/* qPOP(QUEUE *pq,void *e,type)
 * Retrieves and deletes the top element of queue *pq, storing it at address
 * 'e', assuming that its type is 'type'.
 * REQUIRES: the queue *pq must be non-empty.
 * MODIFIES: the content of the area pointed by 'e', the queue elements, and 
 * (possibly) the queue pointer *pq. 
 */
#define qPOP(pq,e,type) {memcpy((void *)e,(*(pq))->next->data,sizeof(type)); qDeleteFirst(pq);}

/* See qOrderedInsert */
#define REPEATING 1

int qInsertFirst(QUEUE *pq, void *e, int size);
/* Inserts an element of size 'size' pointed by 'e' as the first element of
 * queue *pq.
 * MODIFIES: the queue elements and (possibly) the queue pointer *pq.
 */

int qInsertLast(QUEUE *pq, void *e, int size);
/* Inserts an element of size 'size' pointed by 'e' as the last element of
 * queue *pq.
 * MODIFIES: the queue elements and (possibly) the queue pointer *pq.
 */
 
int qDeleteFirst(QUEUE *pq);
/* Deletes the first element of queue *pq
 * MODIFIES: the queue elements and the queue pointer *pq.
 */

QUEUE qBrowse(QUEUE q, int (*found)(QUEUE , void *),void *data);
/* Allows browsing the queue q and performing some arbitrary operation until
 * the end of the queue is reached or some element is found.
 * Argument 'found' is a pointer to a function of type
 *   int (*found) (QUEUE pos,void *data)
 * that will be called for each pointer 'pos' to each element in list 'q'.
 * When this function returns 0, the browsing will continue until reaching
 * the queue end. Otherwise, it may return 1 (for instance, when some searched
 * element is found) and the browsing will stop at that moment.
 * The pointer 'data' is used to pass common data to each call of function
 * (*found).
 * REQUIRES: function (*found) should return 0 or 1 and should not modify
 * the element pointers (should not delete or insert elements in q).
 * MODIFIES: It depends on function (*found), which can modify the content of
 * the elements in the queue.
 * EXAMPLE: We want to add some constant k to all the elements in a list of
 * integer numbers until we reach some negative number:
 *
 *  int addConstant(QUEUE q,void *data) {
 *    if (*qFirst(q,int) < 0) 
 *      return 1; 
 *    int *pk=(int *)data;
 *    *qFirst(q,int) += *pk;
 *    return 0;
 *  }
 *
 *  ...
 *  int k=10;
 *  qBrowse(q,addConstant,&k);
 *  ...
 */
 
int qDelete(QUEUE *pq, QUEUE pos);
/* Deletes the element of queue *pq at position pointed by queue pointer 'pos'.
 * REQUIRES: 'pos' must be one of the valid position pointers inside queue
 * *pq.
 * MODIFIES: the queue elements and possibly the content of *pq.
 */

int qMove(QUEUE *q1, QUEUE *q2, int (*movethis)(void *),int size);
/* Moves all the elements in *q1 to *q2 that satisfy a property specified
 * by the generic function (*movethis). The moved elements are removed from
 * *q1 and appended to *q2, that is, they are inserted in the end. The elements
 * size is fixed to 'size'.
 * MODIFIES: the elements of both queues, and possibly *q1 and *q2.
 */

int qFree(QUEUE *q);
/* Deletes all the queue elements leaving *q empty. */
 
int qOrderedInsert(QUEUE *q, void *e, int size,int (*cmp)(void *, void *),
               char repeating);
/* Makes an ordered insertion of element of size 'size' pointed by 'e' in
 * queue *q. Generic function (*cmp) is used to compare two elements 
 * (passed as void pointers) so that it returns a value <0 if the first
 * one is lower, =0 if they are equal, or >0 if the first element is greater.
 * Argument 'repeating' is used to point out whether we allow repeated elements
 * or not (1 means with repeated elements, 0 means no repeated elements).
 * REQUIRES: the elements in *q should be ordered with respect to (*cmp) 
 * ordering criterion.
 * MODIFIES: the queue elements and (possibly) the pointer *q.
 */
	       
int qDeleteThoseThat(QUEUE *q,int (*DeleteThis)(QUEUE pos,void *data),void *data);
/* Deletes from queue *q all those elements that satisfy proerty specified
 * by generic function (*DeleteThis). Argument 'data' is used for passing
 * additional data to (*DeleteThis) if needed.
 * REQUIRES: function DeleteThis should return 1 if the first element of
 * pointer 'pos' should be deleted, and 0 otherwise.
 * MODIFIES: the queue elements and (possibly) the pointer *q.
 */

QUEUE qCopy(QUEUE q,int size);
/* Returns a full copy of q. */

QUEUE qMerge(QUEUE q,QUEUE r,int size,int (*cmp)(void *,void *),char repeating);
/* It returns a list containing the result of merging the two ordered lists q  
 * and r. The new list contains a copy of the elements in the old lists.
 * The ordering criterion is specified by the generic function (*cmp) (see
 * qOrderedInsert). When 'repeating' is 0, repeated elements are copied only
 * once. The size elements is fixed to 'size'.
 */

QUEUE qIntersect(QUEUE q,QUEUE r,int size,int (*cmp)(void *,void *));
/* Returns the common elements of queues q and r. The new list contains a 
 * copy of the elements in the old lists. Generic function (*cmp) returns 0 
 * when two elements are equal (see qOrderedInsert). The size elements is 
 * fixed to 'size'.
 */

QUEUE qDiff(QUEUE q,QUEUE r,int size,int (*cmp)(void *,void *));
/* Returns the elements in q not in r. The new list contains a 
 * copy of the elements in the old lists. Generic function (*cmp) returns 0 
 * when two elements are equal (see qOrderedInsert). The size elements is 
 * fixed to 'size'.
 */

unsigned int qCount(QUEUE q);
/* Returns the number of elements in a list. */

void *Queue2Array(QUEUE q,unsigned int size,unsigned int *num);
/* Returns an array (void *) containing a copy of all the elements in the 
 * queue q. The elements size is fixed to 'size'.
 * It also returns the number of elements in *num.
 */

QUEUE qAppend(QUEUE q,QUEUE r);
/* Returns the result of appending queue r in the end of queue q. 
 * The new list is not a copy: it collects the elements in q and r.
 * The structure of lists q and r is modified.
 */
