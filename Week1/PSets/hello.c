#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Take name from user and says hello
    string name = get_string("What's your name? ");
    printf("Hello, %s!\n", name);
}
