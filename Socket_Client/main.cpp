#include "Client.h"

int main()
{
    // Client Ŭ���� ����
    Client* cClient = new Client();

    // Ŭ���̾�Ʈ �ʱ� ����
    if (cClient->Initialize())
    {
        return 0;
    }

    auto thr = new thread(GetOtherClientMessage, cClient->sock);

    while (1)
    {
		// �ַܼ� ���� �Է��� �޴´�.
		char input[BUFFERSIZE];
		// ������ ���� �Է� �ޱ�
		cin >> input;
		// ������ ������
        cout << "�� : " << input << "\n>";
		send(cClient->sock, input, strlen(input), 0);

		continue;
    }
    // ���� ���� ����
    closesocket(cClient->sock);
    // ���� ����
    WSACleanup();
    delete cClient;
    return 0;
}