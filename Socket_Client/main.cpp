#include "Client.h"

int main()
{
    Client* cClient = new Client();
    // telent은 한글자씩 데이터가 오기 때문에 글자를 모을 buffer가 필요하다.
    vector<char> buffer;
    // 수신 데이터
    char x;
    while (1)
    {
        // 데이터를 받는다. 에러가 발생하면 멈춘다.
        if (recv(cClient->sock, &x, sizeof(char), 0) == SOCKET_ERROR)
        {
            // 에러 콘솔 출력
            cout << "error" << endl;
            break;
        }
        // 버퍼에 글자를 하나 넣는다.
        buffer.push_back(x);
        // \r\n>\0가 나오면 콘솔에 출력하고 콘솔로 부터 메시지를 기다린다.
        if (buffer.size() > 4 && *(buffer.end() - 4) == '\r' && *(buffer.end() - 3) == '\n' && *(buffer.end() - 2) == '>' && *(buffer.end() - 1) == '\0')
        {
            // 메시지 출력
            print(&buffer);
            // 버퍼 초기화
            buffer.clear();
            // 콘솔로 부터 입력을 받는다.
            char input[BUFFERSIZE];
            // 유저로 부터 입력 받기
            cin >> input;
            // 입력받은 길이를 받는다.
            int size = strlen(input);
            // 개행을 넣는다.
            *(input + size + 1) = '\r';
            *(input + size + 2) = '\n';
            // 서버로 보내기
            send(cClient->sock, input, size + 3, 0);
            // 메시지가 exit라면 종료
            if (*input == 'e' && *(input + 1) == 'x' && *(input + 2) == 'i' && *(input + 3) == 't')
            {
                break;
            }
            continue;
        }
    }
    // 서버 소켓 종료
    closesocket(cClient->sock);
    // 소켓 종료
    WSACleanup();
    delete cClient;
    return 0;
}