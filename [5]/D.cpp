#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <list>
using namespace std;
 
class Set {
private:
    vector<list<string> > hashTable;
    unsigned hash(string key) {
        unsigned hash = 0;
        int charcode;
        const int k = 199;
        for (char i : key) {
            charcode = tolower(i) - 'a';
            hash = (hash * k + charcode) % hashTable.size();
        }
        return hash;
    }
public:
    Set(unsigned size) {
        hashTable.resize(size);
    }
    bool exists(string key) {
        unsigned index = hash(key);
        for (string i : hashTable[index]) {
            if (i == key)
                return true;
        }
        return false;
    }
    void insert(string key) {
        if (!exists(key))
            hashTable[hash(key)].push_back(key);
    }
    void remove(string key) {
        unsigned index = hash(key);
        for (auto i = hashTable[index].begin(); i != hashTable[index].end(); i++) {
            if (*i == key) {
                hashTable[index].erase(i);
                return;
            }
        }
    }
 
    vector<string> getAll() {
        vector<string> result;
        for (list<string> values : hashTable) {
            for (string value : values) {
                result.push_back(value);
            }
        }
        return result;
    }
 
    void reSet() {
        unsigned size = hashTable.size();
        hashTable.clear();
        hashTable.resize(size);
    }
};
 
class map {
private:
    struct node{
        string key;
        shared_ptr<Set> values;
    };
    vector<list<node> > hashes;
    unsigned valueSetsize;
    unsigned hash(string key) {
        unsigned hash = 0;
        int charcode;
        const int k = 199;
        for (char i : key) {
            charcode = tolower(i) - 'a';
            hash = (hash * k + charcode) % hashes.size();
        }
        return hash;
    }
    shared_ptr<Set> getvalueSet(string key) {
        unsigned index = hash(key);
        for (node &node : hashes[index]) {
            if (node.key == key) {
                return node.values;
            }
        }
        return nullptr;
    }
public:
    map(unsigned mapSize, unsigned valueSetSize) {
        hashes.resize(mapSize);
        valueSetsize = valueSetSize;
    }
    void put(string key, string value) {
        shared_ptr<Set> valueSet = getvalueSet(key);
        if (valueSet != nullptr)
            valueSet->insert(value);
        else {
            node newNode;
            newNode.key = key;
            newNode.values = make_shared<Set>(valueSetsize);
            newNode.values->insert(value);
            hashes[hash(key)].push_back(newNode);
        }
    }
    vector<string> get(string key) {
        shared_ptr<Set> valueSet = getvalueSet(key);
        if (valueSet != nullptr)
            return valueSet->getAll();
        else
            return vector<string>(0);
    }
    void remove(string key, string value) {
        shared_ptr<Set> valueSet = getvalueSet(key);
        if (valueSet != nullptr)
            valueSet->remove(value);
    }
    void removeAll(string key) {
        unsigned index = hash(key);
        for (auto i = hashes[index].begin(); i != hashes[index].end(); i++) {
            if (i->key == key) {
                hashes[index].erase(i);
                return;
            }
        }
    }
};

int main()
{
    ifstream fin("multimap.in");
    ofstream fout("multimap.out");
    map map(100003, 235);
    string s, x, y;
    while (fin >> s) {
        fin >> x;
        if (s == "put") {
            fin >> y;
            map.put(x, y);
        } else if (s == "get") {
            vector <string> values = map.get(x);
            fout << values.size() << " ";
            for (string value : values)
                fout << value << " ";
            fout << endl;
        } else if (s == "delete") {
            fin >> y;
            map.remove(x, y);
        } else if (s == "deleteall") {
            map.removeAll(x);
        }
    }
}