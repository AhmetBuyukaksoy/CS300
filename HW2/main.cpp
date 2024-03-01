//
//  main.cpp
//  hw3
//
//  Created by Ahmet Büyükaksoy on 22.04.2023.
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "AVLtree.h"
#include "BSTtree.h"
using namespace std;
struct Contact{
    string firstname, lastname, phonenum, address;
    Contact(string fn, string ln, string no = "", string add= ""){
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
    bool operator>(const Contact& other){
        // Compare first names alphabetically
        if (firstname < other.firstname) {
            return false;
        } else if (firstname > other.firstname) {
            return true;
        }

        // First names are equal, compare last names alphabetically
        return (lastname > other.lastname);
    }
    bool operator== (const Contact& rhs){
        return (firstname==rhs.firstname && lastname==rhs.lastname);
    }
    string getFullName(){
        return firstname + " " + lastname;
    }
    bool checkPrefix(string prefix){
        return getFullName().substr(0, prefix.size()) == prefix;
    }
    
    
};
ostream& operator<<(ostream& os, const Contact& contact) {
    os << contact.firstname << " " << contact.lastname << " ";
    os << contact.phonenum << " ";
  os << contact.address ;
  return os;
}

void search_contact(AVLTree<Contact>::Node* root, string query) {
    if (root == nullptr) {
        return;
    }
    for (auto & c: query) c = toupper(c);

    // PhoneBook-sample4.txt
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
// fix!!!!
void search_contact(BSTtree<Contact>::Node* root, string query) {
    
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
void readIntoBST(string filename, BSTtree<Contact> &contactsBST){
    auto start1 = chrono::high_resolution_clock::now(); // start time
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
             auto end1 = chrono::high_resolution_clock::now(); // end time
             auto duration1 = chrono::duration_cast<chrono::milliseconds>(end1 - start1);
             long long timer1 = duration1.count (); // get the elapsed time in micro seconds

             cout << "Phonebook creation in BST took " << timer1 << " milliseconds. . ." << endl;
             contactsBST.fixHeights();
             if(contactsBST.getRoot()->right->height !=contactsBST.getRoot()->left->height ){
                 cout << "The tree is not balanced" << endl;
                 cout << "The heights of BST are for left: " << contactsBST.getRoot()->left->height <<  " and right: " << contactsBST.getRoot()->right->height << endl;
             }
         } else {
             cout << "Error opening file!" << endl;
         }
}
void readIntoAVL(string filename, AVLTree<Contact> &contactsAVL){
    auto start1 = chrono::high_resolution_clock::now(); // start time

    ifstream inputFile(filename.c_str());

     string line;
         if (inputFile.is_open()) {
             cout << "Loading the phonebook into an AVL." << endl;

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
                 contactsAVL.insert(c);
                 }
             inputFile.close();
             auto end1 = chrono::high_resolution_clock::now(); // end time
             auto duration1 = chrono::duration_cast<chrono::milliseconds>(end1 - start1);
             long long timer1 = duration1.count (); // get the elapsed time in micro seconds

             cout << "Phonebook creation in AVL took " << timer1 << " milliseconds. . ." << endl;
             if(contactsAVL.getRoot()->right->height !=contactsAVL.getRoot()->left->height ){
                 cout << "The tree is not balanced" << endl;
                 cout << "The heights of AVL are for left: " << contactsAVL.getRoot()->left->height <<  " and right: " << contactsAVL.getRoot()->right->height << endl;
             }

         } else {
             cout << "Error opening file!" << endl;
         }
}

int main() {
    AVLTree<Contact> contactsAVL;
    BSTtree<Contact> contactsBST;
    string filename;
    cout << "Please enter the contact filename: ";
    cin >> filename;
    
    readIntoBST(filename,contactsBST);
    readIntoAVL(filename, contactsAVL);
    // reading is done now display the options
    int option = 0;
    
    while(option != 6){
        cout << endl;
        cout << "Choose which action to perform from 1 to 6:\n"
                 << "1 - Search a phonebook contact\n"
                 << "2 - Adding a phonebook contact\n"
                 << "3 - Deleting a phonebook contact\n"
                 << "4 - Print the phonebook to a file(inorder)\n"
                 << "    Print the phonebook to a file(preorder)\n"
                 << "5 - Draw the phonebook as a Tree to a file\n"
                 << "6 - Press 6 to exit\n";
        cin >> option;
        if(option == 1){
            string firstname,lastname,search;
            cout << "Search for a contact: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            getline(cin, search);

                size_t pos = search.find(' ');

                if (pos != string::npos) {
                    firstname = search.substr(0, pos);
                    lastname = search.substr(pos + 1);
                    search = firstname + " " + lastname;

                } else {
                    firstname = search;
                }
            for (auto & c: search) c = toupper(c);

            cout << "Searching an item in the phonebook (BST)..." << endl;
            cout << "Phonebook: Searching for: (" << search << ")" << endl;
            cout << "====================================" << endl;
            auto start1 = chrono::high_resolution_clock::now(); // start time
            search_contact(contactsBST.getRoot(), search);
            auto end1 = chrono::high_resolution_clock::now(); // end time
            auto duration1 = chrono::duration_cast<chrono::milliseconds>(end1 - start1);
            long long timer1 = duration1.count (); // get the elapsed time in micro seconds
            cout << endl;
            cout << "Searching an item in the phonebook (AVL)..." << endl;
            cout << "Phonebook: Section: (" << search << ")" << endl;
            cout << "====================================" << endl;
            auto start2 = chrono::high_resolution_clock::now(); // start time
            search_contact(contactsAVL.getRoot(), search);
            auto end2 = chrono::high_resolution_clock::now(); // end time
            auto duration2 = chrono::duration_cast<chrono::milliseconds>(end2 - start2);
            long long timer2 = duration2.count (); //
            cout << "The search in BST took " << timer1 <<" milliseconds. . ." << endl;
            cout << "The search in AVL took " << timer2 <<" milliseconds. . ." << endl;
        }
        if(option == 2){
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
            
            cout << "Adding an item to the phonebook AVL . . ."  << endl;
            auto start2 = chrono::high_resolution_clock::now(); // start time
            contactsAVL.insert(Contact(firstname,secondname,tel,city));
            auto end2 = chrono::high_resolution_clock::now(); // end time
            auto duration2 = chrono::duration_cast<chrono::nanoseconds>(end2 - start2);
            long long timer2 = duration2.count (); // get the elapsed time in micro seconds
            
            cout << "===================================="  << endl;
            cout << "Contact has been added successfully to the AVL" << endl;
            cout << "Adding a contact to the Binary Tree took " << timer1 << " nanoseconds. . ." << endl;
            cout << "Adding a contact to the AVL Tree took "<< timer2 <<" nanoseconds. . ." << endl;
            
        }
        if(option == 3){
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
            bool rem2 = contactsAVL.remove(Contact(firstname,secondname));
            auto end2 = chrono::high_resolution_clock::now(); // end time
            auto duration2 = chrono::duration_cast<chrono::nanoseconds>(end2 - start2);
            long long timer2 = duration2.count (); // get the elapsed time in micro seconds
            if(rem1 && rem2){
                cout << "Deleted successfully" << endl;
                cout << "Deletion from the Binary Tree took " << timer1 << " nanoseconds. . ." << endl;
                cout << "Deletion from AVL Tree took " << timer2 << " nanoseconds. . ." << endl;
            }
            else{
                cout << "Contact does not exist in the tree" << endl;
            }
            
            
        }
        if(option == 4){
            auto start1 = chrono::high_resolution_clock::now(); // start time

            contactsAVL.printInorderToFile("InorderAVL.txt");
            contactsBST.printInorderToFile("InorderBST.txt");
            auto end1 = chrono::high_resolution_clock::now(); // end time
            auto duration1 = chrono::duration_cast<chrono::nanoseconds>(end1 - start1);
            long long timer1 = duration1.count (); // get the elapsed time in micro seconds

            auto start2 = chrono::high_resolution_clock::now(); // start time
            contactsAVL.printPreorderToFile("PreorderAVL.txt");
            contactsBST.printPreorderToFile("PreorderBST.txt");
            auto end2 = chrono::high_resolution_clock::now(); // end time
            auto duration2 = chrono::duration_cast<chrono::nanoseconds>(end2 - start2);
            long long timer2 = duration2.count (); // get the elapsed time in micro seconds
            cout << "Saving the book to a file (Inorder) took " << timer1 <<" nanoseconds" << endl;
            cout << "Saving the book to a file (Preorder) took " << timer2 <<" nanoseconds" << endl;

        }
        
        if(option == 5) {
    
            ofstream outputFileAVL("phonebookTreeAVL.txt");
            ofstream outputFileBST("phonebookTreeBST.txt");

            contactsAVL.drawTree(outputFileAVL);
            contactsBST.drawTree(outputFileBST);
            
        }
        }
    
   
    
    
    
    
   
    return 0;
}
