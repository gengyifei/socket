/*
 * server.c
 *
 *  Created on: 2019年11月8日
 *      Author: gyf
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>



void readline(char *str)
{
    char ch;
    char tmp[100];
    while ( (ch = getchar() ) != '\n') {
        sprintf(tmp, "%c", ch);
        strcat(str, tmp);
    }
}
int main(){
    //创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口

    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    //进入监听状态，等待用户发起请求
    listen(serv_sock, 20);

    //接收客户端请求
    printf("wait client connect \n");
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);


    //向客户端发送数据
    int i = 0;
    char str[100];
    while(1) {
        memset(str, 0, sizeof(str));
        //sprintf(str, "server i:%d", i++);
        printf("input data:");
        readline(str);
        write(clnt_sock, str, sizeof(str));
        if (strcmp(str, "end") == 0)
            break;
    }
    //关闭套接字
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

