/*************************************************************************
	> File Name: udp_client.c
	> Author: 
	> Mail: 
	> Created Time: Mon Dec  4 17:02:04 2017
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

#define PORT_SERV 6789 //服务器端口
#define BUFF_LEN 256 //缓冲区大小

static void udpclient_echo(int s, struct sockaddr *to) {

    char buff[BUFF_LEN] = "A SIMPLE TEST FOR C/S UDP"; //发送给服务器的测试数据
    
    int n; //接收字节数
    struct sockaddr_in from; //本地地址
    socklen_t len = sizeof(*to); //地址长度
    int count = 0;
    while (count++ < 5) {
        sendto(s, buff, BUFF_LEN, 0, to, len); //发送数据
        memset(&buff, 0, sizeof(buff));
        n = recvfrom(s, buff, 5, 0, (struct sockaddr*) &from, &len); //接收数据
        printf("recved<%d>: %s size: %d\n", count, buff, n);
        sleep(2);
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

    udpclient_echo(s, (struct sockaddr *)&addr_serv); //客户端回显程序

    close(s);
    return 0;
}

