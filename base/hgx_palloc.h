#ifndef HGX_PALLOC_H
#define HGX_PALLOC_H

#define HGX_MAX_ALLOC_FROM_POOL   (hgx_pagesize - 1)
#define HGX_DEFAULT_POOL_SIZE     (16*1024)
#define hgx_test_null(p,alloc,rc)  if((p=alloc) == NULL){ return rc;} //���ƵĴ����飬��װ�ɺ궨�壬�ɼ򻯴���

typedef struct hgx_pool_large_s hgx_pool_large;

struct  hgx_pool_large_s{
	void *alloc;
	hgx_pool_large_s *next;
};

typedef struct hgx_pool_s hgx_pool;

struct hgx_pool_s{
	char             *last; //ָ������Ϊchar*  ��Ϊ����ָ������ʱ����
	char             *end;
	hgx_pool         *next;
	hgx_pool_large   *large;
	//log 
};

void *hgx_alloc(size_t size);
void *hgx_calloc(size_t size);

hgx_pool *ngx_create_pool(size_t size);
void hgx_destory_pool(hgx_pool *pool);

void *hgx_palloc(hgx_pool *pool,size_t size);
void *hgx_pcalloc(hgx_pool *poll,size_t size);
void  hgx_pfree(hgx_pool *pool,void *p);


#endif