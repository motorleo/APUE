#ifndef _HTTP_HTTPRESPONSE_H_
#define _HTTP_HTTPRESPONSE_H_
#include <muduo/net/Buffer.h>

#include <string>
#include <map>

namespace leo
{
class HttpResponse
{
	enum Status
	{
		s200,
		s400,
		s404,
		s505,
	};

	enum Version
	{
		v10,
		v11,
		vUnknow,
	};
public:
	bool setVersion(const std::string& value);

	std::string getVersion();

	bool setStatus(const std::string value); 

	std::string getStatus();

	bool setReason(const std::string& value) { reason_ = value;	return true; }

	const std::string& getReason() { return reason_; }

	bool addHeader(const std::string& str) 
	{
	   	size_t colon = str.find(':');
		if (colon == 0 || colon == str.size()) return false;
		headers_.push_back(str); 
		return true;
	}

	const std::vector<std::string>& getHeaders() { return headers_; }

	bool setBody(const std::string& body) { body_ = body; return true; }

	bool appendBuffer(muduo::net::Buffer* buf);
private:
	Version version_;
	Status status_;
	std::string reason_;
	std::vector<std::string> headers_;
	std::string body_;
};
}//namespace leo
#endif
