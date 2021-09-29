#include <iostream>

void pidLoop(double angle)
{
    //Math related variables that should not be accessed outside of calculations
    double e = 0;
    double ePrior = 0;
    double integral = 0;
    double integralPrior = 0;
    double derive = 0;
    double actual = 0;
    //User decided variables default values if not set
    double kP = 0.005;
    double kI = 0.0001;
    double kD = 0.001;
    double bias = 0;
    double timestep = 20;
    double goal = 0;
    double tolerance = 0;

    //Calculate coefficients of P, I, and D
    actual = angle;
    e = goal - actual;

    integral = integralPrior + e * timestep;
    derive = (e - ePrior) / timestep;
    //Save Output
    double output = kP * e + kI * integral + kD * derive + bias;
    std::cout << output << "\n";
    //std::cout << e << ",  " << output << "\n";
    //Update values for next loop
    ePrior = e;
    integralPrior = integral;
}
/*sleep for time*/
int main()
{
    double angle = 0;
    while (true)
    {
        std::cout << "Please input next angle:  ";
        std::cin >> angle;
        pidLoop(angle);
    }
}