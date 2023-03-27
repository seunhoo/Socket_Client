#include "Client.h"


Client::Client()
{
}

Client::~Client()
{
}

int Client::Initialize()
{
    // 소켓 실행.
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        return 1;
    }
    // Internet의 Stream 방식으로 소켓 생성 
    sock = socket(PF_INET, SOCK_STREAM, 0);

    // 구조체 초기화
    memset(&addr, 0, sizeof(addr));
    // 소켓은 Internet 타입
    addr.sin_family = AF_INET;
    // 127.0.0.1(localhost)로 접속하기
    addr.sin_addr.s_addr = inet_addr(IPADDR);
    // 포트 9090으로 접속
    addr.sin_port = htons(9090);
    // 접속
    if (connect(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        // 에러 콘솔 출력
        cout << "error" << endl;
        return 1;
    }
}


// 콘솔에 메시지를 출력하는 함수
int CheckConnecting(string str)
{
    if (str.compare("/noclient") == 0)
    {
        cout << "Waiting For Other Client\n";
        return 0;
    }

    cout << "상대 : " << str << "\n>";
    
    return 1;
}

void GetOtherClientMessage(SOCKET sock)
{
    string buffer;
	char x[BUFFERSIZE];
    while (1)
    {
		memset(x, 0x00, sizeof(x));

		// 데이터를 받는다. 에러가 발생하면 멈춘다.
		if (recv(sock, x, sizeof(x), 0) == SOCKET_ERROR)
		{
			// 에러 콘솔 출력
			cout << "error" << endl;
            break;
		}
		// 메시지 출력
		buffer = x;

		if (!CheckConnecting(buffer))
			continue;
    }
}
