#include "hgx_palloc.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void clearUpTest(void *data){
	char *string = (char*)(data);
	printf("clear up to done %s \n",string);
}

int main(){
	hgx_pool *pool = hgx_create_pool(16*1024,NULL);
	int alloc_num = 0;
	int count = 0;
	alloc_num = 4000;
	while (alloc_num != -1 && count<10000){
		void *p = hgx_pcalloc(pool, alloc_num);
		printf("count %d \n",++count);
	}
	void *ptr_array[1000];
	for (int i = 0; i < 1000;i++){
		ptr_array[i] = hgx_pcalloc(pool,6666);
		memcpy(ptr_array[i],"memnory test success ",30);
	}
	for (int i = 0; i < 1000;i++){
		printf("index: %d , %s \n",i,(char*)ptr_array[i]);
	}
	
	for (int i = 45; i < 75;i++){
		int ret = hgx_pfree_large(pool,ptr_array[i]);
		if (ret != 0){
			printf("pfree_large error \n");
		}
	}
	

	hgx_pool_cleanup_add(pool,clearUpTest,"success ");

	hgx_destory_pool(pool, NULL);
	
	sleep(10);

	printf("malloc size : %ld , free size : %ld \n",mallocsize,freesize);
}