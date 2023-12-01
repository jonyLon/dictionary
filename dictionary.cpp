#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;


using word = string;
using translation = string;
using amount = int;

void writeMaptoFile(const map<string, string> map, const string& filename) {
    ofstream file(filename);
    for (const auto& pair : map) {
        file << pair.first << " = " << pair.second << endl;
    }
    file.close();
}
map<word, translation> readMapfromFile(const string& filename) {
    ifstream file(filename);
    map<word, translation> maper;
    string line, key, value;
    while (getline(file,line)){
        int pos = line.find(" = ");
        if (pos != string::npos) 
        {
            key = line.substr(0, pos);
            value = line.substr(pos + 3);
            maper[key] = value;
        }
    }

    file.close();
    return maper;
}
map<word, amount> readOtherMapfromFile(const string& filename) {
    ifstream file(filename);
    map<word, amount> maper;
    string word, key;
    amount value;
    while (file >> word) {
        if (word.find(",") != string::npos || word.find(".") != string::npos) {
            word.pop_back();
        }
        if (maper.find(word) == maper.end())
        {
            key = word;
            value = 1;
            maper[key] = value;
        }
        else
        {
            auto it = maper.find(word);
            int amount = it->second + 1;
            maper.erase(it);
            maper.insert({ word,amount });
        }
    }

    file.close();
    return maper;
}
void writeOtherMaptoFile(const map<word, amount> map, const string& filename) {
    ofstream file(filename);
    for (const auto& pair : map) {
        file << pair.first << " - " << pair.second << endl;
    }
    file.close();
}


int main()
{

    //1
	map<word, translation> dictionary;
	
    dictionary["hello"] = "privit";
    dictionary["world"] = "svit";
    dictionary["book"] = "knyha";
    dictionary["apple"] = "yabluko";
    dictionary["tree"] = "derevo";
    dictionary["computer"] = "kompiuter";
    dictionary["phone"] = "telefon";
    dictionary["sun"] = "sonce";
    dictionary["moon"] = "misyac";
    dictionary["star"] = "zirka";
    dictionary["sky"] = "nebo";
    dictionary["river"] = "richka";
    dictionary["mountain"] = "hora";
    dictionary["ocean"] = "okean";
    dictionary["lake"] = "ozero";
    dictionary["forest"] = "lis";
    dictionary["car"] = "avtomobil";
    dictionary["bicycle"] = "velosyped";
    dictionary["train"] = "poyizd";
    dictionary["airplane"] = "litak";
    dictionary["ship"] = "korabl";
    dictionary["house"] = "budynok";
    dictionary["school"] = "shkola";
    dictionary["university"] = "universytet";
    dictionary["teacher"] = "vykladach";
    dictionary["student"] = "student";
    dictionary["coffee"] = "kava";
    dictionary["tea"] = "chai";
    dictionary["water"] = "voda";

    dictionary.insert({ "food", "yizha" });
    dictionary.erase("tea");

    translation otherword = "kava";
    auto it = find_if(dictionary.begin(), dictionary.end(), [otherword](const pair<word, translation> el) {return el.second == otherword; });
    if (it != dictionary.end())
    {
        dictionary.erase(it);
    }
    else cout << otherword << " not found" << endl;

    dictionary["house"] = "hata";
    for (const auto& pair : dictionary) {
        cout << pair.first << " = " << pair.second << endl;
    }
    cout << endl;
    //system("cls");
    writeMaptoFile(dictionary, "dictionary.txt");
    map<word,translation> newDictionary = readMapfromFile("dictionary.txt");
    cout << "New dictionary: \n";
    for (const auto& pair : newDictionary) {
        cout <<"\t" << pair.first << " = " << pair.second << endl;
    }

    //2

    map<word, amount> words_frequency = readOtherMapfromFile("text.txt");
    cout << "New : \n";
    for (const auto& pair : words_frequency) {
        cout << "\t" << pair.first << " = " << pair.second << endl;
    }

    writeOtherMaptoFile(words_frequency,"result.txt");

    pair<word, amount> max = {"",0};
    for (const auto& pair : words_frequency) {
        if (pair.second > max.second)
        {
            max = pair;
        }
    }
    cout << "The most frequent word \'" << max.first << "\'. Frequency: " << max.second << endl;



}

