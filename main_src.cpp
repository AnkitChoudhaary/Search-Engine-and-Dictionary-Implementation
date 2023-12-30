#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "search.h"
#include <chrono>
void print(Node *rt, int &sz)
{
    int k = sz;
    system("touch Output_Src.txt");
    ofstream out;
    out.open("Output_Src.txt", ios::app);
    while (rt)
    {
        out << "Count No. :" << k - sz + 1 << '\n';
        out << "BOOK :" << rt->book_code << "  | "
            << "Page :" << rt->page << "  |  "
            << "Para:" << rt->paragraph << " |  ";
        out << "Sen No." << rt->sentence_no << "   |  OffSet:" << rt->offset << "\n";
        out << "\n";
        sz--;
        Node *prv = rt;
        rt = rt->right;
        delete prv;
    }
    out.close();
}
int main()
{
    SearchEngine s;
    auto start = std::chrono::high_resolution_clock::now();
    const std::string FILENAME_PREFIX = "./txtfiles/mahatma-gandhi-collected-works-volume-1.txt";

    std::ifstream inputFile(FILENAME_PREFIX);

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open the input file." << std::endl;
        return 1;
    }
    std::string tuple;
    std::string sentence;
    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence))
    {
        tuple += ')';
        std::vector<int> metadata;
        std::istringstream iss(tuple);
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

        // Insert in the dictionary
        s.insert_sentence(metadata[0], metadata[1], metadata[2], metadata[3], sentence);
    }
    inputFile.close();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    int n_counts = 0;

    // search pattern Here ******* **********************

    ofstream output("Output_Src.txt");
    if (!output.is_open())
    {
        cout << "Error Unable to open Output file\n";
        exit(0);
    }
    string pattern = "gandhiji";
    output << "Output for pattern = " << pattern << " :\n";
    Node *head = s.search(pattern, n_counts);
    output << "We have a total of " << n_counts << " matching counts." << std::endl;
    cout << "We have a total of " << n_counts << " matching counts." << std::endl;
    print(head, n_counts);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - end);
    // std::cout << "Time taken by the process: " << duration.count() * 0.000001 << " seconds" << std::endl;
    // Print the matched sentences if needed
    // printBaseline(s.extract_baseline(head));

    // Clean up memory if necessary
    output.close();
    return 0;
}
