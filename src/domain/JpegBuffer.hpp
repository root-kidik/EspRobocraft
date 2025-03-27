#pragma once

#include <array>
#include <cstdint>
#include <vector>

#include <domain/JpegConsumer.hpp>

namespace esp_robocraft
{

class JpegBuffer
{
public:
    JpegBuffer(JpegConsumer& consumer);

    void add(const std::array<std::uint8_t, 1024>& data, std::size_t size);

private:
    std::vector<std::uint8_t> _buffer;

    JpegConsumer& _consumer;
};

} // namespace esp_robocraft
