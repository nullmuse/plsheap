#include "plsmem.h"


int main(int argc, char *argv[]) { 

int i,k; 
char *fmem; 
char *ptr;
char *ptar[60];
struct plsblock *plsptr;
char *ptr1 = "data one"; 
char *ptr2 = "DATA two"; 
char *ptr3 = "three"; 
char *ptr4 = "This is data 4";  
if(--argc) { 
char *plstable = pls_start(50);
fmem = addmem(2);  
k = argc / 2; 
for(i = 1; i <= argc; i++) { 
   ptr = addmem(strlen(argv[i]) + 1); 
   memcpy(ptr,argv[i],strlen(argv[i]) + 1); 
   ptar[i] = ptr; 
} 
printf("Printing heap memory:\n\n"); 
plsptr = (struct plsblock *) plstable;
while(plsptr->next != NULL) {
printf("plsblock at %p\n\tplsblock->active: %i\n\tplsblock->size: %i\n\tplsblock->addr: %p\n",plsptr,plsptr->active,plsptr->size,plsptr->addr); 
if(plsptr->addr != NULL)
printf("\t\t%s\n",plsptr->addr); 
printf("\tplsblock->next: %p\n",plsptr->next); 
plsptr = plsptr->next; 
} 
printf("Above is heap memory with your values allocated\n");
printf("Press enter to continue\n"); 
fgets(fmem,2,stdin); 
printf("\n\nfreeing half\n"); 
for(i=0;i < argc; i += 2) { 
plsfree(ptar[i]); 
} 
printf("Printing heap memory:\n\n");
plsptr = (struct plsblock *) plstable;
while(plsptr->next != NULL) {
printf("plsblock at %p\n\tplsblock->active: %i\n\tplsblock->size: %i\n\tplsblock->addr: %p\n",plsptr,plsptr->active,plsptr->size,plsptr->addr);
if(plsptr->addr != NULL)
printf("\t\t%s\n",plsptr->addr);
printf("\tplsblock->next: %p\n",plsptr->next);
plsptr = plsptr->next;
}
printf("Above is heap memory with every other value you entered free'd\n"); 
printf("Press moar enter to continuen\n"); 
fgets(fmem,2,stdin);
printf("Allocating stack data\n\n"); 
ptr = addmem(strlen(ptr1) + 1); 
memcpy(ptr,ptr1,strlen(ptr1)); 
ptr = addmem(strlen(ptr2) + 1);
memcpy(ptr,ptr2,strlen(ptr2));
ptr = addmem(strlen(ptr3) + 1);
memcpy(ptr,ptr3,strlen(ptr3));
ptr = addmem(strlen(ptr4) + 1);
memcpy(ptr,ptr4,strlen(ptr4));
printf("Printing heap memory:\n\n");
plsptr = (struct plsblock *) plstable;
while(plsptr->next != NULL) {
printf("plsblock at %p\n\tplsblock->active: %i\n\tplsblock->size: %i\n\tplsblock->addr: %p\n",plsptr,plsptr->active,plsptr->size,plsptr->addr);
if(plsptr->addr != NULL)
printf("\t\t%s\n",plsptr->addr);
printf("\tplsblock->next: %p\n",plsptr->next);
plsptr = plsptr->next;
}
printf("Above is heap memory after I have allocated some data on the stack into the heap.\n"); 
printf("Done\n"); 

}
else
printf("./plstest this is some data please allocate\n");
}
