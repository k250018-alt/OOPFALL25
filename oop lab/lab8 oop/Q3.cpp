#include<iostream>
using namespace std;
class ComplexNumber{
    int real;
    int imag;
    public:
    ComplexNumber(int r, int i):real(r), imag(i){}
    ComplexNumber():real(0), imag(0){}
    ComplexNumber operator+(const ComplexNumber& c)
    {
        return ComplexNumber(real + c.real, imag + c.imag);
    }
    friend ComplexNumber operator-(const ComplexNumber& c , const ComplexNumber& c2)
    {
        return ComplexNumber(c.real - c2.real, c.imag - c2.imag);
    }
    ComplexNumber operator*(const ComplexNumber& c){
        return ComplexNumber((real * c.real) - (imag * c.imag), (real * c.imag) + (imag * c.real));

    }
    ComplexNumber operator/(const ComplexNumber& c){
        int denominator = (c.real * c.real) + (c.imag * c.imag);
        return ComplexNumber(((real * c.real) + (imag * c.imag)) / denominator, ((imag * c.real) - (real * c.imag)) / denominator);
    }
    ComplexNumber operator++()
    {
        real++;
        imag++;
        return *this;
    }
    ComplexNumber operator++(int)
    {
        ComplexNumber temp = *this;
        real++;
        imag++;
        return temp;
    }
    friend istream& operator>>(istream& in, ComplexNumber& c)
    {
        cout << "Enter real part: ";
        in >> c.real;
        cout << "Enter imaginary part: ";
        in >> c.imag;
        return in;
    }
    friend ostream& operator<<(ostream& out, const ComplexNumber& c)
    {
        out <<"("<< c.real << " + " << c.imag << "i)";
        return out;
    }
    bool operator==(const ComplexNumber& c)
    {
        return (real == c.real) && (imag == c.imag);
    }
    bool operator!=(const ComplexNumber& c)
    {
        return !(*this == c);
    }
    bool operator<(const ComplexNumber& c)
    {
        return (real < c.real) || (real == c.real && imag < c.imag);
    }
    bool operator>(const ComplexNumber& c)
    {
        return (real > c.real) || (real == c.real && imag > c.imag);
    }
    bool operator<=(const ComplexNumber& c)
    {
        return !(*this > c);
    }
    bool operator>=(const ComplexNumber& c)
    {
        return !(*this < c);
    }

};

int main()
{
    ComplexNumber c1(2, 3);
    ComplexNumber c2(4, 5);
    ComplexNumber c3 = c1 + c2;
    cout << c1 << " + " << c2 << " = " << c3 << endl;
}