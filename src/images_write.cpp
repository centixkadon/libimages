
#include <exstl.hpp>

#include "images.hpp"

using namespace std;
using namespace cv;

void Images::_write() {
  tout << "cvWrite: begin" << tendl;

  _Myimage images_write;
  _Myname names_write;
  while (_images_writes.pop_front(images_write) && _names_writes.pop_front(names_write)) {
    for (size_t i = 0; i < _window_writes.size(); ++i) {
      imwrite(names_write.names[i], images_write.images[_window_writes[i]]);
    }
  }

  tout << "cvWrite: end ================================" << tendl;
}
