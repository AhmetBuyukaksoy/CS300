//
//  main.cpp
//  hw5
//
//  Created by Ahmet Büyükaksoy on 18.05.2023.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include<chrono>
#include<vector>
#include <algorithm>

using namespace std;


struct Contact{
    string firstname, lastname, phonenum, address;
    Contact(string fn = "", string ln = "", string no = "", string add= ""){
        firstname = fn;
        lastname = ln;
        phonenum = no;
        address = add;
        for (auto & c: firstname) c = toupper(c);
        for (auto & c: lastname) c = toupper(c);
        
    }
    bool operator<(const Contact& other) const {
        // Compare first names alphabetically
        
        if (firstname < other.firstname) {
            return true;
        } else if (firstname > other.firstname) {
            return false;
        }
        
        // First names are equal, compare last names alphabetically
        return lastname < other.lastname;
    }
    bool operator>(const Contact& other) const{
        // Compare first names alphabetically
        if (firstname < other.firstname) {
            return false;
        } else if (firstname > other.firstname) {
            return true;
        }
        
        // First names are equal, compare last names alphabetically
        return (lastname > other.lastname);
    }
    bool operator==(const Contact& rhs) const{
        return (firstname==rhs.firstname && lastname==rhs.lastname);
    }
    
    void operator=(const Contact& rhs) {
        firstname = rhs.firstname;
        lastname = rhs.lastname;
        phonenum = rhs.phonenum;
        address = rhs.address;
    }
    bool operator>=(const Contact& other) const{
        return (*this > other || *this == other);
    }
    bool operator<=(const Contact& other) const{
        return (*this < other || *this == other);
    }
    string getFullName() const{
        return firstname + " " + lastname;
    }
    bool checkPrefix(string prefix) const{
        return getFullName().substr(0, prefix.size()) == prefix;
    }
    
};
ostream& operator<<(ostream& os, const Contact& contact) {
    os << contact.firstname << " " << contact.lastname << " ";
    os << contact.phonenum << " ";
  os << contact.address ;
  return os;
}

void readIntoVector(vector<Contact> & v, string filename){
    ifstream inputFile(filename.c_str());
    string line;
         if (inputFile.is_open()) {
          //   cout << "Loading the phonebook into a vector." << endl;

             while (getline(inputFile, line)) {
                     
                 stringstream ss(line);
                 vector<string> data;
                 string temp;
                 while (ss >> temp) {
                     data.push_back(temp);
                     }
                 for (auto & c: data[0]) c = toupper(c);
                 for (auto & c: data[1]) c = toupper(c);

                 v.push_back(Contact(data[0],data[1],data[2],data[3]));
                 

             }
             inputFile.close();
            
         } else {
             cout << "Error opening file!" << endl;
         }
    
}

template <typename T>
int partition(vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

template <typename T>
void quickSort(vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
               quickSort(arr, low, pi - 1);
               quickSort(arr, pi + 1, high);
           }
       }
// Quick Sort Ends


// Quick Sort Ends

// Insertion Sort Algorithm
template <typename T>
void insertionSort(vector<T>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        T key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        arr[j + 1] = key;
    }
}
// Insertion Sort Ends

