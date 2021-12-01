#include <cmath>
class PIDController
{
    double e = 0;
    double ePrior = 0;
    double integral = 0;
    double integralPrior = 0;
    double derive = 0;
    double output = 0;

public:
    double P = 0;
    double I = 0;
    double D = 0;
    double bias = 0;
    double timestep = 10;
    double actual = 0;
    double goal = 0;
    double tolerance = 0;

    double readError()
    {
        return e;
    }

    double calculate_raw()
    {
        e = goal - actual;
        integral = integralPrior + e * timestep;
        derive = (e - ePrior) / timestep;
        output = P * e + I * integral + D * derive + bias;
        ePrior = e;
        integralPrior = integral;
        return output;
    }

    double calculate_tolerance()
    {
        output = calculate_raw();
        /* Deadband */
        if (fabs(actual) < tolerance)
        {
            return 0;
        }
        return output;
    }
};