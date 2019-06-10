#ifndef MYHASHSET_H_INCLUDED
#define MYHASHSET_H_INCLUDED
#include "myHashMap.h"
typedef struct myHashSet
{
    int size; //大小
    int initialCapacity; //初始容量
    float loadFactor; //加载因子
    int (*hashCode)(void *data);
    int (*equal)(void *data1, void *data2);
    MyList ** dataList;
} MyHashSet;

typedef struct myHashSetIterator
{
    int index; //第几个链表
    MyHashSet *set;
    MyNode *current;
    int count; //第几个数据
} MyHashSetIterator;

//创建HashSet
MyHashSet *createMyHashSet(int (*hashCode)(void *data),int (*equal)(void *data1,void *data2));

//使用全部参数创建HashSet
MyHashSet *createMyHashSetForAll(int initialCapacity,float loadFactor,int (*hashCode)(void *data),int (*equal)(void *data1,void *data2));

//释放HashSet
void freeMyHashSet(MyHashSet * set);

//是否包含某个data
int myHashSetContains(MyHashSet * const set, void * const data);

//增加一条数据,返回是否添加成功
int myHashSetAddData(MyHashSet * const set, void * const data);

//数据的容量
int myHashSetGetSize(const MyHashSet * const set);

//创建迭代器
MyHashSetIterator* createMyHashSetIterator(MyHashSet * const set);

//释放迭代器
void freeMyHashSetIterator(MyHashSetIterator* iterator);

//迭代器是否有下一个
int myHashSetIteratorHasNext(MyHashSetIterator* iterator);

//遍历下一个元素
void* myHashSetIteratorNext(MyHashSetIterator* iterator);

//删除一条数据，返回是否删除成功
int myHashSetRemoveData(MyHashSet * const set, void * const data);

//将第二个Set的全部对象加入到第一个，返回增加的个数
int myHashSetAddAllSet(MyHashSet * set,MyHashSet *other);

//复制HashSet
MyHashSet* myHashSetCopy(MyHashSet * set);

//遍历
void myHashSetOutput(MyHashSet *set, void(*pt)(void*));

#endif // MYHASHSET_H_INCLUDED
