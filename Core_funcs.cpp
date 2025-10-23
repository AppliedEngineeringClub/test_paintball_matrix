#include "Core.hpp"        // for your struct definition
#include <iostream>        // for std::cout, std::cerr
#include <stdexcept>       // for std::runtime_error
#include <cstdlib>         // for std::system()
#include <fstream>         // for std::ifstream
#include <cstddef>         // for std::size_t
#include <cstdint>         // for uint8_t

// Constructor
Core::Core(std::size_t m_, std::size_t n_)
  : m(m_), n(n_), matrix()
{}

void Core::imageProcessor() {
    // --- Step 1: Get dimensions from Python via external script ---
    {
        int ret = std::system("python3 get_dimensions.py > pythonoutput.txt");
        if (ret != 0) {
            throw std::runtime_error("Failed to run get_dimensions.py");
        }

        std::ifstream in("pythonoutput.txt");
        if (!in) {
            throw std::runtime_error("Cannot open pythonoutput.txt for reading dimensions");
        }
        long w, h;
        in >> w >> h;
        in.close();

        if (w <= 0 || h <= 0) {
            throw std::runtime_error("Invalid dimensions read from pythonoutput.txt");
        }

        origWidth  = static_cast<std::size_t>(w);
        origHeight = static_cast<std::size_t>(h);
    }

    // --- Step 2: Allocate the matrix buffer based on these dimensions ---
    const int CHANNELS = 3;  // R, G, B
    matrix.clear();
    matrix.resize(static_cast<std::size_t>(CHANNELS) * origHeight * origWidth);

    // --- Step 3: Get the full pixel data from Python via another script ---
    {
        int ret2 = std::system("python3 get_matrix_data.py > pythonoutput.bin");
        if (ret2 != 0) {
            throw std::runtime_error("Failed to run get_matrix_data.py");
        }

        std::ifstream in2("pythonoutput.bin", std::ios::binary);
        if (!in2) {
            throw std::runtime_error("Cannot open pythonoutput.bin for reading matrix data");
        }
//[ [[225,244,232].[234,234,234],[234,234,234]],
//      [[r,g,b]    ,[r,g,b],       [r,g,b]]      ]
        in2.read(reinterpret_cast<char*>(matrix.data()),
                 matrix.size() * sizeof(uint8_t));
        if (!in2) {
            throw std::runtime_error("Error reading matrix data from pythonoutput.bin");
        }
        in2.close();
    }

    // --- Debug: Print first few values to inspect content ---
    {
        std::size_t maxToPrint = std::min(matrix.size(), static_cast<std::size_t>(10));
        std::cout << "Debug: first " << maxToPrint << " values of matrix: ";
        for (std::size_t i = 0; i < maxToPrint; ++i) {
            std::cout << static_cast<int>(matrix[i]) << " ";
        }
        std::cout << "\n";
    }

    // --- Step 4: Clear the content of the intermediary files for next time ---
    {
        // Opening in truncation mode clears the existing contents (if any)
        std::ofstream ofs1("pythonoutput.txt", std::ios::out | std::ios::trunc);
        ofs1.close();
        std::ofstream ofs2("pythonoutput.bin", std::ios::out | std::ios::trunc | std::ios::binary);
        ofs2.close();
    }

    // --- Final debug print of size info ---
    std::cout << "Core::imageProcessor(): matrix loaded ("
              << CHANNELS << " × " << origHeight << " × " << origWidth << ")\n";
}


// mapToNearestColor implementation stub
void Core::mapToNearestColor(const std::vector<std::array<uint8_t,3>>& palette) {
    // TODO: implement nearest-color mapping
}

// reduceBlocks implementation stub
Core Core::reduceBlocks(std::size_t blockM, std::size_t blockN) const {
    // TODO: implement block reduction logic
    return Core(0,0);
}

// matrixToBalls implementation stub
void Core::matrixToBalls() {
    // TODO: implement matrix-to-balls logic
}
