#ifndef HGX_ARRAY_H
#define HGX_ARRAY_H

#include "../core/hgx_core.h"

struct  hgx_array_s{
	void            *datas;
	unsigned int    nums;//��ǰ����
	size_t          size;//Ԫ�ش�С
	unsigned int    nalloc;//Ԥ�ȷ��������
	hgx_pool        *pool;
};
//�������Ҳ������ڴ�ص�list���ƣ���Ȼ�����٣���ֻ���ͷ���������µ�һС���֣�Ƶ��ʹ�ã����������������ڴ�ز������һ�µĻ�ʵ�ʻ������Դ���˷�
//�����ǲ��Ͻ��������ʱ������������ܶ�ı����ڴ棬�����Ż����ڴ��һ���ͷš���ʵ����Щ���Բ������ͷ���Դ�����ݽṹ��ʹ�ó���������


hgx_array *hgx_create_init_array(hgx_pool *pool, unsigned int n, size_t size);


void hgx_destroy_array(hgx_array *a);//ʵ��ʹ���п������岻������������������п��ܱȽϿ�����,�ɴ಻ʵ���ˣ��������������ٵĳ������õ��ڿ�


void *hgx_push_array(hgx_array *a);




#endif