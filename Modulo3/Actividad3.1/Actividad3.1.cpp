// Programa que resuelve un laberinto | Backtracking & Branch and bound
// Carlos Daniel Diaz Arrazate - A01734902
// Jose Angel Gonzalez Carrera - A01552274
// Carlos Eduardo Ruiz Lira - A01735706
// 25/09/2022

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    char value;
    vector<Node*> children;

    Node() {
        value = '\0';
    }

    Node(char letter) {
        value = letter;
        vector<struct Node*> children;
    }

    void addChild(char letter) {
        Node* tmp = new Node(letter);
        children.push_back( tmp );
    }

};

// Insert a letter in a tree
// Time Complexity: O(n)
// Input: Pointer to node, char
// Output: Pointer to position of parent of char
Node* insertLetter(Node* head, char letter) {
    Node* tmp = head;

    for(int i=0; i<tmp->children.size(); i++) {
        if (tmp->children[i]->value == letter) {
            return tmp->children[i];
        }
    }
    head->addChild(letter);
    return head->children[head->children.size()-1];
}

// Insert a word in the tree
// Time Complexity: O(n)
// Input: Pointer to node, string
// Output: None
void insertWord(Node* head, string word) {
    Node* last = head;
    for(int i=0; i<word.length(); i++) {
        last = insertLetter(last, word[i]);
    }

}


// Search for a letter in tree
// Time Complexity: O(n)
// Input: Pointer to node, char
// Output: Position of letter
int searchLetter(Node* head, char letter) {
    for(int i=0; i<head->children.size(); i++) {
        if (head->children[i]->value == letter) {
            return i;
        }
    }
    return -1;
}

// Search word in tree
// Time Complexity: O(n)
// Input: Pointer to node, string
// Output: Bool
bool searchWord(Node* head, string word) {
    int pos = 0;
    for(int i=0; i<word.length(); i++) {
        pos = searchLetter(head, word[i]);
        if (pos >= 0) {
            head = head->children[pos];
        }
        else {
            return false;
        }
    }
    return true;

}

// Depth first search
// Time Complexity: O(n)
// Input: Head of tree
// Output: None
void dfs(Node *head) {
    cout << head->value << " ";
    for(int i=0; i<head->children.size(); i++) {
        dfs(head->children[i]);
    }
}





int main() {

    int n;
    int m;
    string str;
    struct Node head = Node();

    // Input words into tree
    cin >> n;

    for(int i=0; i<n; i++) {
        cin >> str;
        insertWord(&head, str);
    }
    

    // Search for words into tree
    cin >> m; 
    cout << boolalpha;
    for(int i=0; i<m; i++) {
        cin >> str;
        cout << searchWord(&head, str) << endl;
    }
    

    // Print dfs of tree
    for(int i=0; i<head.children.size(); i++) {
        dfs(head.children[i]);
    }

    cout << endl;

    return 0;
}
