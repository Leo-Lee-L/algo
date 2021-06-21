#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct array {
	int size;
	int used;
	int *arr;
};

void dump(struct array *array)//���ѷ�
{
	int idx;

	for (idx = 0; idx < array->used; idx++)
		printf("[%02d]: %08d\n", idx, array->arr[idx]);
}

void alloc(struct array *array)
{
	array->arr = (int *)malloc(array->size * sizeof(int));
}

int insert(struct array *array, int elem)
{
	int idx;
	if (array->used >= array->size)
		return -1;

	for (idx = 0; idx < array->used; idx++) {
		if (array->arr[idx] > elem)
			break;
	}

	if (idx < array->used)
		memmove(&array->arr[idx+1], &array->arr[idx],
			(array->used - idx) * sizeof(int));
		//void *memmove(void *str1, const void *str2, size_t n)
		//copies n characters from str2 to str1, but for overlapping memory blocks,
		// memmove() is a safer approach than memcpy().
	array->arr[idx] = elem;
	array->used++;
	return idx;
}

int delete(struct array *array, int idx)
{
	if (idx < 0 || idx >= array->used)
		return -1;

	memmove(&array->arr[idx], &array->arr[idx+1],
		(array->used - idx - 1) * sizeof(int));
	array->used--;
	return 0;
}

int search(struct array *array, int elem)
{
	int idx;

	for (idx = 0; idx < array->used; idx++) {
		if (array->arr[idx] == elem)
			return idx;
		if (array->arr[idx] > elem)
			return -1;
	}

	return -1;
}

int main()
{
	int idx;
	struct array ten_int = {10, 0, NULL};//size used *arr

	alloc(&ten_int);
	//alloc()��ջ�ϴ����ռ䣬����ִ�н������Զ����ͷţ�Ч�ʺܸߵ��ڴ�ռ�����
	if (!ten_int.arr)
		return -1;
	insert(&ten_int, 1);
	insert(&ten_int, 3);
	insert(&ten_int, 2);
	printf("=== insert 1, 3, 2\n");
	dump(&ten_int);

	idx = search(&ten_int, 2);
	printf("2 is at position %d\n", idx);
	idx = search(&ten_int, 9);
	printf("9 is at position %d\n", idx);

	printf("=== delete [6] element \n");
	delete(&ten_int, 6);
	dump(&ten_int);
	printf("=== delete [0] element \n");
	delete(&ten_int, 0);
	dump(&ten_int);
	return 0;
}
