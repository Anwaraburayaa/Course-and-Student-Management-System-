#pragma once


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
        T m_data;
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
    //helper recurrsive funtions for insert, find & delete:
    node* insert_aux(node* curr, int key, const T& data, bool& inserted);
    node* find_aux(node* curr, int key);
    node* remove_aux(node* curr, int key, bool& deleted);
//helper fuction max:
    int max2(int a, int b) const {
        return (a > b) ? a : b;
    }
public:

    AVLTree() : m_root(nullptr) {}
    int get_height(node* v);
    ~AVLTree() { delete m_root; }
    void update_height(node* v);
    int balance_factor(node* v);

    node* rotate_right(node* d);
    node* rotate_left(node* d);
    node* rotate_left_right(node* f);
    node* rotate_right_left(node* f);
    node* rebalance(node* v);


    node* find(int key);
    bool insert(int key, const T& data);
    bool remove(int key);

};

/*-----cotrs-----*/

template <class T>
int AVLTree<T>::get_height(node* v) {
    return (v == nullptr) ? 0 : v->m_height;
}
/*-----helper internal functions-----*/

template <class T>
void AVLTree<T>::update_height(node* v){
    v->m_height = 1 + max2(get_height(v->m_left_son), get_height(v->m_right_son));
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
        curr->m_right_son=insert_aux(curr->m_right_son,key,data, inserted);
    }
    //if key already exists we ruturn curr
    else {
        inserted=false;
        return curr; // <-- This return stops the function here.
    }
    ///now we update the tree height:
    update_height(curr); // These lines are correctly skipped on duplicate.
    return rebalance(curr);
}

template<class T>
typename AVLTree<T>::node* AVLTree<T>::find_aux(node* curr, int key) {
    if (curr == nullptr || curr->m_key == key) {
        return curr;
    }
    return (key < curr->m_key) ? find_aux(curr->m_left_son, key) : find_aux(curr->m_right_son, key);
}

/**
 * AVLTree<T>::remove_aux
 *
 * there is three cases:
 *
 * 1. Node has one child at most:
 * we delete the node, and its single child (or nullptr for a leaf) is returned to replace it.
 *
 * 2. Node has two children:
 * To maintain the BST property, the content (key and data) of the node to be deleted is replaced
 * with the content of its IN-ORDER SUCCESSOR (the node with the smallest key in the right subtree).
 * A second recursive call to remove_aux is then made on the right subtree to physically delete the successor.
 * After the recursive call, the current node proceeds with update_height and rebalance.
 */
template<class T>
typename AVLTree<T>::node* AVLTree<T>::remove_aux(node* curr, int key, bool& deleted) {
    // if key not found in this subtree
    if (curr == nullptr) {
        deleted = false;
        return nullptr;
    }

    if (key < curr->m_key) {
        curr->m_left_son = remove_aux(curr->m_left_son, key, deleted);
    }
    else if (key > curr->m_key) {
        curr->m_right_son = remove_aux(curr->m_right_son, key, deleted);
    }
    else {
        // Found the node to delete
        deleted = true;

        //first case: node with at most one child
        //--- node is a leaf (עלה)---
        if (curr->m_left_son == nullptr && curr->m_right_son == nullptr) {
            delete curr;
            return nullptr;
        }
        // ---- node has only right child ----
        else if (curr->m_left_son == nullptr && curr->m_right_son != nullptr) {
            node* child = curr->m_right_son;
            curr->m_right_son = nullptr;
            delete curr;
            return child;
        }
        // ---- node has only left child ----
        else if (curr->m_right_son == nullptr && curr->m_left_son != nullptr) {
            node* child = curr->m_left_son;
            curr->m_left_son = nullptr;
            delete curr;
            return child;
        }
        // second case: node with two children
        node* inorderSuccessor = curr->m_right_son;
        while (inorderSuccessor->m_left_son != nullptr) {
            inorderSuccessor = inorderSuccessor->m_left_son;
        }
        curr->m_key = inorderSuccessor->m_key;
        curr->m_data = inorderSuccessor->m_data;
        bool successorWasDeleted = false;
        curr->m_right_son = remove_aux(curr->m_right_son, inorderSuccessor->m_key, successorWasDeleted);
    }

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
    f->m_left_son = rotate_left(f->m_left_son);
    return rotate_right(f);
}

template <class T>
typename AVLTree<T>::node* AVLTree<T>::rotate_right_left(node* f) {
    f->m_right_son = rotate_right(f->m_right_son);
    return rotate_left(f);
}

// v is the node that was inserted or removed -> the root of the subtree we need to rotate
template <class T>
typename AVLTree<T>::node* AVLTree<T>::rebalance(node* v) {
    update_height(v);
    int curr_BF = balance_factor(v);
    if (curr_BF > 1) {
        if (v->m_left_son && balance_factor(v->m_left_son) < 0) {  //check LEFT son
            return rotate_left_right(v); //(LR) case
        }
        return rotate_right(v); //(LL) case
    }
    if (curr_BF < -1) {
        if (v->m_right_son && balance_factor(v->m_right_son) > 0) {  //check RIGHT son and compare > 0
            return rotate_right_left(v); //(RL) case
        }
        return rotate_left(v); // (RR) case
    }
    return v; //|BF(v)| <= 1
}


/*-----Tree operations-----*/
template<class T>
bool AVLTree<T>::insert(int key, const T &data) {
    bool inserted=false;
    m_root= insert_aux(m_root, key, data, inserted);
    return inserted;
}
template<class T>
typename AVLTree<T>::node* AVLTree<T>::find(int key) {
    return find_aux(m_root, key);
}

template<class T>
bool AVLTree<T>::remove(int key) {
    bool deleted = false;
    m_root = remove_aux(m_root, key, deleted);
    return deleted;
}









