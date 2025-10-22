#include "Core.hpp"
#include <iostream>
#include <stdexcept>
#include <Python.h>
// Constructor
Core::Core(std::size_t m_, std::size_t n_)
  : m(m_), n(n_), matrix()
{}

// imageProcessor implementation
void Core::imageProcessor() {

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
