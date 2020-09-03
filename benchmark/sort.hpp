#include <vector>
#include <algorithm>

namespace sort
{
    template <typename T>
    void quicksort(T array[], std::size_t begin, std::size_t end);
    template <typename T>
    std::size_t partition(T array[], std::size_t begin, std::size_t end);
    template <typename T>
    void tripleSort(T &low, T &mid, T &high);

    template <typename T>
    void mergesort(T array[], std::size_t begin, std::size_t end);
    template <typename T>
    void topDownMergesort(T array[], T temp_array[],
        std::size_t begin, std::size_t end);
    template <typename T>
    void merge(T array[], T temp_array[],
        std::size_t begin, std::size_t mid, std::size_t end);

    template <typename T>
    void heapsort(T array[], std::size_t begin, std::size_t end);
    template <typename T>
    void buildMaxHeap(T array[], std::size_t begin, std::size_t end);
    template <typename T>
    void maxHeapify(T array[], std::size_t node, std::size_t end);


    template <typename T>
    void tripleSort(T &low, T &mid, T &high)
    {
        if (low > high)
            std::swap(low, high);
        if (low > mid)
            std::swap(low, mid);
        if (mid > high)
            std::swap(mid, high);
    }

    template <typename T>
    std::size_t partition(T array[], std::size_t begin, std::size_t end)
    {
        tripleSort(array[begin], array[(begin + end) / 2], array[end]); // Decreasing the chance of worst-case behavior
        T pivot = array[(begin + end) / 2];
        std::size_t i = begin - 1, j = end + 1;

        // Hoare partition scheme
        while (true)
        {
            do
            {
                ++i;
            } while (array[i] < pivot);
            do
            {
                --j;
            } while (array[j] > pivot);

            if (i >= j)
                return j;
            std::swap(array[i], array[j]);
        }
    }

    template <typename T>
    void quicksort(T array[], std::size_t begin, std::size_t end)
    {
        if (end > begin)
        {
            std::size_t p = partition(array, begin, end);
            quicksort(array, begin, p);
            quicksort(array, p + 1, end);
        }
    }


    template <typename T>
    void mergesort(T array[], std::size_t begin, std::size_t end)
    {
        std::vector<T> v(end - begin + 1);
        topDownMergesort(array, v.data(), begin, end);
    }

    template <typename T>
    void topDownMergesort(T array[], T temp_array[],
        std::size_t begin, std::size_t end)
    {
        if (end - begin > 1)
        {
            std::size_t mid = (begin + end) / 2;
            topDownMergesort(array, temp_array, begin, mid);
            topDownMergesort(array, temp_array, mid + 1, end);
            merge(array, temp_array, begin, mid, end);
        }
    }

    template <typename T>
    void merge(T array[], T temp_array[],
        std::size_t begin, std::size_t mid, std::size_t end)
    {
        std::size_t i = begin, j = mid + 1, k = begin;

        while (i <= mid && j <= end)
        {
            if (array[i] <= array[j])
                temp_array[k++] = array[i++];
            else
                temp_array[k++] = array[j++];
        }
        while (i <= mid)
            temp_array[k++] = array[i++];
        while (j <= end)
            temp_array[k++] = array[j++];
        
        for (i = begin; i <= end; ++i)
            array[i] = temp_array[i];
    }


    template <typename T>
    void buildMaxHeap(T array[], std::size_t begin, std::size_t end)
    {
        for (std::size_t i = end / 2; i > begin; --i)
            maxHeapify(array, i, end);
        maxHeapify(array, begin, end);
    }

    template <typename T>
    void maxHeapify(T array[], std::size_t node, std::size_t end)
    {
        std::size_t max = node, left = 2 * node, right = 2 * node + 1;

        if (left <= end && array[left] > array[max])
            max = left;
        if (right <= end && array[right] > array[max])
            max = right;

        if (max != node)
        {
            std::swap(array[node], array[max]);
            maxHeapify(array, max, end);
        }
    }

    template <typename T>
    void heapsort(T array[], std::size_t begin, std::size_t end)
    {
        buildMaxHeap(array, begin, end);

        for (std::size_t i = end; i > begin; --i)
        {
            std::swap(array[begin], array[i]);
            maxHeapify(array, begin, i - 1);
        }
    }

} // namespace sort
