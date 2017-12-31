#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#define BREAKLINK(Q,QOLD,QNEXTOLD) {(QOLD)=(Q); (QNEXTOLD)=(Q)->next;(Q)=(Q)->next; (QOLD)->next=qEMPTY;}

/* Round queues */

static QUEUE qAux;

int qInsertFirst(QUEUE *q, void *e, int size)
{
  QUEUE p;
  
  if ((p=(QUEUE)malloc(sizeof(struct qNode)+size))!=NULL)
  { 
    memcpy((void *)(p->data),e,size);
    
    if (qIsEmpty(*q))
    { *q=p;
      (*q)->next=(*q);
    }
    else
    { p->next = (*q)->next;
      (*q)->next = p;
    }
    return 1;
  }
  else return 0;
}


int qDeleteFirst(QUEUE *q)
{ 
  QUEUE p;

  if (qIsEmpty(*q)) return 0;

  if (*q == (*q)->next)
  { free(*q);
    *q=qEMPTY;
  }
  else
  { p=(*q)->next;
    (*q)->next=p->next; 
    free(p);
  }
  return 1;
}

int qInsertLast(QUEUE *q, void *e, int size)
{
  QUEUE p;
  
  if (!qInsertFirst(q,e,size))
    return 0;
  *q=(*q)->next;
  return 1;
}

QUEUE qBrowse(QUEUE q, int (*found)(QUEUE, void *),void *data)
{
  QUEUE p;
  int stop;
  
  if (qIsNotEmpty(q))
  { 
    p=q;
    while (! (stop=(*found)(p,data) ) &&
           (p=p->next)!=q );
    if (stop)
      return p;
  }
  return NULL;
}

int qDelete(QUEUE *q, QUEUE pos)
{
  if (qIsEmpty(*q) || qIsEmpty(pos) ) return 0;

  if (pos->next==*q)
  {
    *q=pos;
    return qDeleteFirst(q);
  }
  
  return qDeleteFirst(&pos);
}

int qMove(QUEUE *q1, QUEUE *q2, int (*movethis)(void *elem),int size)
{
  QUEUE p;
  
  p=qEMPTY;
  while (qIsNotEmpty(*q1))
  {
    if ((*movethis)((void *)(*q1)->next->data))
      { if (!qInsertLast(q2,(void *)((*q1)->next->data),size)) return 0; }
    else
      { if (!qInsertLast(&p,(void *)((*q1)->next->data),size)) return 0; }
    if (!qDeleteFirst(q1)) return 0;
  }
  *q1=p;

  return 1;
}


int qFree(QUEUE *q)
{ 
  while ((*q)!=NULL) qDeleteFirst(q);
}

struct cmpData
{
  void *elem;
  int (*cmp)(void *, void *);  
};

static int FirstIsgeqThan(QUEUE q,void *e)
{
  struct cmpData *d;
  d=(struct cmpData*)e;
  return (d->cmp(q->next->data,d->elem)>=0);
}

int qOrderedInsert(QUEUE *q, void *e, int size,int (*cmp)(void *, void *),
               char repeating)
{
  QUEUE p;
  struct cmpData d;
  
  d.cmp=cmp;
  d.elem=e;
  p=qBrowse(*q,FirstIsgeqThan,&d);
  if (p==NULL)
    qInsertLast(q,e,size);
  else
    {
      if (!repeating && cmp(p->next->data,e)==0) return 0;
      qInsertAt(q,p,e,size);
    }
  return 1;
}

int qDeleteThoseThat(QUEUE *q,int (*DeleteThis)(QUEUE,void *),void *data)
{
  QUEUE p;
  char InFirst;
  int n=0;

  if (qIsNotEmpty(*q))
  { 
    p=*q;
    InFirst=1;
    do
    {
      if (DeleteThis(p,data))
      {
        qDelete(q,p);
	n++;
        if (InFirst) InFirst=(p==*q);
      }
      else
      {
        p=p->next;
	InFirst=0;
      }
    } while(qIsNotEmpty(*q) && (p!=*q || InFirst));
  }
  return n;
}


static int CopyElem(QUEUE q,void *e)
{
  qInsertLast(&qAux,q->next->data,*(int *)e);
  return 0;
}

QUEUE qCopy(QUEUE q,int size)
{
  qAux=qEMPTY;
  qBrowse(q,CopyElem,&size);
  return qAux;
}

