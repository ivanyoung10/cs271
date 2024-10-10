#include <stdio.h>
#include <string.h>

int main(){
    // printf("%s", "hello, world\n");
    // printf("%d\n", 42);
    // printf("%c\n", 'A');
    // return 0;

    // declare the strings
    char str1[] = "Oregon State Cascades";
    char str2[] = {'O', 'S', 'U', 'C', '\0'};

    // print the strings
    printf("str1: \t%s\n", str1);
    printf("str2: \t%s\n", str2);

    // treat as an array
    printf("char[4]:%c\n", str1[13]);

    //read a string
    char input[20];
    int number;
    printf("Who are you?: ");
    scanf("%s", input);
    printf("Your favorite number?: ");
    scanf("%d", &number);
    printf("%s entered %d\n", input, number);

    // string copy
    char str5[] = "Green eggs and ham";
    char str6[100];

    strcpy(str6, str5);
    printf("str6 %s\n", str6);
    strcat(str6, " and ");
    printf("str6 %s\n", str6);



}

