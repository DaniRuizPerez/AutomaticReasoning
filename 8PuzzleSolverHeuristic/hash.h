#include <stdio.h>

typedef struct tHashTable_ {
  QUEUE *lists;		   /* Array of lists */
  unsigned int numLists;   /* Number of lists (use a prime number) */
  unsigned int keySize;    /* Fixed size for all keys */
} tHashTable;

typedef struct tHashEntry_ {
  void *key;		/* Pointer to key */
  void *data;		/* Pointer to data */
} tHashEntry;


/*----------------------------------------------------------------
   Creates a hash table 'numLists' lists (use a prime number), and
   'keySize' fixed size for all keys
   REQUIRES 'numLists' should be a prime number.
   RETURNS the pointer to the hash table structure.
*/
tHashTable *hashCreate(unsigned int numLists,unsigned int keySize);

/*----------------------------------------------------------------
   Inserts an element in the hash table. For computing the hash value,
   it will use h->keySize bytes beginning at the 'key' pointer. The 'data'
   will be stored just as a pointer. If 'data' is not used, fix it to NULL.
   REQUIRES pointer 'h' must point to a correctly created non-null hash
           structure.
   RETURNS 1 if the element is inserted, 0 if the key was already in the table.
*/
int hashInsert(tHashTable *h,void *key, void *data);


/*----------------------------------------------------------------
   Searchs for entry 'e'.
   REQUIRES e->key should contain the searched key. 
            The value of e->data before calling is irrelevant.
   RETURNS 0 if key was not found. 
           1 if key was found. 
	     If found, the corresponding data pointer is stored in e->data.
*/
int hashFind(tHashTable *h,tHashEntry *e);

/*----------------------------------------------------------------
   Frees memory assigned to the hash table. 
   It will NOT free the assigned memory to each element key and element data,
   just the structures that exclusively correspond to the hash table structure.
*/
void hashFree(tHashTable *h);
