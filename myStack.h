#include<stdio.h>
#include<malloc.h>

struct stackElement {
              float x; //само значение
              struct stackElement* prev; //указатель на предыдущий элемент
              struct stackElement* next; //указатель на следующий элемент
              
};      

              void init_stackElement(struct stackElement* sE, float xx) {
                   sE->x = xx;
                   sE->prev = NULL;
                   sE->next = NULL;
                   return;     
              }
             

             float get(struct stackElement sE) {
                   return sE.x;      
             } //получить значение
             
             
             struct stackElement* nextElPtr(struct stackElement sE) {
                          return sE.next;
             } //возвращает указатель на следующий элемент
             
             struct stackElement* previousElPtr(struct stackElement sE) {
                          return sE.prev;
             } //возвращает указатель на предыдущий элемент
             
             
             
             void linkToPreviousEl(struct stackElement* sE, struct stackElement* prevElement) {
                  sE->prev = prevElement;
                  prevElement->next = sE;
                  return;
             } //связывает элемент с данным предыдущим
             
             void linkToNextEl(struct stackElement* sE, struct stackElement* nextElement) {
                  sE->next = nextElement;
                  nextElement->prev = sE;
                  return;
             } //связывает элемент с данным следующим
             
             void nullNextElPtr(struct stackElement* sE) {
                  sE->next = NULL;
                  return;     
             } //обнуление указателя на следующий элемент
             
             void nullPreviousElPtr(struct stackElement* sE) {
                  sE->prev = NULL;
                  return;     
             } //обнуление указателя на предыдущий элемент
             
             
             void insertUpper(struct stackElement* sE, struct stackElement* prv) {  // вставка элемента перед данным в цепи
                  struct stackElement* nxt;
                  int flag = 1;
                  if (prv->next != NULL)
                     nxt = prv->next;
                  else 
                       flag = 0;
                  linkToPreviousEl(sE, prv);
                  if (flag == 1)
                     linkToNextEl(sE, nxt);
                  return;                  
             }
             
             void insertLower(struct stackElement* sE, struct stackElement* nxt) {  // вставка элемента после данного в цепи
                  struct stackElement* prv;
                  int flag = 1;
                  if (nxt->prev != NULL)
                     prv = nxt->prev;
                  else 
                       flag = 0;
                  linkToNextEl(sE, nxt);
                  if (flag == 1)
                     linkToPreviousEl(sE, prv);
                  return;                  
             }
             
             void excludeFromChain(struct stackElement* sE) {  //исключение элемента из цепи
                  struct stackElement *nxt;
                  struct stackElement *prv;
                  int flag_next = 1;
                  int flag_prev = 1;
                  if (sE->next == NULL)
                     flag_next = 0;
                  else
                      nxt = sE->next;
                  if (sE->prev == NULL)
                     flag_prev = 0;
                  else
                      prv = sE->prev;
                  if (flag_next * flag_prev == 1)
                     linkToPreviousEl(nxt, prv);
                  else if (flag_next == 0)
                       prv->next = NULL;
                  else 
                       nxt->prev = NULL;
                  sE->next = NULL;
                  sE->prev = NULL;
                  return;
             }

struct stack {
            struct stackElement* header;
            int length;
};
 
    void init_stack(struct stack* stk, struct stackElement* head, int len) {
         stk->header = head;
         stk->length = len;
         return;     
    }

void push(struct stack* stk, struct stackElement* sE) { 
     insertLower(sE, stk->header);
     ++(stk->length);
     return;
} 

void input_stack(struct stack* stk) {
	int initial_length;
	int i, n;
	float elem;
	struct stackElement* element_to_push;
	initial_length = stk->length;
	printf("input number of elements to input: ");
  	scanf("%d", &n);
  	for(i = initial_length + 1; i <= initial_length + n; i++) {
    	printf("input element # %d: ", i);
    	scanf("%f", &elem);
    	element_to_push = (struct stackElement*)malloc(sizeof(struct stackElement));
    	init_stackElement(element_to_push, elem);
    	push(stk, element_to_push);
  	}
  	return;
}

