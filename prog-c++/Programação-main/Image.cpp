#include "Image.hpp"
using namespace std;
namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
      Width=w;
      Height=h;
      Pixels=vector<vector<Color>> (Height,vector<Color>(Width,fill)); // Makes Pixels a vector of size Height made up of
                                                                       // smaller vectors of size Width containing fill
  }
  Image::Image(const Image& x){
    Width = x.Width;
    Height = x.Height;
    Pixels = x.Pixels;
  }
  Image::~Image() //The destructor is not implemented because dynamically allocated memory is not used explicitly.
  {
  }
  int Image::width() const //Get image width.
  {
    return Width;
  }
  int Image::height() const  //Get image height.
  {
    return Height;
  }

  Color& Image::at(int x, int y) //Get mutable reference to the value of pixel (x, y)
  {
    return Pixels[y][x];
  }

  const Color& Image::at(int x, int y) const //Get read-only reference to the value of pixel (x, y).
  {
    return Pixels[y][x];
  }
}