//
//  main.cpp
//  hw4
//
//  Created by Ahmet Büyükaksoy on 8.05.2023.
//

#include <iostream>
#include "HashTable.h"
#include "BST.h"
#include <fstream>
#include <sstream>
#include<chrono>
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
    bool operator==(const Contact& rhs){
        return (firstname==rhs.firstname && lastname==rhs.lastname);
    }
    void operator=(const Contact& rhs) {
        firstname = rhs.firstname;
        lastname = rhs.lastname;
        phonenum = rhs.phonenum;
        address = rhs.address;
    }
    string getFullName(){
        return firstname + " " + lastname;
    }
    bool checkPrefix(string prefix){
        return getFullName().substr(0, prefix.size()) == prefix;
    }
    int hash() const{
        int sum = 0;
            for (char c : firstname) {
                sum += 10* static_cast<int>(tolower(c));
            }
            for (char c : lastname) {
                sum += 10* static_cast<int>(tolower(c));
            }
            
            return sum;
    }
    
    
};


ostream& operator<<(ostream& os, const Contact& contact) {
    os << contact.firstname << " " << contact.lastname << " ";
    os << contact.phonenum << " ";
  os << contact.address ;
  return os;
}
    bool operator==(const Contact& lhs, const Contact& rhs) {
        return lhs.firstname == rhs.firstname && lhs.lastname == rhs.lastname;
    }

