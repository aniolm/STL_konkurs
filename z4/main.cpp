
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace std {
std::ostream& operator<<(std::ostream& o, const std::pair<std::string, int>& p) {
    return o << p.first;
}
}  // namespace std

std::string readFile(const std::string& file) {
    std::ifstream fs(file);
    if (!fs) {
        std::cerr << "File not found\n";
        return "";
    }
    std::string text((std::istreambuf_iterator<char>(fs)),
                     std::istreambuf_iterator<char>());
    fs.close();
    return text;
}
std::vector<std::string> text2vector(const std::string& text) {
    std::istringstream ss(text);
    std::vector<std::string> textVector;
    std::for_each(std::istream_iterator<std::string>(ss),
                  std::istream_iterator<std::string>(),
                  [&textVector](const std::string& word) { textVector.push_back(word); });
    return textVector;
}

std::map<std::string, int> text2map(const std::string& text) {
    std::istringstream ss(text);
    std::map<std::string, int> duplicateTable;
    std::for_each(std::istream_iterator<std::string>(ss),
                  std::istream_iterator<std::string>(),
                  [&duplicateTable](const std::string& word) { duplicateTable[word]++; });
    return duplicateTable;
    ;
}

void printWordsOfTheSameLenght(const std::vector<std::string>& text, const std::string& referenceWord) {
    std::copy_if(text.begin(),
                 text.end(),
                 std::ostream_iterator<std::string>(std::cout, " "),
                 [&referenceWord](const std::string& word) { return word.size() == referenceWord.size(); });
    std::cout << "\n";
}

void printDuplicatedWords(const std::map<std::string, int>& text, const int occurences) {
    std::copy_if(text.begin(),
                 text.end(),
                 std::ostream_iterator<std::pair<std::string, int>>(std::cout, " "),
                 [&occurences](const std::pair<std::string, int> word) { return word.second == occurences; });
    std::cout << "\n";
}

std::size_t countCharacters(const std::string& text) {
    std::istringstream ss(text);
    return std::distance(std::istreambuf_iterator<char>(ss),
                         std::istreambuf_iterator<char>());
}

std::size_t countWords(const std::string& text) {
    std::istringstream ss(text);
    return std::distance(std::istream_iterator<std::string>(ss),
                         std::istream_iterator<std::string>());
}

std::size_t countLines(const std::string& text) {
    std::istringstream ss(text);
    return std::count(std::istreambuf_iterator<char>(ss),
                      std::istreambuf_iterator<char>(),
                      '\n');
}

std::string findLongestWord(const std::vector<std::string>& text) {
    auto itLongestWord = std::max_element(text.begin(),
                                          text.end(),
                                          [](const std::string& s1, const std::string& s2) {
                                              return s1.size() < s2.size();
                                          });
    return (*itLongestWord);
}

std::string findShortestWord(const std::vector<std::string>& text) {
    auto itShortestWord = std::min_element(text.begin(),
                                           text.end(),
                                           [](const std::string& s1, const std::string& s2) {
                                               return s1.size() < s2.size();
                                           });
    return (*itShortestWord);
}

std::string findMostDuplicatedWord(std::map<std::string, int> duplicateTable) {
    auto itMostDuplicatedWord = std::max_element(duplicateTable.begin(),
                                                 duplicateTable.end(),
                                                 [](const std::pair<std::string, int>& word1, const std::pair<std::string, int>& word2) {
                                                     return word1.second < word2.second;
                                                 });
    return (*itMostDuplicatedWord).first;
}

std::string findLeastDuplicatedWord(std::map<std::string, int> duplicateTable) {
    auto itLeastDuplicatedWord = std::min_element(duplicateTable.begin(),
                                                  duplicateTable.end(),
                                                  [](const std::pair<std::string, int>& word1, const std::pair<std::string, int>& word2) {
                                                      return word1.second < word2.second;
                                                  });
    return (*itLeastDuplicatedWord).first;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: text_analyser <file_name>\n";
        return EXIT_FAILURE;
    }

    std::string text = readFile(argv[1]);

    std::cout << "Number of characters:"
              << "\t" << countCharacters(text) << std::endl;
    std::cout << "Number of words:"
              << "\t" << countWords(text) << std::endl;
    std::cout << "Number of lines:"
              << "\t" << countLines(text) << std::endl;

    std::vector<std::string> textVector = text2vector(text);
    std::string longestWord = findLongestWord(textVector);
    std::cout << "Longest words:"
              << "\t";
    printWordsOfTheSameLenght(textVector, longestWord);
    std::cout << "Length:"
              << "\t" << longestWord.size() << "\n";
    std::cout << "Shortest words:"
              << "\t";
    std::string shortestWord = findShortestWord(textVector);
    printWordsOfTheSameLenght(textVector, shortestWord);
    std::cout << "Length:"
              << "\t" << shortestWord.size() << "\n";

    std::map<std::string, int> duplicateTable = text2map(text);
    std::string mostDuplicatedWord = findMostDuplicatedWord(duplicateTable);
    std::cout << "Most duplicated words:"
              << "\t";
    printDuplicatedWords(duplicateTable, duplicateTable[mostDuplicatedWord]);
    std::cout << "Duplications:"
              << "\t" << duplicateTable[mostDuplicatedWord] << "\n";
    std::string leastDuplicatedWord = findLeastDuplicatedWord(duplicateTable);
    std::cout << "Least duplicated words:"
              << "\t";
    printDuplicatedWords(duplicateTable, duplicateTable[leastDuplicatedWord]);
    std::cout << "Duplications:"
              << "\t" << duplicateTable[leastDuplicatedWord] << "\n";
    return 0;
}