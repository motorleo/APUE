#define BOOST_TEST_MODULE Httptest
#include "../HttpRequest.h"
#include "../HttpResponse.h"
#include <boost/test/included/unit_test.hpp>

#include <string>

BOOST_AUTO_TEST_CASE (HttpRequest_test)
{
	leo::HttpRequest test;
	std::string str = "GET";
	test.setMethod(str.c_str(),str.c_str() + 3);
	BOOST_CHECK_EQUAL(test.getMethod(),str);
	str = "/";
	test.setPath(str.c_str(),str.c_str() + 1);
	BOOST_CHECK_EQUAL(test.getPath(),str);
	str = "a&b";
	test.setQuery(str.c_str(),str.c_str() + 3);
	BOOST_CHECK_EQUAL(test.getQuery(),str);
	str = "HTTP/1.1";
	test.setVersion(str.c_str(),str.c_str() + 8);
	BOOST_CHECK_EQUAL(test.getVersion(),str);
	str = "Host: local";
	test.addHeader(str.c_str(),str.c_str() + 11);
	BOOST_CHECK_EQUAL(test.getHeader("Host"),"local");
	str = "GET / HTTP/1.1\r\nHost: local\r\n\r\n";
	muduo::net::Buffer buf;
	buf.append(str);
	test.parseFormBuffer(&buf);
	BOOST_CHECK_EQUAL(test.getMethod(),"GET");
	BOOST_CHECK_EQUAL(test.getPath(),"/");
	BOOST_CHECK_EQUAL(test.getVersion(),"HTTP/1.1");
	BOOST_CHECK_EQUAL(test.getHeader("Host"),"local");
}

BOOST_AUTO_TEST_CASE (HttpResponse_test)
{
	leo::HttpResponse test;
	test.setVersion("1.1");
	BOOST_CHECK_EQUAL(test.getVersion(),"HTTP/1.1");
	test.setStatus("200");
	BOOST_CHECK_EQUAL(test.getStatus(),"200");
	test.setReason("test");
	BOOST_CHECK_EQUAL(test.getReason(),"test");
	test.addHeader("test: test");
	BOOST_CHECK_EQUAL(test.getHeaders().back(),"test: test");
	std::string str = "HTTP/1.1 200 test\r\ntest: test\r\n\r\n";
	muduo::net::Buffer buf;
	test.appendBuffer(&buf);
	BOOST_CHECK_EQUAL(std::string(buf.peek(),buf.readableBytes()),str);
}
