#include "sort.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <chrono>

std::mt19937_64 random_engine(
    std::chrono::high_resolution_clock::now().time_since_epoch().count());

template <typename T>
void fillRandomly(T array[], std::size_t begin, std::size_t end)
{
    for (std::size_t i = begin; i <= end; ++i)
        array[i] = random_engine();
}

int main()
{
    std::ofstream fout("nlogn.csv");

    auto start = std::chrono::high_resolution_clock::now();
    for (std::size_t i = 10000; i <= 2000000; i += 10000)
    {
        std::vector<long long> v1(i), v2(i), v3(i);
        fillRandomly(v1.data(), 0, i - 1);
        fillRandomly(v2.data(), 0, i - 1);
        fillRandomly(v3.data(), 0, i - 1);

        auto start1 = std::chrono::high_resolution_clock::now();
        sort::quicksort(v1.data(), 0, i - 1);
        auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> runtime1 = end1 - start1;

        auto start2 = std::chrono::high_resolution_clock::now();
        sort::mergesort(v2.data(), 0, i - 1);
        auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> runtime2 = end2 - start2;

        auto start3 = std::chrono::high_resolution_clock::now();
        sort::heapsort(v3.data(), 0, i - 1);
        auto end3 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> runtime3 = end3 - start3;
        
        fout << runtime1.count() * 1000 << ','
             << runtime2.count() * 1000 << ','
             << runtime3.count() * 1000 << ','
             << '\n';
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> runtime = end - start;

    std::cout << "Done!\nRuntime: " << runtime.count() << "s";
    std::cin.sync();
    std::cin.get();
    return 0;
}
