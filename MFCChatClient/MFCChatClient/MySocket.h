#pragma once
#include <afxsock.h>

class MySocket :public CAsyncSocket
{
public:
	MySocket();
	virtual ~MySocket();
	virtual void OnConnect();
	virtual void OnReceive();
};

