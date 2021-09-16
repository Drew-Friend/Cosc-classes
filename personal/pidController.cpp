#include <iostream>
#include <cmath>

class PIDMath
{
private:
    //Math related variables that should not be accessed outside of calculations
    double e = 0;
    double ePrior = 0;
    double integral = 0;
    double integralPrior = 0;
    double derive = 0;
    double actual = 0;

public:
    //User decided variables default values if not set
    double kP = 0;
    double kI = 0;
    double kD = 0;
    double bias = 0;
    double time = 10;
    double goal = 0;
    double tolerance = 0;

    //Calculates a single iteration of the PID loop, requires the current position/value
    double singleLoop(double received)
    {
        //Calculate coefficients of P, I, and D
        actual = received;
        e = goal - actual;

        integral = integralPrior + e * time;
        derive = (e - ePrior) / time;
        //Save Output
        double output = kP * e + kI * integral + kD * derive + bias;
        std::cout << e << ",  " << output << "\n";
        //Update values for next loop
        ePrior = e;
        integralPrior = integral;
        return output;
        /*sleep for time*/
    }
    void fullLoop(double start)
    {
        //Get starting position to pass in as first actual value
        double recent = start;
        //Run until output is within tolerance. In a for loop to keep track of iterations for funsies
        for (int i = 0; std::abs((goal - actual)) > tolerance; i++)
        {
            recent = singleLoop(recent);
            std::cout << i << "\n";
        }
    }
};

int main()
{
    //Instantiate
    PIDMath pidControl;
    //Choose coefficients
    pidControl.kP = 0.1;
    pidControl.kI = 0.05;
    pidControl.kD = 0.01;
    //Bias is the value to use when actual = desired, 0 for position, !0 for speed
    pidControl.bias = 200;
    //Iteration time, likely 10 because of 10 millisecond loop time
    pidControl.time = 10;
    //Goal value(position or speed or what have you)
    pidControl.goal = 200;
    //Acceptable deviation to exit the loop
    pidControl.tolerance = 0.05;
    //Probably wouldn't use a real loop in robot code, instead run singleLoop once per code cycle
    pidControl.fullLoop(15);
    /*Each loop cycle prints in the form of:
        error,  actual_value,  iteration_num
    */
}