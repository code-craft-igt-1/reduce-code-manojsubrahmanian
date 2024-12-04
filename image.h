#pragma once
#include <cstdint>
#include <memory>
#include <functional>
#include <vector>

class Image {
 public:
    int m_rows;
    int m_columns;
    std::vector<uint8_t> pixels;

    // Constructor
    Image(int rows, int columns) : m_rows(rows), m_columns(columns), pixels(rows * columns) {}

    void processPixels(const std::function<void(int, int)>& processor) {
        for (int x = 0; x < m_rows; x++) {
            for (int y = 0; y < m_columns; y++) {
                processor(x, y);
            }
        }
    }
};
