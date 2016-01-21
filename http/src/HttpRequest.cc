#include "HttpRequest.h"

namespace leo
{
bool HttpRequest::parseFormBuffer(muduo::net::Buffer* buf)
{
	const char* crlf = buf->findCRLF();
	//ignore empty line
	while (crlf == buf->peek()) 
	{
	   	buf->retrieve(2);
		crlf = buf->findCRLF();
   	}
	if (crlf == NULL) return false;
	//request line
	if (!parseRequestLine(buf->peek(),crlf)) return false;
	buf->retrieveUntil(crlf + 2);
	//hearers line
	bool ok = false;
	while (true)
	{
		crlf = buf->findCRLF();
		if (crlf)
		{
			if (crlf != buf->peek())
			{
				if (!addHeader(buf->peek(),crlf)) break;
				buf->retrieveUntil(crlf + 2);
			}
			else //empty line
			{
				buf->retrieve(2);
				ok = true;
				break;
			}
		}
		else
		{
			break;
		}
	}
	return ok;
}

bool HttpRequest::parseRequestLine(const char* begin,const char* end)
{
	const char* iter = std::find(begin,end,' ');
	if (iter == end || !setMethod(begin,iter)) return false;
	++iter;
	const char* path = std::find(iter,end,' ');
	if (path == end) return false;
	const char* query = std::find(iter,end,'?');
	if (query != end)
	{
		setPath(iter + 1,query);
		setQuery(query + 1,path);
	}
	else
	{
		setPath(iter + 1,path);
	}
	iter = path + 1;
	if (!setVersion(iter,end)) return false;
	return true;
}

std::string HttpRequest::getMethod() const
{
	switch (method_)
	{
		case kGet :
			return "GET";
		case kHead :
			return "HEAD";
		default :
			return "UNKNOW";
	}
}

bool HttpRequest::setMethod(const char* begin,const char* end)
{
	std::string method(begin,end);
	if (method == "GET")
	{
		method_ = kGet;
		return true;
	}
	if (method == "HEAD")
	{
		method_ = kHead;
		return true;
	}
	return false;
}

std::string HttpRequest::getVersion() const
{
	switch (version_)
	{
		case v10 :
			return "HTTP/1.0";
		case v11 :
			return "HTTP/1.1";
		default :
			return "UNKNOW";
	}
}

bool HttpRequest::setVersion(const char* begin,const char* end)
{
	std::string version(begin,begin + 5);
	if (version != "HTTP/") return false;
	begin += 5;
	std::string num(begin,end);
	if (num == "1.0")
	{
		version_ = v10;
		return true;
	}
	if (num == "1.1")
	{
		version_ = v11;
		return true;
	}
	return false;
}

bool HttpRequest::addHeader(const char* begin,const char* end)
{
	while (begin < end && *begin == ' ') ++begin;
	while (begin < end && *(end - 1) == ' ') --end;
	if (begin == end) return false;
	const char* colon = std::find(begin,end,':');
	if (colon == end) return false;
	const char* name_end = colon;
	while (begin < name_end && *(name_end-1) == ' ') --name_end;
	std::string name(begin,name_end);
	++colon;
	while (colon < end && *colon == ' ') ++colon;
	std::string value(colon,end);
	headers_[name] = value;
	return true;
}

std::string HttpRequest::getHeader(const std::string& name)
{
	std::string result;
	std::map<std::string,std::string>::iterator it = headers_.find(name);
	if (it != headers_.end()) result = it->second;
	return result;
}
	
}
