# Search Engine and Dictionary Implementation

This repository contains the implementation of a search engine and a word count dictionary as part of an assignment. The assignment consists of two main parts: building a dictionary to count word occurrences in a given corpus and implementing a search engine to find patterns in the text.

## Table of Contents
- [Dictionary Implementation](#dictionary-implementation)
  - [Dict Class](#dict-class)
- [Search Engine Implementation](#search-engine-implementation)
  - [SearchEngine Class](#searchengine-class)
- [How to Use](#how-to-use)
- [File Structure](#file-structure)
- [Testing](#testing)
- [Contributing](#contributing)

## Dictionary Implementation

### Dict Class

The `Dict` class is responsible for counting the occurrences of words in a given document. The key functions are:

- **`Dict()`:** Create a Dict instance. Initialize data structures for storing word counts.
- **`void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string s)`:** Split the given sentence into words and increment word counts.
- **`int get_word_count(string word)`:** Given a word, return its count in the document (case-insensitive).
- **`void dump_dictionary(string filename)`:** Dump the dictionary into a file, with each line containing a word and its count.
- **`~Dict()`:** Destroy the Dict instance.

### Data Structure used:
- **AVL Tree + Hash Maps:** : The primary data structure is a `hash table`, ensuring quick access to word counts. To mitigate potential collisions, a chaining mechanism is integrated, where each node in the hash table hosts an AVL (Adelson-Velsky and Landis) tree.<br>
- This innovative approach leverages the speed of hash table lookups while significantly reducing collision-related concerns through the use of AVL trees, resulting in a robust and efficient word counting mechanism.

## Search Engine Implementation

### SearchEngine Class

The `SearchEngine` class leverages the Boyer-Moore algorithm, a powerful string searching technique, to efficiently locate patterns within the document. This advanced algorithm enhances the speed of the search process, making it well-suited for practical applications.

#### Key Features:

- **`SearchEngine()`:** Creates a `SearchEngine` instance and initializes the necessary data structures for pattern search, incorporating the Boyer-Moore algorithm.

- **`void insert_sentence(int book_code, int page, paragraph, int sentence_no, string s)`:** Pre-processes the provided sentence to facilitate quick pattern searches using the Boyer-Moore algorithm.

- **`Node* search(string pattern, int &n_matches)`:** Executes the Boyer-Moore algorithm to generate a linked list of nodes, each containing detailed information about pattern matches in the text. The nodes include the book code, page number, paragraph, sentence number, and the starting offset relative to the beginning of the sentence. The `n_matches` variable holds the count of matches.

- **`~SearchEngine()`:** Destroys the `SearchEngine` instance, ensuring proper cleanup.

By incorporating the Boyer-Moore algorithm, renowned for its efficiency in string searching, the `SearchEngine` class delivers a high-performance solution for locating patterns within the document. This choice of algorithm significantly enhances the search speed, making it a robust and effective tool for pattern retrieval.

## Reqiurnments:
1. g++ or any c++ compiler.
2. Using Linux is recommanded.

## How to Use

1. Clone the repository: `git clone https://github.com/yourusername/search-engine.git`
2. type `make task=<Task No.>` for compile specific task file {Task no.= 1 for Dictionary, 2 for Search Engine.}
3. now run `make run task=<Task No.>` for executing the file.
P.S : Before make sure you initialize all the txt files paths & search texts in corresponding main file.

## File Structure
search-engine/
│
├── dict.h
├── dict.cpp
├── search.h
├── search.cpp
├── node.h
├── node.cpp
├── main_dict.cpp
├── main_src.cpp
└── README.md

## Testing
I have provided a sample Input `.txt` file in the txtfiles. You can also generate similar text files and use the tool.
For initial testing, just run the `make` commands.

## Contributing

If you'd like to contribute to this project, please follow the standard GitHub flow: fork the repository, create a branch, make changes, and submit a pull request.

#### Follow Up
If you find this stuff intersting please give a star to it :)