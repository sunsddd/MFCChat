#pragma once
#include <afxsock.h>
class ChatServer : public CAsyncSocket
{
public:
	ChatServer();
	virtual ~ChatServer();

	void OnReceive(int nErrorCode);
};

