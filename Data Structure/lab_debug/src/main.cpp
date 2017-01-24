#include<iostream>
#include "epng.h"
using namespace std;

// sets up the output image
epng::png* setupOutput(int w, int h);

// Returns my favorite color
epng::rgba_pixel* myFavoriteColor(int intensity);

int main()
{
    // Load in.png
    epng::png* original;
    original = new epng::png;
cout<<"At Function main"<<"  At Line"<<__LINE__<<endl;
    original->load("in.png");
cout<<"At Function main"<<"  At Line"<<__LINE__<<endl;
    int width = original->width();
cout<<"At Function main"<<"  At Line"<<__LINE__<<endl;
    int height = original->height();
cout<<"At Function main"<<"  At Line"<<__LINE__<<endl;

    // Create out.png
    epng::png* output;
    output = new epng::png;
    cout<<width<<endl;
    cout<<height<<endl;
    output=setupOutput(width, height);
cout<<"At Function main"<<"  At Line"<<__LINE__<<endl;
    // Loud our favorite color to color the outline
    epng::rgba_pixel* myPixel = myFavoriteColor(192);
cout<<"At Function main"<<"  At Line"<<__LINE__<<endl;
    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    for (int y = 1; y< height; y++)
    {
        for (int x = 1; x < width; x++)
        {
            // Calculate the pixel difference
            epng::rgba_pixel* prev = (*original)(x - 1, y - 1);
            epng::rgba_pixel* curr = (*original)(x, y);

            int diff = abs(curr->red - prev->red) +
                       abs(curr->green - prev->green) +
                       abs(curr->blue - prev->blue);

            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            epng::rgba_pixel* currOutPixel = (*output)(x, y);

            if (diff > 100)
                *currOutPixel = *myPixel;
cout<<"x"<<x<<"y"<<y<<endl;
        }
    }
cout<<"At Function main"<<"  At Line"<<__LINE__<<endl;
    // Save the output file
    output->save("out.png");
cout<<"At Function main"<<"  At Line"<<__LINE__<<endl;
    // Clean up memory
    delete myPixel;
cout<<"At Function main"<<"  At Line"<<__LINE__<<endl;
    delete output;
cout<<"At Function main"<<"  At Line"<<__LINE__<<endl;
    delete original;
cout<<"At Function main"<<"  At Line"<<__LINE__<<endl;
    return 0;
}

// sets up the output image
epng::png* setupOutput(int w, int h)
{
    epng::png* image = new epng::png(w, h);
    return image;
}

// Returns my favorite color
//epng::rgba_pixel* myFavoriteColor(int intensity)
//{
//    epng::rgba_pixel color;
//    color.red = 0;
//    color.green = intensity / 2;
//    color.blue = intensity;
//    return& color;
//}

epng::rgba_pixel* myFavoriteColor(int intensity)
{
    epng::rgba_pixel* bb= new epng::rgba_pixel;
    (*bb).red = 0;
    (*bb).green = intensity / 2;
    (*bb).blue = intensity;
    return bb;
}
