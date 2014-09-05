#include <cstdio>
#include<iostream>
#include <winsock2.h>
using namespace std;
int main()
{
	int n, i, j,k;
	// Initialize Winsock.

	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult != NO_ERROR)
		cout << "Client: Error at WSAStartup()." << endl;
	else
		cout << "Client: WSAStartup() is OK." << endl;
	// Create a socket.

	SOCKET m_socket;

	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET)
	{
		cout << "Client: socket() - Error at socket(): " << WSAGetLastError();
		WSACleanup();
		return 0;
	}
	else
		cout << "Client: socket() is OK." << endl;

	// Connect to a server.

	sockaddr_in clientService;

	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr("192.168.1.80");
	clientService.sin_port = htons(55555);

	if (connect(m_socket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		cout << "Client: connect() - Failed to connect." << endl;

		WSACleanup();
		return 0;
	}
	// Send and receive data.

	int bytesSent;
	int bytesRecv = SOCKET_ERROR;

	// Be careful with the array bound, provide some checking mechanism

	char recvbuf[200] = "";


	cout << "wprowadz wymiar macierzy: ";
	cin >> n;
	double **A = new double *[n];
	for (i = 0; i < n; i++)
		A[i] = new double[n];

	for (i = 0; i < n; i++)
	for (j = 0; j < n; j++)
		cin >> A[i][j];

	for (i = 0; i < n; i++){
	cout << endl;
	for (j = 0; j < n; j++)
		cout <<" "<< A[i][j];
}
	cout << endl;
	k = 0;
	char *sendbuf=new char [n*n];
	for (i = 0; i < n; i++)
	for (j = 0; j < n; j++){
		sendbuf[k] = A[i][j];
		k++;
	}

	bytesSent = send(m_socket, sendbuf, n*n, 0);

	cout<< "Client: send() - Bytes Sent:"<< bytesSent << endl;

	while (bytesRecv == SOCKET_ERROR)
	{
		bytesRecv = recv(m_socket, recvbuf, 32, 0);
		if (bytesRecv == 0 || bytesRecv == WSAECONNRESET)
		{
			cout<<"Client: Connection Closed."<<endl;
			break;
		}
		else
			cout<< "Client: recv() is OK."<<endl;

		if (bytesRecv < 0)
			return 0;
		else
			cout<<"Client: Bytes received - "<< bytesRecv<<endl;
	}

	bytesSent = send(m_socket,(char*) sendbuf, n*n, 0);
	cout<<"Client: Bytes sent "<< bytesSent<<endl;
	getchar();
	getchar();
	return 0;

}