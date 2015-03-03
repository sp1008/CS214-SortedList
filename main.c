#include <string.h>
#include "sorted-list.h"

int compareInts(void *p1, void *p2){
	int i1 = *(int *)p1;
	int i2 = *(int *)p2;
	return i1 - i2;
}

int compareDoubles(void *p1, void *p2){
	double d1 = *(double *)p1;
	double d2 = *(double *)p2;
	if(d1 < d2){
		return -1;
	}else if(d1 > d2){
		return 1;
	}else{
		return 0;
	}
}

int compareStrings(void *p1, void *p2){
	char *s1 = p1;
	char *s2 = p2;
	return strcmp(s1, s2);
}

void destruct(void *a){
	free(a);
}

void testInts(){
	SortedListPtr sl = SLCreate(&compareInts, &destruct);
	int *n1 = malloc(sizeof(int*));
	int *n2 = malloc(sizeof(int*));
	int *n3 = malloc(sizeof(int*));
	int *n4 = malloc(sizeof(int*));
	int *n5 = malloc(sizeof(int*));
	int *n6 = malloc(sizeof(int*));
	
	*n1 = 5;
	*n2 = 10;
	*n3 = 3;
	*n4 = 8;
	*n5 = 11;
	*n6 = 9;
	
	printf("Test 1: Integers - inserting \n");
	
	SLInsert(sl, n1);
	SLInsert(sl, n2);
	SLInsert(sl, n3);
	SLInsert(sl, n5);
	SortedListIteratorPtr sp = SLCreateIterator(sl);
	
	int* foo;
	do{
		foo = SLNextItem(sp);
		if (foo == NULL) {
			break;
		}
		printf("%d\n", *foo);
	} while (foo != NULL);
	
	SLDestroyIterator(sp);
	
	printf("Test 2: Integers - removing, inserting, iterator repositioning \n");
	sp = SLCreateIterator(sl);
	
	foo = SLNextItem(sp);
	printf("%d\n", *foo);
	
	SLRemove(sl, n2);
	SLInsert(sl, n6);
	
	foo = SLNextItem(sp);
	printf("%d\n", *foo);
	SLRemove(sl, n1);
	foo = SLNextItem(sp);
	printf("%d\n", *foo);
	
	
	free(n1);
	free(n2);
	free(n3);
	free(n4);
	free(n5);
	free(n6);
	SLDestroyIterator(sp);
	SLDestroy(sl);
}

void emptyList(){
	SortedListPtr sl = SLCreate(&compareDoubles, &destruct);
	
	double *n1 = malloc(sizeof(double*));
	double *n2 = malloc(sizeof(double*));
	double *n3 = malloc(sizeof(double*));
	double *n4 = malloc(sizeof(double*));
	double *n5 = malloc(sizeof(double*));
	double *n6 = malloc(sizeof(double*));
	
	*n1 = 4.322;
	*n2 = 10.293;
	*n3 = -0.2;
	*n4 = -0.599;
	*n5 = 14.23;
	*n6 = 10.293;
	
	printf("Test 3: Adding, Empty List Iterator, Identical Data\n");
	
	SLInsert(sl, n1);
	SLInsert(sl, n2);
	SLInsert(sl, n3);
	SLInsert(sl, n4);
	SLInsert(sl, n5);
	SLInsert(sl, n6);
	
	SortedListIteratorPtr sp = SLCreateIterator(sl);
	double* boo;
	do{
		boo = SLNextItem(sp);
		if (boo == NULL) {
			break;
		}
		printf("%g\n", *boo);
	} while (boo != NULL);
	
	SLDestroyIterator(sp);
	SLRemove(sl, n1);
	SLRemove(sl, n2);
	SLRemove(sl, n3);
	SLRemove(sl, n4);
	SLRemove(sl, n5);
	sp = SLCreateIterator(sl);
	
	/*shouldn't print anything */
	do{
		boo = SLNextItem(sp);
		if (boo == NULL) {
			break;
		}
		printf("%g\n", *boo);
	} while (boo != NULL);
	
	SLDestroyIterator(sp);
	SLDestroy(sl);
}

