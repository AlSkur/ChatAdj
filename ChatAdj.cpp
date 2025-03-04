#include <iostream>
#include <vector>
#include <string>
#include <cctype> 

using namespace std;

struct TrieNode {
    bool isWordEnd;
    TrieNode* children[26];

    TrieNode() : isWordEnd(false) {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr; 
        }
    }
};


bool isValidChar(char c) {
    return (c >= 'a' && c <= 'z');
}

void insertWord(TrieNode* root, const string& word) {
    TrieNode* currentNode = root;
    for (char c : word) {
        c = tolower(c); 
        if (!isValidChar(c)) {
            cerr << "Error: Invalid character '" << c << "' in word: " << word << endl;
            return; 
        }
        int index = c - 'a';
        if (!currentNode->children[index]) {
            currentNode->children[index] = new TrieNode();
        }
        currentNode = currentNode->children[index];
    }
    currentNode->isWordEnd = true;
}

void findSuggestions(TrieNode* node, string currentPrefix, vector<string>& suggestions) {
    if (!node) return; 

    if (node->isWordEnd) {
        suggestions.push_back(currentPrefix);
    }

    for (char c = 'a'; c <= 'z'; c++) {
        int index = c - 'a';
        if (node->children[index]) {
            findSuggestions(node->children[index], currentPrefix + c, suggestions);
        }
    }
}

vector<string> autocomplete(TrieNode* root, const string& prefix) {
    vector<string> suggestions;
    TrieNode* currentNode = root;

    for (char c : prefix) {
        c = tolower(c); 
        if (!isValidChar(c)) {
            cerr << "Error: Invalid prefix character '" << c << "'" << endl;
            return suggestions; 
        }
        int index = c - 'a';
        if (!currentNode->children[index]) {
            return suggestions;
        }
        currentNode = currentNode->children[index];
    }

    findSuggestions(currentNode, prefix, suggestions);
    return suggestions;
}

int main() {
    TrieNode* root = new TrieNode();

    string dictionary[] = { "apple", "app", "banana", "bat", "ball", "cat", "call", "dog", "dream"};
    for (string word : dictionary) {
        insertWord(root, word);
    }

    string input;
    cout << "Autocomplete System (english lowercase). Type 'exit' to quit.\n";

    while (true) {
        cout << "\nEnter prefix: ";
        cin >> input;

        if (input == "exit") break;

        
        bool valid = true;
        for (char c : input) {
            if (!isValidChar(tolower(c))) {
                cerr << "Error: Invalid character '" << c << "' in prefix" << endl;
                valid = false;
                break;
            }
        }

        if (!valid) continue;

        vector<string> suggestions = autocomplete(root, input);

        if (suggestions.empty()) {
            cout << "No suggestions :(";
        }
        else {
            cout << "Suggestions:\n";
            for (string word : suggestions) {
                cout << "-> " << word << endl;
            }
        }
    }

    return 0;
}