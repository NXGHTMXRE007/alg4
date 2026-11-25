
#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

// 1. Проверка HTML-тегов
bool checkHTML(string s) {
    stack<string> st;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] != '<') continue;

        int j = s.find('>', i);
        if (j == string::npos) return false;

        string tag = s.substr(i + 1, j - i - 1);
        if (tag.empty() || tag[0] == '!' || tag[0] == '?') {
            i = j;
            continue;
        }

        bool close = tag[0] == '/';
        bool self = tag.back() == '/';

        if (close) tag.erase(0, 1);
        if (self) tag.pop_back();

        string name = tag.substr(0, tag.find_first_of(" \t"));

        if (name == "br" || name == "img" || name == "hr" ||
            name == "input" || name == "meta" || name == "link")
            self = true;

        if (close) {
            if (st.empty() || st.top() != name) return false;
            st.pop();
        }
        else if (!self) {
            st.push(name);
        }

        i = j;
    }

    return st.empty();
}

// 2. Удаление четных чисел из очереди
void removeEven(queue<int>& q) {
    int n = q.size();

    while (n--) {
        int x = q.front();
        q.pop();
        if (x % 2 != 0) q.push(x);
    }
}

// 3. Проверка палиндрома
bool palindrome(string s) {
    deque<char> d;

    for (unsigned char c : s) {
        if (isalnum(c))
            d.push_back(tolower(c));
    }

    while (d.size() > 1) {
        if (d.front() != d.back())
            return false;

        d.pop_front();
        d.pop_back();
    }

    return true;
}

// 4. Приоритетная очередь
void priorityQueueExample() {
    priority_queue<int> pq;

    pq.push(5);
    pq.push(2);
    pq.push(10);
    pq.push(7);

    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
}

int main() {
    cout << "HTML: "
        << (checkHTML("<html><body></body></html>") ? "OK" : "Error")
        << endl;

    queue<int> q;
    for (int x : {1, 2, 3, 4, 5, 6}) q.push(x);

    removeEven(q);
    cout << "Queue: ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }

    cout << "\nPalindrome: "
        << (palindrome("А роза упала на лапу Азора") ? "Yes" : "No")
        << endl;

    cout << "Priority queue: ";
    priorityQueueExample();

    return 0;
}
