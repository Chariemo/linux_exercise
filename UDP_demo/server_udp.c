/*************************************************************************
	> File Name: upd_server.c
	> Author: 
	> Mail: 
	> Created Time: Mon Dec  4 16:46:48 2017
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

#define PORT_SERV 6789 //服务器端口
#define BUFF_LEN 256 //缓冲区大小

void static udpserv_echo(int s, struct sockaddr * client) {

    int n; //接收数据长度
    char buff[BUFF_LEN]; //接受缓冲区
    socklen_t len; //地址长度
    int count = 0;
    while(1) { //循环接收发送
        len = sizeof(*client);
        n = recvfrom(s, buff, BUFF_LEN, 0, client, &len);
        printf("The server recved and send<%d> ... size: %d\n", ++count, n);
        sendto(s, buff, n, 0, client, len);
    }
}

int main(int argc, char * argv[]) {

    int s;//套接字描述符
    struct sockaddr_in addr_serv, addr_clie;//地址结构
    
    s = socket(AF_INET, SOCK_DGRAM, 0);//建立数据报套接字

    memset(&addr_serv, 0, sizeof(addr_serv));//清空地址结构
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);//任意本机地址
    addr_serv.sin_port = htons(PORT_SERV);

    bind(s, (struct sockaddr*)&addr_serv, sizeof(addr_serv));//绑定地址

    udpserv_echo(s, (struct sockaddr*)&addr_clie);//回显处理程序
    return 0;
}


