#include "../HttpRequest.h"
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

int main()
{
	muduo::net::EventLoop loop;
	muduo::net::InetAddress listenAddr(80);
	muduo::net::TcpServer server(&loop,listenAddr,"testServer");
	server.start();
	loop.loop();
	return 0;
}
