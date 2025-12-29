#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/json.hpp>
#include <map>
#include <memory>

namespace boostpp {

namespace net = boost::asio;
namespace ssl = net::ssl;
namespace beast = boost::beast;
namespace http = beast::http;

using tcp = net::ip::tcp;

enum class HttpMethod {
    Get,
    Post,
    Put,
    Delete,
};

struct RequestOptions
{
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> query;
    std::chrono::milliseconds timeout {30000};

    bool keep_alive {true};
    bool follow_redirects {true};
};

struct Response
{
    int status {0};
    std::string body;
    std::map<std::string, std::string> headers;

    bool ok() const
    {
        return status >= 200 && status < 300;
    }
};

struct Error
{
    beast::error_code ec;
    std::string msg;

    explicit operator bool() const { return !!ec; }
};

//
// AsyncRequest Class
// Support GET/POST/PUT/DELETE
// Support SSL/TLS
// Support HTTP/2
// Support JSON
// Support Query Parameters
// Support Custom Headers
// Support Timeout
// Support Redirects
// Support Connection Pooling
// Support Logging
// Support Cancellation
// Support Proxy
// Support Keep-Alive
// Support Chunked Transfer Encoding
// Support Connection Reuse
// Support Pipelining
//
// Support Callback
//

// Boost HTTP Request
// - HTTP
//  - Resolve
//  - Connect
//  - Write
//  - Read
// - HTTPS
//  - Resolve
//  - Connect
//  - TLS Handshake
//  - Write
//  - Read
//
class AsyncRequest : std::enable_shared_from_this<AsyncRequest>
{
public:
    using Callback = std::function<void(const Error &, const Response &)>;

    AsyncRequest(net::io_context &ioc)
        : m_resolver(ioc)
        , m_ssl_ctx(ssl::context::tlsv12_client)
        , m_ssl_stream(ioc, m_ssl_ctx)
        , m_stream(ioc)
        , m_timer(ioc)
    {
    }

    ~AsyncRequest() = default;

    void GET(const std::string &url,
             const RequestOptions &options);

    void POST(const std::string &url,
              const RequestOptions &options);

    void PUT(const std::string &url,
             const RequestOptions &options);

    void DELETE(const std::string &url,
                const RequestOptions &options);

private:
    void request(HttpMethod method,
                 const std::string &url,
                 const RequestOptions &options)
    {
    }

    // async chain
    void onResolve(beast::error_code ec, tcp::resolver::results_type results)
    {
    }

    void onConnect(beast::error_code ec, tcp::resolver::results_type::endpoint_type endpoint)
    {
    }

    void onHandshake(beast::error_code ec)
    {
    }

    void onWrite(beast::error_code ec, std::size_t bytes_transferred)
    {
    }

    void onRead(beast::error_code ec, std::size_t bytes_transferred)
    {
    }

private:
    tcp::resolver m_resolver;
    // ssl
    ssl::context m_ssl_ctx;
    beast::ssl_stream<beast::tcp_stream> m_ssl_stream;
    // no ssl stream
    beast::tcp_stream m_stream;
    beast::flat_buffer m_buffer;
    http::request<http::string_body> m_request;
    http::response<http::string_body> m_response;
    net::steady_timer m_timer;

    std::string m_host;
    std::string m_port;
    std::string m_target;

    bool m_ssl {false};

    Callback m_callback;
};

struct RequestBuilder
{
    net::io_context &m_ioc;
    HttpMethod m_method;
    std::string m_url;
    RequestOptions m_options;

    RequestBuilder &method(HttpMethod method)
    {
        this->m_method = method;
        return *this;
    }

    RequestBuilder &url(const std::string &url)
    {
        this->m_url = url;
        return *this;
    }

    RequestBuilder &options(const RequestOptions &options)
    {
        this->m_options = options;
        return *this;
    }
};

} // namespace boostpp