void stkPrint(struct stack stk) {
  int i;
  struct stackElement* sE;
  i = stk.length;
  sE = stk.header;
  if(i == 0) {
       printf("Stack is empty!\n");
       return;
  }
  do {
    i--;
    sE = previousElPtr(*sE);
    printf("%f\n", get(*sE));
  } while(i>0);
  printf("End of stack!\n");
  return;
}

struct stackElement pop(struct stack* stk) {
  struct stackElement* sE;
  if((stk->length) > 0) {
    stk->length--;    
    sE = previousElPtr(*(stk->header));
    excludeFromChain(sE);
    return *sE;
  } else {
    printf("stack is empty!\n");
    return *(stk->header);
  }
}

struct stackElement stkTop(struct stack stk) {
  if((stk.length) > 0) {
    return *(previousElPtr(*(stk.header)));
  } else {
    printf("stack is empty!\n");
    return *(stk.header);
  }
}

int getlength(struct stack stk) {
 return(stk.length);
}

void sort(struct stack* stk) {
     struct stack sorted;
     struct stackElement* current;
     int flag, j, i;    
     struct stackElement* sE;
     struct stackElement* prv = NULL;
     
     if (stk->length < 2) 
        return;   
     init_stack(&sorted, stk->header, 1);

     sE = previousElPtr(*(previousElPtr(*(stk->header))));
     for (i = stk->length - 2; i >= 0; --i) {
         if (i > 0)
            prv = previousElPtr(*sE);
         excludeFromChain(sE);
         current = previousElPtr(*(sorted.header));
         flag = 0;
         j = sorted.length;
         while (flag == 0 && j > 0) {
               --j;
               if (get(*sE) >= get(*current))
                  flag = 1;
               if (j > 0 && flag == 0)
                  current = previousElPtr(*current);                  
         }
         if (flag == 1)
            insertUpper(sE, current);
         else
             insertLower(sE, current);
         ++(sorted.length);
         if (i > 0)
            sE = prv;
     }
     return;
}

void inverse(struct stack* stk) {  //инвертировать стек
	int n, i;
    struct stackElement *current;   //последний новоупорядоченный элемент
	struct stackElement *beforeLast; //следующий для последнего староупорядоченного
	struct stackElement *last;       //последний староупорядоченный
	
    n  = stk->length;
	if (n < 2)
	   return;           //если длина < 2 - ничего не делать
	
	current = (stk->header);
	beforeLast =  (stk->header);
	
	for (i = 1; i < n; ++i)
	    beforeLast = previousElPtr(*beforeLast);
     last = previousElPtr(*beforeLast);
     for (i = 1; i <= n; ++i) {
         excludeFromChain(last);
         insertLower(last, current);
         current = last;
         last = beforeLast;
         beforeLast = nextElPtr(*beforeLast);
     }
     return;
}

void merge(struct stack* stk, struct stack* paste) {
     int n_bottom;
     int n_top;
     int i;
     struct stackElement *sE;
     
     n_bottom = stk->length;    
     n_top = getlength(*paste);     
     sE = paste->header;
     for (i = 1; i <= n_top; i++)
         sE = previousElPtr(*sE);
     linkToNextEl(stk->header, sE);
     excludeFromChain(stk->header);
     stk->header = paste->header;
     stk->length = n_top + n_bottom;
     return;
}

void delete_by_index(struct stack* stk, float key) {
     int n;
     n  = stk->length;
     struct stackElement* sE;
     struct stackElement* removed;
     
     if (n == 0)
        return;
        
     sE = previousElPtr(*(stk->header));
     while (n > 0) {
             --n;
             if (get(*sE) == key) {
                           removed = sE;
                           if (n>0) 
                              sE = previousElPtr(*sE);
                           excludeFromChain(removed);
                           --(stk->length);
                           free(removed);
             } else
                   if (n>0)
                      sE = previousElPtr(*sE);
                      
     }
	return;
}

void delete_stack(struct stack* stk) {
     stk->header = NULL;
     free(stk);
     return;
}


