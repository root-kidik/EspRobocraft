#include <userver/components/component_list.hpp>
#include <userver/logging/log.hpp>
#include <userver/yaml_config/merge_schemas.hpp>

#include <arpa/inet.h>
#include <netinet/in.h>

#include <infrastructure/VideoReceiver.hpp>

namespace esp_robocraft
{

VideoReceiver::VideoReceiver(const userver::components::ComponentConfig&  config,
                             const userver::components::ComponentContext& context) :
ComponentBase{config, context},
_jpeg_buffer{_video_writer},
_socket{userver::engine::io::AddrDomain::kInet, userver::engine::io::SocketType::kDgram}
{
    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));

    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(config["port"].As<std::uint32_t>());
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    _socket.Bind(userver::engine::io::Sockaddr{&addr});

    _background_task_storage.AsyncDetach("recv frame chunk",
                                         [this]()
                                         {
                                             std::array<std::uint8_t, 1024> buffer;

                                             while (!userver::engine::current_task::ShouldCancel())
                                             {
                                                 const auto read_bytes = _socket.ReadSome(buffer.data(), buffer.size(), {});

                                                 _jpeg_buffer.add(buffer, read_bytes);
                                             }
                                         });
}

userver::yaml_config::Schema VideoReceiver::GetStaticConfigSchema()
{
    return userver::yaml_config::MergeSchemas<userver::components::ComponentBase>(R"(
# yaml
type: object
description: |
  Component for consuming video from esp camera
additionalProperties: false
properties:
  port:
    type: number
    description: porn on which udp socket listening
    defaultDescription: 8019
)");
}

} // namespace esp_robocraft
