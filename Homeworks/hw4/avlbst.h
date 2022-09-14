#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
    virtual void insertHelper(const Key& key, const Value& val, AVLNode<Key, Value>* curr);
    void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* child);
    void removeFix(AVLNode<Key, Value>* n, char diff);
    void rotateRight(AVLNode<Key, Value>* grand);
    void rotateLeft(AVLNode<Key, Value>* grand);
    // Add helper functions here


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    Key newKey = new_item.first;
    Value newVal = new_item.second;
    if (this->empty())
    {
        this->root_ = new AVLNode<Key, Value>(newKey, newVal, NULL);
        return;
    }
    if (this->find(newKey) != this->end())
    {
        this->find(newKey).current_->setValue(newVal);
    }
    else 
    {
        insertHelper(newKey, newVal, static_cast<AVLNode<Key,Value>*>(this->root_));
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertHelper(const Key& key, const Value& val, AVLNode<Key, Value>* curr)
{
    if (key > curr->getKey())
    {
        if (curr->getRight() == NULL)
        {
            curr->Node<Key, Value>::setRight(new AVLNode<Key, Value>(key, val, curr));
            curr->updateBalance(1);
            if (curr->getBalance() == 1)
            {
                insertFix(curr, curr->getRight());
            }
        }
        else
        {
            insertHelper(key, val, curr->getRight());
        }
    }
    else if (key < curr->getKey())
    {
        if(curr->getLeft() == NULL)
        {
            curr->setLeft(new AVLNode<Key, Value>(key, val, curr));
            curr->updateBalance(-1);
            if (curr->getBalance() == -1)
            {
                insertFix(curr, curr->getLeft());
            }
        }
        else
        {
            insertHelper(key, val, curr->getLeft());
        }
    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* child)
{
    if (parent == NULL || parent->getParent() == NULL)
    {
        return;
    }
    AVLNode<Key, Value>* grand = parent->getParent();
    if (grand->getLeft() == parent)
    {
        grand->updateBalance(-1);
        if (grand->getBalance() == 0)
        {
            return;
        }
        else if (grand->getBalance() == -1)
        {
            insertFix(grand, parent);
        }
        else if (grand->getBalance() == -2)
        {
            if (child == parent->getLeft())
            {
                rotateRight(grand);
                grand->setBalance(0);
                parent->setBalance(0);
            }
            else
            {
                rotateLeft(parent);
                rotateRight(grand);
                if (child->getBalance() == -1)
                {
                    child->setBalance(0);
                    parent->setBalance(0);
                    grand->setBalance(1);
                }
                else if (child->getBalance() == 0)
                {
                    parent->setBalance(0);
                    grand->setBalance(0);
                }
                else if (child->getBalance() == 1)
                {
                    child->setBalance(0);
                    parent->setBalance(-1);
                    grand->setBalance(0);
                }
            }
        }
    }
    else
    {
        grand->updateBalance(1);
        if (grand->getBalance() == 0)
        {
            return;
        }
        else if (grand->getBalance() == 1)
        {
            insertFix(grand, parent);
        }
        else if (grand->getBalance() == 2)
        {
            if (child == parent->getRight())
            {
                rotateLeft(grand);
                grand->setBalance(0);
                parent->setBalance(0);

            }
            else
            {
                rotateRight(parent);
                rotateLeft(grand);
                if (child->getBalance() == 1)
                {
                    child->setBalance(0);
                    parent->setBalance(0);
                    grand->setBalance(-1);
                }
                else if (child->getBalance() == 0)
                {
                    parent->setBalance(0);
                    grand->setBalance(0);
                }
                else if (child->getBalance() == -1)
                {
                    child->setBalance(0);
                    parent->setBalance(1);
                    grand->setBalance(0);
                }
            }
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    AVLNode<Key, Value>* n = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));
    if (n == NULL)
    {
        return;
    }
    if (n->getLeft() != NULL && n->getRight() != NULL)
    {
        nodeSwap(n, static_cast<AVLNode<Key,Value>*>(this->predecessor(n)));
    }
    AVLNode<Key, Value>* p = n->getParent();
    char diff = 0;
    if (p != NULL)
    {
        if (p->getLeft() == n)
        {
            diff = 1;
            if (n->getLeft() == NULL && n->getRight() == NULL)
            {
                p->setLeft(NULL);
            }
            else if (n->getLeft() == NULL)
            {
                p->setLeft(n->getRight());
                n->getRight()->setParent(p);
            }
            else
            {
                p->setLeft(n->getLeft());
                n->getLeft()->setParent(p);
            }
        }
        else
        {
            diff = -1;
            if (n->getLeft() == NULL && n->getRight() == NULL)
            {
                p->setRight(NULL);
            }
            else if (n->getLeft() == NULL)
            {
                p->setRight(n->getRight());
                n->getRight()->setParent(p);
            }
            else
            {
                p->setRight(n->getLeft());
                n->getLeft()->setParent(p);
            }
        }
        delete n;
        removeFix(p, diff);
    }
    else
    {
        if (n->getLeft() == NULL && n->getRight() == NULL)
        {
            this->root_ = NULL;
            delete n;
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>:: removeFix(AVLNode<Key, Value>* n, char diff)
{
    if (n == NULL)
    {
        return;
    }
    AVLNode<Key, Value>* p = n->getParent();
    char ndiff = 0;
    if (p != NULL)
    {
        if (n == p->getLeft())
        {
            ndiff = 1;
        }
        else
        {
            ndiff = -1;
        }
    }
    if (diff == -1)
    {
        if (n->getBalance() + diff == -2)
        {
            AVLNode<Key, Value>* c = n->getLeft();
            if (c->getBalance() == -1)
            {
                rotateRight(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p, ndiff);
            }
            else if (c->getBalance() == 0)
            {
                rotateRight(n);
                n->setBalance(-1);
                c->setBalance(1);
            }
            else if (c->getBalance() == 1)
            {
                AVLNode<Key, Value>* g = c->getRight();
                rotateLeft(c);
                rotateRight(n);
                if (g->getBalance() == 1)
                {
                    c->setBalance(-1);
                    n->setBalance(0);
                    g->setBalance(0);
                }
                else if (g->getBalance() == 0)
                {
                    c->setBalance(0);
                    n->setBalance(0);
                    g->setBalance(0);
                }
                else if (g->getBalance() == -1)
                {
                    c->setBalance(0);
                    n->setBalance(1);
                    g->setBalance(0);
                }
                removeFix(p, ndiff);
            }
        }
        else if (n->getBalance() + diff == -1)
        {
            n->setBalance(-1);
        }
        else if (n->getBalance() + diff == 0)
        {
            n->setBalance(0);
            removeFix(p, ndiff);
        }
    }
    else if (diff == 1)
    {
        if (n->getBalance() + diff == 2)
        {
            AVLNode<Key, Value>* c = n->getRight();
            if (c->getBalance() == 1)
            {
                rotateLeft(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p, ndiff);
            }
            else if (c->getBalance() == 0)
            {
                rotateLeft(n);
                n->setBalance(1);
                c->setBalance(-1);
            }
            else if (c->getBalance() == -1)
            {
                AVLNode<Key, Value>* g = c->getLeft();
                rotateRight(c);
                rotateLeft(n);
                if (g->getBalance() == -1)
                {
                    c->setBalance(1);
                    n->setBalance(0);
                    g->setBalance(0);
                }
                else if (g->getBalance() == 0)
                {
                    c->setBalance(0);
                    n->setBalance(0);
                    g->setBalance(0);
                }
                else if (g->getBalance() == 1)
                {
                    c->setBalance(0);
                    n->setBalance(-1);
                    g->setBalance(0);
                }
                removeFix(p, ndiff);
            }
        }
        else if (n->getBalance() + diff == 1)
        {
            n->setBalance(1);
        }
        else if (n->getBalance() + diff == 0)
        {
            n->setBalance(0);
            removeFix(p, ndiff);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>:: rotateRight(AVLNode<Key, Value>* grand)
{
    AVLNode<Key, Value>* ggrand = grand->getParent();
    AVLNode<Key, Value>* parent = grand->getLeft();
    AVLNode<Key, Value>* rChild = parent->getRight();
    if (ggrand != NULL)
    {
        if (ggrand->getRight() == grand)
        {
            ggrand->Node<Key,Value>::setRight(parent);
        }
        else
        {
            ggrand->Node<Key,Value>::setLeft(parent);
        }
    }
    parent->Node<Key,Value>::setParent(ggrand);
    grand->Node<Key,Value>::setLeft(rChild);
    if (rChild != NULL)
    {
        rChild->Node<Key,Value>::setParent(grand);
    }
    grand->Node<Key,Value>::setParent(parent);
    parent->Node<Key,Value>::setRight(grand);
    if (this->root_ == grand)
    {
        this->root_ = parent;
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>:: rotateLeft(AVLNode<Key, Value>* grand)
{
    AVLNode<Key, Value>* ggrand = grand->getParent();
    AVLNode<Key, Value>* parent = grand->getRight();
    AVLNode<Key, Value>* lChild = parent->getLeft();
    if (ggrand != NULL)
    {
        if (ggrand->getLeft() == grand)
        {
            ggrand->Node<Key,Value>::setLeft(parent);
        }
        else
        {
            ggrand->Node<Key,Value>::setRight(parent);
        }
    }
    parent->Node<Key,Value>::setParent(ggrand);
    grand->Node<Key,Value>::setRight(lChild);
    if (lChild != NULL)
    {
        lChild->Node<Key,Value>::setParent(grand);
    }
    grand->Node<Key,Value>::setParent(parent);
    parent->Node<Key,Value>::setLeft(grand);
    if (this->root_ == grand)
    {
        this->root_ = parent;
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
