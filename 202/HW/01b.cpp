#include <iostream>

int strlen(char *str)
{
    for (int j = 0; true; j++)
    {
        if (str[j] == '\0')
            return j;
    }
}

int main(int argc, char **argv)
{
    std::cout << "Num args = " << argc << '\n';

    for (int i = 0; i < argc; i++)
        std::cout << "arg[" << i << "] = " << &argv[i] << ' ' << argv[i] << " (strlen=" << strlen(argv[i]) << ")\n";
}
