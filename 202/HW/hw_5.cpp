#include <iostream>
#include <string>
template <typename T>

// This does not work for strings on my windows machine
// It does run correctly on the Hydra's though

class stats
{
    // Initialize private variables
    int iterations = 0;
    T sum = T();

public:
    // Output variables
    void print()
    {
        std::cout << "N   = " << iterations
                  << "\nsum = " << sum
                  << "\n";
    }

    // Update variables for each input
    void push(T val)
    {
        iterations++;
        sum = sum + val;
    }
};

int main()
{
    stats<std::string> math;
    std::string val;
    // Continue the cycle for each value given
    while (std::cin >> val)
    {
        math.push(val);
    }
    math.print();
    return 0;
}
