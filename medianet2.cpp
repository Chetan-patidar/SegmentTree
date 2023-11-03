#include <iostream>
#include<bits/stdc++.h>
using namespace std;

class dt{
    public:
    int data;
    int setbit;
    dt(char d){
        if(d=='0'){
            data = 0;
            setbit = 0;
        }
        else{
            data = 1;
            setbit = 1;
        }
    }
    dt(){
        data=0;
        setbit=0;
    }
};

class SGT{
    public:
    vector<dt> arr;
    vector<int> lazy;
    SGT(int n){
        arr.resize(4*n+1);
        lazy.resize(4*n+1,0);
    }
    
    void build(int index,int low,int high,string str){
        if(low==high){
            dt temp(int(str[low]));
            //cout<<str[low]<<"  ";
            //cout<<temp.setbit<<" ";
            arr[index] = temp;
            return;
        }
        
        int mid = (low+high)/2;
        build(2*index+1,low,mid,str);
        build(2*index+2,mid+1,high,str);
        dt t(0);
        t.setbit = arr[2*index+1].setbit + arr[2*index+2].setbit;
        arr[index] = t;
    }
    
    
    void update(int index,int low,int high,int l,int h){
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
      
        if(high<l || r<low){
          return;
        }

      
        if(low==high){
            if(arr[index].data=='0'){
                arr[index].data = 1;
                arr[index].setbit = 1;
            }
            else{
                arr[index].data = 0;
                arr[index].setbit = 0;
            }
            return;
        }
        
        else if(l<=low && high<=r){
            r
        }
    }
    
    
    void print(int n){
        for(int i=0;i<4*n;i++){
            cout<<arr[i].setbit<<"   ";
        }
    }
};

int main()
{
    //cout<<"Hello World";
    string test = "10101";
    int n = test.size();
    SGT st(n);
    st.build(0,0,n-1,test);
    st.print(n);
    return 0;
}
