#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/reduce.h>
#include <thrust/iterator/constant_iterator.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>



double calculateVariance(thrust::device_vector<double>& differences, double mean) {
    // Use thrust::constant_iterator to dynamically supply the mean value
    auto mean_iterator = thrust::make_constant_iterator(mean);

    // Vector to store the squared differences
    thrust::device_vector<double> squaredDifferences(differences.size());

    // Calculate (difference - mean)^2 for each element using constant_iterator
    thrust::transform(differences.begin(), differences.end(), mean_iterator, squaredDifferences.begin(),
                      [] __host__ __device__ (const double& x, const double& mean) {
                          return (x - mean) * (x - mean);
                      });

    // Sum the squared differences
    double sumOfSquares = thrust::reduce(squaredDifferences.begin(), squaredDifferences.end(), 0.0, thrust::plus<double>());

    // Calculate variance
    double variance = sumOfSquares / differences.size();

    return variance;
}

int main() {
    // Host vectors to store the stock prices of Apple and Microsoft
    thrust::host_vector<double> host_AAPL;
    thrust::host_vector<double> host_MSFT;

    std::ifstream file("stocks.txt");
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string price_AAPL, price_MSFT;

        std::getline(ss, price_AAPL, ',');
        std::getline(ss, price_MSFT, ',');

        host_AAPL.push_back(std::stod(price_AAPL));
        host_MSFT.push_back(std::stod(price_MSFT));
    }
    file.close();

    // Transfer prices to the GPU
    thrust::device_vector<double> device_AAPL(host_AAPL);
    thrust::device_vector<double> device_MSFT(host_MSFT);
    thrust::device_vector<double> differences(device_AAPL.size());

    // Calculate the difference between Apple and Microsoft stock prices
    thrust::transform(device_AAPL.begin(), device_AAPL.end(), device_MSFT.begin(), differences.begin(), thrust::minus<double>());

    // Calculate the mean of the differences
    double total_difference = thrust::reduce(differences.begin(), differences.end(), 0.0, thrust::plus<double>());
    double mean_difference = total_difference / differences.size();

    // Calculate the variance using the function with constant_iterator
    double variance = calculateVariance(differences, mean_difference);

    std::cout << "Variância das diferenças entre os preços das ações: " << variance << std::endl;

    return 0;
}
