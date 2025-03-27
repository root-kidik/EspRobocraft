#include <userver/logging/log.hpp>
#include <userver/yaml_config/merge_schemas.hpp>

#include <infrastructure/VideoReceiver.hpp>

namespace esp_robocraft
{

VideoReceiver::VideoReceiver(const userver::components::ComponentConfig&  config,
                             const userver::components::ComponentContext& context) :
TcpAcceptorBase{config, context},
_jpeg_buffer{_video_writer}
{
}

void VideoReceiver::ProcessSocket(userver::engine::io::Socket&& sock)
{
    std::array<std::uint8_t, 1024> buffer;

    while (!userver::engine::current_task::ShouldCancel())
    {
        const auto read_bytes = sock.ReadAll(buffer.data(), buffer.size(), {});

        _jpeg_buffer.add(buffer, read_bytes);
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
