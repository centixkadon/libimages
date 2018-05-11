
#include <exstl.hpp>

#include "images.hpp"

using namespace std;
using namespace cv;

bool Images::preprocess(map<string, Mat> & images_read) {
  for (auto & image_read : images_read) {
    if (image_read.second.empty()) return false;
    cvtColor(image_read.second, image_read.second, CV_RGB2GRAY);
  }
  return true;
}

void Images::_read() {
  tout << "cvRead: begin" << tendl;

  _Myname names_read;
  while (_names_reads.pop_front(names_read)) {
    _Myimage images_read;
    images_read.index = names_read.index;

    for (size_t i = 0; i < _window_reads.size(); ++i) {
      if (names_read.names[i] == "")
        images_read.images[_window_reads[i]] = Mat();
      else
        images_read.images[_window_reads[i]] = imread(names_read.names[i]);
    }

    if (!preprocess(images_read.images)) break;
    _images_reads.push_back(images_read);
  }

  _images_reads.close();
  tout << "cvRead: end ================================" << tendl;
}
