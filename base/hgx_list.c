#include "hgx_list.h"
//与原实现有差别，使用时要注意，只能声明指针，然后调用init,list的内存完全使用pool中的内存

hgx_list *create_init_list(hgx_pool *pool,unsigned int n,size_t size){
	hgx_list *list;
	if (hgx_list_init(&list, pool, n, size) == 0){
		return list;
	}

	return NULL;
}

int hgx_list_init(hgx_list **plist,hgx_pool *pool,unsigned int n,size_t size) { //注意在函数中改变传入对象的内容，必须使用该对象的指针，或引用（c++）
	if (((*plist) = hgx_pcalloc(pool, sizeof(hgx_list) + n*size)) == NULL) {  //特别是所传递的对象是指针的时候，要注意区分是要使用该指针获取还是要改
		return HGX_ERROR;                                                     //变该指针的内容。比如此处。。。注意！！！！！！原bug应发为参数为（*list）
	}																		 //而函数中初始化分配了一个指针，重新赋值。所以无效。
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
	hgx_list_node *p = list->last; //只有前面满了才新增节点
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
