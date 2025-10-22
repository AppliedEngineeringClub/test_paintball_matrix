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

// imageProcessor implementation
void Core::imageProcessor() {
    // --- Step 1: Get dimensions from Python via external script ---
    {
        // Run the Python script "get_dimensions.py" and redirect its output
        int ret = std::system("python3 get_dimensions.py > pythonoutput.txt");
        // Check return code: 0 typically means success for system(...)
        if (ret != 0) {
            throw std::runtime_error("Failed to run get_dimensions.py");
        }

        // Open the output file that the Python script wrote
        std::ifstream in("pythonoutput.txt");
        if (!in) {
            throw std::runtime_error("Cannot open pythonoutput.txt for reading dimensions");
        }

        long w, h;
        // Read width and height (assuming the script writes them as two numbers)
        in >> w >> h;
        in.close();

        // Validate the values we got
        if (w <= 0 || h <= 0) {
            throw std::runtime_error("Invalid dimensions read from pythonoutput.txt");
        }

        // Set the struct’s dimension fields
        origWidth  = static_cast<std::size_t>(w);
        origHeight = static_cast<std::size_t>(h);
    }

    // --- Step 2: Allocate the matrix buffer based on these dimensions ---
    const int CHANNELS = 3;  // number of color channels (R, G, B)
    matrix.clear();
    matrix.resize(static_cast<std::size_t>(CHANNELS) * origHeight * origWidth);
    // Note: matrix is flattened as channel major, then row, then column.

    // --- Step 3: Get the full pixel data from Python via another script ---
    {
        // Run the Python script "get_matrix_data.py" and redirect its output (binary) to a file
        int ret2 = std::system("python3 get_matrix_data.py > pythonoutput.bin");
        if (ret2 != 0) {
            throw std::runtime_error("Failed to run get_matrix_data.py");
        }

        // Open the binary file written by the Python script
        std::ifstream in2("pythonoutput.bin", std::ios::binary);
        if (!in2) {
            throw std::runtime_error("Cannot open pythonoutput.bin for reading matrix data");
        }

        // Read byte-by-byte into our matrix buffer
        in2.read(reinterpret_cast<char*>(matrix.data()), matrix.size() * sizeof(uint8_t));
        if (!in2) {
            throw std::runtime_error("Error reading matrix data from pythonoutput.bin");
        }
        in2.close();
    }

    // --- Final step: Print debug info about the outcome ---
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
