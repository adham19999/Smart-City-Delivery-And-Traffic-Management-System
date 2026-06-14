#include "../../Headers/Algorithms/Sorting.h"
#include <algorithm>

// ========== COMPARE HELPER ==========

bool Sorting::compare(const Delivery& a, const Delivery& b, const string& criterion)
{
    if (criterion == "deadline")
        return a.deadline < b.deadline;
    if (criterion == "priority")
        return a.priority > b.priority;  // higher priority first
    if (criterion == "weight")
        return a.weight < b.weight;
    if (criterion == "id")
        return a.id < b.id;
    return a.deadline < b.deadline;
}

// ========== MERGE SORT ==========

void Sorting::mergeSort(vector<Delivery>& deliveries, const string& criterion)
{
    if (deliveries.size() <= 1)
        return;

    cout << "MergeSort: Sorting " << deliveries.size() << " deliveries by " << criterion << "\n";
    mergeSortHelper(deliveries, 0, (int)deliveries.size() - 1, criterion);
}

void Sorting::mergeSortHelper(vector<Delivery>& arr, int left, int right, const string& criterion)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, left, mid, criterion);
    mergeSortHelper(arr, mid + 1, right, criterion);
    merge(arr, left, mid, right, criterion);
}

void Sorting::merge(vector<Delivery>& arr, int left, int mid, int right, const string& criterion)
{
    vector<Delivery> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<Delivery> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < (int)leftArr.size() && j < (int)rightArr.size())
    {
        if (compare(leftArr[i], rightArr[j], criterion))
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }

    while (i < (int)leftArr.size())
        arr[k++] = leftArr[i++];
    while (j < (int)rightArr.size())
        arr[k++] = rightArr[j++];
}

void Sorting::mergeSortVehicleId(vector<int>& ids)
{
    if (ids.size() <= 1)
        return;
    sort(ids.begin(), ids.end());
}

// ========== QUICK SORT ==========

void Sorting::quickSort(vector<Delivery>& deliveries, int low, int high, const string& criterion)
{
    if (low < high)
    {
        int pivot = partition(deliveries, low, high, criterion);
        quickSort(deliveries, low, pivot - 1, criterion);
        quickSort(deliveries, pivot + 1, high, criterion);
    }
}

int Sorting::partition(vector<Delivery>& arr, int low, int high, const string& criterion)
{
    Delivery pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (compare(arr[j], pivot, criterion))
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// ========== DISPLAY ==========

void Sorting::displaySorted(const vector<Delivery>& deliveries, const string& label)
{
    cout << "\n=== " << label << " (" << deliveries.size() << " items) ===\n";
    cout << "ID | Customer | Deadline | Priority | Weight | Status\n";
    cout << "---|----------|----------|----------|--------|-------\n";
    for (const auto& d : deliveries)
    {
        cout << d.id << "  | " << d.customerId << "        | "
             << d.deadline << "       | " << d.priority << "        | "
             << d.weight << "    | " << d.status << "\n";
    }
}
