#include<iostream>
using namespace std;
class Run;
class BallsFaced;
int calculateStrikeRate(Run& r, BallsFaced& b);
class Run
{
    private:
    int run;
    public:
    Run(int r):run(r){}
    friend int calculateStrikeRate(Run& r, BallsFaced& b);
};
class BallsFaced
{
    private:
    int balls;
    public:
    BallsFaced(int b):balls(b){}
    friend int calculateStrikeRate(Run& r, BallsFaced& b);
};
int calculateStrikeRate(Run& r, BallsFaced& b)
{
    return (r.run * 100) / b.balls;
}
int main()
{
    Run r(50);
    BallsFaced b(30);
    cout<<"Strike Rate: "<<calculateStrikeRate(r,b);
    return 0;
}