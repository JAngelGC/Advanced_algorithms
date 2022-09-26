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
        //cout << "Inserted value: " << children[children.size()-1]->value << endl;
    }

};

Node* insertLetter(Node* head, char letter) {
    Node* tmp = head;

    for(int i=0; i<tmp->children.size(); i++) {
        if (tmp->children[i]->value == letter) {
            //tmp = tmp->children[i];
            return tmp->children[i];
        }
    }
    head->addChild(letter);
    return head->children[head->children.size()-1];
}

void insertWord(Node* head, string word) {
    Node* last = head;
    for(int i=0; i<word.length(); i++) {
        last = insertLetter(last, word[i]);
    }

}


int searchLetter(Node* head, char letter) {
    for(int i=0; i<head->children.size(); i++) {
        if (head->children[i]->value == letter) {
            return i;
        }
    }
    return -1;
}

bool searchWord(Node* head, string word) {
    int pos = 0;
    //cout << endl;
    for(int i=0; i<word.length(); i++) {
        pos = searchLetter(head, word[i]);
        //cout << head->children[pos]->value;
        if (pos >= 0) {
            head = head->children[pos];
        }
        else {
            return false;
        }
    }
    return true;

}


void dfs(Node *head) {

    //cout << head->value;
    cout << head->value << " ";
    for(int i=0; i<head->children.size(); i++) {
        dfs(head->children[i]);
        //cout << endl;
    }
    //cout << " ";

}





int main() {

    int n;
    int m;
    string str;
    struct Node head = Node();

    cin >> n;

    for(int i=0; i<n; i++) {
        cin >> str;
        insertWord(&head, str);
    }
    

    cin >> n; 
    cout << boolalpha;
    for(int i=0; i<n; i++) {
        cin >> str;
        cout << searchWord(&head, str) << endl;
    }
    
    for(int i=0; i<head.children.size(); i++) {
        dfs(head.children[i]);
    }

    cout << endl;

    return 0;
}
