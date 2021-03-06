#pragma once

#include "common/uri/Uri.hpp"
#include "common/JoinableThread.hpp"

#include "ResponseResult.hpp"
#include "ProxyInfo.hpp"

#include <boost/asio/io_context.hpp>
#include <boost/thread/future.hpp>
#include <boost/noncopyable.hpp>
#include <boost/beast/http/verb.hpp>

using HttpResponseResult = ResponseResult<std::string>;
class HttpSession;
class Uri;

class HttpManager : private boost::noncopyable
{
public:
    ~HttpManager();

    static HttpManager& instance();

    void shutdown();
    void setProxyServer(const std::string& host, const std::string& username, const std::string& password);
    boost::future<HttpResponseResult> get(const Uri& uri);
    boost::future<HttpResponseResult> post(const Uri& uri, const std::string& body);

private:
    HttpManager();

    boost::future<HttpResponseResult> send(boost::beast::http::verb method, const Uri& uri, const std::string& body);

    boost::future<HttpResponseResult> managerStoppedError();
    void cancelActiveSession();

private:
    boost::asio::io_context m_ioc;
    boost::asio::io_context::work m_work;
    std::vector<std::unique_ptr<JoinableThread>> m_workerThreads;
    std::vector<std::weak_ptr<HttpSession>> m_activeSessions;
    boost::optional<ProxyInfo> m_proxyInfo;
};
