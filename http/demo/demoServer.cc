#include "../src/HttpServer.h"
#include <muduo/net/EventLoop.h>

#include <sstream>
#include <stdio.h>

class demoServer
{
public:
	demoServer(muduo::net::EventLoop* loop,
			   const muduo::net::InetAddress& listenAddr)
		:server_(loop,listenAddr) 
	{
		server_.setHttpCallback(
				boost::bind(&demoServer::onHttp,this,_1,_2));
	}

	void start() { server_.start(); }

private:
	void onHttp(const leo::HttpRequest* request,leo::HttpResponse* response)
	{
		if (request->getPath() == "/")
		{
			response->setBody("test!");
			response->setVersion("1.1");
			response->setStatus("200");
			response->setReason("OK");
			response->addHeader("Content-Type: text/html");
			response->addHeader("Content-Length: 5");
			response->addHeader("Connection: Keep-Alive");
		}
		else
		{
			//do whatever you want.
		}
	}
	leo::HttpServer server_;
};

int main()
{
	muduo::net::EventLoop loop;
	muduo::net::InetAddress listenAddr(80);
	demoServer server(&loop,listenAddr);
	server.start();
	loop.loop();
}

