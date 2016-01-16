#include "HttpResponse.h"

namespace leo
{
bool HttpResponse::setVersion(const std::string& value)
{
	if (value == "1.0")
	{
		version_ = v10;
		return true;
	}
	if (value == "1.1")
	{
		version_ = v11;
		return true;
	}
	return false;
}

std::string HttpResponse::getVersion()
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

bool HttpResponse::setStatus(const std::string value)
{
	if (value == "200")
	{
		status_ = s200;
		return true;
	}
	if (value == "400")
	{
		status_ = s400;
		return true;
	}
	if (value == "404")
	{
		status_ = s404;
		return true;
	}
	if (value == "505")
	{
		status_ = s505;
		return true;
	}
	return false;
}

std::string HttpResponse::getStatus()
{
	switch (status_)
	{
		case s200 :
			return "200";
		case s400 :
			return "400";
		case s404 :
			return "404";
		case s505 :
			return "505";
		default :
			return "UNKNOW";
	}
}

bool HttpResponse::appendBuffer(muduo::net::Buffer* buf)
{
	std::string version = getVersion();
	if (version == "UNKNOW") return false;
	std::string status = getStatus();
	if (status == "UNKNOW") return false;
	std::string response = version + ' ' + status + ' ' + getReason() + "\r\n";
	for (std::vector<std::string>::iterator it = headers_.begin();
											it != headers_.end();
											++it)
	{
		response = response + *it + "\r\n";
	}
	response += "\r\n";
	buf->append(response);
	if (body_) buf->append(*body_);
	return true;
}
}//namespace leo
