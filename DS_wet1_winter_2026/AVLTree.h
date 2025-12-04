#pragma once

#include <math.h>

//TODO L haya
//TODO R haya
//TODO LR haya
//TODO RR haya
//TODO LL haya
//TODO RL haya
//TODO node stuff anwar
//TODO big three of tree anwar
//TODO insert anwar
//TODO remove anwar
//TODO find anwar


template<class T>
class AVLTree {
private:
    node* root;
    struct node
    {
        int m_key;
        int m_height;
        void* m_data;
        struct node* m_left_son;
        struct node* m_right_son;

        node(const T& data, int key)  : m_key(key), m_height(1),m_data(data), m_left_son(nullptr),
        m_right_son(nullptr){}

        ~node() {
            delete m_left_son;
            delete m_right_son;
        }
    };

public:

    AVLTree() : root(nullptr) {}
    int get_height(node* v);

    void update_height(node* v);
    int balance_factor(node* v);

    void rotate_left(node* v);
    void rotate_right(node* v);

    node* find(int key);
    void insert();
    void remove(int key);

};

/*-----cotrs-----*/

template <class T>
int AVLTree<T>::get_height(node* v) {
    return (v == nullptr) ? 0 : v->height;
}

/*-----helper internal functions-----*/

template <class T>
void AVLTree<T>::update_height(node* v){
    v->height = 1 + max(height(v->left), height(v->right));
}

template <class T>
int AVLTree<T>::balance_factor(node* v) {
    return get_height(v->left_son) - get_height(v->right_son);
}

template <class T>
void AVLTree<T>::rotate_left(node* v) {

}

template <class T>
void AVLTree<T>::rotate_right(node* v) {
}

