#ifndef _HTTP_HTTPREQUEST_H_
#define _HTTP_HTTPREQUEST_H_
#include <muduo/net/Buffer.h>

#include <string>
#include <map>

namespace leo
{
class HttpRequest
{
public:
	std::string getMethod() const;

	bool setMethod(const char* begin,const char* end);

	const std::string& getPath() const { return path_; }

	void setPath(const char* begin,const char* end)
   	{
	   	path_.assign(begin,end);
   	}

	const std::string& getQuery() const { return query_; }

	void setQuery(const char* begin,const char* end)
   	{
	   	query_.assign(begin,end);
   	}

	std::string getVersion() const;

	bool setVersion(const char* begin,const char* end);

	const std::map<std::string,std::string>& getHeadersMap() const { return headers_; }

	bool addHeader(const char* begin,const char* end);

	std::string getHeader(const std::string& name);

	bool parseFormBuffer(muduo::net::Buffer* buf);
private:
	bool parseRequestLine(const char* begin,const char* end);

	enum Method 
	{
		kGet,
		kHead,
		kUnknow,
	};

	enum Version
	{
		v10,
		v11,
		vUnknow,
	};

	Method method_;
	std::string path_;
	std::string query_;
	Version version_;
	std::map<std::string,std::string> headers_;
};
}
#endif
