#include "queue.h"
#include "hash.h"

/*----------------------------------------------------------------
   Creates a hash table 'numLists' lists (use a prime number), and
   'keySize' fixed size for all keys
   REQUIRES 'numLists' should be a prime number.
   RETURNS the pointer to the hash table structure.
*/
tHashTable *hashCreate(unsigned int numLists,unsigned int keySize)
{
  tHashTable *h=(tHashTable *) malloc(sizeof(tHashTable));
  h->lists=(QUEUE *)calloc(numLists,sizeof(QUEUE));
  h->numLists=numLists;
  h->keySize=keySize;
  
  return h;
}


/* Compares two hash entries using their keys. The key size is momentarily 
   stored in the static var 'auxKeySize'.
*/
static unsigned int auxKeySize;
static int entryCmp(void *e1, void *e2) {  
  return memcmp(((tHashEntry *)e1)->key,((tHashEntry *)e2)->key,auxKeySize);
}

/* Computes the hash value for a given key */
static unsigned int hv(tHashTable *h,void *key) {
  int n=sizeof(unsigned int);
  union {
    unsigned int x;
    char p[n];
  } u;

  unsigned int sum=0;
  
  int i;
  char *q=key;
  
  for (i=0;i<h->keySize/n;i++,q+=n) {
    memcpy(u.p,q,n);
    sum+=u.x;
  }
  
  for (i=0;i<n;i++) u.p[i]=0;
  memcpy(u.p,q,h->keySize % n);
  sum += u.x;
  
  return sum % h->numLists;
}

/*----------------------------------------------------------------
   Inserts an element in the hash table. For computing the hash value,
   it will use h->keySize bytes beginning at the 'key' pointer. The 'data'
   will be stored just as a pointer. If 'data' is not used, fix it to NULL.
   REQUIRES pointer 'h' must point to a correctly created non-null hash
           structure.
   RETURNS 1 if the element is inserted, 0 if the key was already in the table.
*/
int hashInsert(tHashTable *h,void *key, void *data) {
  tHashEntry e;
  e.key=key;
  e.data=data;
  auxKeySize=h->keySize;
  return qOrderedInsert(&h->lists[hv(h,key)],&e,sizeof(tHashEntry),entryCmp,0);
}

/* Searchs the first entry which is greater or equal than e */
static int geqEntry(QUEUE q, void *e) {  
  return entryCmp(qFirst(q,tHashEntry),e)>=0;
}

/*----------------------------------------------------------------
   Searchs for entry 'e'.
   REQUIRES e->key should contain the searched key. 
            The value of e->data before calling is irrelevant.
   RETURNS 0 if key was not found. 
           1 if key was found. 
	     If found, the corresponding data pointer is stored in e->data.
*/
int hashFind(tHashTable *h,tHashEntry *e) {
  QUEUE aux;
  /* Ordered search in the corresponding list */
  auxKeySize=h->keySize;
  aux=qBrowse(h->lists[hv(h,e->key)],geqEntry,e);
  
  if (aux!=qEMPTY && entryCmp(qFirst(aux,tHashEntry),e)==0) {
    e->data=qFirst(aux,tHashEntry)->data;
    return 1;
  }
    
  return 0; /* not found */
}

/*----------------------------------------------------------------
   Frees memory assigned to the hash table. 
   It will NOT free the assigned memory to each element key and element data,
   just the structures that exclusively correspond to the hash table structure.
*/
void hashFree(tHashTable *h) {
  /* Delete all lists */
  int i;
  for (i=0;i<h->numLists;i++)
    while (qIsNotEmpty(h->lists[i]))
      qDeleteFirst(&h->lists[i]);
  
  free(h->lists); /* Free the lists array */
  free(h);        /* Free the hash table structure */
}


