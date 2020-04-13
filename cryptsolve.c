// CPP program for solving cryptographic puzzles
#include <bits/stdc++.h>
using namespace std;

// vector stores 1 corresponding to index
// number which is already assigned
// to any char, otherwise stores 0
vector<int> use(10);

// structure to store char and its corresponding integer
struct node
{
    char c;
    int digit;
};

// function check for correct solution
int check(node* nodeArr, const int count, string s1,
                               string s2, string s3)
{
    int val1 = 0, val2 = 0, val3 = 0, m = 1, j, i;

    // calculate number corresponding to first string
    for (i = s1.length() - 1; i >= 0; i--)
    {
        char ch = s1[i];
        for (j = 0; j < count; j++)
            if (nodeArr[j].c == ch)
                break;

        val1 += m * nodeArr[j].v;
        m *= 10;
    }
    m = 1;
