#ifndef HGX_ARRAY_H
#define HGX_ARRAY_H

#include "../core/hgx_core.h"

struct  hgx_array_s{
	void            *datas;
	unsigned int    nums;//当前数量
	size_t          size;//元素大小
	unsigned int    nalloc;//预先分配的数量
	hgx_pool        *pool;
};
//这个数组也与基于内存池的list相似，虽然有销毁，但只是释放特殊情况下的一小部分，频繁使用，或者生命周期与内存池不是相对一致的话实际会造成资源的浪费
//尤其是不断进行扩充的时候，往往会产出很多的报废内存，到最后才会与内存池一起释放。故实际这些可以不考虑释放资源的数据结构，使用场景有限制


hgx_array *hgx_create_init_array(hgx_pool *pool, unsigned int n, size_t size);


void hgx_destroy_array(hgx_array *a);//实际使用中恐怕意义不到，满足条件的情况有可能比较恐怕少,干脆不实现了，分配完立马销毁的场景，用到在看


void *hgx_push_array(hgx_array *a);




#endif