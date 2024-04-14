#pragma once 

enum AngularDirection {
    ShortestPath,
    LongestPath
};

float getPath(float target, float actual, AngularDirection direction);