#include "Client.h"

int main()
{
    // Client 클래스 생성
    Client* cClient = new Client();

    // 클라이언트 초기 설정
    if (cClient->Initialize())
    {
        return 0;
    }

    auto thr = new thread(GetOtherClientMessage, cClient->sock);

    while (1)
    {
		// 콘솔로 부터 입력을 받는다.
		char input[BUFFERSIZE];
		// 유저로 부터 입력 받기
		cin >> input;
		// 서버로 보내기
        cout << "나 : " << input << "\n>";
		send(cClient->sock, input, strlen(input), 0);

		continue;
    }
    // 서버 소켓 종료
    closesocket(cClient->sock);
    // 소켓 종료
    WSACleanup();
    delete cClient;
    return 0;
}