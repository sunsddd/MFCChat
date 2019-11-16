#include "stdafx.h"
#include "MySocket.h"


MySocket::MySocket()
{
}


MySocket::~MySocket()
{
}

void MySocket::OnConnect() {
	TRACE("####OnConnect ");
}

void MySocket::OnReceive() {
	TRACE("####OnReceive");
}
