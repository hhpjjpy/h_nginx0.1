#include "hgx_array.h"

#include <stdio.h>

#define TESTNULL(p,msg) if(p==NULL){ printf("error :%s \n",msg); exit(-1); }


int main(){
	hgx_pool *pool = hgx_create_pool(HGX_DEFAULT_POOL_SIZE,NULL);
	TESTNULL(pool, "create pool error ")

	hgx_array *a = hgx_create_init_array(pool,1000,sizeof(int));
	TESTNULL(a, " create init arrat error ")

	int count = 0;
	while (count < 10000){
		void *p = hgx_push_array(pool);
		TESTNULL(p, " push array error ")
		*((int*)(p)) = count;
		count++;
	}
	
	//±éÀúÒ»±é

	







}