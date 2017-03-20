#include "hgx_array.h"

#include <string.h>

hgx_array *hgx_create_init_array(hgx_pool *pool,unsigned int n,size_t size){
	hgx_array *a = hgx_pcalloc(pool,sizeof(hgx_array));
	if (a == NULL)
		return NULL;
	a->nums = 0;
	a->size = size;
	a->nalloc = n;
	a->pool = pool;
	a->datas = hgx_palloc(pool,n*size);
	if (a->datas == NULL)
		return NULL;

	return a;
}

void hgx_destroy_array(hgx_array *a){
	if (a->nalloc*a->size > HGX_MAX_ALLOC_FROM_POOL){
		hgx_pfree_large(a->pool,a->datas);
	}
}

void *hgx_push_array(hgx_array *a){
	if (a->nums == a->nalloc){ //ÒÑ¾­ÂúÁË
		void *p_new = hgx_palloc(a->pool,a->size*a->nalloc*2);
		void *p_free = a->datas;
		int free_size = a->size*a->nalloc;

		memcpy(p_new,a->datas,a->size*a->nalloc);
		a->datas = p_new;
		a->nalloc = a->nalloc * 2;

		if (free_size > HGX_MAX_ALLOC_FROM_POOL){
			hgx_pfree_large(a->pool,p_free);
		}
	}

	void *ret = (char*)a->datas + a->nums*a->size;
	a->nums++;

	return ret;
}

