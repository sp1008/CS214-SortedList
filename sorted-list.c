#include "sorted-list.h"

/* SORTED LIST FUNCTIONS */
SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df){
	SortedListPtr list = malloc(sizeof(struct SortedList) + 1);
	
	list->start = NULL;
	list->cf = cf;
	list->df = df;
	
	return list;
}

void SLDestroy(SortedListPtr list){
	ItemPtr temp = list->start;
	while(temp != NULL){
		ItemPtr temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
	free(list);
}

int SLInsert(SortedListPtr list, void *newObj){
	if(newObj == NULL){
		return 0;
	}
	
	/* create new item node with new Object */
	ItemPtr brandNew = malloc(sizeof(struct Item) + 1);
	brandNew->data = newObj;
	brandNew->ptrRef = 0;
	
	/* empty list */
	if(list->start == NULL){
		list->start = brandNew;
		brandNew->next = NULL;
		brandNew->ptrRef++;
		return 1;
	}		
		/* using comparator */
	ItemPtr temp = list->start;
	/* at the front */
	if(list->cf(brandNew->data, temp->data) > 0){
		list->start = brandNew;
		brandNew->next = temp;
		brandNew->ptrRef++;
		return 1;
	}else if(list->cf(brandNew->data, temp->data) == 0){
		printf("ERROR: This list does not permit two identical data\n");
		return 0;
	}
	/* in the middle */
	while(temp->next != NULL){
		if(list->cf(brandNew->data, temp->next->data) > 0){
			brandNew->next = temp->next;
			brandNew->ptrRef++;
			temp->next = brandNew;
			return 1;
		}else if(list->cf(brandNew->data, temp->next->data) == 0){
			printf("ERROR: This list does not permit two identical data\n");
			return 0;
		}else{
			temp = temp->next;
		}
	}
	/* last item */
	temp->next = brandNew;
	brandNew->next = NULL;
	brandNew->ptrRef++;
	return 1;
}

int SLRemove(SortedListPtr list, void *newObj){
	if((list->start == NULL) || (newObj == NULL)){
		return 0;
	}
	
	ItemPtr temp = list->start;
	/* off with the head */
	if(list->cf(temp->data, newObj) == 0){
		list->start = temp->next;
		temp->ptrRef--;
		free(temp);
		return 1;
	}else{
	/* find them and destroy them */
		ItemPtr prev = temp;
		temp = temp->next;
		while((temp->next != NULL) && (list->cf(temp->data, newObj) > 0)){
			prev = temp;
			temp = temp->next;
		}
		if(list->cf(newObj, temp->data) == 0){
			prev->next = temp->next;
			temp->ptrRef--;
			free(temp);
			return 1;
		}else{
			printf("We could not locate that data in the list.\n");
			return 0;
		}
	}
}

/* ITERATOR FUNCTIONS */
SortedListIteratorPtr SLCreateIterator(SortedListPtr list){
	SortedListIteratorPtr iterator = malloc(sizeof(struct SortedListIterator) + 1);
	if(list->start != NULL){
		iterator->head = list;
		iterator->current = list->start;
		iterator->current->ptrRef++;
		iterator->worth = list->start->data;
		return iterator;
	}
	else{
		return NULL;
	}
}

void SLDestroyIterator(SortedListIteratorPtr iter){
	if((iter != NULL) && (iter->current != NULL)){
		iter->current->ptrRef--;
	}
	
	free(iter);
}

void *SLGetItem(SortedListIteratorPtr iter){
	if((iter == NULL) || (iter->current == NULL)){
		return 0;
	}else{
		return iter->current->data;
	}
}

void *SLNextItem(SortedListIteratorPtr iter){
	if((iter == NULL) || (iter->current == NULL)){
		return NULL;
	}
	
	void *data;
	/* make sure we don't send the deleted data back */
	if(iter->current->ptrRef != 2){
		reRailIter(iter);
	}
	
	data = iter->current->data;
	
	iter->current->ptrRef--;
	iter->current = iter->current->next;
	
	if(iter->current != NULL){
		iter->current->ptrRef++;
		iter->worth = iter->current->data;
	}
	
	return data;
}

/* helper function */
void reRailIter(SortedListIteratorPtr iter){
	ItemPtr onTrack = iter->head->start;
	
	while(iter->head->cf(onTrack->data, iter->worth) > 0){
		onTrack = onTrack->next;
	}
	
	iter->current = onTrack;
	iter->current->ptrRef++;
}
