#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class SGTree{
  public:
  vector<int> seg;
  
  SGTree(int n){
      seg.resize(4*n+1);
  }
  void build(int index,int low,int high,int arr[],bool orr){
      if(low==high){
          seg[index] = arr[low];
          return;
      }
      int mid = (low+high)/2;
      //left
      build(2*index+1,low,mid,arr,!orr);
      //right
      build(2*index+2,mid+1,high,arr,!orr);
      if(orr){
          seg[index] = seg[2*index+1] | seg[2*index+2];
      }
      else{
          seg[index] = seg[2*index+1] ^ seg[2*index+2];
      }
      
  }
  
  void update(int index,int low,int high,int i,int val,bool orr){
      if(low==high){
          seg[index] = val;
          return;
      }
      int mid = (low + high)/2;
      if(i<=mid){
          update(2*index+1,low,mid,i,val,!orr);
      }
      else{
          update(2*index+2,mid+1,high,i,val,!orr);   
      }
      if(orr){
          seg[index] = seg[2*index+1] | seg[2*index+2];
      }
      else{
          seg[index] = seg[2*index+1] ^ seg[2*index+2];
      }
  }
  
  int query(){
      return seg[0];
  }
};

int main(){
    int n,m;
    cin>>n>>m;
    int s = pow(2,n);
    int arr[s];
    for(int i=0;i<s;i++){
        cin>>arr[i];
    }
    
    SGTree s1(s);
    if(n%2==1){
        s1.build(0,0,s-1,arr,true);
    }
    else{
        s1.build(0,0,s-1,arr,false);
    }
    
    while(m--){
        int i,val;
        cin>>i>>val;
        if(n%2==1){
            s1.update(0,0,s-1,i-1,val,true);
        }
        else{
            s1.update(0,0,s-1,i-1,val,false);
        }
        int answer = s1.query();
        cout<<answer<<endl;
        
    }
    
    
    return 0;
}
