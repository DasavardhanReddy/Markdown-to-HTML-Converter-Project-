#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Replace first occurrence of old with new
string replaceFirst(string& str, const string& oldVal, const string& newVal) {
    size_t pos = str.find(oldVal);
    if (pos != string::npos)
        str.replace(pos, oldVal.length(), newVal);
    return str;
}

// Replace second occurrence
string replaceSecond(string& str, const string& oldVal, const string& newVal) {
    size_t pos1 = str.find(oldVal);
    if (pos1 != string::npos) {
        size_t pos2 = str.find(oldVal, pos1 + oldVal.length());
        if (pos2 != string::npos)
            str.replace(pos2, oldVal.length(), newVal);
    }
    return str;
}

int main() {
    ifstream inFile("input.md");
    ofstream outFile("output.html");

    if (!inFile || !outFile) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    outFile << "<html><body>\n";

    string line;
    while (getline(inFile, line)) {
        // Headings: count # at start
        if (line.rfind("#", 0) == 0) {
            int count = 0;
            while (line[count] == '#') count++;
            string content = line.substr(count);
            while (!content.empty() && content[0] == ' ') content.erase(0, 1); // remove space
            outFile << "<h" << count << ">" << content << "</h" << count << ">\n";
        }
        // Bold and Italic
        else {
            if (line.find("**") != string::npos) {
                replaceFirst(line, "**", "<b>");
                replaceSecond(line, "**", "</b>");
            }
            if (line.find("*") != string::npos) {
                replaceFirst(line, "*", "<i>");
                replaceSecond(line, "*", "</i>");
            }
            outFile << "<p>" << line << "</p>\n";
        }
    }

    outFile << "</body></html>";
    cout << "Conversion complete! Check output.html" << endl;

    return 0;
}
