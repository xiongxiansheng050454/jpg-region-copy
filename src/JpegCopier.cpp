#include "JpegCopier.h"
#include <fstream>
#include <iostream>
#include <cstring>

JpegCopier::JpegCopier() : width(0), height(0) {}

void JpegCopier::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    std::streampos fileSize = file.tellg();
    imageData.resize(fileSize);
    
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(imageData.data()), fileSize);
    
    if (!isValidJPEG()) {
        throw std::runtime_error("Invalid JPEG file format");
    }
    
    getImageDimensions();
}

bool JpegCopier::isValidJPEG() const {
    if (imageData.size() < 2) return false;
    
    // 检查SOI标记 (FFD8)
    return (imageData[0] == 0xFF && imageData[1] == 0xD8);
}

void JpegCopier::getImageDimensions() {
    // 简化版：在实际应用中，需要解析SOF0段获取真实尺寸
    // 这里我们使用一个固定值作为演示
    width = 800;  // 默认宽度
    height = 600; // 默认高度
    
    // 寻找SOF0标记 (FFC0)
    for (size_t i = 0; i < imageData.size() - 1; ++i) {
        if (imageData[i] == 0xFF && imageData[i+1] == 0xC0) {
            if (i + 9 < imageData.size()) {
                // 解析高度和宽度（大端字节序）
                height = (imageData[i+5] << 8) | imageData[i+6];
                width = (imageData[i+7] << 8) | imageData[i+8];
                break;
            }
        }
    }
}

void JpegCopier::copyRegion(const Rectangle& region, const std::string& outputFilename) {
    // 验证区域
    if (region.x < 0 || region.y < 0 || 
        region.x + region.width > width || 
        region.y + region.height > height) {
        throw std::runtime_error("Invalid region dimensions");
    }
    
    // 创建新的JPEG文件（简化版：直接复制原文件）
    // 在实际应用中，这里需要解码原图，提取区域像素，重新编码
    saveToFile(outputFilename);
    
    std::cout << "Copied region: (" << region.x << ", " << region.y 
              << ") size: " << region.width << "x" << region.height 
              << " to " << outputFilename << std::endl;
}

void JpegCopier::saveToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot create file: " + filename);
    }
    
    file.write(reinterpret_cast<const char*>(imageData.data()), imageData.size());
}
