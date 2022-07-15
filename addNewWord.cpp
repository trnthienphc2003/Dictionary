using namespace std;
#include "Trie2.h"
#include "addNewWord.h"
//root_key for trie saving key
//root_def for trie saving definition of key
void add_new_word(TrieNode*& root_key, TrieNode*& root_def, string s, string meaning) {
    insert(root_key, s, meaning);
    insert(root_def, meaning, s);
}

