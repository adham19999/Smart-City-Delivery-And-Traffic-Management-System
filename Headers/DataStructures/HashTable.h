#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <functional>
using namespace std;

// Custom hash table using separate chaining for collision resolution
// Supports int and string keys out of the box via built-in hash functions
template<typename K, typename V>
class HashTable
{
private:
    vector<list<pair<K, V>>> table;
    int capacity;
    int count;

    int hashFunc(const K& key) const
    {
        return (int)(hash<K>{}(key) % capacity);
    }

public:
    HashTable(int cap = 16) : capacity(cap), count(0)
    {
        table.resize(capacity);
    }

    ~HashTable() = default;

    void insert(const K& key, const V& value)
    {
        int idx = hashFunc(key);
        for (auto& pair : table[idx])
        {
            if (pair.first == key)
            {
                pair.second = value;
                return;
            }
        }
        table[idx].push_back({key, value});
        count++;

        if (count > capacity * 0.75)
            rehash();
    }

    V* search(const K& key)
    {
        int idx = hashFunc(key);
        for (auto& pair : table[idx])
        {
            if (pair.first == key)
                return &pair.second;
        }
        return nullptr;
    }

    const V* search(const K& key) const
    {
        int idx = hashFunc(key);
        for (const auto& pair : table[idx])
        {
            if (pair.first == key)
                return &pair.second;
        }
        return nullptr;
    }

    bool remove(const K& key)
    {
        int idx = hashFunc(key);
        auto& bucket = table[idx];
        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (it->first == key)
            {
                bucket.erase(it);
                count--;
                return true;
            }
        }
        return false;
    }

    bool contains(const K& key) const
    {
        return search(key) != nullptr;
    }

    int size() const { return count; }
    bool isEmpty() const { return count == 0; }

    vector<K> getAllKeys() const
    {
        vector<K> keys;
        for (const auto& bucket : table)
            for (const auto& pair : bucket)
                keys.push_back(pair.first);
        return keys;
    }

    vector<V> getAllValues() const
    {
        vector<V> values;
        for (const auto& bucket : table)
            for (const auto& pair : bucket)
                values.push_back(pair.second);
        return values;
    }

    void clear()
    {
        for (auto& bucket : table)
            bucket.clear();
        count = 0;
    }

    void display() const
    {
        cout << "\n=== Hash Table (capacity=" << capacity << ", size=" << count << ") ===\n";
        for (int i = 0; i < capacity; i++)
        {
            if (!table[i].empty())
            {
                cout << "  [" << i << "]: ";
                for (const auto& pair : table[i])
                    cout << "(" << pair.first << ") -> ";
                cout << "NULL\n";
            }
        }
    }

private:
    void rehash()
    {
        int newCap = capacity * 2;
        vector<list<pair<K, V>>> newTable(newCap);

        for (const auto& bucket : table)
        {
            for (const auto& pair : bucket)
            {
                int idx = (int)(hash<K>{}(pair.first) % newCap);
                newTable[idx].push_back(pair);
            }
        }

        table = move(newTable);
        capacity = newCap;
    }
};

#endif // HASHTABLE_H
