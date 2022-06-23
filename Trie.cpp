using namespace std;
#include "Trie.h"

void insert(TrieNode *&root, string s, string meaning) {
    if(!root)
        root=new TrieNode();
    int n=s.size();
    TrieNode *cur=root;
    for(int i=0; i<n; ++i) {
        int nxt=int(s[i]-32);
        if(!cur->c[nxt]) cur->c[nxt]=new TrieNode();
        cur=cur->c[nxt];
    }

    cur->isEndOfWord=true;
    cur->meaning.push_back(meaning);
}

// bool lookUpMeaning1(TrieNode* root, string s, string& meaning) {
//     int n = s.size();
//     TrieNode* cur = root;

//     for (int i = 0; i < n; ++i) {
//         int nxt = int(s[i] - 32);
//         if (!cur->c[nxt]) return false;
//         cur = cur->c[nxt];
//     }

//     if (!cur->isEndOfWord) return false;

//     meaning = cur->meaning;
//     return true;
// }


// DFS to check all strings exist on trie with s as prefix
void traverse(vector <pair<string, string>> &v, TrieNode* root, string s) {
    if(root->isEndOfWord)
        for(string &def: root->meaning)
            v.push_back({s, def});
    
    for(int i=0; i<ALP; ++i) {
        if(root->c[i]) {
            string newS=s;
            newS+=char(i+32);
            traverse(v, root->c[i], newS);
        }
    }
}

vector <pair<string, string>> lookUpMeaning(TrieNode *root, string s) {
    int n=s.size();
    TrieNode *cur=root;

    for(int i=0; i<n; ++i) {
        int nxt=int(s[i]-32);
        if(!cur->c[nxt]) return {};
        cur=cur->c[nxt];
    }
    
    vector <pair<string, string>> v;
    traverse(v, cur, s);
    return v;
}

void deallocate(TrieNode* &root) {
    if(!root) return;
    
    for(int i=0; i<ALP; ++i)
        deallocate(root->c[i]);
    
    root->meaning.clear();
    delete root;
}

bool isEmpty(TrieNode* root) {
    for(int i=0; i<ALP; ++i)
        if(root->c[i]) return false;
    return true;
}

TrieNode* remove(TrieNode* &root, string key, int len) {
    if(!root || len>key.size()) return nullptr;

    if(len==key.size()) {
        if(root->isEndOfWord)
            root->isEndOfWord=false;
        if(isEmpty(root)) {
            delete root;
            root=nullptr;
        }

        return root;
    }

    int nxt=key[len]-32;
    root->c[nxt]=remove(root->c[nxt], key, len+1);

    if(isEmpty(root) && !root->isEndOfWord) {
        delete root;
        root=nullptr;
    }

    return root;
}

bool check_exist(TrieNode* &root, string s){
    int n=s.size();
    TrieNode *cur=root;

    for(int i=0; i<n; ++i) {
        int nxt=int(s[i]-32);
        if(!cur->c[nxt]) return false;
        cur=cur->c[nxt];
    }
    if(cur->isEndOfWord) return true;
    else return false;
}
bool check_delete_meaning(TrieNode*&root, string s){
    int n=s.size();
    TrieNode *cur=root;

    for(int i=0; i<n; ++i) {
        int nxt=int(s[i]-32);
        cur=cur->c[nxt];
    }
    if(cur->meaning.size() == 1) return false;
    else return true;
}
bool delete_meaning(TrieNode*&root, string s, string meaning){
    int n=s.size();
    TrieNode *cur=root;
    for(int i=0; i<n; ++i) {
        int nxt=int(s[i]-32);
        cur=cur->c[nxt];
    }
    int pos = -1;
    for(int i = 0; i < cur->meaning.size(); i++){
        if(cur->meaning[i] == meaning){
            pos = i;
            break;
        }
    }
    if(pos != -1){
        for(int i = pos; i < cur->meaning.size()-1; i++){
            cur->meaning[i] = cur->meaning[i+1];
        }
        cur->meaning.pop_back();
        return true;
    }
    else return false;
}

void deleteHistory()
{
    ofstream fout;
    fout.open("lookedupWords.txt", ios_base::trunc);
    fout.close();
}

//called in all searching functions
void savetoHistory(string s)
{
    ofstream fout;
    fout.open("lookedupWords.txt", ios_base::app);

    fout << s << endl;

    fout.close();
}

vector <string> viewHistory()
{
    ifstream fin;
    fin.open("lookedupWords.txt");
    vector <string> v;
    string s;
    while (getline(fin, s))
    {
        v.push_back(s);
    }

    fin.close();
    return v;
}