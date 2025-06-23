#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("working dir: %-*s\t\n", 0, argv[0]);
    printf("emulating: %-*s\t\n", 0, argv[1]);
}