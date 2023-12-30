// Do NOT add any other includes
#include "search.h"

vector<int> suffixes(string str)
{
    vector<int> res(str.length());
    int sz = str.length();
    int var1 = 0, var_2 = sz - 1;
    res.back() = sz;

    for (int i = sz - 2; i >= 0; i--)
    {
        if (i > var_2 && res[i + sz - 1 - var1] < i - var_2)
            res[i] = res[i + sz - 1 - var1];
        else
        {
            if (i < var_2)
                var_2 = i;
            var1 = i;
            while (var_2 >= 0 && str[var_2] == str[var_2 + sz - 1 - var1])
                --var_2;
            res[i] = var1 - var_2;
        }
    }
    return res;
}

void HelpBm(string x, int m, std::vector<int> &vect_2)
{
    vector<int> Es = suffixes(x);

    int j = 0;

    for (int i = m - 1; i >= 0; --i)
    {
        if (Es[i] == i + 1)
        {
            for (; j < m - 1 - i; ++j)
            {
                if (vect_2[j] == m)
                    vect_2[j] = m - 1 - i;
            }
        }
    }
    for (int i = 0; i <= m - 2; ++i)
    {
        vect_2[m - 1 - Es[i]] = m - 1 - i;
    }
}

vector<int> Help_src(string &pattern, string &sentence)
{
    vector<int> res;
    vector<int> vect_1;
    int len = pattern.length();
    vect_1.assign(256, len);
    int n = sentence.length();
    for (int i = 0; i < len; i++)
    {
        if (pattern[i] >= 'A' && pattern[i] <= 'Z')
        {
            pattern[i] += 32;
        }
        vect_1[pattern[i]] = len - i - 1;
    }
    vect_1[pattern.back()] = len;
    vector<int> vect_2;
    vect_2.resize(len, len);
    HelpBm(pattern, len, vect_2);

    int j = 0;
    while (j <= n - len)
    {
        int i = len - 1;
        while (i >= 0 && (pattern[i] == sentence[i + j] || pattern[i] == sentence[i + j] + 32))
        {
            --i;
        }

        if (i < 0)
        {
            res.push_back(j);
            j += vect_2[0];
        }
        else
        {
            if (sentence[i + j] >= 'A' && sentence[i + j] <= 'Z')
                sentence[i + j] += 32;
            j += max(vect_2[i], vect_1[sentence[i + j]] - len + 1 + i);
        }
    }
    return res;
}
SearchEngine::SearchEngine()
{
    vector<Sentence> lib;
}

SearchEngine::~SearchEngine()
{
    // Implement your function here
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    lib.push_back({book_code, page, paragraph, sentence_no, sentence});
    return;
}

Node *SearchEngine::search(string pattern, int &n_matches)
{
    // cout << "Pattern:  " << pattern << "\n";
    Node *root = new Node();
    root->left = NULL;
    Node *rt = root;
    n_matches = 0;
    if (pattern == "")
    {
        delete root;
        return NULL;
    }
    for (size_t i = 0; i < lib.size(); i++)
    {
        if (pattern.size() > lib[i].s.size())
        {
            continue;
        }
        vector<int> offSet = Help_src(pattern, lib[i].s);
        // vector<int> offSet = {};
        for (size_t j = 0; j < offSet.size(); j++)
        {
            rt->book_code = lib[i].book_code;
            rt->page = lib[i].page;
            rt->paragraph = lib[i].paragraph;
            rt->sentence_no = lib[i].sentence_no;
            rt->offset = offSet[j];
            rt->right = new Node();
            rt->right->left = rt;
            rt = rt->right;
        }
        n_matches += offSet.size();
    }
    if (rt->left != NULL)
    {
        rt->left->right = NULL;
        delete rt;
    }
    else if (n_matches == 0)
    {
        delete rt;
        return NULL;
    }
    return root;
}
