//
//  HashTable.h
//  hw4
//
//  Created by Ahmet Büyükaksoy on 8.05.2023.
//

#ifndef HashTable_h
#define HashTable_h

#include <iostream>
#include <vector>

template<typename K, typename V>
class HashTable {
public:
    // initSize is 53, I chose max load factor to be 0.7
    HashTable(int initialSize = 53, double maxLoadFactor = 0.85)
        : table(initialSize), maxLoadFactor(maxLoadFactor) {}
    
    void insert(const K& key, const V& value) {
        int index = hash(key,table.size());
        auto& bucket = table[index];
        for (auto& kvp : bucket) {
            if (kvp.first == key) {
                kvp.second = value;
                return;
            }
        }
        bucket.emplace_back(key, value);
        ++count;
        double currentLoadFactor = (double)count / table.size();
        if (currentLoadFactor > maxLoadFactor) {
            rehash();
        }
    }
    
    bool search(const K& key, V& value) const {
        int index = hash(key,table.size());
        const auto& bucket = table[index];
        for (const auto& kvp : bucket) {
            if (kvp.first == key) {
                value = kvp.second;
                return true;
            }
        }
        return false;
    }
    
    void remove(const K& key) {
        int index = hash(key,table.size());
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --count;
                return;
            }
        }
    }
    int getCount(){return count;}
    int getTablesize(){return table.size();}
    
    
private:
    std::vector<std::vector<std::pair<K,V>>> table;
    int count = 0;
    double maxLoadFactor;
    
    size_t hash(const K& key, int tablesize) const {
        // Replace this with your own hash function
        return key.hash() % tablesize;
    }
    
    void rehash() {
        std::vector<std::vector<std::pair<K,V>>> newTable(table.size() * 2 + 1);
        
        for (const auto& bucket : table) {
            for (const auto& kvp : bucket) {
                size_t index = hash(kvp.first,newTable.size());
                newTable[index].push_back(kvp);
            }
        }
        std::swap(table, newTable);
        std::cout << "Rehashed... \nprevious table size : " << newTable.size()
                  << ", new table size : " << table.size()
        << " current unique item count " << count
                  << ", current load factor : " << static_cast<double>(count) / table.size()
                  << std::endl;
    }
};





#endif /* HashTable_h */
