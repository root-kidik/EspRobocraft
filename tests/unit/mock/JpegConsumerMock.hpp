#pragma once

#include <gmock/gmock.h>

#include <domain/JpegConsumer.hpp>

class JpegConsumerMock final : public esp_robocraft::JpegConsumer
{
public:
    MOCK_METHOD(void, on_jpeg, (const std::vector<std::uint8_t>& jpeg), (override));
};
