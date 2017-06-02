/*
 * Client_Create_socket.c
 *
 *  Created on: May 24, 2017
 *      Author: achoudhury
 */

#include<stdio.h>
#include<winsock2.h>

//#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc , char *argv[])
{
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char *message, server_reply[100];
    int recv_size;

    //printf("Please enter the numbers to be added separated by a space:");
    //scanf("%d %d",&numb1, &numb2);

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    printf("Initialized.\n");

    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }

    printf("Socket created.\n");


    server.sin_addr.s_addr = inet_addr("192.168.10.131");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8000 );

    //Connect to remote server
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    puts("Connected");


    //The following message will contain the 2 numbers to be added
    sprintf(message,"Connection established and received sensor data");

    if( send(s , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");

    //Receive a reply from the server
    if((recv_size = recv(s , server_reply , 100 , 0)) == SOCKET_ERROR)
       {
           puts("recv failed");
       }


    while ((recv_size = recv(s , server_reply , 100 , 0)) > 0)
   {
       server_reply[recv_size] = '\0';
       puts(server_reply);
      // recv_size = recv(s , server_reply , 20 , 0);
   }

   return 0;
}

