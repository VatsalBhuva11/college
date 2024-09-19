#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
using namespace cv;

vector<char> ascii_chars = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};

char mapGrayscaleToAscii(int gray_value)
{
    int num_chars = ascii_chars.size();
    return ascii_chars[gray_value * num_chars / 256];
}

int main()
{
    string image_path = "/home/vbuntu/Downloads/VATSALBHUVA.jpeg";
    Mat image = imread(image_path, IMREAD_GRAYSCALE);
    if (image.empty())
    {
        cerr << "Could not open or find the image\n";
        return -1;
    }

    /*
    The image is resized to a specific size based on the dimensions
    (3.5 inches by 4.5 inches) and a DPI (Dots Per Inch) value of 300.
    The conversion from inches to pixels is done using the formula
    pixels = inches * dpi / 2.54, where 2.54 is the number of centimeters in an inch.
    */
    int dpi = 300;
    int width_px = static_cast<int>(3.5 * dpi / 2.54);
    int height_px = static_cast<int>(4.5 * dpi / 2.54);
    resize(image, image, Size(width_px, height_px));

    string resized_image_path = "/home/vbuntu/Downloads/resized_selfie.jpg";
    imwrite(resized_image_path, image);

    int new_width = 80;
    int new_height = static_cast<int>(new_width * static_cast<float>(height_px) / width_px);
    resize(image, image, Size(new_width, new_height));

    string output_ascii_path = "/home/vbuntu/Downloads/ascii_art.txt";
    ofstream ascii_file(output_ascii_path);
    for (int i = 0; i < image.rows; ++i)
    {
        for (int j = 0; j < image.cols; ++j)
        {
            ascii_file << mapGrayscaleToAscii(image.at<uchar>(i, j));
        }
        ascii_file << '\n';
    }
    ascii_file.close();

    cout << "Grayscale (resized) path: " << resized_image_path << "\n";
    cout << "ASCII art path: " << output_ascii_path << "\n";

    return 0;
}
