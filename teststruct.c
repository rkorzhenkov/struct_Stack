#include "myStack.h"
#include <stdio.h>

int main() {

    struct stack S;
    struct stack Q;
    struct stackElement head;
    struct stackElement head2;
    struct stackElement tmp;
    float index;
    
    init_stackElement(&head, 0);
    init_stackElement(&head2, 0);
    init_stack(&S, &head, 0);   //������������� �����
    init_stack(&Q, &head2, 0);
    
       
    input_stack(&S); //���� ����� � ����������
    printf("\n");
    
    stkPrint(S);    //������ �����
    printf("\n");
    
    /*           // pop
    tmp = pop(&S);
    printf("top element was = %f\n", get(tmp));
    printf("\n"); 
    stkPrint(S);
    printf("\n");
    */
    
    /*           //����� ����� � �������
    printf("length = %d\n", getlength(S));
    printf("top element is = %f\n", get(stkTop(S)));
    */
    
    /*          //��������
    inverse(&S);
    stkPrint(S);
    printf("\n");
    */
    
               //�������
    printf("now input second stack!\n");
    input_stack(&Q);
    stkPrint(Q);
    printf("\n");
    printf("now look at merged stacks!\n");
    merge(&Q, &S);
    stkPrint(Q);
    printf("\n");
    
    
                //�������� �� �����
    
    /*printf("input index to search and delete: ");
    scanf("%f", &index);
    delete_by_index(&S, index);
    stkPrint(S);
    printf("\n");
    
    
    /*             //����������
    sort(&S);
    stkPrint(S);
    */
    
    return 0;
}
