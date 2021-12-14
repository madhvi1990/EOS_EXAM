#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include<string.h>


int main()
{
    pid_t pid1,pid2;
    int pip[2];
    FILE * fd;
    char ch1[40];
    char ch2[40];

    pipe(pip);

    pid1 = fork();
    pid2 = fork();

    fd = fopen("/home/hp/EOS_EXAM/dictionary.txt", "rd");

    if(pid1 == 0)
    {
        close(pip[1]);

        while (read(pip[0], &ch2, sizeof(char*)) == sizeof(char*))
          printf("%s\n", ch2);
            printf("found\n");

        close(pip[0]);
    }
    else
    {
        close(pip[0]);

        while (fscanf(fd, "%s", &ch1) == 1)
        {if (ch1[0] == 'm')
        {
          write(pip[1], &ch1, sizeof(char*));
        }
        }
        close(pip[1]);

        waitpid(pid1, NULL, 0);
    }

    printf("Length of the string is: %ld\n", strlen(ch1));
    printf("Length of the string is: %ld\n", strlen(ch2));

    return 0;
}