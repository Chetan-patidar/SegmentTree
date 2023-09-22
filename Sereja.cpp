#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class block{
    public:
    int open;
    int close;
    int full;
    block(int _open,int _close,int _full){
        open = _open;
        close = _close;
        full = _full;
    }
    block(){
        open = 0;
        close = 0;
        full = 0;
    }
};

class SGTree{
  public:
  vector<block> seg;
  
  SGTree(int n){
      seg.resize(4*n+1);
  }
  
  block merge(block b1,block b2){
    block answer(0,0,0);
    answer.full = b1.full + b2.full + min(b1.open,b2.close);
    answer.open = b1.open + b2.open - min(b1.open,b2.close);
    answer.close = b1.close + b2.close - min(b1.open,b2.close);
    return answer;
  }
  
  void build(int index,int low,int high,string s){
      if(low==high){
          seg[index].open = s[low]=='(';
          seg[index].close = s[low]==')';
          seg[index].full = 0;
          return;
      }
      int mid = (low+high)/2;
      build(2*index+1,low,mid,s);
      build(2*index+2,mid+1,high,s);
      seg[index] = merge(seg[2*index+1],seg[2*index+2]);
      return;
  }
  
  block query(int index,int low,int high,int l,int r){
      
      block result(0,0,0); 
      //no overlapping
      if(high<l || r<low){
          return result;
      }

      //fully overlapping
      if(l<=low && high<=r){
          return seg[index];
      }
      
      //partial overlapping
      int mid = (low+high)/2;
      block b1 = query(2*index+1,low,mid,l,r);
      block b2 = query(2*index+2,mid+1,high,l,r);
      return merge(b1,b2);
      
  }
  
    
};

int main(){
    string str;
    cin>>str;
    int s = str.size();
    int m;
    cin>>m;
    SGTree s1(s);
    s1.build(0,0,s-1,str);
    while(m--){
        int l,r;
        cin>>l>>r;
        block answer = s1.query(0,0,s-1,l-1,r-1);
        cout<<answer.full * 2<<endl;
    }
    
    
    return 0;
}
