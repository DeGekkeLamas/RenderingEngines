#include "CSVTools.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "Boids/BoidObject.hpp"

void CSVTools::writeCSV(const std::vector<float>& frameTimes, const std::string& name)
{
    // Timestamp
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    // Filename
    std::stringstream filename;
    filename << "../DataExports/frameTimes_boids_" << name
        << "_" << std::put_time(localTime, "%Y%m%d_%H%M%S") << ".csv";
    const std::string filenameString =  std::string{filename.str()};

    std::ofstream file(filenameString);

    if (!file) {
        std::cerr << "Error: Could not open " << filenameString << " for writing.\n";
        return;
    }

    // Write header
    file << "Frame;DeltaTime;FPS\n";

    // Write average values
    float averageDeltaTime = 0;
    for (int i = 0; i < frameTimes.size(); i++) {
        averageDeltaTime += frameTimes[i];
    }
    averageDeltaTime /= frameTimes.size();
    file << "Average" << ";"
         << averageDeltaTime << ";"
         << static_cast<int>(std::round(1.0f / averageDeltaTime)) << "\n";

    // Write frametimes
    for (int i = 0; i < frameTimes.size(); i++)
    {
        const float deltaTime = frameTimes[i];
        const int fps = (deltaTime > 0.0f) ? static_cast<int>(std::round(1.0f / deltaTime)) : 0;

        file << i << ";"
             << deltaTime << ";"
             << fps << "\n";
    }

    std::cout << "Saved " << frameTimes.size() << " frames to " << filenameString << "\n";
}
