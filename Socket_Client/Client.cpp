#include "Client.h"

// �ֿܼ� �޽����� ����ϴ� �Լ�
void print(vector<char>* str)
{
    // ����Ʈ ��ġ
    int p = 0;
    // ���� ����. +1�� \0�� �ֱ� ���� ũ��
    char out[BUFFERSIZE + 1];
    // �ܼ� ���
    cout << "From server message : ";

    for (int n = 0; n < (str->size() / BUFFERSIZE) + 1; n++)
    {
        // ���� ������ ����
        int size = str->size();
        // ���� �����Ͱ� ���� ����� �Ѿ��� ���.
        if (size > BUFFERSIZE) {
            if (str->size() < (n + 1) * BUFFERSIZE)
            {
                size = str->size() % BUFFERSIZE;
            }
            else
            {
                size = BUFFERSIZE;
            }
        }
        // echo �޽����� �ܼ� �޽����� �ۼ��Ѵ�.
        for (int i = 0; i < size; i++, p++)
        {
            out[i] = *(str->begin() + p);
        }
        // �ܼ� �޽��� �ܼ� ���.
        cout << out;
    }
}

Client::Client()
{
}

Client::~Client()
{
}

int Client::Initialize()
{
    // ���� ����.
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        return 1;
    }
    // Internet�� Stream ������� ���� ���� 
    sock = socket(PF_INET, SOCK_STREAM, 0);
    
    // ����ü �ʱ�ȭ
    memset(&addr, 0, sizeof(addr));
    // ������ Internet Ÿ��
    addr.sin_family = AF_INET;
    // 127.0.0.1(localhost)�� �����ϱ�
    addr.sin_addr.s_addr = inet_addr(IPADDR);
    // ��Ʈ 9090���� ����
    addr.sin_port = htons(9090);
    // ����
    if (connect(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        // ���� �ܼ� ���
        cout << "error" << endl;
        return 1;
    }
}
