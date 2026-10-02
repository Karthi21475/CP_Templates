struct TrieNode {
    TrieNode* children[26];
    int count = 0;
    bool isEnd = false;

    TrieNode() {
        for (int i = 0; i < 26; i++) children[i] = nullptr;
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(string s) {
        TrieNode* node = root;
        for (char c : s) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new TrieNode();
            node = node->children[idx];
            node->count++;
        }
        node->isEnd = true;
    }

    bool search(string s) {
        TrieNode* node = root;
        for (char c : s) {
            int idx = c - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return node->isEnd;
    }

    bool erase(string s) {
        return eraseHelper(root, s, 0);
    }

private:
    bool eraseHelper(TrieNode* node, string& s, int depth) {
        if (!node) return false;

        if (depth == s.size()) {
            if (!node->isEnd) return false;
            node->isEnd = false;
            return node->count == 0;
        }

        int idx = s[depth] - 'a';
        if (!eraseHelper(node->children[idx], s, depth + 1)) return false;

        delete node->children[idx];
        node->children[idx] = nullptr;
        node->count--;

        return !node->isEnd && node->count == 0;
    }
};
