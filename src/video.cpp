#include "video.hpp"
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
    std::string data;
    data.resize(2);

    while (!userver::engine::current_task::ShouldCancel())
    {
        const auto read_bytes = sock.ReadAll(data.data(), 2, {});
        if (read_bytes != 2 || data != "hi")
        {
            sock.Close();
            return;
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
