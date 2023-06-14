#include <stdlib.h>
#include <stdio.h>

#include "vector.h"

int main(){
    vector_t* vector = NULL;

	int val = 0;
	void* data_ptr = NULL;

	vector = vector_create(5);

	if(vector_push(vector, &val) != VECTOR_SUCCESS){
        printf("push failed\n");
    }

	if(vector_pop(vector, &data_ptr) != VECTOR_SUCCESS){
        printf("pop failed\n");
    }

	if(data_ptr != &val){
        printf("data_ptr: %p != &val: %p\n", data_ptr, &val);
    }

	vector_destroy(vector);
}