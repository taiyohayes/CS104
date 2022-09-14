#include "llrec.h"
#include <iostream>
//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot)
{
    if (head == NULL)
    {
        smaller = NULL;
        larger = NULL;
        return;
    }
    if (head->val <= pivot)
    {
        smaller = head;
        head = head->next;
        smaller->next = NULL;
        llpivot(head, smaller->next, larger, pivot);
    }
    else if (head->val > pivot)
    {
        larger = head;
        head = head->next;
        larger->next = NULL;
        llpivot(head, smaller, larger->next, pivot);
    }
}
