#pragma once

#include <domain/JpegConsumer.hpp>

#include <array>
#include <cstdint>

namespace esp_robocraft
{

class JpegBuffer
{
public:
    JpegBuffer(JpegConsumer& consumer);

    void add(const std::array<std::uint8_t, 1024>& data, std::size_t size);
    void setWaitedSize(std::uint32_t waited_size);
    bool isCompleted() const;

private:
    JpegConsumer& _consumer;

    std::vector<std::uint8_t> _buffer;

    std::uint32_t _waited_size;
    bool          _is_completed;
};

} // namespace esp_robocraft
