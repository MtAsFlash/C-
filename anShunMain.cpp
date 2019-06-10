//2017.10.30 数据结构课程设计
//课程设计名称:八数码问题
#include <bits/stdc++.h>
#include <stdlib.h>
#include "myList.h"
#include "myEqual.h"
#include "myHashCode.h"
#include "myHashMap.h"
#include "myHashSet.h"
using namespace std;
#define swap(x,y){int t;t=x;x=y;y=t;}
typedef pair<int,int>P;
//memset,memcpy,vector,string,length,priority_queue,queue,
//setprecision,setiosflags(ios::fixed),
const int N = 9;//N数码
typedef int State[N];
const int maxn = 1000000 + 10;
State every_state[maxn],target;//every_state为每个状态,target为目标状态
int dist[maxn];//距离数组
//set<int>vis;
int *data;
int *key,*value;
MyHashSet *vis;
//map<int,int>fa;
MyHashMap *fa;
const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};

void init_table(){
  //vis.clear();
  vis = createMyHashSet(myHashCodeInt,myEqualInt);
  fa = createMyHashMap(myHashCodeInt,myEqualInt);
}
int test_insert(int s){
  int v = 0;
  for (int i = 0; i < N; ++i) {
    v = v * 10 + every_state[s][i];
  }
  data = (int*)malloc(sizeof(int));
  *data = v;
  //if(vis.count(v))return 0;
  //vis.insert(v);
  if(myHashSetContains(vis,data))return 0;
  myHashSetAddData(vis,data);
  return 1;
}
int bfs(){
  init_table();//初始化查找表
  int f = 1,r = 2;
  while(f<r){
    State& s = every_state[f];
    if(memcmp(target,s,sizeof(s)) == 0){
      //已经到达目标状态
      return f;//返回成功时刻的状态
    }
    int z;
    for (z = 0; z < N; ++z) {
      if(!s[z])break;//找到0位置
    }
    int x = z/3;//0位置的行号
    int y = z%3;//0位置的列号
    for (int d = 0; d < 4; ++d) {
      int nx = x + dx[d];//新的表内位置X
      int ny = y + dy[d];//新的表内位置Y
      int nz = nx * 3 + ny;//新的线性位置
      if(nx >= 0 && nx < 3 && ny >= 0 && ny < 3){
        //越界判断
        //开始尝试
        State& t = every_state[r];//t引用every_state[r]状态,为其赋值
        //新结点赋值
        memcpy(&t,&s,sizeof(s));//为新结点赋值
        t[nz] = s[z];
        t[z] = s[nz];//更新移动的位置
        dist[r] = dist[f] + 1;//更新移动次数
        if(test_insert(r)){
          //合法状态,存入状态表
          //fa[r]=f;//记录双亲
          key = (int*)malloc(sizeof(int));
          value = (int*)malloc(sizeof(int));
          *key = r;
          *value = f;
          myHashMapPutData(fa,key,value);
          r++;
        }
      }
    }
    f++;
  }
  return -1;
}
int main(){
  freopen("input","r",stdin);
  //freopen("output","w",stdout);
  for (int i = 0; i < N; ++i) {
    cin >> every_state[1][i];//输入初始化状态
  }
  for (int i = 0; i < N; ++i) {
    cin >> target[i];//输入目标状态
  }
  //cout << "读入数据结束" << "\n";
  int ans = bfs();
  //cout << ans << "\n";//最终状态存储位置
  if(ans==-1)cout << "永远无法达到目标状态!" << "\n";
  else{
    int t = ans;
    stack<int>zhan;
    do {
      zhan.push(t);
      t = *(int*)myHashMapGetDataByKey(fa,&t);
      //t = fa[t];
    }while(t!=1);
    zhan.push(1);
    while (!zhan.empty()) {
      int g = zhan.top();
      for (int i = 0; i < N; ++i) {
        cout << every_state[g][i] << " ";
        if(i%3==2)cout << "\n";
      }
      cout << "\n";
      zhan.pop();
    }
    cout << dist[ans] << "\n";//输出最终状态的距离
  }
  return 0;
}