#define COPY(Q) qInsertLast(&qAux,(Q)->data,size)
#define MOVE(Q) (Q)=(Q)->next;


QUEUE qMerge(QUEUE q,QUEUE r,int size,int (*cmp)(void *,void *),char repeating)
{
  QUEUE qOld,rOld,qNextOld,rNextOld;
  int comp;

  if (qIsEmpty(q))
    if (qIsEmpty(r)) return qEMPTY;
    else return qCopy(r,size);
  
  if (qIsEmpty(r)) return qCopy(q,size);
    
  /* Momentaneously break the round links */
  BREAKLINK(q,qOld,qNextOld);
  BREAKLINK(r,rOld,rNextOld);

  qAux=qEMPTY;
  while (q!=qEMPTY && r!=qEMPTY)
  {
    comp=cmp(q->data,r->data);
    
    if (comp<0)      {COPY(q); MOVE(q);}
    else if (comp>0) {COPY(r); MOVE(r);}
    else            {
        	     COPY(q); 
        	     if (repeating) COPY(r);
		     MOVE(q); MOVE(r);
	            }
  }

  while (q!=qEMPTY) {COPY(q); MOVE(q);}
  while (r!=qEMPTY) {COPY(r); MOVE(r);}

  /* Restore round links */
  qOld->next=qNextOld;
  rOld->next=rNextOld;
  
  return qAux;
}

QUEUE qIntersect(QUEUE q,QUEUE r,int size,int (*cmp)(void *,void *))
{
  QUEUE qOld,rOld,qNextOld,rNextOld;
  int comp;
  
  if (qIsEmpty(q)||qIsEmpty(r)) return qEMPTY;
    
  /* Momentaneously break the round links */
  BREAKLINK(q,qOld,qNextOld);
  BREAKLINK(r,rOld,rNextOld);

  qAux=qEMPTY;
  while (q!=qEMPTY && r!=qEMPTY)
  {
  
    comp=cmp(q->data,r->data);
    if (comp<0)     {MOVE(q);}
    else if(comp>0) {MOVE(r);}
    else            {COPY(q); MOVE(q); MOVE(r);}
  }

  /* Restore round links */
  qOld->next=qNextOld;
  rOld->next=rNextOld;
  
  return qAux;
}

QUEUE qDiff(QUEUE q,QUEUE r,int size,int (*cmp)(void *,void *))
{
  QUEUE qOld,rOld,qNextOld,rNextOld;
  int comp;
  
  if (qIsEmpty(q)) return qEMPTY;
  if (qIsEmpty(r)) return qCopy(q,size);
      
  /* Momentaneously break the round links */
  BREAKLINK(q,qOld,qNextOld);
  BREAKLINK(r,rOld,rNextOld);

  qAux=qEMPTY;
  while (q!=qEMPTY && r!=qEMPTY)
  {
    comp=cmp(q->data,r->data);
    if (comp<0)     {COPY(q); MOVE(q);}
    else if(comp>0) {MOVE(r);}
    else            {MOVE(q); MOVE(r);}
  }

  while (q!=qEMPTY) {COPY(q); MOVE(q);}

  /* Restore round links */
  qOld->next=qNextOld;
  rOld->next=rNextOld;
  
  return qAux;
}


static int CountElem(QUEUE q,void *e)
{
  *(unsigned int *)e+=1;
  return 0;
}

unsigned int qCount(QUEUE q)
{
  unsigned int c=0;
  qBrowse(q,CountElem,(void*)&c);
  return c;
}




struct CopyArrayData {
  char *p;
  size_t size;
};
static int Copy2Array(QUEUE q,void *e)
{
  struct CopyArrayData *d;
  d=(struct CopyArrayData *)e;
  memcpy(d->p,qFirst(q,char),d->size);
  d->p+=d->size;
  return 0;
}

void *Queue2Array(QUEUE q,size_t size,unsigned int *num)
{
  void *a;
  struct CopyArrayData d;
  
  *num=qCount(q);
  if (qIsEmpty(q)) return NULL;
  a=(void *)malloc(*num*size);
  d.p=(char *)a;
  d.size=size;
  qBrowse(q,Copy2Array,(void *)&d);
  return a;
}

QUEUE qAppend(QUEUE q,QUEUE r)
{
  QUEUE aux;
  if (qIsEmpty(q)) return r;
  if (qIsEmpty(r)) return q;
  aux=r->next;
  r->next=q->next;
  q->next=aux;
  return r;
}
