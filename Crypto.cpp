#include "Crypto.h"
#include "GrayscaleImage.h"

// Extract the least significant bits (LSBs) from SecretImage, calculating x, y based on message length
std::vector<int> Crypto::extract_LSBits(SecretImage &secret_image, int message_length)
{
    std::vector<int> LSB_array;
    // TODO: Your code goes here.

    // 1. Reconstruct the SecretImage to a GrayscaleImage.
    // 2. Calculate the image dimensions.
    // 3. Determine the total bits required based on message length.
    // 4. Ensure the image has enough pixels; if not, throw an error.
    // 5. Calculate the starting pixel from the message_length knowing that
    //    the last LSB to extract is in the last pixel of the image.
    // 6. Extract LSBs from the image pixels and return the result.

    GrayscaleImage image = secret_image.reconstruct();
    int width = image.get_width();
    int height = image.get_height();
    int total_bits = message_length * 7;

    if (width * height < total_bits)
    {
        throw std::invalid_argument("Image does not have enough pixels to store the LSB array");
    }

    int pixel_index = width * height - total_bits;
    int pixel_row = 0;
    int pixel_col = 0;
    int pixel = 0;

    for (int i = pixel_index; i < image.get_height() * image.get_width(); i++)
    {
        int row = i / image.get_width();
        int col = i % image.get_width();
        pixel = image.get_pixel(row, col);
        std::bitset<8> bits(pixel);
        LSB_array.push_back(bits[0]);
    }

    return LSB_array;
}

// Decrypt message by converting LSB array into ASCII characters
std::string Crypto::decrypt_message(const std::vector<int> &LSB_array)
{
    std::string message;
    // TODO: Your code goes here.

    // 1. Verify that the LSB array size is a multiple of 7, else throw an error.
    // 2. Convert each group of 7 bits into an ASCII character.
    // 3. Collect the characters to form the decrypted message.
    // 4. Return the resulting message.

    if (LSB_array.size() % 7 != 0)
    {
        throw std::invalid_argument("LSB array size is not a multiple of 7");
    }

    for (int i = 0; i < LSB_array.size(); i += 7)
    {
        std::bitset<7> bits;
        for (int j = 0; j < 7; j++)
        {
            bits[6 - j] = LSB_array[i + j];
        }
        unsigned long c = bits.to_ulong();
        message += static_cast<char>(c);
    }

    return message;
}

// Encrypt message by converting ASCII characters into LSBs
std::vector<int> Crypto::encrypt_message(const std::string &message)
{
    std::vector<int> LSB_array;
    // TODO: Your code goes here.

    // 1. Convert each character of the message into a 7-bit binary representation.
    //    You can use std::bitset.
    // 2. Collect the bits into the LSB array.
    // 3. Return the array of bits.

    for (char c : message)
    {
        std::bitset<7> bits(c);
        for (int i = 0; i < 7; i++)
        {
            LSB_array.push_back(bits[6 - i]);
        }
    }

    return LSB_array;
}

// Embed LSB array into GrayscaleImage starting from the last bit of the image
SecretImage Crypto::embed_LSBits(GrayscaleImage &image, const std::vector<int> &LSB_array)
{
    // TODO: Your code goes here.

    // 1. Ensure the image has enough pixels to store the LSB array, else throw an error.
    // 2. Find the starting pixel based on the message length knowing that
    //    the last LSB to embed should end up in the last pixel of the image.
    // 3. Iterate over the image pixels, embedding LSBs from the array.
    // 4. Return a SecretImage object constructed from the given GrayscaleImage
    //    with the embedded message.

    if (image.get_width() * image.get_height() < LSB_array.size())
    {
        throw std::invalid_argument("Image does not have enough pixels to store the LSB array");
    }

    int pixel_index = image.get_width() * image.get_height() - LSB_array.size();
    int row = 0;
    int col = 0;
    int LSB_index = 0;

    for (int i = pixel_index; i < image.get_height() * image.get_width(); i++)
    {
        row = i / image.get_width();
        col = i % image.get_width();
        int pixel = image.get_pixel(row, col);

        std::bitset<8> bits(pixel);
        bits.set(0, LSB_array[LSB_index]);
        LSB_index++;
        image.set_pixel(row, col, int(bits.to_ulong()));
    }
    return SecretImage(image);
}
