#include "XPM2.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <iomanip>
using namespace std;
namespace prog {
    int hex_to_int(const string& string) { //Function that transforms a hexadecimal string into an integer.
        stringstream ss;
        int result;
        ss << hex << string;
        ss >> result;
        return result;
    }

    Image* loadFromXPM2(const std::string& file) {

        ifstream infile(file);
        string line;

        getline(infile, line); // Skip the file header.
        int width,height,num_colors,chars;
        infile >>width>>height>>num_colors>>chars; //The variable "chars" will never be used because its always one character per pixel.
        getline(infile, line); //Consume the end of line character.

        Image *image = new Image(width,height);
        map<char,string> char_color; //Map that pairs all the characters to its corresponding color.
        char symbol,color_entry; //The variable "color_entry" will never be used because the XPM2 colors section contains only c (“color”) entries.
        string hex_color;
        
        for(int i=0;i<num_colors;i++){ //Loop for getting all the character/color pairs.
            infile>>symbol>>color_entry>>hex_color;
            char_color[symbol]=hex_color;
            getline(infile,line); //Consume the end of line character.
        }
        for(int i=0;i<height;i++){
            getline(infile,line);  //Puts each pixel encoding line into string "line".
            for(int j=0;j<width;j++){ 
                image->at(j,i).red()=hex_to_int((char_color[line[j]].substr(1, 2)));
                image->at(j,i).green()=hex_to_int((char_color[line[j]].substr(3, 2)));
                image->at(j,i).blue()=hex_to_int((char_color[line[j]].substr(5, 2)));
            }
        }
        return image;
    }
    
    std::string int_to_hex(int value) {
        //Function that transforms a integer value into a hexadecimal value in string format (returns the string)
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2)<< std::hex << value;
        return ss.str();
    }

    void saveToXPM2(const std::string& file, const Image* image) {
        std::ofstream outfile(file);
        
        int width = image->width();
        int height = image->height();

        outfile << "! XPM2 " << std::endl;
        
        //Store the current position in the file after writing the header line
        std::streampos colorCountPos = outfile.tellp();
        outfile << width << " " << height << " 0 1" << std::endl;

        std::vector<std::pair<Color, char>> colorList;

        char currentSymbol = '!';
        /*
        For each pixel it checks if it is a color already defined in colorList
        and if not it is added in the format 'symbol + c + #hex(color)' and
        it is printed in the outfile.
        */
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                const Color& color = image->at(x, y);
                bool colorExists = false;

                //Check if the color already exists in the colorList
                for (const auto& pair : colorList) {
                    if (color == pair.first) {
                        colorExists = true;
                        break;
                    }
                }

                //If the color does not exist, add it to the colorList with symbol
                if (!colorExists) {
                    outfile << currentSymbol << " c #"
                            << int_to_hex(color.red()) << int_to_hex(color.green())
                            << int_to_hex(color.blue()) << std::endl;

                    colorList.emplace_back(color, currentSymbol);
                    currentSymbol++;
                }
            }
        }

        //Calculate the color count
        int colorCount = colorList.size();
        //Move the file pointer to the stored position and overwrite the line with the correct color count
        outfile.seekp(colorCountPos);
        outfile << width << " " << height << " " << colorCount << " 1" << std::endl;
        //Move the file pointer to the end of the file
        outfile.seekp(0, std::ios::end);

        //For every pixel it prints the symbol corresponding to the color
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                const Color& color = image->at(x, y);

                char symbol = '!';
                for (const auto& pair : colorList) {
                    if (color == pair.first) {
                        symbol = pair.second;
                    }
                }
                outfile << symbol;
            }
            outfile << std::endl;
        }
        outfile.close();
    }
}