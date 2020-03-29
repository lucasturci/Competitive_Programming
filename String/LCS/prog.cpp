// Longest Common Subsequence of two strings
// The idea can be generalized to work with three or more, if constraints are low

// ITERATIVE WAY
// build matrix in which rows represent characters of the first string and columns letters of the second string
// A common subsequence is a set of positions of this matrix such that coordinates of the positions have same characters
// on rows and columns, and also rows are strictly increasing and columns are strictly increasing
// In this DP you just calculate the best answer for the upper left rectangle
int lcs(string & s, string & t) {
    int n = s.size(), m = t.size();
    vector<vector<int> > mat(n, vector<int>(m));

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            mat[i][j] = max({
                i? mat[i-1][j] : 0, 
                j? mat[i][j-1] : 0, 
                (i and j? mat[i-1][j-1] : 0) + (s[i] == t[j])
            });
        }
    }
    return mat[n-1][m-1];
}


// RECURSIVE WAY
// s and t are the global string variables
// i and j are the indices of the strings
// recurrency: you can ignore one character of the first string or ignore one character of the second string. 
// If both are equal, you can sum 1 to the answer
int memo[1007][1007];
int lcs2(int i, int j) {
    if(i == s.size() or j == t.size()) return 0;
    int & st = memo[i][j];
    if(st == -1) {
        if(s[i] == t[j]) st = max(st, lcs2(i+1, j+1) + 1);
        st = max(st, lcs2(i+1, j));
        st = max(st, lcs2(i, j+1));
    }
    return st;
}