#include"iostream"
using namespace std;
void inputarray(int arr[] , int size){
    cout<<"Enter "<< size << " elements: ";
    for(int i=0;i<size;i++){
        cin>>arr[i];
    }
}
void displayarray(int arr[] , int size){
    cout<<"Array elements are: ";
    for(int i=0;i<size;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main() {
    int n[10];
    int even_count=0;
    int odd_count=0;
    inputarray(n,10);
    displayarray(n,10);
    for(int i=0;i<10;i++){
        if(n[i]%2==0)
            even_count++;
        else
            odd_count++;
    }
    cout<<"Even numbers: "<<even_count<<endl;
    cout<<"Odd numbers: "<<odd_count<<endl;
}