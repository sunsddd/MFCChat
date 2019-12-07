#pragma once
#include <afxsock.h>

class CServerSocket : public CAsyncSocket {
public:
	CServerSocket();
	virtual ~CServerSocket();

	void OnAccept(int nErrorCode);
};

