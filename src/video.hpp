#pragma once

#include <userver/components/tcp_acceptor_base.hpp>

namespace esp_robocraft
{

class VideoReceiver final : public userver::components::TcpAcceptorBase
{
public:
    static constexpr std::string_view kName = "video-receiver";

    VideoReceiver(const userver::components::ComponentConfig& config, const userver::components::ComponentContext& context);

    void ProcessSocket(userver::engine::io::Socket&& sock) override;

    static userver::yaml_config::Schema GetStaticConfigSchema();
};

} // namespace esp_robocraft
