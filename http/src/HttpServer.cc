#include "HttpServer.h"
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <algorithm>

namespace leo
{

HttpServer::HttpServer(muduo::net::EventLoop* loop,
				       const muduo::net::InetAddress& listenAddr)
	:loop_(loop),server_(loop,listenAddr,"HttpServer")
{
	server_.setConnectionCallback(
			boost::bind(&HttpServer::onConnection,this,_1));
	server_.setMessageCallback(
		boost::bind(&HttpServer::onMessage,this,_1,_2,_3));
}

//kick incorrect request
void HttpServer::kickOvertime(const muduo::net::TcpConnectionPtr& conn)
{
	if (conn->getContext().empty())
	{
		conn->shutdown();
	}
}

void HttpServer::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
	if (conn->connected())
		loop_->runAfter(10.0,boost::bind(&HttpServer::kickOvertime,this,conn));
}

void HttpServer::onMessage(const muduo::net::TcpConnectionPtr& conn,
						   muduo::net::Buffer* buf,
						   muduo::Timestamp time)
{
	const char crlf[] = "\r\n\r\n";
	const char* end = buf->beginWrite();
	const char* isRequest = std::search(buf->peek(),end,crlf,crlf+4);
	if (isRequest == buf->beginWrite()) return;//wait for request empty line
	conn->setContext(true);//correct request
	HttpRequest request;
	if (!request.parseFormBuffer(buf))
	{
		conn->shutdown();
		return;
	}
	HttpResponse response;
	cb_(&request,&response);
	muduo::net::Buffer bufTemp;
	if (!response.appendBuffer(&bufTemp))
	{
		LOG_FATAL << "Illgal response!";
	}
	conn->send(&bufTemp);
	if (request.getHeader("Connection") == "close") conn->shutdown();
}

}
