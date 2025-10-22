// Core.hpp
#ifndef CORE_HPP
#define CORE_HPP

#include <vector>
#include <cstddef>  // for size_t
#include <cstdint>  // for uint8_t

struct Core {
    std::size_t m;  // number of columns (width)
    std::size_t n;  // number of rows (height)

    // 3D data: channels × n × m
    // flattened into a 1D vector. Each entry is one channel value (0-255).
    std::vector<uint8_t> matrix;
     // Constructor
   explicit Core(std::size_t m_ = 0, std::size_t n_ = 0);

    // imageProcessor will allocate/populate matrix to size (3 * n * m) for 3 channels.
    void imageProcessor();

    void mapToNearestColor(const std::vector<std::array<uint8_t,3>>& palette);

    Core reduceBlocks(std::size_t blockM, std::size_t blockN) const;

    void matrixToBalls();
};

#endif // CORE_HPP
