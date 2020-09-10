//Josh Hnat CSCI E-72
//Project 1 

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <vector>

using namespace std;

//struct for pixel to create linked list
struct pixel
{
    //pixel values
    int red;
    int blue;
    int green;

    //construtor
    pixel(int r, int b, int g)
    {
        red = r;
        blue = b;
        green = g;
    }

    pixel() {}
};

struct picture 
{
    vector<vector<pixel>> pic;
    int height, width;
    unsigned char max_color_val;
    string comment = "#Creator: Josh!", ppmtype;

    picture(){}
};

void lighten(picture *picture) {
    for (int i = 0; i < (*picture).width; i++) {
        for (int p = 0; p < (*picture).height; p++) {
            //have to account for if the pixel value goes above the set maximum
            if ((*picture).pic[i][p].red * 2 > (*picture).max_color_val) {
                (*picture).pic[i][p].red = (*picture).max_color_val;
            }
            else {
                (*picture).pic[i][p].red *= 2;
            }
            if ((*picture).pic[i][p].blue * 2 > (*picture).max_color_val) {
                (*picture).pic[i][p].blue = (*picture).max_color_val;
            }
            else {
                (*picture).pic[i][p].blue *= 2;
            }
            if ((*picture).pic[i][p].green * 2 > (*picture).max_color_val) {
                (*picture).pic[i][p].green = (*picture).max_color_val;
            }
            else {
                (*picture).pic[i][p].green *= 2;
            }
        }
    }
}

void darken(picture *picture) {
    for (int i = 0; i < (*picture).width; i++) {
        for (int p = 0; p < (*picture).height; p++) {
            //have to account for if the pixel value is 0
            if ((*picture).pic[i][p].red == 0) {
                (*picture).pic[i][p].red = 0;
            }
            else {
                (*picture).pic[i][p].red /= 2;
            }
            if ((*picture).pic[i][p].blue == 0) {
                (*picture).pic[i][p].blue = 0;
            }
            else {
                (*picture).pic[i][p].blue /= 2;
            }
            if ((*picture).pic[i][p].green == 0) {
                (*picture).pic[i][p].green = 0;
            }
            else {
                (*picture).pic[i][p].green /= 2;
            }
        }
    }
}

void readFromPPM(string filename, picture *picture) {
    string max; // ween need this for character conversion
    ifstream inFile;

    inFile.open(filename.c_str(), ifstream::in);

    getline(inFile, (*picture).ppmtype);
    getline(inFile, (*picture).comment);
    inFile >> (*picture).width;
    inFile >> (*picture).height;
    //we do this twice because I couldnt figure out how to advance the filepointer to the next line
    getline(inFile, max);
    getline(inFile, max);
    (*picture).max_color_val = (unsigned char)(stoi(max));

    //cout << ppmtype << " " << comment << " " << w << " " << h << " " << max;
    pixel pixel(0, 0, 0);
    string temp;
    
    (*picture).pic.resize((*picture).width);
    for(int i = 0; i < (*picture).pic.size(); i++) //!inFile.eof()
    {
        (*picture).pic[i].resize((*picture).height);
        for (int z = 0; z < (*picture).pic[i].size() ; z++)
        {
            getline(inFile, temp);
            pixel.red = stoi(temp);
            getline(inFile, temp);
            pixel.blue = stoi(temp);
            getline(inFile, temp);
            pixel.green = stoi(temp);

            (*picture).pic[i][z] = pixel;
        }
    }
    
    inFile.close();
}

void writeToPPM(string comment, int w, int h, int c, picture* picture)//takes a head pointer the type of file (P3 in this case), width, height and max color val
{
    ofstream file;

    file.open("out.ppm", ofstream::out);

    file << "P3" << endl << comment << endl << w << " " << h << endl << c << endl; //writes important info to beginning of image file

    //initialize the pixel object being used to write to the file
    
    //traverse the vector and out to the new file!
    for (int i = 0; i < w; i++) {
        for (int p = 0; p < h; p++) {
            file << (*picture).pic[i][p].red << endl;
            file << (*picture).pic[i][p].blue << endl;
            file << (*picture).pic[i][p].green << endl;
        }
    }

    file.close();
}

int main()
{
    picture ppm;

    readFromPPM("test.ppm", &ppm);
    darken(&ppm);
    writeToPPM(ppm.comment, ppm.width, ppm.height, ppm.max_color_val, &ppm);

    cout << endl;    
}
