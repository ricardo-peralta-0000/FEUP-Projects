#include <iostream>
#include <fstream>
#include <algorithm>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }

    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open") {
                open();
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save") {
                save();
                continue;
            } 
            if (command == "invert") {
                invert();
                continue;
            }
            if (command == "to_gray_scale") {
                to_gray_scale();
                continue;
            }
            if (command == "replace") {
                replace();
                continue;
            }
            if (command == "fill"){
                fill();
                continue;
            }
            if (command == "h_mirror"){
                h_mirror();
                continue;
            }
            if (command == "v_mirror"){
                v_mirror();
                continue;
            }
            if (command == "add"){
                add();
                continue;
            }
            if (command == "crop"){
                crop();
                continue;
            }
            if (command == "rotate_left"){
                rotate_left();
                continue;
            }
            if (command == "rotate_right"){
                rotate_right();
                continue;
            }
            if (command == "median_filter"){
                median_filter();
                continue;
            }
            if(command =="xpm2_open"){
                clear_image_if_any();
               string filename;
                input>>filename;
                image = loadFromXPM2(filename);
                continue;
            }
            if(command =="xpm2_save"){
                string filename;
                input >> filename;
                saveToXPM2(filename, image);
                continue;
            }
        }
    }

    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }

    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }

    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }

    void Script::invert(){
        // Makes every rgb value of every pixel be equal to 255 minus itself, e.g. (255,100,55) becomes (0,155,200)
        for(int i=0; i< image->width(); i++){           
            for(int j=0; j< image->height();j++){
                image->at(i,j).red()=255-image->at(i,j).red();
                image->at(i,j).green()=255-image->at(i,j).green();
                image->at(i,j).blue()=255-image->at(i,j).blue();
            }
        }
    }

    void Script::to_gray_scale(){
        // Makes all rgb value of every pixel be the average of r, g and b of that pixel
        for(int i=0; i< image->width(); i++){           
            for(int j=0; j< image->height();j++){
                rgb_value grey_value = (image->at(i,j).red()+image->at(i,j).green()+image->at(i,j).blue())/3; //averages the 3 values
                image->at(i,j).red()=grey_value;
                image->at(i,j).green()=grey_value;
                image->at(i,j).blue()=grey_value;
            }
        }
    }

    void Script::replace(){
        // Replaces all pixels of Color 1 with pixels of Color 2
        Color Color1, Color2;
        input >> Color1;
        input >> Color2;
        for(int i=0; i< image->width(); i++){
            for(int j=0; j< image->height();j++){
                if (image->at(i,j)==Color1){
                    image->at(i,j)=Color2;
                }
            }
        }
    }

    void Script::fill(){
        // Paints a square of starting position (x,y) and of size defined by width and height into Color1
        int x,y,width,height;
        Color Color1;
        input >> x >> y >> width >> height >> Color1;
        for(int i=x; i<x+width; i++){
            for(int j=y; j<y+height;j++){
                image->at(i,j)=Color1;
            }
        }
    }

    void Script::h_mirror(){
        // Swaps every pixel (x,y) with every pixel (width-x,y)
        Color Storage;
        for(int i=0; i<image->width()/2; i++){
            for(int j=0; j< image->height();j++){
                Storage = image->at(i,j);
                image->at(i,j)=image->at(image->width()-i-1,j);
                image->at(image->width()-i-1,j)=Storage;
            }
        }
    }

    void Script::v_mirror(){
        // Swaps every pixel (x,y) with every pixel (x,height-y)
        Color Storage;
        for(int i=0; i<image->width(); i++){
            for(int j=0; j<image->height()/2;j++){
                Storage = image->at(i,j);
                image->at(i,j)=image->at(i,image->height()-j-1);
                image->at(i,image->height()-j-1)=Storage;
            }
        }
    }

    void Script::add(){
        // Copies another image onto a rectangle starting in the coordinates (x,y) of the current image. Ignores all pixels of Color C1.
        string filename;
        Color C1;
        int x,y;
        input >> filename >> C1 >> x >> y;
        const Image* image2;                    // defines a pointer to the image you're copying from
        image2 = loadFromPNG(filename);         // and loads the selected file into that image
        for(int i=0; i<image2->width(); i++){
            for(int j=0; j<image2->height();j++){
                if (image2->at(i,j)==C1){
                    continue;
                }
                image->at(i+x,j+y)=image2->at(i,j); // the coords for image2 are (i,j) but for image they have to be offset by x and y
            }
        }
        delete image2; // deletes image2 to prevent data leaks
    }

    void Script::crop() {
        //Receives (x,y) - a top-left corner of thecropped image
        //Receives width(w) and height(h)
        int x, y, w, h;
        input >> x >> y >> w >> h;
    
        //Create a new image with the cropped dimensions
        Image* cropped = new Image(w, h);

        //Creates the pixels in the cropped image
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                cropped->at(i, j) = image->at(x + i, y + j);
            }
        }
        //Deletes the original pointer and assignes the one to the cropped image
        delete image;  
        image = cropped; 
    }
  
    void Script::rotate_left() {
        
        //Create a new image with the dimensions of the rotated image
        Image* rotated = new Image(image->height(), image->width());

        //Rotates the original image 90 degrees left.
        //Every pixel (x,y) of the final image is swapped
        //with every pixel (height-y-1,x) of the initial one
        for (int i = 0; i < rotated->width(); i++) {
            for (int j = 0; j < rotated->height(); j++) {
                rotated->at(i, j) = image->at(rotated->height() - j - 1, i);
            }
        }

        //Deletes the original pointer and assignes the one to the cropped image
        delete image;  
        image = rotated;  
        }

    void Script::rotate_right() {

        //Create a new image with the dimensions of the rotated image
        Image* rotated = new Image(image->height(), image->width());

        //Rotates the original image 90 degrees right.
        //Every pixel (x,y) of the final image is swapped
        //with every pixel (y, width-x-1) of the initial one
        for (int i = 0; i < rotated->width(); i++) {
            for (int j = 0; j < rotated->height(); j++) {
                rotated->at(i, j) = image->at(j, rotated->width() - i - 1);
            }
        }
        
        //Deletes the original pointer and assignes the one to the cropped image
        delete image;  // Delete the original image.
        image = rotated;  // Update the image pointer to point to the rotated image.
    }

    Color Script::median_values(int min_x, int min_y, int max_x, int max_y){
        // Auxiliary function for median_filter. Given the range of x and y returns the median values of RGB values of those pixels
        vector<int> R, G, B;
        int final_R, final_G, final_B;

        for (int i=min_x; i<=max_x; i++){
            for (int j=min_y; j<=max_y; j++){
                R.push_back(image->at(i,j).red());
                G.push_back(image->at(i,j).green());
                B.push_back(image->at(i,j).blue());
            }
        }
        sort(R.begin(),R.end());
        sort(G.begin(),G.end());
        sort(B.begin(),B.end());

        int size = R.size();
        if (size%2==0){
            final_R = (R[size/2-1]+R[size/2])/2;
            final_G = (G[size/2-1]+G[size/2])/2;
            final_B = (B[size/2-1]+B[size/2])/2;
        }
        else{
            final_R = R[size/2];
            final_G = G[size/2];
            final_B = B[size/2];
        }
        return Color(final_R,final_G,final_B);
        
    }

    void Script::median_filter(){
        // Makes each pixel's RGB values the median of all the pixels' in it's neighboorhood (square of size "ws" centered on the pixel)
        int ms, max_x, max_y, min_x, min_y;
        input >> ms;
        Image* image2 = new Image(*image);  // Defines a pointer "image2" to a new object of type Image which is a copy of
                                            // the object "image" is pointing to. "*image" is used to dereference the pointer "image"

        for(int i=0; i<image->width(); i++){
            for(int j=0; j<image->height();j++){
                min_x = max(0,i-ms/2);
                max_x = min(image->width()-1,i+ms/2);
                min_y = max(0,j-ms/2);
                max_y = min(image->height()-1,j+ms/2);              
                
                image2->at(i,j)=median_values(min_x, min_y, max_x, max_y);
            }
        }
        *image=*image2;  //copies the object pointed at by "image2" into "image"
        delete image2;   //deletes image2 to prevent data leaks
    }
}