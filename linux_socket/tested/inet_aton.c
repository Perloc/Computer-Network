#include<stdio.h>
#include<arpa/inet.h>

void error_handling(char *message);

// 字节序转换
int main(int argc, char *argv[])
{
    char *addr1 = "1.2.3.4";
    char *addr2 = "1.2.3.256";

    char *addr = "127.232.124.79";
    struct sockaddr_in addr_inet;

    unsigned long conv_addr = inet_addr(addr1);
    if (conv_addr = INADDR_NONE)
        printf("Error occured! \n");
    else
        printf("Network ordered integer addr: %#lx \n", conv_addr);

    conv_addr = inet_addr(addr2);
    if (conv_addr = INADDR_NONE)
        printf("Error occured! \n");
    else
        printf("Network ordered integer addr: %#lx \n\n", conv_addr);

    if (!inet_aton(addr, &addr_inet.sin_addr))
        error_handling("Conversion error");
    else
        printf("Network ordered integer addr:%#x \n", addr_inet.sin_addr.s_addr);
    
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}