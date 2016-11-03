#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define PLSDEF 100

void *gplstable;

struct plsblock { 
int active; 
int size; 
void *addr; 
struct plsblock *next; 
}; 


void *mempls(int size) { 

char *start = sbrk(size + 1); 

while(--size)
start[size] = 0; 

return start; 
} 





char *pls_start(int blocks) { 
int pls_size = blocks * sizeof(struct plsblock); 
int i;
int sblock = sizeof(struct plsblock); 
struct plsblock *newblock; 
char *plstable = mempls(pls_size); 
for(i = 0; i < pls_size; i += sizeof(struct plsblock)) { 
newblock = (struct plsblock *) (plstable + i); 
newblock->next = (((int) newblock) + sblock); 
newblock->addr = NULL; 
newblock->size = 0;
newblock->active = 0; 
}
newblock->next = NULL; 
gplstable = plstable; 
return plstable; 

}

void *addmem(int size) { 

struct plsblock *pblock = gplstable; 

while(pblock->size > 0) { 
if(pblock->next == NULL)
return NULL;
if(pblock->size  > size && pblock->active == 0)
break; 
pblock = pblock->next; 
}


if(pblock->addr != NULL) { 
pblock->active = 1;
return pblock->addr; 
}
pblock->addr = mempls(size); 
pblock->size = size; 
pblock->active = 1; 

return pblock->addr; 

} 


int plsfree(void *addr) {
int i; 
struct plsblock *pblock = gplstable;
while((int) pblock->addr != (int) addr) { 
if(pblock->next == NULL)
return 1;
pblock = pblock->next; 
} 
pblock->active = 0; 
char *clean = pblock->addr;
for(i = 0;i < pblock->size; ++i)  
clean[i] = 0; 

return 0; 

} 

