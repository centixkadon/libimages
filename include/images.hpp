
#pragma once

#include <exstl.hpp>

#include <opencv2/opencv.hpp>

class Images {
  typedef Images _Myt;

  struct _Myname {
    size_t index;
    std::vector<std::string> names;
  };
  typedef std::thread_list<_Myname> _Mynames;

  struct _Myimage {
    size_t index;
    std::map<std::string, cv::Mat> images;
  };
  typedef std::thread_list<_Myimage> _Myimages;

public:
  explicit Images(std::vector<std::string> window_reads, std::vector<std::string> window_writes);
  ~Images();
  void join();
  _Myt & process(size_t index, std::vector<std::string> const & names_read, std::vector<std::string> const & names_write);

  inline operator bool() const { return !!*this; }
  inline bool operator!() const { return _closed; }

private:
  void _read();
  void _process();
  void _write();

  virtual bool preprocess(std::map<std::string, cv::Mat> & images_read);
  virtual void calculate(std::map<std::string, cv::Mat> & images_write, std::map<std::string, cv::Mat> & images_read) = 0;
  virtual void evaluate(std::map<std::string, cv::Mat> & images_write, std::map<std::string, cv::Mat> & images_read) {}

  std::vector<std::string> _window_reads, _window_writes;
  _Mynames _names_reads, _names_writes;
  _Myimages _images_reads, _images_writes;
  std::thread _th_read, _th_process, _th_write;
  bool _closed;
};
