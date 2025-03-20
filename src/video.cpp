#include "video.hpp"
#include <opencv4/opencv2/opencv.hpp>
#include <userver/logging/log.hpp>
#include <userver/yaml_config/merge_schemas.hpp>

namespace esp_robocraft
{

VideoReceiver::VideoReceiver(const userver::components::ComponentConfig&  config,
                             const userver::components::ComponentContext& context) :
TcpAcceptorBase(config, context)
{
}

void VideoReceiver::ProcessSocket(userver::engine::io::Socket&& sock)
{
    std::array<char, 1024> buffer;

    std::vector<char> image_buffer;
    image_buffer.reserve(buffer.size());

    while (!userver::engine::current_task::ShouldCancel())
    {
        const auto read_bytes = sock.ReadAll(buffer.data(), buffer.size(), {});
        if (read_bytes <= 0)
            continue;

        bool is_found = false;

        LOG_DEBUG() << "Received: " << read_bytes;

        for (std::size_t i = 0; i < read_bytes - 1; i++)
            if (buffer[i] == static_cast<char>(0xFF) && buffer[i + 1] == static_cast<char>(0xD9))
            {
                LOG_DEBUG() << "JPEG end marker found. Writing image.";

                image_buffer.insert(image_buffer.end(), buffer.begin(), buffer.begin() + i + 2);

                if (auto mat = cv::imdecode(image_buffer, cv::IMREAD_COLOR); !mat.empty())
                {
                    LOG_DEBUG() << "Image written successfully.";
                    cv::imwrite("received_image.jpeg", mat);
                }
                else
                {
                    LOG_ERROR() << "Failed to decode image.";
                }

                image_buffer.clear();

                image_buffer.insert(image_buffer.end(), buffer.begin() + i + 2, buffer.begin() + read_bytes);
                is_found = true;
            }

        if (!is_found)
        {
            LOG_DEBUG() << "Not Found: " << read_bytes;
            image_buffer.insert(image_buffer.end(), buffer.begin(), buffer.begin() + read_bytes);
        }
    }
}

userver::yaml_config::Schema VideoReceiver::GetStaticConfigSchema()
{
    return userver::yaml_config::MergeSchemas<userver::components::TcpAcceptorBase>(R"(
# yaml
type: object
description: |
  Component for consuming video from esp camera
additionalProperties: false
properties:
  greeting:
    type: string
    description: greeting to send to client
    defaultDescription: hi
)");
}

} // namespace esp_robocraft
