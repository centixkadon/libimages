
#include <exstl.hpp>

#include "images.hpp"

using namespace std;
using namespace cv;

void Images::_process() {
  tout << "cvProcess: begin" << tendl;

  _Myimage images_read;
  while (_images_reads.pop_front(images_read)) {
    _Myimage images_write;
    calculate(images_write.index = images_read.index, images_write.images, images_read.images);
    evaluate(images_write.images, images_read.images);

    _images_writes.push_back(images_write);
  }

  _images_writes.close();
  tout << "cvProcess: end ================================" << tendl;
}
