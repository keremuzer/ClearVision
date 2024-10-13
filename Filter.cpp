#include "Filter.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <numeric>
#include <math.h>

// Mean Filter
void Filter::apply_mean_filter(GrayscaleImage &image, int kernelSize)
{
    // TODO: Your code goes here.
    // 1. Copy the original image for reference.
    // 2. For each pixel, calculate the mean value of its neighbors using a kernel.
    // 3. Update each pixel with the computed mean.
    GrayscaleImage original(image);
    int sum = 0;
    int mean = 0;
    for (int i = 0; i < original.get_height(); i++)
    {
        for (int j = 0; j < original.get_width(); j++)
        {
            for (int m = -kernelSize / 2; m <= kernelSize / 2; m++)
            {
                for (int n = -kernelSize / 2; n <= kernelSize / 2; n++)
                {
                    if (i + m >= 0 && j + n >= 0 && i + m < original.get_height() && j + n < original.get_width())
                    {
                        sum += original.get_pixel(i + m, j + n);
                    }
                }
            }
            mean = sum / (kernelSize * kernelSize);
            image.set_pixel(i, j, mean);
            sum = 0;
            mean = 0;
        }
    }
}

// Gaussian Smoothing Filter
void Filter::apply_gaussian_smoothing(GrayscaleImage &image, int kernelSize, double sigma)
{
    // TODO: Your code goes here.
    // 1. Create a Gaussian kernel based on the given sigma value.
    // 2. Normalize the kernel to ensure it sums to 1.
    // 3. For each pixel, compute the weighted sum using the kernel.
    // 4. Update the pixel values with the smoothed results.
}

// Unsharp Masking Filter
void Filter::apply_unsharp_mask(GrayscaleImage &image, int kernelSize, double amount)
{
    // TODO: Your code goes here.
    // 1. Blur the image using Gaussian smoothing, use the default sigma given in the header.
    // 2. For each pixel, apply the unsharp mask formula: original + amount * (original - blurred).
    // 3. Clip values to ensure they are within a valid range [0-255].
}
