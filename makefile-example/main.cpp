#include <iostream>
#include <cstdio>
#include <cstring>
#include "functions.h"

using namespace std;

int main()
{
    char str[] = "ping";
    char *pch = NULL;
    pch = strtok(str, "`");
    if (pch == NULL)
    {
        printf("pch is NULL and the token is not found.\n");
    }
    else
    {
        printf("pch = %s is not NULL and the token is found.\n", pch);
    }

    print_hello();
    cout << endl;
    cout << "The factorial of 5 is " << factorial(5) << endl;
    return 0;
}
