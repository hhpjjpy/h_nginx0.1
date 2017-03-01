#ifndef HGX_PALLOC_H
#define HGX_PALLOC_H

#include "../core/hgx_core.h"
#include <stddef.h>

#define HGX_MAX_ALLOC_FROM_POOL   (hgx_pagesize - 1)
#define HGX_DEFAULT_POOL_SIZE     (16*1024)
#define hgx_test_null(p,alloc,rc)  if((p=alloc) == NULL){ return rc;} //类似的错误检查，封装成宏定义，可简化代码

extern int hgx_pagesize;
extern long mallocsize;
extern long freesize;

typedef struct hgx_pool_large_s hgx_pool_large;

struct  hgx_pool_large_s{
	void *alloc;
	hgx_pool_large *next;
};

typedef struct hgx_pool_data_s  hgx_pool_data;

struct hgx_pool_data_s{
	char       *last;
	char       *end;
	unsigned int failed; //失败次数
	hgx_pool_data *next;
};

typedef struct hgx_clearup_s hgx_clearup;

typedef void(*clear_handle)(void *data);

struct hgx_clearup_s{
	void *data;
	clear_handle handle;
	hgx_clearup *next;
};

typedef struct hgx_pool_s hgx_pool;

struct hgx_pool_s{
	hgx_pool_data data;//小块内存区
	unsigned int max;//单次分配最大值
	hgx_pool_large   *large;
	hgx_clearup      *clearup;
	hgx_log          *log;
};

void *hgx_alloc(size_t size,hgx_log *log);
void *hgx_calloc(size_t size,hgx_log *log);

hgx_pool *hgx_create_pool(size_t size,hgx_log *log);
void hgx_destory_pool(hgx_pool *pool,hgx_log *log);

void *hgx_palloc(hgx_pool *pool,size_t size);
void *hgx_pcalloc(hgx_pool *pool,size_t size);
int  hgx_pfree_large(hgx_pool *pool,void *p); //本实现删除对应的节点

void hgx_pool_cleanup_add(hgx_pool *pool, clear_handle handle, void *data);


#endif