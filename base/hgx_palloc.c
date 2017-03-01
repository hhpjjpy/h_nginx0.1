#include "hgx_palloc.h"

#include <malloc.h>
#include <string.h>

#define HGX_ALIGN       (sizeof(unsigned long) - 1)  /* platform word */
#define HGX_ALIGN_CAST  (unsigned long)              /* size of the pointer */

#define hgx_align(p)    (char *) ((HGX_ALIGN_CAST p + HGX_ALIGN) & ~HGX_ALIGN) //+n-1 在去除余数
//内存对齐

int hgx_pagesize = 4096; //由系统决定，暂定，便于测试

long mallocsize = 0;
long freesize = 0;

void *hgx_alloc(size_t size,hgx_log *log){
	void *p;
	if ((p = malloc(size+sizeof(int))) == NULL){
		//log
		printf("malloc error \n");
		return NULL;
	}
	*((int*)p) = size;
	mallocsize += size;

	return (char*)p + sizeof(int);
}

void *hgx_calloc(size_t size,hgx_log *log){
	void *p;
	if ((p = hgx_alloc(size, log)) == NULL){
		return NULL;
	}
	return p;
}

void *hgx_free(void *ptr){
	char *p = (char*)ptr;
	p = p - sizeof(int);
	int size = *((int*)p);
	freesize += size;
	free(p);
}

hgx_pool *hgx_create_pool(size_t size,hgx_log *log){
	if (size <sizeof(hgx_pool)){
		//log
		return NULL;
	}
	hgx_pool *p;
	if ((p=hgx_alloc(size,log)) == NULL){
		//log
		return NULL;
	}
	p->data.last = (char*)p + sizeof(hgx_pool); //指针运算一定要注意指针类型!!!!!!!!!!,这里编译器检查发现运算时没有指定类型会发出警告。
	p->data.end = (char*)p + size;
	p->data.failed = 0;
	p->data.next = NULL;
	p->max = HGX_MAX_ALLOC_FROM_POOL;
	p->large = NULL;
	p->clearup = NULL;
	p->log = log;
}

hgx_pool_data *hgx_create_pool_data(hgx_pool *pool){ //默认大小
	hgx_pool_data *p;
	if ((p = hgx_alloc(HGX_DEFAULT_POOL_SIZE, pool->log)) == NULL){
		//log
		return NULL;
	}
	p->last = (char*)p + sizeof(hgx_pool_data);
	p->end = (char*)p + HGX_DEFAULT_POOL_SIZE;
	p->next = NULL;
	p->failed = 0;

	hgx_pool_data *p_temp = pool->data.next; //插入链表中,头插法
	pool->data.next = p;
	p->next = p_temp;

	return p;
}

void *hgx_palloc_small(hgx_pool *pool,size_t size){
	hgx_pool_data *p = &(pool->data);
	for ( ; p; p = p->next){
		if (p->failed == 4)
			continue;
		char *p_align = hgx_align(p->last);
		if (p->end - p_align > size){
			p->last = p_align + size;
			return p_align;
		}
		else{
			p->failed++;
		}
	}
	hgx_pool_data *p_new = hgx_create_pool_data(pool);
	char *p_align = hgx_align(p_new->last);
	p_new->last = p_align + size;
	
	return p_align;
}

void *hgx_palloc_large(hgx_pool *pool,size_t size){
	hgx_pool_large *p;
	if ((p = (hgx_pool_large *)hgx_alloc(size + sizeof(hgx_pool_large), pool->log)) == NULL){
		//log
		return p;
	}
	p->alloc = (char*)p + sizeof(hgx_pool_large);
	
	p->next = pool->large; 
	pool->large = p;

	return p->alloc;
}


//这里内存池分配时涉及如何对齐的问题
void *hgx_palloc(hgx_pool *pool,size_t size){
	if (size < pool->max){
		return  hgx_palloc_small(pool,size);
	}
	else{
		return hgx_palloc_large(pool,size);
	}
}

void *hgx_pcalloc(hgx_pool *pool,size_t size){
	void *p;
	if ((p=hgx_palloc(pool,size))==NULL){
		//log
		return NULL;
	}
	memset(p,0,size);

	return p;
}

int hgx_pfree_large(hgx_pool *pool,void *p){
	hgx_pool_large **ppnext = &(pool->large);
	for (; *ppnext;ppnext = &((*ppnext)->next)){
		if ((*ppnext)->alloc == p){
			hgx_pool_large *free_node = *ppnext;
			*ppnext = free_node->next;
			hgx_free(free_node);
			return 0;
		}
	}
	return -1;
}

void hgx_pool_cleanup_add(hgx_pool *pool, clear_handle handle, void *data){
	hgx_clearup *p;
	if ((p = (hgx_clearup*)hgx_alloc(sizeof(hgx_clearup), pool->log)) == NULL){
		//log
		return  ;
	}
	p->data = data;
	p->handle = handle;
	
	p->next = pool->clearup;
	pool->clearup = p;
}

void hgx_destory_pool(hgx_pool *pool, hgx_log *log){
	for (hgx_clearup *pclear = pool->clearup;pclear; pclear = pclear->next){
		clear_handle handle = (clear_handle)(pclear->handle);
		handle(pclear->data);
	}

	hgx_pool_large *p_large = pool->large;
	while (p_large){
		hgx_pool_large *free_node = p_large;
		p_large = p_large->next;
		hgx_free(free_node);
	}

	hgx_pool_data *p_data = pool->data.next;
	while (p_data){
		hgx_pool_data *free_node = p_data;
		p_data = p_data->next;
		hgx_free(free_node);
	}

	hgx_clearup *pclear = pool->clearup;
	while (pclear){
		hgx_clearup *free_node = pclear;
		pclear = pclear->next;
		hgx_free(free_node);
	}

	hgx_free(pool);

	pool = NULL;
}




