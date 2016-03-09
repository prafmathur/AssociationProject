#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;


// struct Association {
//   string word;
//   unsigned int count;
// };




std::map<string, unordered_map<string, int> > WORDS;


void outputWordsSorted() {
  for(auto&& i : WORDS) {
    cout << i.first << "\t| ";
    vector<pair<string, int>> v;
    for(auto&& j : i.second) {
      v.push_back(j);
      // cout << j.first << " ";
    }
    sort(v.begin(),v.end(), [](pair<string, int> a, pair<string, int> b){
      return a.second > b.second;
    });
    int x = 0;
    for(auto&& i : v) {
      if (x == 3)
        break;
      cout << i.first << ":" << i.second << "  " ;
      x++;
    }
    cout << endl;
  }
}

void outputWordsMinified() {
    for(auto&& i : WORDS) {
      cout << i.first << " ";
      cout << i.second.size() << " ";
      for(auto&& j : i.second) {
        cout << j.first << " " << j.second << " ";
      }
      cout << endl;
    }
}

void writeToFileWordsMinified(string filename) {
    ofstream outfile(filename);
    for(auto&& i : WORDS) {
      outfile << i.first << " ";
      outfile << i.second.size() << " ";
      for(auto&& j : i.second) {
        outfile << j.first << " " << j.second << " ";
      }
      outfile << endl;
    }
}


void readWordsDb(string filename) {
  WORDS.clear();
  ifstream infile(filename);

  string word, association;
  int numLinks, weight;
  while(  infile >> word) {
    infile >> numLinks;
    for (int i = 0; i < numLinks; ++i) {

      infile >> association >> weight;
      WORDS[word][association] = weight; 
    }  
  }
}




void readSentencesFile(string filename) {
  //Read in a sentences line by line
  ifstream infile(filename);

  string line;
  while (getline(infile, line)) {
    std::vector<string> sentence;
    // std::multiset<string> sentenceSet;
    std::istringstream iss(line);

    string word;
    while(iss >> word) {
      sentence.push_back(word);
      // sentenceSet.insert(word);
    }

    for(auto&& word : sentence) {
      for(auto&& otherWord : sentence) {
        if (word == otherWord)
          continue;

        unordered_map<string, int> &m = WORDS[word];
        if (m.find(otherWord) == m.end()) 
          m[otherWord] = 1;
        else 
          m[otherWord]++;
      }
    }
  }
}


void storeAssociations(string sentenceFileName, string dbFileName) {
  readSentencesFile(sentenceFileName);
  writeToFileWordsMinified(dbFileName);
}

int main()
{
  // storeAssociations("l.txt", "peterpandb.txt");
  readWordsDb("peterpandb.txt");
  outputWordsSorted();
  return 0;
}