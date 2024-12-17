#include <iostream>
#include <cmath>
#include "player.cpp"
#include "deck.cpp"
#include "dealer.cpp"
#include "GameManager.cpp"

/**
 * Calculate the average of a vector of floats
 * @returns The average of all the elements of vector v
 */
double average(const std::vector<float> v)
{
    // Find sum of array element
    double sum = 0;
    sum += std::accumulate(v.begin(), v.end(), 0);

    return sum / v.size();
}

/**
 * Calculate the standarddeviation of a vector and its average value
 * @returns standard deviation of vector v
 */
double stdev(std::vector<float> v, const double avg)
{
    double x;
    double sum = 0;
    for (std::vector<float>::iterator it = v.begin(); it != v.end(); ++it) {
        x = *it - avg;
        sum += pow(x, 2);
    }

    return sqrt(sum / v.size());
}

double Median(std::vector<float> v)
{
    int n = v.size();
    // Sort the vector
    sort(v.begin(), v.end());

    // Check if the number of elements is odd
    if (n % 2 != 0)
        return (double)v[n / 2];

    // If the number of elements is even, return the average
    // of the two middle elements
    return (double)(v[(n - 1) / 2] + v[n / 2]) / 2.0;
}