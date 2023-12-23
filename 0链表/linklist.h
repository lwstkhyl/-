#pragma once
#ifdef __cplusplus  //这两个ifdef是为了让这个头文件在c++中也能使用
extern "C" {
#endif
	//定义结点数据类型
	struct link_nods
	{
		int data;
		struct link_nods* next;
	};
	//初始化链表
	struct link_nods* init_linklist();
	//在值为old_val的位置插入new_val
	void insert_by_value(struct link_nods* header,int old_val,int new_val);//header指向第一个结点
	//删除值为val的结点
	void remove_by_value(struct link_nods* header, int del_value);
	//遍历
	void foreach_linklist(struct link_nods* header);
	//销毁
	void destroy_linklist(struct link_nods* header);
	//清空
	void clear_linklist(struct link_nods* header);
#ifdef __cplusplus
}
#endif
