#pragma once
#include <vector>
#include <string>
#include <list>

class RedBlack {
private:
    enum COLORS {RED, BLACK};
    struct TreeNode {
        std::string name;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
        int color;
        //--------------Constructors-------------//
        TreeNode()
        {
            //val = 0;
            name = "";
            left = nullptr;
            right = nullptr;
            parent = nullptr;
            int color = RED;
        }
        TreeNode(std::string name)
        {
            //val = key
            this->name = name;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
            int color = RED;
        }
        void flip()
        {
            if (color == BLACK) {
                color = RED;
            }
            else {
                color = BLACK;
            }
        }
    };
    TreeNode* root;
    int numItems;
    std::list<TreeNode*> allNodes;
    TreeNode* rotateLeft(TreeNode* node);
    TreeNode* rotateRight(TreeNode* node);
    TreeNode* balanceTree(TreeNode* root);

public:
    RedBlack();
    ~RedBlack();
    void insert(std::string key);
    bool find(std::string name);
    std::string randomWord(int goTo);
};

