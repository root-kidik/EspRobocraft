#include <opencv4/opencv2/opencv.hpp>

#include <domain/VideoWriter.hpp>

namespace esp_robocraft
{

void VideoWriter::on_jpeg(const std::vector<std::uint8_t>& jpeg)
{
    if (auto mat = cv::imdecode(jpeg, cv::IMREAD_COLOR); !mat.empty())
        cv::imwrite("image.jpeg", mat);
    else
        std::cerr << "ERRRRRRRRRRRRRRRRRRRRRRRRROOOOOOOOOOOOOOOOOOOOOORRRRRRRRRRRRRRRRRR\n";
}

} // namespace esp_robocraft
