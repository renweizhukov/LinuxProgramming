#include <stdio.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[])
{
    // Use fprintf to print to stderr.
    for (int i = 0; i < 3; i++)
    {
        fprintf(stderr, "Print to stderr via fprintf.\n");
        sleep(1);
    }
    printf("==================================================\n");

    // Use buffered printf and use fflush to flush stdout.
    for (int i = 0; i < 3; i++)
    {
        printf("Buffered printf, will be flushed.\n");
        fflush(stdout);
        sleep(1);
    }
    printf("==================================================\n");

    // Use endl to flush stdout.
    for (int i = 0; i < 3; i++)
    {
        cout << "Use endl to flush stdout by cout." << endl;
        sleep(1);
    }
    printf("==================================================\n");

    // Use setbuf to disable stdout buffering.
    setbuf(stdout, NULL);
    for (int i = 0; i < 3; i++)
    {
        printf("Disable buffered printf.\n");
        sleep(1);
    }
    
    return 0;
}
