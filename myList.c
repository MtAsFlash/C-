#include "myList.h"
#include <stdlib.h>

//创建链表
MyList* createMyList(){
  MyList* list = (MyList*)malloc(sizeof(MyList));
  list->count=0;
  list->first=NULL;
  list->last=NULL;
  list->equal=NULL;//?
  return list;
}

//释放链表
void freeMyList(MyList* list){
  MyNode* p;
  while (list->first) {
    p = list->first->next;
    free(list->first);
    list->first = p;
  }
  free(list);
}

//尾部插入
void myListInsertDataAtLast(MyList* const list,void* const data){
  MyNode* node = (MyNode*)malloc(sizeof(MyNode));
  node->data = data;
  node->next = NULL;//尾部next为空
  if (list->count) {
    //如list不空
    list->last->next = node;//原链表的最后一个元素的next指向新节点
    list->last = node;//更改当前链表last指针指向尾部插入的新节点
  }else{
    //如果当前list空,头尾指针指向唯一的节点
    list->first = node;
    list->last = node;
  }
  (list->count)++;//链表长度++
}

//首部插入
void myListInsertDataAtFirst(MyList* const list,void* const data){
  MyNode* node = (MyNode*)malloc(sizeof(MyNode));
  node->data = data;
  node->next = NULL;
  if (list->count) {
    //如果链表不空
    node->next = list->first;
    list->first = node;
  }else {
    //如果链表为空,头尾指针指向唯一的节点
    list->first=node;
    list->last=node;
  }
  (list->count)++;//链表长度++
}

//获取链表长度
int myListGetSize(const MyList* const list){
  return list->count;
}

//打印
//跳过

//头部删除
void* myListRemoveDataAtFirst(MyList* const list){
  MyNode *p = list->first;//创建临时指针指向list的第一个元素
  list->first = p->next;//头指针指向第二个元素
  void* data = p->data;
  free(p);
  (list->count)--;//链表长度--
  if (list->count == 0) {
    //如果此时链表为空,说明刚刚删除了last指向的元素
    list->last = NULL;
  }
  return data;
}

//尾部删除
void* myListRemoveDataAtLast(MyList* const list){
  if (list->count == 1) {
    //只有一个元素
    return myListRemoveDataAtFirst(list);
  }
  MyNode* p = list->first;//临时指针p
  while (p->next != list->last) {
    //找到倒数第二个元素
    p = p->next;
  }
  void* data = list->last->data;
  free(list->last);
  p->next = NULL;
  list->last = p;
  (list->count)--;//链表长度--
  return data;
}

//插入指定位置(index)
void myListInsertDataAt(MyList* const list,void* const data,int index){
  if (index==0) {
    //插入位置为链表首部
    myListInsertDataAtFirst(list,data);
    return;
  }
  if(index==list->count){
    //插入位置为链表尾部
    myListInsertDataAtLast(list,data);
    return;
  }
  //创建新节点
  MyNode* node = (MyNode*)malloc(sizeof(MyNode));
  node->data = data;
  node->next = NULL;

  MyNode* p = list->first;
  for (int i = 0; i < index - 1; ++i) {
    //找到要插入位置(前一个节点位置)
    p = p->next;
  }
  //调整链表,插入新节点
  node->next = p->next;
  p->next = node;

  (list->count)++;//链表长度++
}

//删除指定位置(index)
void* myListRemoveDataAt(MyList* const list,int index){
  if(index==0){
    //删除位置为链表首部
    return myListRemoveDataAtFirst(list);
  }
  if (index == list->count - 1) {
    //删除位置为链表尾部(count-1)
    return myListRemoveDataAtLast(list);
  }
  MyNode* p = list->first;
  for (int i = 0; i < index - 1; ++i) {
    //找到删除位置
    p = p->next;
  }
  //调整链表
  MyNode* tp = p->next;
  p->next = tp->next;
  void* data = tp->data;
  free(tp);
  (list->count)--;//链表长度--
  return data;
}

//获取第一个数据
void* myListGetDataAtFirst(const MyList* const list){
  return list->first->data;
}

//获取最后一个数据
void* myListGetDataAtLast(const MyList* const list){
  return list->last->data;
}

//获取指定位置的数据
void* myListGetDataAt(const MyList *const list,int index){
  if (index == 0){
    //要获取的数据为链表首部数据
    return myListGetDataAtFirst(list);
  }
  if (index == list->count - 1) {
    //要获取的数据为链表尾部数据
    return myListGetDataAtLast(list);
  }
  MyNode* p = list->first;
  for (int i = 0; i < index; ++i) {
    p = p->next;
  }
  return p->data;
}

//查找某个数据的位置,如果equal方法为空，比较地址，否则调用equal方法
//如果不存在返回-1，如果存在，返回出现的第一个位置
int myListFindDataIndex(const MyList * const list, void * data)
{
  MyNode * p = list->first;
  int re = 0;
  if (list->equal)
    {
      while (p)
        {
          if (p->data == data || (*(list->equal))(p->data, data))
            {
              return re;
            }
          re++;
          p = p->next;
        }

    }
  else
    {
      while (p)
        {
          if (p->data == data)
            {
              return re;
            }
          re++;
          p = p->next;
        }
    }
  return -1;
}

//创建链表,带有相等参数,用于查找
MyList * createMySearchList(int(*equal)(void * a, void * b)){
  MyList * re = createMyList();
  re->equal = equal;//equal!
  return re;
}


//创建迭代器
MyListIterator* createMyListIterator(const MyList* const list){
  MyListIterator* iterator = (MyListIterator*)malloc(sizeof(MyListIterator));
  iterator->p = list->first;
  iterator->allSize = list->count;
  iterator->count = 0;//当前指向位置
  return iterator;
}

//释放迭代器
void freeMyListIterator(MyListIterator* iterator){
  free(iterator);
}

//遍历器是否有下一个元素
int myListIteratorHasNext(const MyListIterator* const iterator){
  return iterator->count < iterator->allSize;//当前指向位置是否大于链表总长
}

//返回迭代器的下一个元素
void* myListIteratorNext(MyListIterator* const iterator){
  void* data = iterator->p->data;//获取当前指向位置的数据
  iterator->p = iterator->p->next;//迭代器指向位置++
  (iterator->count)++;//迭代器逻辑位置++
  return data;
}

//删除元素,返回是否删除成功
int myListRemoveDataObject(MyList* const list,void* data){
  MyListIterator* iterator = createMyListIterator(list);
  int bool_state = 0;//记录删除成功/失败的状态
  while (myListIteratorHasNext(iterator)) {
    void* t = myListIteratorNext(iterator);
    if(data == t){
      bool_state = 1;//允许删除,此时迭代器停留在所找到的数据的位置
      break;
    }
  }
  if(bool_state){
    //允许删除时,删除迭代器找到后停留的位置的数据
    myListRemoveDataAt(list,iterator->count - 1);//删除该位置元素
  }
  return bool_state;
}
