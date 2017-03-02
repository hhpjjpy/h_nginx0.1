#pragma once
#ifndef HGX_LIST_H
#define HGX_LIST_H
#include "../core/hgx_core.h"
#include <stddef.h>


typedef struct hgx_list_node_s hgx_list_node;

struct hgx_list_node_s {
	void             *datas;
	unsigned int     nums;
	hgx_list_node    *next;
};

typedef struct {
	hgx_list_node      *last;
	hgx_list_node      part;
	size_t             size;//元素大小
	unsigned int       nalloc;//每个节点包含的数量
	hgx_pool           *pool;
}hgx_list;

//没有销毁？？？是与内存一起释放掉吗！！！！后续看使用场景，是否生命周期与内存池，或相关具体业务模块强关联
//而且没有获取接口？？？

hgx_list *create_init_list(hgx_pool *pool,unsigned int n,size_t size);


int hgx_list_init(hgx_list **list,hgx_pool *pool,
						unsigned int n,size_t size);


void *hgx_list_push(hgx_list *list);




#endif // !HGX_LIST_H
