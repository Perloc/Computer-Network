#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
    WSADATA wsaData;
    SOCKET hServSock, hClntSock;
    SOCKADDR_IN servAddr, clntAddr;

    int szClntAddr;
    char message[] = "Hello World!";
    if (argv != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    // 初始化套接字库
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        error_handling("WSAStartip() error!");
    
    // 创建套接字
    hServSock = socket(PF_INET, SOCK_STREAM, 0);
    if (hServSock == INVALID_SOCKET)
        error_handling("socket() error");

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));

    // 分配IP地址和端口号
    if (bind(hServSock, (struct sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        error_handling("bind() error");

    // 使创建的套接字成为服务器端套接字
    if (listen(hServSock, 5) == SOCKET_ERROR)
        error_handling("listen() error");

    szClntAddr = sizeof(clntAddr);
    // 受理客户端连接请求
    hClntSock = accept(hServSock, (struct sockaddr*)&clntAddr, &szClntAddr);
    if (hClntSock == INVALID_SOCKET)
        error_handling("accept() error");

    // 向连接的客户端传输数据
    send(hClntSock, message, sizeof(message), 0);
    closesocket(hClntSock);
    closesocket(hServSock);
    // 注销套接字库
    WSACleanup();
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}