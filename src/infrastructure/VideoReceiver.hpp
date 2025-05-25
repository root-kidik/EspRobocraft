#pragma once

#include <userver/components/tcp_acceptor_base.hpp>
#include <userver/concurrent/background_task_storage.hpp>
#include <userver/engine/io/socket.hpp>

#include <domain/JpegBuffer.hpp>
#include <domain/VideoWriter.hpp>

namespace esp_robocraft
{

class VideoReceiver final : public userver::components::ComponentBase
{
public:
    static constexpr std::string_view kName = "video-receiver";

    VideoReceiver(const userver::components::ComponentConfig& config, const userver::components::ComponentContext& context);

    static userver::yaml_config::Schema GetStaticConfigSchema();

private:
    VideoWriter _video_writer;
    JpegBuffer _jpeg_buffer;
    userver::engine::io::Socket _socket;

    userver::concurrent::BackgroundTaskStorage _background_task_storage;
};

} // namespace esp_robocraft
