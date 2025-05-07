#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cstdlib>

namespace fs = std::filesystem;

const std::string ASCII_CHARS = "@%#*+=-:. ";  // dark to light

char pixelToAscii(int brightness) {
    int index = brightness * (ASCII_CHARS.size() - 1) / 255;
    return ASCII_CHARS[index];
}

void showFrame(const cv::Mat& frame) {
    for (int y = 0; y < frame.rows; ++y) {
        for (int x = 0; x < frame.cols; ++x) {
            uchar pixel = frame.at<uchar>(y, x);
            std::cout << pixelToAscii(pixel);
        }
        std::cout << "\n";
    }
}

int main() {
    std::vector<fs::path> images;

    for (const auto& entry : fs::directory_iterator("frames")) {
        if (entry.path().extension() == ".png") {
            images.push_back(entry.path());
        }
    }

    std::sort(images.begin(), images.end());

    //start sound
    std::system("mpg123 bad_apple.mp3 &");

    // ASCII  
    for (const auto& path : images) {
        cv::Mat img = cv::imread(path.string(), cv::IMREAD_GRAYSCALE);
        if (img.empty()) continue;

        std::cout << "\033[2J\033[H";  // clear screen + cursor to top-left
        showFrame(img);

        std::this_thread::sleep_for(std::chrono::milliseconds(66)); // ~15 fps smth
    }

    return 0;
}
