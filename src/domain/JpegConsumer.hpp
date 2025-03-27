#pragma once

#include <cstdint>
#include <vector>

namespace esp_robocraft
{

class JpegConsumer
{
public:
    virtual ~JpegConsumer() = default;

    virtual void on_jpeg(const std::vector<std::uint8_t>& jpeg) = 0;
};

} // namespace esp_robocraft
