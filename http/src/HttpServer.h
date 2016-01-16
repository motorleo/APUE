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
typedef boost::function<void (const HttpRequest*,
							  HttpResponse*)> HttpCallback;
public:
	HttpServer(muduo::net::EventLoop* loop,
			   const muduo::net::InetAddress& listenAddr);

	void start() { server_.start(); }

	void setHttpCallback(const HttpCallback& cb) { cb_ = cb; }
private:
	void kickOvertime(const muduo::net::TcpConnectionPtr& conn);

	void onConnection(const muduo::net::TcpConnectionPtr& conn);

	void onMessage(const muduo::net::TcpConnectionPtr& conn,
				   muduo::net::Buffer* buf,
				   muduo::Timestamp time);

	muduo::net::EventLoop* loop_;
	HttpCallback cb_;
	muduo::net::TcpServer server_;
};
}//namespace leo

#endif
