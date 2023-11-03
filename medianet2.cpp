/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include<bits/stdc++.h>
using namespace std;

class SGT{
    public:
    vector<pair<int,int>> arr;
    vector<int> lazy;
    
    SGT(int n){
        arr.resize(4*n+1);
        lazy.resize(4*n+1,0);
    }
    
    void build(int index,int low,int high,string str){
        if(low==high){
            if(str[low]=='0'){
                arr[index].first = 0;
                arr[index].second = 0;
            }
            else{
                arr[index].first = 1;
                arr[index].second = 1;
            }
            return;
        }
        
        int mid = (low+high)/2;
        
        build(2*index+1,low,mid,str);
        build(2*index+2,mid+1,high,str);
        arr[index].first = 0;
        arr[index].second = arr[2*index+1].second + arr[2*index+2].second;
        return;
    }
    
    
    void update(int index,int low,int high,int l,int h){
        if(lazy[index]!=0){
            int c = lazy[index];
            if(lazy[index]%2==1){
                arr[index].second = (high-low+1) - arr[index].second;
                lazy[2*index+1] = c;
                lazy[2*index+2] = c;
                lazy[index] = 0;
            }
            else{
                lazy[index] = 0;
            }
        }
        
        
        if(high<l || h<low)
            return;
            
        else if(l<=low && high<=h){
            arr[index].second = (high-low+1) - arr[index].second;
            lazy[2*index+1]++;
            lazy[2*index+2]++;
        }
        
        else{
            int mid = (low+high)/2;
            
            update(2*index+1,low,mid,l,h);
            update(2*index+2,mid+1,high,l,h);
            arr[index].second = arr[2*index+1].second + arr[2*index+2].second;
        }
        
        return;
    }
    
    int query(int index,int low,int high,int l,int h){
        if(lazy[index]!=0){
            int c = lazy[index];
            if(lazy[index]%2==1){
                arr[index].second = (high-low+1) - arr[index].second;
                lazy[2*index+1] = c;
                lazy[2*index+2] = c;
                lazy[index] = 0;
            }
            else{
                lazy[index] = 0;
            }
        }
        
        if(high<l || h<low)
            return 0;
            
        else if(l<=low && high<=h){
            return arr[index].second;
        }
        else{
            int mid = (low+high)/2;
            int left = query(2*index+1,low,mid,l,h);
            int right = query(2*index+2,mid+1,high,l,h);
            return left+right;
        }
        return 0;
    }
};

int main()
{
    //cout<<"Hello World";
    vector<int> ans;
    string test = "10101";
    int n = test.size();
    SGT st(n);
    st.build(0,0,n-1,test);
    int q;
    cin>>q;
    while(q--){
        int op;
        cin>>op;
        int l,r;
        cin>>l>>r;
        if(op==1){
            st.update(0,0,n-1,l,r);
        }
        else{
            int answer = st.query(0,0,n-1,l,r);
            ans.push_back(answer);
        }
    }
    
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<"    ";
    }

    return 0;
}
