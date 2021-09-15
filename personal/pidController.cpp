#include <iostream>
#include <cmath>
using namespace std;

class PIDMath
{
private:
    double e = 0;
    double ePrior = 0;
    double integral = 0;
    double integralPrior = 0;
    double derive = 0;

public:
    double kP = 0;
    double kI = 0;
    double kD = 0;
    double bias = 0;
    double time = 0;
    double goal = 0;
    double actual = 0;
    double tolerance = 0;

    double singleLoop()
    {
        e = goal - actual;
        cout << e << ",  ";
        integral = integralPrior + e * time;
        derive = (e - ePrior) / time;
        double output = kP * e + kI * integral + kD * derive + bias;
        ePrior = e;
        integralPrior = integral;
        /*this line is for testing only*/ actual = output;
        return output;
        /*sleep for time*/
    }
    void fullLoop()
    {
        int iter = 0;
        while (abs((goal - actual)) > tolerance)
        {
            iter += 1;
            cout << singleLoop() << ",  " << iter << "\n";
        }
    }
};

int main()
{
    PIDMath pidControl;
    pidControl.kP = 0.1;
    pidControl.kI = 0.05;
    pidControl.kD = 0.01;
    pidControl.bias = 200;
    pidControl.time = 10;
    pidControl.goal = 200;
    pidControl.actual = 15;
    pidControl.tolerance = 0.05;
    pidControl.fullLoop();
}