void readIntoBST(string filename, BSTtree<Contact> &contactsBST){
    ifstream inputFile(filename.c_str());
     string line;
         if (inputFile.is_open()) {
             cout << "Loading the phonebook into a BST." << endl;

             while (getline(inputFile, line)) {
                     
                 stringstream ss(line);
                 vector<string> data;
                 string temp;
                 while (ss >> temp) {
                     data.push_back(temp);
                     }
                 for (auto & c: data[0]) c = toupper(c);
                 for (auto & c: data[1]) c = toupper(c);

                 Contact c = Contact(data[0],data[1],data[2],data[3]);
                 contactsBST.insert(c);
                 }
             inputFile.close();
            
         } else {
             cout << "Error opening file!" << endl;
         }
}
void readIntoHashTable (string filename, HashTable<Contact, Contact> & contactsHashTable){
    ifstream inputFile(filename.c_str());
     string line;
         if (inputFile.is_open()) {
             cout << "Loading the phonebook into a hash table." << endl;

             while (getline(inputFile, line)) {
                     
                 stringstream ss(line);
                 vector<string> data;
                 string temp;
                 while (ss >> temp) {
                     data.push_back(temp);
                     }
                 for (auto & c: data[0]) c = toupper(c);
                 for (auto & c: data[1]) c = toupper(c);

                 Contact c = Contact(data[0],data[1],data[2],data[3]);
                 contactsHashTable.insert(c,c);
                 }
             cout << "After preprocessing, the unique contact count is "<< contactsHashTable.getCount() << ". Current load ratio is " << (double)contactsHashTable.getCount() / contactsHashTable.getTablesize() << endl;
             inputFile.close();
             
            
         } else {
             cout << "Error opening file!" << endl;
         }
}
void search_contact(BSTtree<Contact>::Node* root, string query) {
    
    if (root == nullptr) {
        return;
    }
    for (auto & c: query) c = toupper(c);

    // PhoneBook-sample1.txt
    if (root->value.getFullName().find(query) == 0) {
     //   cout << root->value.firstname << " " << root->value.lastname << " " << root->value.phonenum << " " << root->value.address << endl;
        search_contact(root->left, query);
        
        search_contact(root->right, query);
       
        
        return;

    }
    if (query < root->value.getFullName()) {
        search_contact(root->left, query);
    }
    else if ( query == root->value.getFullName()){
       // cout << root->value.firstname << " " << root->value.lastname << " " << root->value.phonenum << " " << root->value.address << endl;
    }
    else {
        search_contact(root->right, query);
    }
    
    
}
void search_contact_with_print(BSTtree<Contact>::Node* root, string query) {
    
    if (root == nullptr) {
        return;
    }
    for (auto & c: query) c = toupper(c);

    // PhoneBook-sample1.txt
    if (root->value.getFullName().find(query) == 0) {
        cout << root->value.firstname << " " << root->value.lastname << " " << root->value.phonenum << " " << root->value.address << endl;
        search_contact(root->left, query);
        
        search_contact(root->right, query);
       
        
        return;

    }
    if (query < root->value.getFullName()) {
        search_contact(root->left, query);
    }
    else if ( query == root->value.getFullName()){
        cout << root->value.firstname << " " << root->value.lastname << " " << root->value.phonenum << " " << root->value.address << endl;
    }
    else {
        search_contact(root->right, query);
    }
    
    
}
int main() {
    
    HashTable<Contact, Contact> contactsHashTable;
    BSTtree<Contact> contactsBST;
    string filename;
    cout << "Please enter the contact filename: ";
    cin >> filename;
    
    
    readIntoBST(filename,contactsBST);
    readIntoHashTable(filename,contactsHashTable);
  //  cout << "debugging " << endl;
    int choice = 0;
    
    while(choice != 4){
        cout << "Choose which action to perform from 1 to 6: " <<
        "\n1 - Search a phonebook contact" <<
        "\n2 - Adding a phonebook contact" <<
        "\n3 - Deleting a phonebook contact" <<
        "\n4 - Press 4 to exit" << endl;
        // search
        cin >> choice;
        cout << endl;
        if(choice == 1)
        {
            string firstname, lastname;
            cout << "Enter name to search for: ";
            cin >> firstname >> lastname;
            cout << endl;
            string search = firstname + " " + lastname;
            for (auto & c: search) c = toupper(c);
            Contact dummyContact(firstname,lastname);
            bool foundinhash = false;
            cout << "Searching for an item in the phonebook (BST) . . ." << endl;
            cout << "Phonebook: Searching for : (" << search << ")" << endl;
            cout << "====================================" << endl;
            int k = 500;
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < k; i++)
            {
                contactsBST.Search(dummyContact);
                
            }
            if(dummyContact.phonenum != "")
            {cout << dummyContact << endl;}
            else{cout << "Name not found!" << endl;}
            Contact dummyContact2(firstname,lastname);
            Contact dummyContact3;
            auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);
            cout << "\nBST Search Time: " << BSTTime.count() / k << "\n\n";
            start = std::chrono::high_resolution_clock::now();
            cout << "Searching for an item in the phonebook (HashTable) . . ." << endl;
            cout << "Phonebook: Searching for : (" << search << ")" << endl;
            cout << "====================================" << endl;
            for (int i = 0; i < k; i++)
            {
                foundinhash = contactsHashTable.search(dummyContact2, dummyContact3);
            }
            if(foundinhash)
            {cout << dummyContact3 << endl;}
            else{cout << "Name not found!" << endl;}
            auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);
            cout << "\nHash Table Search Time: " << HTTime.count() / k << "\n";
            cout << "Speed Up: " << (double)BSTTime.count() / (double)HTTime.count()  << endl;
        }
        // add
        else if(choice == 2){
            string firstname,secondname,tel,city;
            cout << "Enter the information of the contact to be added:" << endl;
            cout << "Name: ";
            cin >> firstname >> secondname;
            cout << "Tel: " ;
            cin >> tel;
            cout << "City: ";
            cin >> city;
            cout << "Adding an item to the phonebook BST . . ."  << endl;
            auto start1 = chrono::high_resolution_clock::now(); // start time
            contactsBST.insert(Contact(firstname,secondname,tel,city));
            auto end1 = chrono::high_resolution_clock::now(); // end time
            auto duration1 = chrono::duration_cast<chrono::nanoseconds>(end1 - start1);
            long long timer1 = duration1.count (); // get the elapsed time in micro seconds
            cout << "===================================="  << endl;
            cout << "Contact has been added successfully to the BST" << endl << endl;
            
            cout << "Adding an item to the phonebook (HashTable) . . ."  << endl;
            auto start2 = chrono::high_resolution_clock::now(); // start time
            contactsHashTable.insert(Contact(firstname,secondname,tel,city),Contact(firstname,secondname,tel,city));
            auto end2 = chrono::high_resolution_clock::now(); // end time
            auto duration2 = chrono::duration_cast<chrono::nanoseconds>(end2 - start2);
            long long timer2 = duration2.count (); // get the elapsed time in micro seconds
            
            cout << "===================================="  << endl;
            cout << "Contact has been added successfully to the Hashtable" << endl << endl;
            cout << "Adding a contact to the Binary Tree took " << timer1 << " nanoseconds. . ." << endl;
            cout << "Adding a contact to the hash table Tree took "<< timer2 <<" nanoseconds. . ." << endl;
            
        }
        else if(choice == 3){
            cout << "Deleting an item from the phonebook . . ." << endl;
            string firstname,secondname;
            cout << "Enter the fullname of the contact to be deleted: " ;
            cin >> firstname >> secondname;
            auto start1 = chrono::high_resolution_clock::now(); // start time
            bool rem1 = contactsBST.remove(Contact(firstname,secondname));
            auto end1 = chrono::high_resolution_clock::now(); // end time
            auto duration1 = chrono::duration_cast<chrono::nanoseconds>(end1 - start1);
            long long timer1 = duration1.count (); // get the elapsed time in micro seconds
            
            auto start2 = chrono::high_resolution_clock::now(); // start time
            contactsHashTable.remove(Contact(firstname,secondname));
            auto end2 = chrono::high_resolution_clock::now(); // end time
            auto duration2 = chrono::duration_cast<chrono::nanoseconds>(end2 - start2);
            long long timer2 = duration2.count (); // get the elapsed time in micro seconds
            if(rem1){
                cout << "Deleted successfully" << endl;
                cout << "Deletion from the Binary Tree took " << timer1 << " nanoseconds. . ." << endl;
                cout << "Deletion from hash table took " << timer2 << " nanoseconds. . ." << endl;
            }
            else{
                cout << "Contact does not exist in the phonebook" << endl;
            }
            
        }
    }
    return 0;
}
