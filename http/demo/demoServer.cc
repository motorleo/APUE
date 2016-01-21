#include "../src/HttpServer.h"
#include <muduo/net/EventLoop.h>

int main()
{
	muduo::net::EventLoop loop;
	muduo::net::InetAddress listenAddr(80);
	leo::HttpServer server(&loop,listenAddr);
	server.setDefaultPath("home.html");
	server.start();
	loop.loop();
}

