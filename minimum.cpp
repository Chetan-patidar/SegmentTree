// Online C++ compiler to run C++ program online
#include <iostream>
#include<bits/stdc++.h>
#include<vector>
using namespace std;
class SGTree{
  public:
    vector<int> seg;
  public:
  SGTree(int n){
      seg.resize(4*n+1);
  }
  void build(int index,int low,int high,int arr[]){
      if(low==high){
          seg[index] = arr[low];
          return;
      }
      int mid = (low+high)/2;
      build(2*index+1,low,mid,arr);
      build(2*index+2,mid+1,high,arr);
      seg[index] = min(seg[2*index+1],seg[2*index+2]);
      return;
  }
  void update(int index,int low,int high,int i,int val){
      if(low==high){
          seg[index] = val;
          return;
      }
      int mid = (low+high)/2;
      if(i<=mid){
          update(2*index+1,low,mid,i,val);
      }
      else{
          update(2*index+2,mid+1,high,i,val);
      }
      seg[index] = min(seg[2*index+1],seg[2*index+2]);
      return;
  }
  int query(int index,int l,int r,int low,int high){
      //no overlapping
      if(high<l || r<low){
          return INT_MAX;
      }
      
      //fully overlapping
      if(l<=low && high<=r){
          return seg[index];
      }
      
      //partial overlapping
      int mid = (low+high)/2;
      int left = query(2*index+1,l,r,low,mid);
      int right = query(2*index+2,l,r,mid+1,high);
      return min(left,right);
  }
  void print(int n){
      for(int i=0;i<4*n;i++){
          cout<<seg[i]<<endl;
      }
  }
};
int main() {
    
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    SGTree s1(n);
    s1.build(0,0,n-1,arr);
    //s1.print(n);
    int q;
    cin>>q;
    while(q--){
        int l,r,op;
        cin>>op;
        if(op==1){
            int i,val;
            cin>>i>>val;
            s1.update(0,0,n-1,i,val);
        }
        else{
            cin>>l>>r;
            int answer = s1.query(0,l,r,0,n-1);
            cout<<answer<<endl;
        }
    }

    return 0;
}
