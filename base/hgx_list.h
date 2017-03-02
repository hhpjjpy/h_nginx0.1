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
	size_t             size;//Ԫ�ش�С
	unsigned int       nalloc;//ÿ���ڵ����������
	hgx_pool           *pool;
}hgx_list;

//û�����٣����������ڴ�һ���ͷŵ��𣡣�����������ʹ�ó������Ƿ������������ڴ�أ�����ؾ���ҵ��ģ��ǿ����
//����û�л�ȡ�ӿڣ�����

hgx_list *create_init_list(hgx_pool *pool,unsigned int n,size_t size);


int hgx_list_init(hgx_list **list,hgx_pool *pool,
						unsigned int n,size_t size);


void *hgx_list_push(hgx_list *list);




#endif // !HGX_LIST_H
