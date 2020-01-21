#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;

/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author Gabriel Casciano
 */
void PQ_insert(int priority, char * data) {
    //prepare new node for insertion
    Node_ptr_t new = malloc(sizeof(Node_t));
    new->data = data;
    new->priority = priority;
    
    //prepare temporary and iterator variables for use
    Node_ptr_t iter, tmp;
    iter = malloc(sizeof(Node_t));
    tmp = malloc(sizeof(Node_t));
    
    if(PQ_get_size() == 0){//if the head has not been initialized yet
        head = malloc(sizeof(Node_t));
        head = new;
    }
    else{
        tmp = malloc(sizeof(Node_t));//reset tmp
        for(iter = head; iter != NULL; iter = iter->next){
            if(iter->priority <= priority){//iter has equal or lower than new
                memcpy(tmp, iter, sizeof(Node_t));
                iter->data = data;
                iter->priority = priority;
                iter->next = tmp;
                break;//break out of loop
            }
            else if(iter->data == NULL){//end of loop, new lowest priority
                iter->next = malloc(sizeof(Node_t));
                iter->next = new;
            }
               
        }
    }
   
}
/**
 * Delete and return the node with the highest priority.
 * @return The highest priority Node.
 */
Node_ptr_t PQ_delete() {
    Node_ptr_t tmp = malloc(sizeof(Node_t));
    if(head != NULL){
        tmp = head;
        if(head->next != NULL)
            head = head->next;
        return tmp;
    }
    else
        return NULL;
}   

/**
 * Do NOT modify this function.
 * @return A pointer to the head of the list.  (NULL if list is empty.)
 */
Node_ptr_t PQ_get_head() {
    return head;
}

/**
 * Do NOT modify this function.
 * @return the number of items in the queue
 */
int PQ_get_size() {
    int size = 0;
    Node_ptr_t tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next, size++)
        ;
    return size;
}