void randomTest(){
	printf("Test 4: Restarting Iterator\n");
	SortedListPtr sl = SLCreate(&compareInts, &destruct);
	int *n1 = malloc(sizeof(int*));
	int *n2 = malloc(sizeof(int*));
	int *n3 = malloc(sizeof(int*));
	int *n4 = malloc(sizeof(int*));
	int *n5 = malloc(sizeof(int*));
	int *n6 = malloc(sizeof(int*));
	
	*n1 = 5;
	*n2 = 10;
	*n3 = 3;
	*n4 = 8;
	*n5 = 11;
	*n6 = 1;
	
	SLInsert(sl, n1);
	SLInsert(sl, n2);
	SLInsert(sl, n3);
	SLInsert(sl, n4);
	SortedListIteratorPtr sp = SLCreateIterator(sl);
	
	int* too;
	
	too = SLNextItem(sp);
	printf("%d\n", *too);
	
	SLInsert(sl, n6);
	SLRemove(sl, n4);
	SLInsert(sl, n5);
	SLRemove(sl, n2);
	
	do{
		too = SLNextItem(sp);
		if (too == NULL) {
			break;
		}
		printf("%d\n", *too);
	} while (too != NULL);
	
	printf("Test 5: Restart Iterator\n");
	SortedListIteratorPtr sp2 = SLCreateIterator(sl);
	do{
		too = SLNextItem(sp2);
		if (too == NULL) {
			break;
		}
		printf("%d\n", *too);
	} while (too != NULL);

	SLDestroyIterator(sp);
	SLDestroyIterator(sp2);
	SLDestroy(sl);
}

void charTest(){
	printf("Test 6: String Test\n");
	SortedListPtr sl = SLCreate(&compareStrings, &destruct);
	char *c1 = malloc(sizeof(char*) * 10);
	char *c2 = malloc(sizeof(char*) * 10);
	char *c3 = malloc(sizeof(char*) * 10);
	char *c4 = malloc(sizeof(char*) * 10);
	char *c5 = malloc(sizeof(char*) * 10);
	char *c6 = malloc(sizeof(char*) * 10);
	
	strcpy(c1, "May");
	strcpy(c2, "Say");
	strcpy(c3, "'Kay");
	strcpy(c4, "Jay");
	strcpy(c5, "Bay");
	strcpy(c6, "Pay");
	
	SLInsert(sl, c1);
	SLInsert(sl, c2);
	SLInsert(sl, c4);
	SLInsert(sl, c3);
	
	SortedListIteratorPtr sp = SLCreateIterator(sl);
	
	char *moo;

	do{
		moo = SLNextItem(sp);
		if (moo == NULL) {
			break;
		}
		printf("%s\n", moo);
	} while (moo != NULL);

	printf("Test 7: String Manipulation\n");
	SortedListIteratorPtr sp2 = SLCreateIterator(sl);
	
	moo = SLNextItem(sp2);
	printf("%s\n", moo);
	moo = SLNextItem(sp2);
	printf("%s\n", moo);
	
	SLInsert(sl, c5);
	SLRemove(sl, c3);
	SLRemove(sl, c4);
	SLInsert(sl, c6);
	
	do{
		moo = SLNextItem(sp2);
		if (moo == NULL) {
			break;
		}
		printf("%s\n", moo);
	} while (moo != NULL);
	
	printf("Test 8: Reset the Iterator\n");
	SortedListIteratorPtr sp3 = SLCreateIterator(sl);
	
	do{
		moo = SLNextItem(sp3);
		if (moo == NULL) {
			break;
		}
		printf("%s\n", moo);
	} while (moo != NULL);

	SLDestroyIterator(sp);
	SLDestroyIterator(sp2);
	SLDestroyIterator(sp3);
	SLDestroy(sl);
}
int main(int argc, char **argv)
{
	testInts();
	emptyList();
	randomTest();
	charTest();
	return 0;
}

