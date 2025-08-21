#ifndef JPEG_COPIER_H
#define JPEG_COPIER_H

#include <string>
#include <vector>
#include <stdexcept>

class JpegCopier {
public:
    struct Rectangle {
        int x;
        int y;
        int width;
        int height;
        
        Rectangle(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {}
    };

    // 构造函数
    JpegCopier();
    
    // 从文件加载JPEG图像
    void loadFromFile(const std::string& filename);
    
    // 将图像保存到文件
    void saveToFile(const std::string& filename) const;
    
    // 拷贝指定区域
    void copyRegion(const Rectangle& region, const std::string& outputFilename);
    
    // 获取图像信息
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
private:
    std::vector<unsigned char> imageData;
    int width;
    int height;
    
    // 解析JPEG头信息
    void parseHeader();
    
    // 检查是否为有效的JPEG文件
    bool isValidJPEG() const;
    
    // 获取图像尺寸（简化版）
    void getImageDimensions();
};

#endif // JPEG_COPIER_H
