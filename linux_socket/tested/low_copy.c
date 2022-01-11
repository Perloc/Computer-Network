#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

#define BUF_SIZE 100
#define FILENAME_SIZE 20

void error_handling(char *message);
int low_read(char *filename, char *content);
int low_open(char *filename, char *content);

int main(void)
{
    char content[BUF_SIZE];
    char filename[FILENAME_SIZE];

    printf("输入需要复制的文件: ");
    scanf("%s", filename);

    if (low_read(filename, content) != 0)
        error_handling("read() error!");

    if (low_open(filename, content) != 0)
        error_handling("write() error!");

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int low_read(char *filename, char *content)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        error_handling("open() error!");
    printf("file descriptor: %d \n", fd);

    if (read(fd, content, sizeof(content)) == -1)
        error_handling("read() error!");

    close(fd);
    return 0;
}

int low_open(char *filename, char *content)
{
    int fd;

    filename[strlen(filename)] = '2';
    fd = open(filename, O_CREAT|O_WRONLY|O_TRUNC);
    if (fd == -1)
        error_handling("open() error!");
    printf("file descriptor: %d \n", fd);

    if (write(fd, content, sizeof(content)) == -1)
        error_handling("write() error!");

    close(fd);
    return 0;
}