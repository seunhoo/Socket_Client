#pragma once
// ������ ����ϱ� ���ؼ� ���̺귯�� �����ؾ� �Ѵ�.
#pragma comment(lib, "ws2_32")
// inet_ntoa�� deprecated�� �Ǿ��µ�.. ����Ϸ��� �Ʒ� ������ �ؾ� �Ѵ�.
#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>
// ������ ����ϱ� ���� ���̺귯��
#include <WinSock2.h>
// ���� ���� ������
#define BUFFERSIZE 8196
#define IPADDR "192.168.0.190"
using namespace std;

int CheckConnecting(string str);
void GetOtherClientMessage(SOCKET sock);


class Client
{
public:

	Client();
	~Client();

	int Initialize();

    // ���� ���� ������ ����
    WSADATA wsaData;
    // Internet�� Stream ������� ���� ���� 
    SOCKET sock;
    // ���� �ּ� ����
    SOCKADDR_IN addr;

};

