#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

/*
 *  验证tcp套接字传输的数据不存在数据边界
 *  服务器端多次调用write函数传输数据
 *  客户端需要延迟调用read函数
*/

void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;
    int idx=0, read_len=0;
    int i;

    if (argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    // create tcp socket
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    // 调用connect函数使刚建立的套接字成为客户端套接字，connect向服务器端发送连接请求
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error");

    // 延迟read函数的调用
    for (i=0; i<3000; i++)
        printf("Wait time %d \n", i);

    while (read_len = read(sock, &message[idx++], 1))
    {
        if (read_len == -1)
            error_handling("read() error!");

        str_len += read_len;
    }

    printf("Message from server : %s \n", message);
    printf("Function read call count: %d \n", str_len);
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}