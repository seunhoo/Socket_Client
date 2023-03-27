#include "Client.h"

// 콘솔에 메시지를 출력하는 함수
void print(vector<char>* str)
{
    // 포인트 위치
    int p = 0;
    // 버퍼 설정. +1은 \0를 넣기 위한 크기
    char out[BUFFERSIZE + 1];
    // 콘솔 출력
    cout << "From server message : ";

    for (int n = 0; n < (str->size() / BUFFERSIZE) + 1; n++)
    {
        // 버퍼 사이즈 설정
        int size = str->size();
        // 수신 데이터가 버퍼 사이즈를 넘었을 경우.
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
        // echo 메시지와 콘솔 메시지를 작성한다.
        for (int i = 0; i < size; i++, p++)
        {
            out[i] = *(str->begin() + p);
        }
        // 콘솔 메시지 콘솔 출력.
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
