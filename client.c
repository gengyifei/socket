/*
 * client.c
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
#include <sys/time.h>
#include <signal.h>

void handler(int sock)
{
    printf("server is sleep\n");
    close(sock);
    exit(1);
}
int main(){
    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    signal(SIGALRM, handler);

    struct itimerval value;
    value.it_value.tv_sec = 3;
    value.it_value.tv_usec = 0;
    value.it_interval = value.it_value;

    //读取服务器传回的数据
    char buffer[40];
    int i = 0;
    while (1) {
        sleep(0.5);
        read(sock, buffer, sizeof(buffer)-1);
            if ((strcmp(buffer, "end") != 0)) {
                if (strlen(buffer) > 0) {
                    printf("Message form server: %s\n", buffer);
                }
            }
         else {
            close(sock);
            exit(1);
        }
    }
    return 0;
}