// Merge Sort Algorithm
template <typename T>
void merge(vector<T>& arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    vector<T> L(n1), R(n2);
    
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    i = 0;
    j = 0;
    k = l;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void mergeSort(vector<T>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
// Merge Sort Ends

// Heap Sort Algorithm
template <typename T>
void heapify(vector<T>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    
    if (l < n && arr[l] > arr[largest])
        largest = l;
    
    if (r < n && arr[r] > arr[largest])
        largest = r;
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

template <typename T>
void heapSort(vector<T>& arr) {
    int n = arr.size();
    
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
// Heap Sort Ends

// Linear search with partial matching
void linearSearch(const vector<Contact>& contacts, const string& query) {
    bool found = false;
    for (const Contact& contact : contacts) {
        if (contact.getFullName() == query || contact.checkPrefix(query)) {
            cout << contact << endl;
            found = true;
        }
    }
    if (!found) {
        cout << query << " does NOT exist in the dataset." << endl;
    }
}

// Binary search with partial matching
void binarySearch(const vector<Contact>& contacts, const string& query) {
    int left = 0;
    int right = contacts.size() - 1;
    bool found = false;

    while (left <= right) {
        int mid = (left + right) / 2;
        const Contact& contact = contacts[mid];
        string fullName = contact.getFullName();

        if (contact.checkPrefix(query)) {
            // if partial of full match is found check the left and right sides of the it
            // to find all matches
            int leftsrc = mid - 1;
            int rightsrc = mid + 1;
            // matches in the left should be printed in reverse
            while(contacts[leftsrc].checkPrefix(query)){
                   // cout << contacts[leftsrc] << endl;
                    leftsrc--;
                            }
            leftsrc++;
            while(leftsrc != mid){
                cout << contacts[leftsrc] << endl;
                leftsrc++;
            }
            
            
            
            cout << contact << endl;
            
            while(contacts[rightsrc].checkPrefix(query)){
                    cout << contacts[rightsrc] << endl;
                    rightsrc++;
            }
            found = true;
            break;  // Exit the loop after finding the full match
        } else if (fullName < query) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (!found) {
        cout << query << " does NOT exist in the dataset." << endl;
    }
}



int main() {
    
    vector<Contact> unsortedV;
    // vectors to be sorted
    vector<Contact> quickSortV;
    vector<Contact> insertionSortV;
    vector<Contact> mergeSortV;
    vector<Contact> heapSortV;
   

    
    string filename, firstname,lastname,query;
    cout << "Please enter the contact filename: ";
    cin >> filename;
    
    readIntoVector(unsortedV, filename);
    readIntoVector(quickSortV, filename);
    readIntoVector(insertionSortV, filename);
    readIntoVector(mergeSortV, filename);
    readIntoVector(heapSortV, filename);
    
    cout << "Please enter the word to be queried: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    getline(cin, query);

        size_t pos = query.find(' ');

        if (pos != string::npos) {
            firstname = query.substr(0, pos);
            lastname = query.substr(pos + 1);
            query = firstname + " " + lastname;

        } else {
            firstname = query;
        }
    for (auto & c: query) c = toupper(c);
    
    cout << endl;
    cout << "Sorting the vector copies" << endl;
    cout << "======================================" << endl;
    // Quick Sort Algorithm
    
   
    // Quick Sort
    auto start = std::chrono::high_resolution_clock::now();
        quickSort(quickSortV, 0, quickSortV.size() - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto durationQSort = duration_cast<std::chrono::nanoseconds>(stop - start);
        cout << "Quick Sort Time: " << durationQSort.count() << " nanoseconds" << endl;
        
        // Insertion Sort
    start = std::chrono::high_resolution_clock::now();
        insertionSort(insertionSortV);
    stop = std::chrono::high_resolution_clock::now();
    auto durationISort = duration_cast<std::chrono::nanoseconds>(stop - start);
        cout << "Insertion Sort Time: " << durationISort.count() << " nanoseconds" << endl;
        
        // Merge Sort
    start = std::chrono::high_resolution_clock::now();
        mergeSort(mergeSortV, 0, mergeSortV.size() - 1);
    stop = std::chrono::high_resolution_clock::now();
    auto durationMSsort = duration_cast<std::chrono::nanoseconds>(stop - start);
        cout << "Merge Sort Time: " << durationMSsort.count() << " nanoseconds" << endl;
        
        // Heap Sort
    start = std::chrono::high_resolution_clock::now();
        heapSort(heapSortV);
    stop = std::chrono::high_resolution_clock::now();
    auto durationHSort = duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "Heap Sort Time: " << durationHSort.count() << " nanoseconds" << endl << endl;
    
    cout << "Searching for " << query << endl;
    cout << "======================================" << endl;
    // Perform binary search
    start = std::chrono::high_resolution_clock::now();
    binarySearch(insertionSortV, query);
    stop = std::chrono::high_resolution_clock::now();
    auto durationBinSearch = duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "Binary Search Time: "<< durationBinSearch.count() << " Nanoseconds" << endl << endl;
    
    // Perform linear search
    cout << "Search results for Sequential Search:" << endl;
    start = std::chrono::high_resolution_clock::now();
    linearSearch(insertionSortV, query);
    stop = std::chrono::high_resolution_clock::now();
    auto durationLinSearch = duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "Sequential Search Time: "<< durationLinSearch.count() << " Nanoseconds" << endl << endl;
    cout << "SpeedUp between search algorithms" << endl;
    cout << "======================================" << endl;
    double speedup = static_cast<double>(durationLinSearch.count()) / durationBinSearch.count();
    double algSpeedup1 = static_cast<double>(durationISort.count()) / durationQSort.count();
    double algSpeedup2 = static_cast<double>(durationMSsort.count()) / durationQSort.count();
    double algSpeedup3 = static_cast<double>(durationHSort.count()) / durationQSort.count();


    cout << "(Sequential Search / Binary Search) SpeedUp = " << speedup << endl;
    
    cout <<"SpeedUps between Sorting Algorithms " << endl
    << "======================================" << endl
    << "(Insertion Sort/ Quick Sort) SpeedUp = " << algSpeedup1 << endl
    << "(Merge Sort / Quick Sort) SpeedUp = " << algSpeedup2 << endl
    << "(Heap Sort / Quick Sort) SpeedUp = " << algSpeedup3 << endl;
    
   
        
    
    return 0;
}

