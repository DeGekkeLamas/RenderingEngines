#pragma once
#include <string>
#include <vector>


static class CSVTools {
    public:
    static void writeCSV(const std::vector<float>& frameTimes, const std::string& name);
};
