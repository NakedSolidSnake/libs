#include <collection/list_static.h>
#include <stdio.h>

typedef struct 
{
    char name[10];
    int age;
} Person;

int main(int argc, char *argv[])
{

    List *list = List_create(10, sizeof(Person));

    Person p1 = 
    {
        .name = "Someone",
        .age = 16
    };

    Person p2 = 
    {
        .name = "Anyone",
        .age = 17
    };

    List_add(list, &p1);
    List_add(list, &p2);


    List_destroy(list);
    return 0;
}
