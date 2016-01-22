#ifndef _HTTP_HTTPSERVER_H_
#define _HTTP_HTTPSERVER_H_

#include "HttpRequest.h"
#include "HttpResponse.h"

#include <muduo/net/TcpServer.h>
#include <boost/bind.hpp>
#include <boost/function.hpp>

namespace leo
{
class HttpServer : public boost::noncopyable
{
public:
	HttpServer(muduo::net::EventLoop* loop,
			   const muduo::net::InetAddress& listenAddr);

	void start() { server_.start(); }

	void setDefaultPath(const std::string& path) { defaultPath_ = path; }

private:
	void kickOvertime(const muduo::net::TcpConnectionPtr& conn);

	void onConnection(const muduo::net::TcpConnectionPtr& conn);

	void onMessage(const muduo::net::TcpConnectionPtr& conn,
				   muduo::net::Buffer* buf,
				   muduo::Timestamp time);

	void staticServe(HttpRequest* request,
					 HttpResponse* response,
					 muduo::net::Buffer* buf);

	void dynamicServe(HttpRequest* request,
					  HttpResponse* response,
					  muduo::net::Buffer* buf);

	std::string getCurentDir();

	muduo::net::EventLoop* loop_;
	std::string defaultPath_;
	muduo::net::TcpServer server_;
};
}//namespace leo

#endif
