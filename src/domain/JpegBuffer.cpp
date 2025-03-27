#include <domain/JpegBuffer.hpp>

namespace esp_robocraft
{

JpegBuffer::JpegBuffer(JpegConsumer& consumer) : _consumer{consumer}
{
}

void JpegBuffer::add(const std::array<std::uint8_t, 1024>& data, std::size_t size)
{
    if (size == 0)
        return;

    bool is_found = false;

    for (std::size_t i = 0; i < size - 1; i++)
        if (data[i] == 0xFF && data[i + 1] == 0xD9)
        {
            _buffer.insert(_buffer.end(), data.begin(), data.begin() + i + 2);

            _consumer.on_jpeg(_buffer);

            _buffer.clear();

            _buffer.insert(_buffer.end(), data.begin() + i + 2, data.begin() + size);
       
            is_found = true;
       
            break;
        }

    if (!is_found)
    {
        _buffer.insert(_buffer.end(), data.begin(), data.begin() + size);
    }
}

} // namespace esp_robocraft
