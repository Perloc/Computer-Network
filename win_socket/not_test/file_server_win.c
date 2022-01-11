#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<WinSock2.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
    WSADATA wsaData;
    SOCKET hServSock, hClntSock;
    FILE *fp;
    char buf[BUF_SIZE];
    int readCnt;

    SOCKADDR_IN servAdr, clntAdr;
    int clntAdrSz;

    if (argv != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    // 初始化套接字库
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        error_handling("WSAStartip() error!");
    
    fp = fopen("file_server_win.c", "rb");
    // 创建套接字
    hServSock = socket(PF_INET, SOCK_STREAM, 0);
    if (hServSock == INVALID_SOCKET)
        error_handling("socket() error");

    memset(&servAdr, 0, sizeof(servAdr));
    servAdr.sin_family = AF_INET;
    servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAdr.sin_port = htons(atoi(argv[1]));

    // 分配IP地址和端口号
    if (bind(hServSock, (struct sockaddr*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
        error_handling("bind() error");

    // 使创建的套接字成为服务器端套接字
    if (listen(hServSock, 5) == SOCKET_ERROR)
        error_handling("listen() error");

    clntAdrSz = sizeof(clntAdr);
    // 受理客户端连接请求
    hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);
    if (hClntSock == INVALID_SOCKET)
        error_handling("accept() error");

    while (1)
    {
        readCnt = fread((void*)buf, 1, BUF_SIZE, fp);
        if (readCnt < BUF_SIZE)
        {
            send(hClntSock, (char*)&buf, readCnt, 0);
            break;
        }
        send(hClntSock, (char*)&buf, BUF_SIZE, 0);
    }

    shutdown(hClntSock, SD_SEND);
    recv(hClntSock, (char*)buf, BUF_SIZE, 0);
    printf("Message from client: %s \n", buf);

    fclose(fp);
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