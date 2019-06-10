#ifndef MYLIST_H_INCLUDED//检测宏是否已经被定义,与#endif对应
#define MYLIST_H_INCLUDED
#include <stdio.h>

typedef struct myNode
{
  void *data;
  struct myNode *next;
}MyNode;//结点类型

typedef struct myList
{
  MyNode *first;//头指针
  MyNode *last;//尾指针
  int count;//长度
  int (*equal)(void *a,void *b);//?
}MyList;//链表类型

typedef struct myListIterator
{
  myNode *p;
  int count;//当前指向的位置
  int allSize;//总长度
}MyListIterator;//迭代器类型

//创建链表
MyList *createMyList();

//创建链表,带相等参数,用于查找
//跳过
MyList *createMySearchList(int(*equal)(void *a,void *b));

//释放链表
void freeMyList(MyList *list);

//尾部插入
void myListInsertDataAtLast(MyList* const list,void* const data);

//首部插入
void myListInsertDataAtFirst(MyList* const list,void* const data);

//插入到指定位置
void myListInsertDataAt(MyList* const list,void* const data,int index);

//尾部删除
void* myListRemoveDataAtLast(MyList* const list);

//首部删除
void* myListRemoveDataAtFirst(MyList* const list);

//删除指定位置
void* myListRemoveDataAt(MyList* const list,int index);

//删除元素,返回是否删除成功
int myListRemoveDataObject(MyList* const list,void *data);

//获取链表长度
int myListGetSize(const MyList * const list);

//打印链表
//跳过
void myListOutput(const MyList * const list,void(*pt)(const void* const));

//获取指定位置的数据
void* myListGetDataAt(const MyList* const list,int index);

//获取第一个数据
void* myListGetDataAtFirst(const MyList* const list);

//获取最后一个数据
void* myListGetDataAtLast(const MyList* const list);

//查找某个数据的位置,如果equal方法为空,比较地址,负责调用equal方法
//如果不存在返回-1,如果存在,返回出现的第一个位置
int myListFindDataIndex(const MyList* const list,void* data);

//创建迭代器
MyListIterator* createMyListIterator(const MyList* const list);

//释放迭代器
void freeMyListIterator(MyListIterator* iterator);

//迭代器是否有下一个元素
int myListIteratorHasNext(const MyListIterator* const iterator);

//返回迭代器的下一个元素
void* myListIteratorNext(MyListIterator* const iterator);

#endif
