#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class SGT{
  public:
  vector<int> seg;
  vector<int> lazy;
  
  SGT(int n){
      seg.resize(4*n+1,0);
      lazy.resize(4*n+1,0);
  }
  
  void build(int index,int low,int high,int arr[]){
      if(low==high){
          seg[index] = arr[low];
          return;
      }
      
      int mid = (low+high)/2;
      build(2*index+1,low,mid,arr);
      build(2*index+2,mid+1,high,arr);
      seg[index] = seg[2*index+1] + seg[2*index+2];
      return;
      
  }
  
  void update(int index,int low,int high,int l,int r){
      //first check for previous update
      if(lazy[index]!=0){
          if(lazy[index]%2==1){
            int count = high-low+1;
            seg[index] = count - seg[index];
            //propagate
            if(low!=high){
                lazy[2*index+1]++;
                lazy[2*index+2]++;
            }
            lazy[index] = 0;
          }
          else{
              lazy[index] = 0;
          }
      }
      
      //no overlapping
      if(high<l || r<low){
          return;
      }
      
      
      //complete overlapping
      if(l<=low && high<=r){
            int count = high-low+1;
            seg[index] = count - seg[index];
            //propagate
            if(low!=high){
                lazy[2*index+1]++;
                lazy[2*index+2]++;
            }
            return;
      }
      
      
      //partial overlapping
      int mid = (low+high)/2;
      update(2*index+1,low,mid,l,r);
      update(2*index+2,mid+1,high,l,r);
      return;
  }
  
  int query(int index,int low,int high,int l,int r){
      //first check for previous update
      if(lazy[index]!=0){
          if(lazy[index]%2==1){
            int count = high-low+1;
            seg[index] = count - seg[index];
            //propagate
            if(low!=high){
                lazy[2*index+1]++;
                lazy[2*index+2]++;
            }
            lazy[index] = 0;
          }
          else{
              lazy[index] = 0;
          }
      }
      
      //no overlapping
      if(high<l || r<low){
          return 0;
      }
      
      
      //complete overlapping
      if(l<=low && high<=r){
          return seg[index];
      }
      
      
      //partial overlapping
      int mid = (low+high)/2;
      int left = query(2*index+1,low,mid,l,r);
      int right = query(2*index+2,mid+1,high,l,r);
      return left+right;
      
  }
    
};



int main(){
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    
    SGT st(n);
    st.build(0,0,n-1,arr);
    int q;
    cin>>q;
    while(q--){
        int type;
        cin>>type;
        if(type==1){
            int l,r;
            cin>>l>>r;
            cout<<st.query(0,0,n-1,l,r)<<endl;
        }
        else{
            int l,r;
            cin>>l>>r;
            st.update(0,0,n-1,l,r);
        }
    }
    cout<<"Program finish"<<endl;
    
}
