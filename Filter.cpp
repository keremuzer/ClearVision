#include "Filter.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <numeric>
#include <math.h>
#include <iostream>

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
    double kernel[kernelSize][kernelSize];
    double weight_sum = 0;

    for (int i = -kernelSize / 2; i <= kernelSize / 2; i++)
    {
        for (int j = -kernelSize / 2; j <= kernelSize / 2; j++)
        {
            kernel[i + kernelSize / 2][j + kernelSize / 2] = (1 / (2 * M_PI * sigma * sigma)) * exp(-(i * i + j * j) / (2 * sigma * sigma));
            weight_sum += kernel[i + kernelSize / 2][j + kernelSize / 2];
        }
    }

    for (int i = 0; i < kernelSize; i++)
    {
        for (int j = 0; j < kernelSize; j++)
        {
            kernel[i][j] /= weight_sum;
        }
    }

    double sum = 0;
    GrayscaleImage original(image);
    for (int i = 0; i < original.get_height(); i++)
    {
        for (int j = 0; j < original.get_width(); j++)
        {
            sum = 0;
            for (int m = -kernelSize / 2; m <= kernelSize / 2; m++)
            {
                for (int n = -kernelSize / 2; n <= kernelSize / 2; n++)
                {
                    if (i + m >= 0 && j + n >= 0 && i + m < original.get_height() && j + n < original.get_width())
                    {
                        sum += original.get_pixel(i + m, j + n) * kernel[m + kernelSize / 2][n + kernelSize / 2];
                    }
                }
            }
            image.set_pixel(i, j, floor(sum));
        }
    }
}

// Unsharp Masking Filter
void Filter::apply_unsharp_mask(GrayscaleImage &image, int kernelSize, double amount)
{
    // TODO: Your code goes here.
    // 1. Blur the image using Gaussian smoothing, use the default sigma given in the header.
    // 2. For each pixel, apply the unsharp mask formula: original + amount * (original - blurred).
    // 3. Clip values to ensure they are within a valid range [0-255].
    GrayscaleImage original(image);
    apply_gaussian_smoothing(image, kernelSize);
    for (int i = 0; i < image.get_height(); i++)
    {
        for (int j = 0; j < image.get_width(); j++)
        {
            int result = original.get_pixel(i, j) + amount * (original.get_pixel(i, j) - image.get_pixel(i, j));
            if (result > 255)
            {
                result = 255;
            }
            else if (result < 0)
            {
                result = 0;
            }
            image.set_pixel(i, j, result);
        }
    }
}
