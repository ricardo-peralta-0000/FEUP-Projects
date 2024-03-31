#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"
#include <vector>
namespace prog
{
  class Image
  {
  private:
    int Width;
    int Height;
     std::vector<std::vector<Color>> Pixels; //2Dvector to represent a image, the width is the 
                                             //number of columns and the height is the number of lines.
                                             //Each element represents a pixel, and each pixel has a color.
  public:
    Image(int w, int h, const Color &fill = {255, 255, 255});
    Image(const Image& x);
    ~Image();
    int width() const;
    int height() const;
    Color &at(int x, int y);
    const Color &at(int x, int y) const;
  };
}
#endif