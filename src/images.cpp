
#include "images.hpp"

using namespace std;

Images::Images(vector<string> window_reads, vector<string> window_writes)
  : _window_reads(window_reads), _window_writes(window_writes), _names_reads(), _names_writes(), _images_reads(), _images_writes(), _closed(false),
    _th_read(bind(&Images::_read, this)),
    _th_process(bind(&Images::_process, this)),
    _th_write(bind(&Images::_write, this)) {}

Images::~Images() {
  join();
}

void Images::join() {
  _names_reads.close();
  _names_writes.close();
  if (_th_read.joinable()) _th_read.join();
  if (_th_process.joinable()) _th_process.join();
  if (_th_write.joinable()) _th_write.join();
}

Images::_Myt & Images::process(size_t index, std::vector<std::string> const & names_read, std::vector<std::string> const & names_write) {
  if (!*this) return *this;

  for (auto & name_read : names_read) {
    if (!ifstream(name_read)) {
      _closed = true;
      return *this;
    }
  }

  _names_reads.push_back({ index, names_read });
  _names_writes.push_back({ index, names_write });
  return *this;
}
