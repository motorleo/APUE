#include "HttpServer.h"
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <algorithm>
#include <sstream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

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
		loop_->runAfter(20.0,boost::bind(&HttpServer::kickOvertime,this,conn));
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
	muduo::net::Buffer bufTemp;
	if (request.getQuery().empty())//static request
	{
		staticServe(&request,&response,&bufTemp);
	}
	else//dynamic request
	{
		//TODO:
	}
	conn->send(&bufTemp);
	if (request.getHeader("Connection") == "close") conn->shutdown();
}

void HttpServer::staticServe(HttpRequest* request,
							 HttpResponse* response,
							 muduo::net::Buffer* buf)
{
	if (request->getPath().empty()) request->setPath(defaultPath_);//url == "/"
	int fd = ::open(request->getPath().c_str(),O_RDONLY);
	if (fd == -1)
	{
		//FIXME:httpError();
		return;
	}
	struct stat stat;//for file size
	if (::stat(request->getPath().c_str(),&stat) < 0)
	{
		LOG_FATAL << "stat error!";
	}
	//set headers
	response->setVersion("1.1");
	response->setStatus("200");
	response->setReason("OK");
	response->addHeader("Content-Type: text/html");
	std::ostringstream str;
	str << "Content-Length: " << stat.st_size;
	response->addHeader(str.str());
	response->addHeader("Connection: Keep-Alive");
	if (!response->appendBuffer(buf))
	{
		LOG_FATAL << "Illgal response!";
	}
	//send html file
	void* htmlFile = ::mmap(0,stat.st_size,PROT_READ,MAP_PRIVATE,fd,0);
	if (htmlFile == MAP_FAILED)
	{
		LOG_FATAL << "mmap error!";
	}
	close(fd);
	buf->append(static_cast<char*>(htmlFile),stat.st_size);
	munmap(htmlFile,stat.st_size);
}

}
