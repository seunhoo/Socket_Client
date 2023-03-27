#include "Client.h"


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


// �ֿܼ� �޽����� ����ϴ� �Լ�
int CheckConnecting(string str)
{
    if (str.compare("/noclient") == 0)
    {
        cout << "Waiting For Other Client\n";
        return 0;
    }

    cout << "��� : " << str << "\n>";
    
    return 1;
}

void GetOtherClientMessage(SOCKET sock)
{
    string buffer;
	char x[BUFFERSIZE];
    while (1)
    {
		memset(x, 0x00, sizeof(x));

		// �����͸� �޴´�. ������ �߻��ϸ� �����.
		if (recv(sock, x, sizeof(x), 0) == SOCKET_ERROR)
		{
			// ���� �ܼ� ���
			cout << "error" << endl;
            break;
		}
		// �޽��� ���
		buffer = x;

		if (!CheckConnecting(buffer))
			continue;
    }
}
