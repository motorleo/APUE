#include "../HttpServer.h"
#include <muduo/net/EventLoop.h>

const std::string str = "test!";

void onHttp(const leo::HttpRequest* request,leo::HttpResponse* response)
{
	response->setVersion("1.1");
	response->setStatus("200");
	response->setReason("OK");
	response->setBody(&str);
}

int main()
{
	muduo::net::EventLoop loop;
	muduo::net::InetAddress listenAddr(80);
	leo::HttpServer server(&loop,listenAddr);
	server.setHttpCallback(
			boost::bind(&onHttp,_1,_2));
	server.start();
	loop.loop();
	return 0;
}
