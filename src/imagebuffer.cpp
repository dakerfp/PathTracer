#include "imagebuffer.h"

#include <cmath>

namespace PathTrace {

static std::ostream& operator<<(std::ostream& stream, const color& color)
{
    stream << round(color.r) << " ";
    stream << round(color.g) << " ";
    stream << round(color.b) << " ";
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const ImageBuffer &image)
{
    stream << "P3" << std::endl; // P3 is the magic number
    stream << image.w << " "<< image.h << std::endl;
    stream << 255 << std::endl; // XXX: get this automaticaly
    for (const auto& color : image.buffer) {
        stream << color << " ";
    }
    return stream;
}

}