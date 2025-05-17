#include <bits/stdc++.h>

using namespace std;

struct Node {
    char ch; //Character(leaf node only)
    long long freq; //Appearance frequency
    int order; //Track the first appearance order
    Node* left; //Left child
    Node* right; //Right child

    // Construct leaf node
    Node(char c, long long f, int o):
        ch(c), freq(f), order(o), left(nullptr), right(nullptr) {}

    // Construct Internal node(combine two nodes)
    Node(Node* l, Node* r):
        ch(0), freq(l->freq + r->freq), order(min(l->order, r->order)), left(l), right(r) {}
};

// Frequency comparison for priority queue
struct Compare {
    bool operator()(Node* a, Node* b) const {
        if (a->freq != b->freq)
            return a->freq > b->freq; //Primary key: Low frequency high priority
        return a->order > b->order; //Alternate key: Front appearance order high priority
    }
};

// Recursive visit tree to build binary codes for each character
void buildCodes(Node* node, const string &prefix, unordered_map<char, string> &codes) {
    if (!node) return;
    // Store code if reach leaf node
    if (!node->left && !node->right) {
        codes[node->ch] = prefix.empty() ? "0" : prefix; //Use 0 for encoding if only one node in tree
    }
    buildCodes(node->left, prefix + '0', codes);
    buildCodes(node->right, prefix + '1', codes);
}

int main() {
    // Speed up I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;
    if (!getline(cin, input)) return 0; //Read input line

    // Calculate character frequency & first appearance position
    unordered_map<char, long long> freq;
    unordered_map<char, int> firstPos;
    for (int i = 0; i < (int)input.size(); ++i) {
        char c = input[i];
        if (freq[c] == 0) firstPos[c] = i; //Record first appearance position
        freq[c]++;
    }

    // Build priority queue (min-heap) based on frequency & first appearance
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto &p : freq) {
        pq.push(new Node(p.first, p.second, firstPos[p.first]));
    }

    // Combine nodes until only one node remains in priority queue
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* parent = new Node(left, right); //Merge nodes into one
        pq.push(parent); //Push back to priority queue
    }
    Node* root = pq.top(); //Last node is root

    // Generate huffman codes from root node
    unordered_map<char, string> codes;
    buildCodes(root, "", codes);

    // Transform input text into binary string
    string bits;
    bits.reserve(input.size() * 8);
    for (char c : input) bits += codes[c];

    // Use 0 padding to make bits length be multiple of 4
    int pad = (4 - bits.size() % 4) % 4;
    bits.append(pad, '0');

    // Binary convert to hexadecimal
    string hex;
    for (size_t i = 0; i < bits.size(); i += 4) {
        int val = (bits[i]-'0')*8 + (bits[i+1]-'0')*4 + (bits[i+2]-'0')*2 + (bits[i+3]-'0');
        if (val < 10) hex.push_back('0' + val);
        else hex.push_back('A' + (val - 10));
    }
    cout << hex;

    return 0;
}
