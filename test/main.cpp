
#include "precomp.hpp"

#include "images.hpp"

using namespace std;
using namespace cv;

class CalcDisparityImages : public Images {
public:
  explicit CalcDisparityImages(int maxDisparity)
    : Images({ "left", "right", "groundtruth" }, { "disparity" }),
      _maxDisparity(maxDisparity),
      _sgbm(stereo::StereoBinarySGBM::create(0, _maxDisparity, 9)) {}

private:
  virtual void calculate(std::map<std::string, cv::Mat> & images_write, std::map<std::string, cv::Mat> & images_read) {
    Mat disp;
    _sgbm->compute(images_read["left"], images_read["right"], disp);
    disp.convertTo(disp, CV_8UC1, 256.0 / ((_maxDisparity - 1) * 16), 0.0);
    images_write["disparity"] = disp;
  };
  virtual void evaluate(std::map<std::string, cv::Mat> & images_write, std::map<std::string, cv::Mat> & images_read) {
    double alpha = _maxDisparity / 256.0;
    Mat err = (abs(images_read["groundtruth"] * alpha - images_write["disparity"] * alpha)(Range(16, 300), Range(64, 400)) > 4) / 255;
    tout << sum(err)[0] / err.size().area() << tendl;
  };

  int const _maxDisparity;
  Ptr<stereo::StereoBinarySGBM> _sgbm;
};

int main(int argc, char ** argv) {
  cout << "cvMain: Hello OpenCV" << endl;

  CalcDisparityImages ths(64);
  for (size_t index = 1; index < (size_t)-1; ++index) {
    string images_index = static_cast<stringstream &>(stringstream() << setw(4) << setfill('0') << index).str();
    ths.process(
      index,
      { "./book/L" + images_index + ".png",
        "./book/R" + images_index + ".png",
        "./book/TL" + images_index + ".png" },
      { "./bin/output/SGBM" + images_index + ".png" });
    if (!ths) break;
  }
  ths.join();

  return 0;
}
