#include<cstring>

int main(){
    char buf[200];

    strlen(buf); // returns length of string

    strcpy(buf, "Hi there"); // ! use strcpy_s if strcpy deprecated

    strcmp(buf, "Hi"); // returns a lexicographic comparison
                       // returns 0 if strings are equal
                       // returns < 0 if string1 less than string2
                       // returns > 0 if string1 greater than string2

    return 0;
}