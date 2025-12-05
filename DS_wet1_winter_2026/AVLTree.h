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
    node* m_root;
    //helper recurrsive funtions for insert/find/delete:
    node* insert_aux(node* curr, int key, const T& data, bool& inserted);
//helper fuction max:
    int max2(int a, int b) const {
        return (a > b) ? a : b;
    }
public:

    AVLTree() : m_root(nullptr) {}
    int get_height(node* v);

    void update_height(node* v);
    int balance_factor(node* v);

    node* rotate_right(node* d);
    node* rotate_left(node* d);
    node* rotate_left_right(node* f);
    node* rotate_right_left(node* f);
    node* rebalance(node* v);


    node* find(int key);
    bool insert(int key, const T& data);
    void remove(int key);

};

/*-----cotrs-----*/

template <class T>
int AVLTree<T>::get_height(node* v) {
    return (v == nullptr) ? 0 : v->m_height;
}
/*-----helper internal functions-----*/

template <class T>
void AVLTree<T>::update_height(node* v){
    v->height = 1 + max2(get_height(v->m_left_son), get_height(v->m_right_son));
}

template <class T>
int AVLTree<T>::balance_factor(node* v) {
    return get_height(v->m_left_son) - get_height(v->m_right_son);
}
template<class T>
typename AVLTree<T>::node *AVLTree<T>::insert_aux(node *curr, int key, const T &data, bool &inserted) {
    //if the tree is empty we insert the new nood at the root
    if (curr==nullptr) {
        inserted=true;
        return new node(data,key);
    }
    //if the tree is not empty we do the presses recursivly tell we find it place
    //we first compare the key to the root
    if (key< curr->m_key) {
        curr->m_left_son=insert_aux(curr->m_left_son,key,data, inserted);
    }
    else if (key>curr->m_key) {
        curr->m_right_son_son=insert_aux(curr->m_right_son,key,data, inserted);
    }
    //if key already exists we ruturn curr
    else {
        inserted=false;
        return curr;
    }
    ///now we update the tree height:
    update_height(curr);
    return rebalance(curr);
}





/*-----rotations----*/

// Performs a single Right Rotation (LL case) by making the left child (b) the new parent of d
//following the slides names for the nodes
//b should have bf of +1
//check for nulls and catching mechanisms (here or in application later)
template <class T>
typename AVLTree<T>::node* AVLTree<T>::rotate_right(node* d) {
    node* b_left_sub_tree = d->m_left_son;
    d->m_left_son = b_left_sub_tree->m_right_son;
    b_left_sub_tree->m_right_son = d;

    update_height(d);
    update_height(b_left_sub_tree);

    return b_left_sub_tree;
}

// Performs a single Left Rotation (RR case) by making the right child (b) the new parent of d
template <class T>
typename AVLTree<T>::node* AVLTree<T>::rotate_left(node* d) {
    node* b_right_sub_tree = d->m_right_son;
    d->m_right_son = b_right_sub_tree->m_left_son;
    b_right_sub_tree->m_left_son = d;

    update_height(d);
    update_height(b_right_sub_tree);

    return b_right_sub_tree;

}

template <class T>
typename AVLTree<T>::node* AVLTree<T>::rotate_left_right(node* f) {
    node* b_left_sub_tree = f->m_left_son;
    f->m_left_son = rotate_left(b_left_sub_tree);
    node* d_new_root = rotate_right(f);
    return d_new_root;
}

template <class T>
typename AVLTree<T>::node* AVLTree<T>::rotate_right_left(node* f) {
}

template <class T>
typename AVLTree<T>::node* AVLTree<T>::rebalance(node* v) {
}


/*-----Tree operations-----*/
template<class T>
bool AVLTree<T>::insert(int key, const T &data) {
    bool inserted=false;
    m_root= insert_aux(m_root, key, data, inserted);
    return inserted;
}









