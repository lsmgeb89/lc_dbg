#ifndef LC_DBG_H_
#define LC_DBG_H_

#ifdef __GNUC__
#include <bits/stdc++.h>
#else
#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <cstddef>
#include <deque>
#include <forward_list>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#endif

using namespace std;

/*
 * Definitions
 */

// Definition for singly-linked list
struct ListNode {
  int val;
  ListNode *next;

  ListNode(int x) : val(x), next(nullptr) {}
};

// Definition for singly-linked list with a random pointer
struct RandomListNode {
  int label;
  RandomListNode *next;
  RandomListNode *random;

  RandomListNode(int x) : label(x), next(nullptr), random(nullptr) {}
};

// Definition for binary tree node
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Definition for undirected graph
struct UndirectedGraphNode {
  int label;
  vector<UndirectedGraphNode *> neighbors;

  UndirectedGraphNode(int x) : label(x) {};
};

/*
 * Helper Funtions
 */

// Function for creating a singly-linked list
template<typename NodeType>
static NodeType* MakeList(const vector<int> &nums) {
  NodeType dummy(0);
  NodeType* iter(&dummy);

  for (auto &num : nums) {
    iter->next = new NodeType(num);
    iter = iter->next;
  }

  return dummy.next;
}

// Function for printing a singly-linked list
static string ListToString(ListNode *head) {
  stringstream ss;

  while (head) {
    ss << " " << head->val;
    head = head->next;
  }

  return ss.str();
}

// Function for printing a singly-linked list with a random pointer
static string RandomListToString(RandomListNode *head) {
  stringstream ss;

  while (head) {
    ss << " label = " << head->label;
    if (head->random) { ss << ", random = " << head->random->label; }
    ss << "\n";
    head = head->next;
  }

  return ss.str();
}

// Function for destroying a singly-linked list
template<typename NodeType>
static void DestroyList(NodeType *head) {
  NodeType *tmp(head);

  while (head) {
    tmp = head;
    head = head->next;
    delete tmp;
  }
}

// Function for deserializing a binary tree
static TreeNode* Deserialize(string data) {
  size_t begin = 0;
  size_t end = 0;
  string val_str;

  TreeNode *root = nullptr;
  TreeNode *node = nullptr;
  queue<TreeNode *> nodes;
  bool left_child = true;

  // remove all spaces
  data.erase(remove_if(data.begin(), data.end(), isspace), data.end());

  if (data.empty() || data.front() != '[' || data.back() != ']') {
    return nullptr;
  } else {
    data.erase(data.begin());
    data.pop_back();
    data += ",";
  }
  
  while ((end = data.find(",", begin)) != string::npos) {
    val_str = data.substr(begin, end - begin);
    begin = end + 1;

    if (val_str.empty() || val_str == "null") {
      node = nullptr;
    } else {
      node = new TreeNode(stoi(val_str));
    }

    if (!nodes.empty()) {
      if (left_child) {
        nodes.front()->left = node;
      } else {
        nodes.front()->right = node;
        nodes.pop();
      }
      left_child = !left_child;
    } else {
      root = node;
    }

    if (node) { nodes.push(node); }
  }

  return root;
}

#endif // LC_DBG_H_
