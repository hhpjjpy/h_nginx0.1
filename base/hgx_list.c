#include "hgx_list.h"
//��ԭʵ���в��ʹ��ʱҪע�⣬ֻ������ָ�룬Ȼ�����init,list���ڴ���ȫʹ��pool�е��ڴ�

hgx_list *create_init_list(hgx_pool *pool,unsigned int n,size_t size){
	hgx_list *list;
	if (hgx_list_init(&list, pool, n, size) == 0){
		return list;
	}

	return NULL;
}

int hgx_list_init(hgx_list **plist,hgx_pool *pool,unsigned int n,size_t size) { //ע���ں����иı䴫���������ݣ�����ʹ�øö����ָ�룬�����ã�c++��
	if (((*plist) = hgx_pcalloc(pool, sizeof(hgx_list) + n*size)) == NULL) {  //�ر��������ݵĶ�����ָ���ʱ��Ҫע��������Ҫʹ�ø�ָ���ȡ����Ҫ��
		return HGX_ERROR;                                                     //���ָ������ݡ�����˴�������ע�⣡����������ԭbugӦ��Ϊ����Ϊ��*list��
	}																		 //�������г�ʼ��������һ��ָ�룬���¸�ֵ��������Ч��
	(*plist)->size     = size;
	(*plist)->nalloc   = n;
	(*plist)->pool     = pool;
	(*plist)->part.datas = (char*)(*plist) + sizeof(hgx_list);
	(*plist)->part.nums = 0;
	(*plist)->part.next = NULL;
	(*plist)->last = &((*plist)->part);

	return HGX_OK;
}


void *hgx_list_push(hgx_list *list) {
	hgx_list_node *p = list->last; //ֻ��ǰ�����˲������ڵ�
	if (p->nums < list->nalloc) {
		void *ret = (char*)(p->datas) + (p->nums)*(list->size);
		p->nums++;
		return ret;
	}

	hgx_list_node *p_new = hgx_pcalloc(list->pool,sizeof(hgx_list_node)+(list->nalloc)*(list->size));
	if (p_new == NULL) {
		return NULL;
	}
	p_new->datas = (char*)p_new + sizeof(hgx_list_node);
	p_new->nums = 0;
	p_new->next = NULL;
	
	void *ret = p_new->datas;
	p_new->nums++;

	list->last->next = p_new;
	list->last = p_new;

	return ret;

}
