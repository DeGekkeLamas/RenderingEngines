# Rendering engines
This project is a small rendering engine, made as a school project for Rendering Engines. 

## How to use
This is a C++ project and can be opened using an IDE for C++, such as CLion for example. From here you can run the project to use it. 

## Testrunner
The [TestRunner branch of this repository](https://github.com/DeGekkeLamas/RenderingEngines/tree/TestRunner) contains a modified version of the engine, designed for running tests back to back. In order to use it, modify the code in the `main()` function to fit your specific need. Examples of usage include:

Example code to test performance of every implementation for boid quantities 0 through 1000, with a step size of 100:
```cs
int main() {
    constexpr int maxExportSize = 500;
    constexpr int sectioningDepth = 3;

    // Alter this with code or replace it for your specific test sequences
    for (int i = 0; i < 1001; i+=100) { // Different boid quantities
        for (int j = 0; j < 4; j++) { // Different implementations
            mainFunc(static_cast<BoidType>(j), i, maxExportSize, sectioningDepth);
        }
    }
    return 0;
}
```

Example code to test performance of the implementation using spacial partitioning, for sectioning depths 0 through 10, with a set quantity of 1000 boids:
```cs
int main() {
    constexpr int maxExportSize = 500;
    constexpr int numBoids = 1000;

    // Alter this with code or replace it for your specific test sequences
    for (int i = 0; i < 11; i++) { // Different depths
        mainFunc(IterativeSectioning, numBoids, maxExportSize, i);
    }
    return 0;
}
```
