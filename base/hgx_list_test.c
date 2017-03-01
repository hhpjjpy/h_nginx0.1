#include "hgx_list.h"

#include <stdio.h>
#include <unistd.h>

int main() {
	hgx_pool *pool = hgx_create_pool(HGX_DEFAULT_POOL_SIZE,NULL);
	
	hgx_list *list;
	if (hgx_list_init(&list,pool,10,sizeof(int)) != 0) {
		printf("list init error \n");
		return -1;
	}

	for (int i = 0; i < 1000;i++) {
		void *p = hgx_list_push(list);
		if (p == NULL) {
			printf("list push error \n");
			return -1;
		}
		*((int*)p) = i * 10;
	}

	//±éÀúÒ»±é
	hgx_list_node *p = &list->part;
	while (p) {
		char *ptr = (char*)(p->datas);
		for (int i = 0; i < p->nums;i++) {
			int data = *((int*)(ptr + (list->size)*i));
			printf(" %d ", data);
		}
		printf("\n");
		p = p->next;
	}

	hgx_destory_pool(pool,NULL);

	sleep(10);

	printf("malloc size : %ld , free size : %ld \n", mallocsize, freesize);
}
