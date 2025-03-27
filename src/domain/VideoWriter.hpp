#pragma once

#include <domain/JpegConsumer.hpp>

namespace esp_robocraft
{

class VideoWriter final : public JpegConsumer
{
public:
    void on_jpeg(const std::vector<std::uint8_t>& jpeg) override;
};

} // namespace esp_robocraft
