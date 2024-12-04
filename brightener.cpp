#include "./brightener.h"

ImageBrightener::ImageBrightener(std::shared_ptr<Image> inputImage): m_inputImage(inputImage) {
}

int ImageBrightener::BrightenWholeImage() {
    int attenuatedPixelCount = 0;
    m_inputImage->processPixels([&](int x, int y) {
        int pixelIndex = x * m_inputImage->m_columns + y;
        if (m_inputImage->pixels[pixelIndex] > (255 - 25)) {
            ++attenuatedPixelCount;
            m_inputImage->pixels[pixelIndex] = 255;
        } else {
            m_inputImage->pixels[pixelIndex] += 25;
        }
    });
    return attenuatedPixelCount;
}

bool ImageBrightener::AddBrighteningImage(std::shared_ptr<Image> imageToAdd, int& attenuatedCount) {
    if (imageToAdd->m_rows != m_inputImage->m_rows || imageToAdd->m_columns != m_inputImage->m_columns) {
        return false;
    }
    attenuatedCount = 0;
    m_inputImage->processPixels([&](int x, int y) {
        int pixelIndex = x * m_inputImage->m_columns + y;
        if (static_cast<int>(m_inputImage->pixels[pixelIndex]) + imageToAdd->pixels[pixelIndex] > 255) {
            ++attenuatedCount;
            m_inputImage->pixels[pixelIndex] = 255;
        } else {
            imageToAdd->pixels[pixelIndex] += m_inputImage->pixels[pixelIndex];
        }
    });
    return true;
}
