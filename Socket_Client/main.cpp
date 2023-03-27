#include "Client.h"

int main()
{
    Client* cClient = new Client();
    // telent�� �ѱ��ھ� �����Ͱ� ���� ������ ���ڸ� ���� buffer�� �ʿ��ϴ�.
    vector<char> buffer;
    // ���� ������
    char x;
    while (1)
    {
        // �����͸� �޴´�. ������ �߻��ϸ� �����.
        if (recv(cClient->sock, &x, sizeof(char), 0) == SOCKET_ERROR)
        {
            // ���� �ܼ� ���
            cout << "error" << endl;
            break;
        }
        // ���ۿ� ���ڸ� �ϳ� �ִ´�.
        buffer.push_back(x);
        // \r\n>\0�� ������ �ֿܼ� ����ϰ� �ַܼ� ���� �޽����� ��ٸ���.
        if (buffer.size() > 4 && *(buffer.end() - 4) == '\r' && *(buffer.end() - 3) == '\n' && *(buffer.end() - 2) == '>' && *(buffer.end() - 1) == '\0')
        {
            // �޽��� ���
            print(&buffer);
            // ���� �ʱ�ȭ
            buffer.clear();
            // �ַܼ� ���� �Է��� �޴´�.
            char input[BUFFERSIZE];
            // ������ ���� �Է� �ޱ�
            cin >> input;
            // �Է¹��� ���̸� �޴´�.
            int size = strlen(input);
            // ������ �ִ´�.
            *(input + size + 1) = '\r';
            *(input + size + 2) = '\n';
            // ������ ������
            send(cClient->sock, input, size + 3, 0);
            // �޽����� exit��� ����
            if (*input == 'e' && *(input + 1) == 'x' && *(input + 2) == 'i' && *(input + 3) == 't')
            {
                break;
            }
            continue;
        }
    }
    // ���� ���� ����
    closesocket(cClient->sock);
    // ���� ����
    WSACleanup();
    delete cClient;
    return 0;
}