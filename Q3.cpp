#include"iostream"
using namespace std;
int add(int a, int b) {
    while (b != 0) {
        int carry = (a & b) << 1;
        a = a ^ b;
        b = carry;
    }
    return a;
}
int claculateopp(int a , int b , char op){
    if(op=='+')
        return add(a,b);
    else if(op=='-')
        return a-b;
    else if(op=='*')
        return a*b;
    else if(op=='/')
        return a/b;
    else
        return -1;
}
int main() {
    int a, b;
    char op;
    cin >> a >> op >> b;
    cout << claculateopp(a, b, op) << endl;
}