#include <bits/stdc++.h>
#include "dict.h"
#define file_ct 1
#define dump_test_freq 1
#define mode 0
#define bound 20
#define FILE "mahatma-gandhi-collected-works-volume-1.txt"
bool compareFiles(const std::string &p1, const std::string &p2, string &a, string &b)
{
    ifstream File1;
    ifstream File2;
    string line, line2;
    File1.open(p1);
    File2.open(p2);
    if (File1.fail())
    {
        cerr << "Error opening file !!" << endl;
        exit(1);
    }
    if (File2.fail())
    {
        cerr << "Error opening file !!" << endl;
        exit(1);
    }

    while (!File1.eof())
    { // read file until you reach the end
        getline(File1, line);
        getline(File2, line2);
        if (line != line2)
        {
            a = line;
            b = line2;
            return false;
        }
    }
    return true;
}
int main()
{
    // auto total_time = chrono::high_resolution_clock::now();
    string dir = "./txtfiles/mahatma-gandhi-collected-works-volume-";
    for (int i = 1; i <= file_ct; i++)
    {
        auto str = chrono::high_resolution_clock::now();
        string FILENAME = dir + to_string(i) + ".txt";
        std::ifstream inputFile(FILENAME);

        if (!inputFile.is_open())
        {
            std::cerr << "Error: Unable to open the input file." << std::endl;
            return 1;
        }

        std::string tuple;
        std::string sentence;

        Dict dict;

        while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence))
        {
            // Get a line in the sentence
            tuple += ')';

            std::vector<int> metadata;
            std::istringstream iss(tuple);

            // Temporary variables for parsing
            std::string token;

            // Ignore the first character (the opening parenthesis)
            iss.ignore(1);

            // Parse and convert the elements to integers
            while (std::getline(iss, token, ','))
            {
                // Trim leading and trailing white spaces
                size_t start = token.find_first_not_of(" ");
                size_t end = token.find_last_not_of(" ");
                if (start != std::string::npos && end != std::string::npos)
                {
                    token = token.substr(start, end - start + 1);
                }

                // Check if the element is a number or a string
                if (token[0] == '\'')
                {
                    // Remove the single quotes and convert to integer
                    int num = std::stoi(token.substr(1, token.length() - 2));
                    metadata.push_back(num);
                }
                else
                {
                    // Convert the element to integer
                    int num = std::stoi(token);
                    metadata.push_back(num);
                }
            }

            // Now we have the string in sentence
            // And the other info in metadata
            // Add to the dictionary

            // Insert in the dictionary
            dict.insert_sentence(metadata[0], metadata[1], metadata[2], metadata[3], sentence);
        }
        dict.dump_dictionary("Output_dict.txt");
        auto end = chrono::high_resolution_clock::now();
        auto time_taken = chrono::duration_cast<chrono::microseconds>(end - str);
    }
    return 0;
}