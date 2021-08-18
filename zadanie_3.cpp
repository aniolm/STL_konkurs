/* Konkurs STL - Zadanie 3 */

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

bool writeFile(const std::string& filename, const std::string& input) {
    std::fstream file(filename, std::ios::out | std::ios::binary);
    if (file.good()) {
        file << input;
        file.close();
        return true;
    }

    return false;
}

bool readFile(const std::string& filename, std::string& input) {
    std::fstream file(filename, std::ios::in | std::ios::binary);
    if (file.good()) {
        std::copy(std::istreambuf_iterator<char>(file),
                  std::istreambuf_iterator<char>(),
                  std::back_inserter(input));
        file.close();
        return true;
    }

    return false;
}

auto removeRedundantLFsAndSpaces(const std::string& input) {
    std::string result(input);
    result.erase(std::unique(begin(result), end(result),
                             [](const auto& lhs, const auto& rhs) {
                                 return (lhs == ' ' && rhs == ' ') ||
                                        (lhs == '\n' && rhs == '\n');
                             }),
                 result.end());
                
    return result;
}

auto createInputFile(const std::string& filename) {
    std::string input("Ala ma kota a kot\n\nnie ma   \n\n\nali   "
                      "\n\n\n!!!\n\n\nI co     teraz   ?? \n\nHmmm??\n\n\n\n\n?");
    writeFile(filename, input);

    return input;
}

void printAssertedResult(const std::string& result) {
    std::string output("Ala ma kota a kot\nnie ma \nali \n!!!\nI co teraz ?? \nHmmm??\n?");
    assert(result == output);
    std::cout << result << std::endl;
}

int main() {
    const std::string filename("Sumfing.txt");
    std::string input;

    if (!readFile(filename, input)) {
        input = createInputFile(filename);
    };

    auto result = removeRedundantLFsAndSpaces(input);
    printAssertedResult(result);
    
    /* overwrite original file ?
    writeFile(filename, result); */

    return 0;
}
