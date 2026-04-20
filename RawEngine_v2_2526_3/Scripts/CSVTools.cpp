#include "CSVTools.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "Boids/BoidObject.hpp"

void CSVTools::writeCSV(const std::vector<float>& frameTimes)
{
    std::string filename = "../frameTimes_boids_";
    filename += std::to_string(BoidObject::boids.size());
    filename += ".csv";

    std::ofstream file(filename);

    if (!file) {
        std::cerr << "Error: Could not open " << filename << " for writing.\n";
        return;
    }

    // Write header
    file << "Frame;DeltaTime;FPS\n";

    // Write frametimes
    for (int i = 0; i < frameTimes.size(); i++)
    {
        const float deltaTime = frameTimes[i];
        const int fps = (deltaTime > 0.0f) ? static_cast<int>(std::round(1.0f / deltaTime)) : 0;

        file << i << ";"
             << deltaTime << ";"
             << fps << "\n";
    }

    std::cout << "Saved " << frameTimes.size() << " frames to " << filename << "\n";
}
