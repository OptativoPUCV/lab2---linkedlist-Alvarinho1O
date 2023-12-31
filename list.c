#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* newList = (List*)malloc(sizeof(List));
    if (newList == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para la lista.\n");
        exit(EXIT_FAILURE);
    }
    newList->head = NULL;
    return newList;
}

void * firstList(List * list) {
  if (list->head != NULL) {
    list->current = list->head;
    return list->current->data;
  }else {
    fprintf(stderr, "Error: La lista está vacía.\n");
    return NULL;
  }
}

void * nextList(List * list) {
  if (list->current != NULL && list->current->next != NULL) {
    list->current = list->current->next;
    return list->current->data;
  }else {
    fprintf(stderr, "Error: No hay nodo siguiente o el nodo actual no está configurado.\n");
    return NULL;
  }
}

void * lastList(List * list) {
  if (list->tail != NULL) {
    list->current = list->tail;
    return list->current->data;
  }else {
    fprintf(stderr, "Error: La lista está vacía.\n");
    return NULL;
    }

}

void * prevList(List * list) {
  if (list->current != NULL && list->current->prev != NULL) {
      list->current = list->current->prev;
      return list->current->data;
  }else {
      fprintf(stderr, "Error: No hay nodo anterior o el nodo actual no está configurado.\n");
      return NULL;
    }

}

void pushFront(List * list, void * data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

void pushBack(List * list, void * data) {
    Node* newNode = createNode(data);
    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void pushCurrent(List * list, void * data) {
    if (list->current == NULL) {
        fprintf(stderr, "Error: El nodo actual no está configurado.\n");
        return;
    }

    Node* newNode = createNode(data);
    newNode->next = list->current->next;
    newNode->prev = list->current;
    
    if (list->current->next != NULL) {
        list->current->next->prev = newNode;
    } else {
        list->tail = newNode;
    }
    
    list->current->next = newNode;
}

void * popFront(List * list) {
    if (list->head == NULL) {
        fprintf(stderr, "Error: La lista está vacía.\n");
        return NULL;
    }
    Node* oldHead = list->head;
    void* data = oldHead->data;
    list->head = oldHead->next;
    if (list->head != NULL) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }
    free(oldHead);
    return data;
}

void * popBack(List * list) {
    if (list->tail == NULL) {
        fprintf(stderr, "Error: La lista está vacía.\n");
        return NULL;
    }
    Node* oldTail = list->tail;
    void* data = oldTail->data;
    list->tail = oldTail->prev;
    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }
    free(oldTail);
    return data;
}

void * popCurrent(List * list) {
    if (list->current == NULL) {
        fprintf(stderr, "Error: El nodo actual no está configurado.\n");
        return NULL;
    }
    Node* currentNode = list->current;
    void* data = currentNode->data;

    if (currentNode->prev != NULL) {
        currentNode->prev->next = currentNode->next;
    } else {
        list->head = currentNode->next;
    }
    if (currentNode->next != NULL) {
        currentNode->next->prev = currentNode->prev;
    } else {
        list->tail = currentNode->prev;
    }
    if (currentNode->prev == NULL && currentNode->next == NULL) {
        list->head = NULL;
        list->tail = NULL;
    }
    list->current = currentNode->next;
    free(currentNode);
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}