#include "list.h"

List *List_create() { return calloc(1, sizeof(List)); }

void List_destroy(List *list) {
	free(list->first);
  free(list->last);
  free(list);
}

void List_clear(List *list) {
  ListNode *temp = list->first;
	
	while(temp != NULL){
		free(temp->value);
		temp = temp->next;
		/*ListNode *temporal = temp->next;
		free(temp);
		temp = temporal;*/
	}
}

void List_clear_destroy(List *list) {
  List_clear(list);
  List_destroy(list);
}

void List_push(List *list, void *value) {
  ListNode *node = calloc(1, sizeof(ListNode));
  if (node == NULL) {
    return;
  }

  node->value = value;

  if (list->last == NULL) {
    list->first = node;
    list->last = node;
  } else {
    list->last->next = node;
    node->prev = list->last;
    list->last = node;
  }
  list->count++;
}

void *List_pop(List *list) {
  ListNode *node = list->last;
  return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value) {
  ListNode *node = calloc(1, sizeof(ListNode));
  if (node == NULL) {
    return;
  }

  node->value = value;
  if (list->first == NULL) {
    list->first = node;
    list->last = node;
  } else {
    node->next = list->first;
    list->first->prev = node;
    list->first = node;
  }

  list->count++;
}

void *List_shift(List *list) {
  ListNode *node = list->first;
  return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node) {
  void *result = NULL;

  if ((list->first == NULL && list->last == NULL) || (node == NULL)) {
    return NULL;
  }

  if (node == list->first && node == list->last) {
    list->first = NULL;
    list->last = NULL;
  } else if (node == list->first) {
    list->first = node->next;
    list->first->prev = NULL;
  } else if (node == list->last) {
    list->last = node->prev;
    list->last->next = NULL;
  } else {
    ListNode *after = node->next;
    ListNode *before = node->prev;
    after->prev = before;
    before->next = after;
  }

  list->count--;
  result = node->value;
  free(node);

  return result;
}
