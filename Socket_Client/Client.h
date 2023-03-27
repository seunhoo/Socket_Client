#pragma once
// 소켓을 사용하기 위해서 라이브러리 참조해야 한다.
#pragma comment(lib, "ws2_32")
// inet_ntoa가 deprecated가 되었는데.. 사용하려면 아래 설정을 해야 한다.
#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>
// 소켓을 사용하기 위한 라이브러리
#include <WinSock2.h>
// 수신 버퍼 사이즈
#define BUFFERSIZE 8196
#define IPADDR "127.0.0.1"
using namespace std;

void print(vector<char>* str);


class Client
{
public:

	Client();
	~Client();

	int Initialize();

    // 소켓 정보 데이터 설정
    WSADATA wsaData;
    // Internet의 Stream 방식으로 소켓 생성 
    SOCKET sock;
    // 소켓 주소 설정
    SOCKADDR_IN addr;

};

