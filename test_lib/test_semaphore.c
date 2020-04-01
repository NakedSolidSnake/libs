#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore/semaphore.h>

int main(int argc, char *argv[])
{
    sema_t sema = {
        .id = -1,
        .sema_count = 1,
        .state = LOCKED
    };

    int i;
    int pause_time;
    char op_char = 'O';
    srand((unsigned int)getpid());

    semaphore_init(&sema, 1234);
    if (argc > 1)
    {        
        op_char = 'X';
        sleep(2);
    }

    for (i = 0; i < 10; i++)
    {
        if (semaphore_lock(&sema))
            exit(EXIT_FAILURE);
        printf("%c", op_char);
        fflush(stdout);
        pause_time = rand() % 3;
        sleep(pause_time);
        printf("%c", op_char);
        fflush(stdout);
        if (semaphore_unlock(&sema))
            exit(EXIT_FAILURE);
        pause_time = rand() % 2;
        sleep(pause_time);
    }
    printf("\n % d - finished\n", getpid());
    if (argc > 1)
    {
        sleep(10);
        semaphore_destroy(&sema);
    }
    exit(EXIT_SUCCESS);
}
