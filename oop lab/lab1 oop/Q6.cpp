#include<iostream>
using namespace std;
void printer(int start,int end){
    int even_Count=0;
    if(start%2!=0)start++;
    for(int i=start;i<=end;i+=2){
    cout<<i << endl;
        even_Count++;
        if(even_Count==5){
            int odd=i+1;
            if(odd<=end)cout<<odd << endl;
            even_Count=0;
        }
}
}
int main(){
    int start,end;
    cout<<"Enter the range (start end): ";
    cin>>start>>end;
    printer(start,end);
}