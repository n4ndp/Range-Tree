#pragma once
#include <iostream>
#include <vector>
#include <memory>

template <
    typename K,
    typename V>
class AVLTree {
    using k__ptr = std::unique_ptr<K>;
    //using v__ptr = std::unique_ptr<V>;

    struct Node {
        k__ptr key;
        //v__ptr value;

        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        int height;

        Node(K key) : key(std::make_unique<K>(key)), left(nullptr), right(nullptr), height(1) {}
    };

    std::unique_ptr<Node> root;

    int get_height(std::unique_ptr<Node>& node) {
        return node ? node->height : 0;
    }

    int get_balance(std::unique_ptr<Node>& node) {
        // return the difference between the height of the left and right subtrees
        return node ? this->get_height(node->left) - this->get_height(node->right) : 0;
    }

    void update_height(std::unique_ptr<Node>& node) {
        // update the height of the node based on the height of its children
        node->height = 1 + std::max(this->get_height(node->left), this->get_height(node->right));
    }

    void rotate_left(std::unique_ptr<Node>& node) {
        std::unique_ptr<Node> right = std::move(node->right);
        node->right = std::move(right->left);
        right->left = std::move(node);

        this->update_height(node);
        this->update_height(right);

        node = std::move(right);
    }

    void rotate_right(std::unique_ptr<Node>& node) {
        std::unique_ptr<Node> left = std::move(node->left);
        node->left = std::move(left->right);
        left->right = std::move(node);

        this->update_height(node);
        this->update_height(left);

        node = std::move(left);
    }

    void balance(std::unique_ptr<Node>& node) {
        int balance = this->get_balance(node);

        if (balance > 1) {
            if (this->get_balance(node->left) < 0) {
                this->rotate_left(node->left);
            }
            this->rotate_right(node);
        } else if (balance < -1) {
            if (this->get_balance(node->right) > 0) {
                this->rotate_right(node->right);
            }
            this->rotate_left(node);
        }
    }
    
};