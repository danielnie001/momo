#ifndef WATCH_DOG_H_
#define WATCH_DOG_H_

#include <functional>

// Boost
#include <boost/asio.hpp>

/*
    用于监视超时的类。
    调用 Enable() 后，经过一定时间会调用回调函数。
    回调发生时 WatchDog 会被禁用，因此如果需要，可以再次调用 Enable() 或 Reset()。
    注意，在多线程环境下不工作。
*/
class WatchDog {
 public:
  WatchDog(boost::asio::io_context& ioc, std::function<void()> callback);
  void Enable(int timeout);
  void Disable();
  void Reset();

 private:
  int timeout_;
  boost::asio::deadline_timer timer_;
  std::function<void()> callback_;
};

#endif
