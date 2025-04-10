#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <mock/JpegConsumerMock.hpp>

#include <domain/JpegBuffer.hpp>

template <typename... Arrays>
std::vector<std::uint8_t> vector_from_arrays(std::size_t size = 1024, const Arrays&... arrays)
{
    std::vector<std::uint8_t> vector;
    (vector.insert(vector.end(), arrays.begin(), arrays.begin() + +size), ...);
    return vector;
}

std::array<std::uint8_t, 1024> generate_jpeg(std::size_t size = 1024, bool is_end_generated_needed = true)
{
    std::array<std::uint8_t, 1024> buffer;

    for (std::size_t i = 0; i < size; i++)
        buffer[i] = i % 255;

    if (is_end_generated_needed)
    {
        buffer[size - 2] = 0xFF;
        buffer[size - 1] = 0xD9;
    }

    return buffer;
}

TEST(JpegBuffer, ReadOne)
{
    JpegConsumerMock jpeg_consumer;

    esp_robocraft::JpegBuffer jpeg_buffer{jpeg_consumer};

    const auto received_buffer = generate_jpeg();

    EXPECT_CALL(jpeg_consumer, on_jpeg(vector_from_arrays(received_buffer.size(), received_buffer))).WillOnce(testing::Return());

    jpeg_buffer.add(received_buffer, received_buffer.size());
}

TEST(JpegBuffer, ReadTwo)
{
    JpegConsumerMock jpeg_consumer;

    esp_robocraft::JpegBuffer jpeg_buffer{jpeg_consumer};

    const std::size_t received_buffer_begin_size = 512;
    const std::size_t received_buffer_end_size   = 512;

    const auto received_buffer_begin = generate_jpeg(received_buffer_begin_size, false);
    const auto received_buffer_end   = generate_jpeg(received_buffer_end_size, true);

    EXPECT_CALL(jpeg_consumer,
                on_jpeg(vector_from_arrays(received_buffer_begin_size, received_buffer_begin, received_buffer_end)))
        .WillOnce(testing::Return());

    jpeg_buffer.add(received_buffer_begin, received_buffer_begin_size);
    jpeg_buffer.add(received_buffer_end, received_buffer_end_size);
}

TEST(JpegBuffer, ReadThree)
{
    JpegConsumerMock jpeg_consumer;

    esp_robocraft::JpegBuffer jpeg_buffer{jpeg_consumer};

    const std::size_t sz = 512;

    const auto received_buffer_first_end    = generate_jpeg(sz, true);
    const auto received_buffer_second_begin = generate_jpeg(sz, false);

    std::array<std::uint8_t, 1024> first;
    for (std::size_t i = 0; i < sz; i++)
        first[i] = received_buffer_first_end[i];
    for (std::size_t i = sz, j = 0; i < sz * 2; i++, j++)
        first[i] = received_buffer_second_begin[j];

    EXPECT_CALL(jpeg_consumer, on_jpeg(vector_from_arrays(sz, received_buffer_first_end))).WillOnce(testing::Return());

    jpeg_buffer.add(first, sz * 2);

    const auto received_buffer_second_end = generate_jpeg(sz, true);

    EXPECT_CALL(jpeg_consumer, on_jpeg(vector_from_arrays(sz, received_buffer_second_begin, received_buffer_second_end))).WillOnce(testing::Return());

    jpeg_buffer.add(received_buffer_second_end, sz);
}

TEST(JpegBuffer, ReadN)
{
    JpegConsumerMock jpeg_consumer;

    esp_robocraft::JpegBuffer jpeg_buffer{jpeg_consumer};

    const std::size_t received_buffer_begin_size = 512;
    const std::size_t received_buffer_end_size   = 512;

    const std::size_t count_frames = 10;

    for (std::size_t i = 0; i < count_frames; i++)
    {
        const auto received_buffer_begin = generate_jpeg(received_buffer_begin_size, false);
        const auto received_buffer_end   = generate_jpeg(received_buffer_end_size, true);

        EXPECT_CALL(jpeg_consumer,
                    on_jpeg(vector_from_arrays(received_buffer_begin_size, received_buffer_begin, received_buffer_end)))
            .WillOnce(testing::Return());

        jpeg_buffer.add(received_buffer_begin, received_buffer_begin_size);
        jpeg_buffer.add(received_buffer_end, received_buffer_end_size);
    }
}
