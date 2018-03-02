/*************************************************************************
	> File Name: client_1.c
	> Author: 
	> Mail: 
	> Created Time: Tue Dec  5 23:35:13 2017
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

#define PORT_SERV 6789 //服务器端口
#define BUFF_LEN 1024 //缓冲区大小

static void udpclient_echo(int s, struct sockaddr *to) {

    char buff1[128] = "The First Time"; //第一次发送的数据
    char buff2[256] = "The Second Time"; //第二次发送的数据
    
    int n;
    struct sockaddr_in from; //本地地址
    socklen_t len = sizeof(*to); //地址长度
    int count = 0;
    while (count++ < 1) {
        printf("NO.<%d> time\n", count);
        n = sendto(s, buff1, 128, 0, to, len); //第一次发送100数据包
        printf("sent size: %d\n", n);
        sleep(1);
        n = sendto(s, buff2, 256, 0, to, len); //第二次
        printf("sent size: %d\n", n);
//        sleep(3);
    }
}

int main(int argc, char * argv[]) {
    
    int s; //套接字文件描述符
    struct sockaddr_in addr_serv; //地址结构

    s = socket(AF_INET, SOCK_DGRAM, 0); //建立数据报套接字

    memset(&addr_serv, 0, sizeof(addr_serv)); //清空地址结构
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY); //任意本地地址
    addr_serv.sin_port = htons(PORT_SERV);

    udpclient_echo(s, (struct sockaddr *)&addr_serv); //客户端发送消息

    close(s);
    return 0;
}

