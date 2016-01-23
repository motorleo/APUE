#include "HttpServer.h"
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <algorithm>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
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
		dynamicServe(&request,&response,&bufTemp);		
	}
	conn->send(&bufTemp);
	if (request.getHeader("Connection") == "close") conn->shutdown();
}

void HttpServer::staticServe(HttpRequest* request,
							 HttpResponse* response,
							 muduo::net::Buffer* buf)
{
	if (request->getPath().empty()) request->setPath(defaultPath_);//url == "/"
	std::string filePath = getCurentDir() + request->getPath();
	int fd = ::open(filePath.c_str(),O_RDONLY);
	//printf("%s\n%d\n",filePath.c_str(),fd);
	if (fd == -1)
	{
		errorServe("404","Not Found",response,buf);
		return;
	}
	struct stat stat;//for file size
	if (::fstat(fd,&stat) < 0)
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

void HttpServer::dynamicServe(HttpRequest* request,
							  HttpResponse* response,
							  muduo::net::Buffer* buf)
{
	struct stat stat;//check file
	std::string cmdString = getCurentDir() + request->getPath();
	if (::stat(cmdString.c_str(),&stat) < 0)
	{
		errorServe("400","Bad Request",response,buf);
		return;
	}
	if (!(S_IXUSR & stat.st_mode))
	{
		errorServe("403","Forbidden",response,buf);
		return;
	}
	response->setVersion("1.1");
	response->setStatus("200");
	response->setReason("OK");
	response->addHeader("Server: Leo webServer");
	if (!response->appendBuffer(buf))
	{
		LOG_FATAL << "Illgal response!";
	}
	//execute file
	std::string query = request->getQuery();
	std::replace(query.begin(),query.end(),'&',' ');
	cmdString +=' ' + query;
	FILE* file = ::popen(cmdString.c_str(),"r");
	char temp[1024];
	while (::fgets(temp,1024,file) != NULL)
	{
		//printf("%s%zd\n",temp,strlen(temp));
		buf->append(temp,strlen(temp));
	}
	fclose(file);
}

void HttpServer::errorServe(std::string status,
							std::string reason,
							HttpResponse* response,
							muduo::net::Buffer* buf)
{
	response->setVersion("1.1");
	response->setStatus(status);
	response->setReason(reason);
	response->addHeader("Content-type: text/html");
	std::string body = "<html>\r\n"\
		"<title>Web Server Error</title>\r\n"\
		"<body>\r\n"\
		"<h2 style=\"text-align:center;\">ERROR " + status + "</h2>\r\n"\
		"<p style=\"text-align:center;\">There is some mistake:</p>\r\n"\
		"<p style=\"text-align:center;\">" + reason + ".</p>\r\n"\
		"<p style=\"text-align:right;\">Leo webServer.</p>\r\n"\
		"</body>\r\n"\
		"</html>\r\n";
	std::ostringstream str;
	str << "Content-Length: " << body.size();
	response->addHeader(str.str());
	response->setAndSwapBody(body);
	response->appendBuffer(buf);
}

std::string HttpServer::getCurentDir()
{
	char buf[256];
	ssize_t n = readlink("/proc/self/exe",buf,256);
	if (n < 0 || n > 256)
	{
		LOG_FATAL << "readlink error!";
	}
	for ( ; n >=0 && buf[n] != '/'; --n);//delete filename
	buf[n+1] = '\0';
	//printf("%s\n",buf);
	return std::string(buf,::strlen(buf));
}

}
