#pragma once
#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
// alphabet: ASCII 32-127 (all printable characters)
// For Dictionary project (with special characters like -, $, #...)
const int ALP = 96;

struct TrieNode {
    int cnt;
    TrieNode* c[ALP];
    bool isEndOfWord;
    vector <string> meaning;

    TrieNode() {
        this->cnt = 0;
        for (int i = 0; i < ALP; ++i)
            this->c[i] = nullptr;
        this->isEndOfWord = false;
       this-> meaning = {};
    }
};

void insert(TrieNode*& root, string s, string meaning);
// bool lookUpMeaning1(TrieNode* root, string s, string& meaning);
void traverse(vector <pair<string, string>>& v, TrieNode* root, string s);
vector <pair<string, string>> lookUpMeaning(TrieNode* root, string s);
bool lookUpMeaning1(TrieNode* root, string s, string& meaning);
void deallocate(TrieNode*& root);
bool isEmpty(TrieNode* root);
TrieNode* remove(TrieNode*& root, string key, int len);
bool check_exist(TrieNode*& root_key, string s);
bool check_delete_meaning(TrieNode*& root, string s);
bool delete_meaning(TrieNode*& root, string s, string meaning);
void deleteHistory(std::string address);
void savetoHistory(std::string s, std::string address, std::string meaning);
vector <pair<string, string>> viewHistory(std::string address);
vector <pair<string, string>> loadLikeWord(std::string address);
void releaseLikeWord(std::string address, vector<pair<string, string>> save);
