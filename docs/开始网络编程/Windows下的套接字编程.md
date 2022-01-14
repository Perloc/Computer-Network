# Windows下的套接字编程

## 1 Winsock的初始化

```c
#include<winsock2.h>

/**
 ** 成功返回0，失败返回非0的错误代码值
 ** wVersionRequested	要用的Winsock版本信息
 ** lpWSAData			WSADATA结构体变量的地址
 **/
int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
```

- wVersionRequested：借助MAKEWORD宏函数构建WORD型版本信息赋予这个参数
  如：MAKEWORD(2, 2);	// 第一个参数意为主版本为2，第二个参数副版本为2，返回0x0202

-  lpWSAData：需要传入WSADATA型结构体变量的地址信息（LPWSADATA是WSADATA的指针类型）

- WSAStartup的调用过程：

  ```c
  int main(int argc, char* argv[])
  {
      WSADATA wsaData;
      ....
      if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
          ErrorHandling("WSAStartup() error!");
      ....
      return 0;
  }
  ```

- Winsock相关库的注销

  ```c
  #include<winsock2.h>
  
  int WSACleanup(void)
  ```

## 2 套接字相关函数

```c
#include<winsock2.h>

// 成功返回套接字句柄，失败返回INVALID_SOCKET
SOCKET socket(int af, int type, int protocol);

// 成功返回0，失败返回SOCKET_ERROR
int bind(SOCKET s, const struct sockaddr *name, int namelen);

// 成功返回0，失败返回SOCKET_ERROR
int listen(SOCKET s, int backlog);

// 成功返回套接字句柄，失败返回INVALID_SOCKET
SOCKET accept(SOCKET s, struct sockaddr *addr, int *addrlen);

// 成功返回0，失败返回SOCKET_ERROR
int connect(SOCKET s, const struct sockaddr *name, int namelen);

// 成功返回0，失败返回SOCKET_ERROR
int closesocket(SOCKET s);
```

## 3 基于Windows的I/O函数

```c
#include<winsock2.h>

/** 
 ** 成功返回传输字节数，失败返回SOCKET_ERROR
 ** s		数据传输对象连接的套接字句柄值
 ** buf		待传输数据的缓冲地址值
 ** len		要传输的字节数
 ** flags	传输数据时用到的多种选项信息
 **/
int send(SOCKET s, const char *buf, int len, int flags);

/** 
 ** 成功返回传输字节数，失败返回SOCKET_ERROR
 ** s		数据接收对象连接的套接字句柄值
 ** buf		保存接收数据的缓冲地址值
 ** len		能够接收的最大字节数
 ** flags	接收数据时用到的多种选项信息
 **/
int recv(SOCKET s, const char *buf, int len, int flags);
```

