#include <domain/JpegBuffer.hpp>

#include <cstring>

namespace esp_robocraft
{

JpegBuffer::JpegBuffer(JpegConsumer& consumer) : _consumer{consumer}, _waited_size{0}, _is_completed{true}
{
    _buffer.reserve(1024 * 500);
}

void JpegBuffer::add(const std::array<std::uint8_t, 1024>& data, std::size_t size)
{
    _buffer.insert(_buffer.end(), data.begin(), data.begin() + size);

    if (_buffer.size() >= _waited_size)
    {
        _consumer.on_jpeg(_buffer);
        _buffer.clear();
        _is_completed = true;
    }
}

void JpegBuffer::setWaitedSize(std::uint32_t waited_size)
{
    _waited_size = waited_size;
    _buffer.reserve(_waited_size);
    _is_completed = false;
}

bool JpegBuffer::isCompleted() const
{
    return _is_completed;
}

} // namespace esp_robocraft
