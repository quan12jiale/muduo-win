// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is a public header file, it must only include public header files.

#ifndef MUDUO_NET_HTTP_HTTPSERVER_H
#define MUDUO_NET_HTTP_HTTPSERVER_H

#include "uncopyable.h"
#include "InetAddress.h"
#include <EventLoop.h>
#include "TcpServer.h"

namespace calm
{
namespace net
{

class HttpRequest;
class HttpResponse;

/// A simple embeddable HTTP server designed for report status of a program.
/// It is not a fully HTTP 1.1 compliant server, but provides minimum features
/// that can communicate with HttpClient and Web browser.
/// It is synchronous, just like Java Servlet.
class HttpServer : calm::uncopyable
{
 public:
  typedef std::function<void (const HttpRequest&,
                              HttpResponse*)> HttpCallback;

  HttpServer(calm::net::EventLoop* loop,
             const calm::net::InetAddress& listenAddr,
             const std::string& name,
             calm::net::TcpServer::Option option = calm::net::TcpServer::kNoReusePort);

  calm::net::EventLoop* getLoop() const { return server_.getLoop(); }

  /// Not thread safe, callback be registered before calling start().
  void setHttpCallback(const HttpCallback& cb)
  {
    httpCallback_ = cb;
  }

  void setThreadNum(int numThreads)
  {
    server_.setThreadNum(numThreads);
  }

  void start();

 private:
  void onConnection(const calm::net::TcpConnectionPtr& conn);
  void onMessage(const calm::net::TcpConnectionPtr& conn,
      calm::net::Buffer* buf,
      calm::Timestamp receiveTime);
  void onRequest(const calm::net::TcpConnectionPtr&, const HttpRequest&);

  calm::net::TcpServer server_;
  HttpCallback httpCallback_;
};

}  // namespace net
}  // namespace muduo

#endif  // MUDUO_NET_HTTP_HTTPSERVER_H
