#pragma once
#include <afxsock.h>

class MySocket : public CAsyncSocket
{
public:
	MySocket();
	virtual ~MySocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
};

