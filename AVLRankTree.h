
//
// Created by Tom Guy on 01/01/2022.
//
#include <cmath>
#include <cstdio>
#include <exception>
#include <memory>
#include <iostream>

#ifndef AVLRANKTREE_H_
#define AVLRANKTREE_H_

namespace wet2_dast{

    const int NOT_EXIST = -1;

    template<class T>
    class AVLRankTree
    {

    private:
        class Node
        {
            friend class AVLRankTree<T>;
            T* value;
            Node *father;
            Node *right_son;
            Node *left_son;
            int height;
            int rank; // the size of the tree that this node is his root.

            explicit Node(T* val = nullptr, Node *father = nullptr) : value(val), father(father), right_son(nullptr),
                                                                      left_son(nullptr),
                                                                      height(0), rank(1)
            {
                left_son=nullptr;
                right_son=nullptr;
            }
            ~Node()
            {

                father = nullptr;
                right_son = nullptr;
                left_son = nullptr;
                delete value;
                value=nullptr;
            }

            bool operator==(Node *other)
            {
                return (*value == *(other->value));
            }

            bool operator<=(Node *other)
            {
                return (*value <= *(other->value));
            }

            void Tree_Creator_AUX(int *size_of_tree, int height_of_tree,int* remainder);

            int GetHeight(Node* node);

        };

        Node *root; //belongs to AVLRankTree
        int size;
        //@param loc and father_of_loc are getting changed in this function according to the situation.
        //@ver - the current vertex we are looking at.
        //@val - the value we are looking for.

        T *find_in_tree(Node *ver, const T &val, Node **loc, Node **father_of_loc)
        {
            if (*(ver->value) == val) //if we're in the location
            {

                *loc = ver; // mark this as the location.
                *father_of_loc = ver->father;//mark father.
                return ver->value; // return us the value.
            }
            //if left son doesn't exist , and the value we look for is lesser than the current vertex(meaning he doesn't;t exist in the tree according ot convention)
            //or alternatively ,right son doesn't exist and the current value we're looking for is larger than the current vertex value(meaning we want to go right according to convention,meaning he doesn't exist).
            if ((!ver->left_son && val <= *(ver->value)) || (!ver->right_son && *(ver->value) <= val))
            {
                *loc = nullptr; //the place doesn't exist.
                *father_of_loc = ver; //mark him as his father.
                return nullptr; //return nullptr,we couldn't find him
            }

            if (val <= *(ver->value) && ver->left_son) //if the value we are looking for is lesser than the current vertex ,go left.
            {
                return find_in_tree(ver->left_son, val, loc, father_of_loc);
            } else if(*(ver->value) <= val && ver->right_son)
            {
                //else go right,because he's larger than him.
                return find_in_tree(ver->right_son, val, loc, father_of_loc);
            }
            *loc = nullptr; //the place doesn't exist.
            *father_of_loc = ver; //mark him as his father.
            return nullptr; //return nullptr,we couldn't find him
        }

        int getHeight(Node *ver);
        static int getRank(Node* ver);
        int balance(Node *ver);

        Node *easyCaseRemove(Node *loc, bool &easy_case);

        void rootCaseRemove();

        void swapWithNext(Node *loc, Node** place);

        void checkForRolls(Node *start);

        void ll_roll(Node *first_ubl);

        void lr_roll(Node *first_ubl);

        void rl_roll(Node *first_ubl);

        void rr_roll(Node *first_ubl);

        void inorderHelper(T* values[], int* index, Node *ver, int max_size);

        void inorderIn(T* values[] , int &index, Node *ver);

        void createEmptyTree(int size_of_tree);

        static void postOrderDelete(Node* ver, bool delete_values);

        int findIndex(Node* ver) const;

        Node* ClosestFromAbove(T* value) const;

        Node* ClosestFromBelow(T *value) const;

    public:
        friend void combineTrees(AVLRankTree<T> &to_delete, AVLRankTree<T>& to_insert)
        {
            T** array_to_insert=to_insert.inorderOut(to_insert.size);
            T** array_to_delete = to_delete.inorderOut(to_delete.size);
            T** all_players = new T*[to_insert.size + to_delete.size];
            int i = 0, j = 0, k;
            for (k = 0; k < to_insert.size + to_delete.size; k++)
            {
                if (i==to_insert.size || j==to_delete.size) break;
                if (*(array_to_delete[j]) == *(array_to_insert[i]))
                {
                    delete[] array_to_delete;
                    delete[] array_to_insert;
                    delete[] all_players;
                    throw AVLRankTree<T>::ItemInBothTrees();
                }
                if (*(array_to_insert[i]) <= *(array_to_delete[j]))
                {
                    all_players[k] = array_to_insert[i++];
                    continue;
                }
                if (*(array_to_delete[j]) <= *(array_to_insert[i]))
                {
                    all_players[k] = array_to_delete[j++];
                    continue;
                }
            }
            for (; i < to_insert.size&&k<to_insert.size+to_delete.size; i++)
            {
                all_players[k++] = array_to_insert[i];

            }
            for (; j < to_delete.size&&k<to_insert.size+to_delete.size; j++)
            {
                if(k<to_insert.size+to_delete.size) {
                    all_players[k++] = array_to_delete[j];
                }
            }
            int full_size = to_delete.size + to_insert.size;
            delete[] array_to_delete;
            delete[] array_to_insert;
            to_insert.createEmptyTree(full_size);
            int index = 0;
            to_insert.inorderIn(all_players, index ,to_insert.root);
            to_insert.size = full_size;
            delete[] all_players;
            T** empty_values = new T*[to_delete.size];
            for(j=0; j<to_delete.size; j++)
            {
                empty_values[j] = nullptr;
            }
            index = 0;
            to_delete.inorderIn(empty_values, index, to_delete.root);
            delete[] empty_values;
        }
        int getSize() const;
        AVLRankTree() : size(0)
        {
            root=nullptr;
        }

        AVLRankTree(const AVLRankTree<T> &other) = delete;
        ~AVLRankTree()
        {
            postOrderDelete(root, true);
        }

        AVLRankTree &operator=(const AVLRankTree<T> &other) = delete;

        T* find(const T &val);

        void insert(T &val);

        void remove(const T &val);

        T** inorderOut(int size) ;

        void inorderInsert(T** values, int size);

        class exceptions : public std::exception
        {
        };

        class ItemExist : public exceptions
        {
        };

        class ItemNotExist : public exceptions
        {
        };

        class ItemInBothTrees : public exceptions
        {
        public:
            const char *what() const noexcept override
            {
                return "The same item is in both trees";
            }
        };

        T* findClosestFromBelow(const T &value); // return thr closest from below to the value in the tree

        T* findClosestFromAbove(const T &value); // return thr closest from above to the value in the tree

        T* GetLowesValue();

        int between_to_places(T* lower, T* higher);

    };
    static int max(int a, int b);

    template<class T>
    void AVLRankTree<T>::Node::Tree_Creator_AUX(int *size_of_tree, int height_of_tree, int* remainder)
    {
        //stopping condition,if we reached the bottom of the tree,stop.
        if (*size_of_tree <= 0 || height_of_tree == -1)
        {
            return;
        }
        if(height_of_tree==0)
        {
            if(*remainder>0)
            {
                (*remainder)-=1;
            }
            else return;
        }
        if(!left_son && *size_of_tree>0 && height_of_tree> -1  )
        {
            left_son = new typename AVLRankTree<T>::Node();
            left_son->father = this;
            (*size_of_tree)--;
            left_son->Tree_Creator_AUX(size_of_tree,height_of_tree-1,remainder);
        }
        //if we can , build to the right?
        if(height_of_tree==0)
        {
            if(*remainder>0)
            {
                (*remainder)-=1;
            }
            else return;
        }
        if(!right_son && *size_of_tree>0 && height_of_tree> -1 )
        {
            right_son = new typename AVLRankTree<T>::Node();
            right_son->father = this;
            (*size_of_tree)--;
            right_son->Tree_Creator_AUX(size_of_tree, height_of_tree - 1,remainder);
        }
        if (left_son!=nullptr)
            left_son->father = this;
        if (right_son!=nullptr)
            right_son->father = this;
        this->height = max(GetHeight(this->left_son), GetHeight(this->right_son))+1;
        rank = getRank(left_son) + getRank(right_son) + 1;
    }

    template<class T>
    int AVLRankTree<T>::Node::GetHeight(Node* node) {
        if(!node)
            return NOT_EXIST;
        return node->height;
    }

    template<class T>
    void AVLRankTree<T>::createEmptyTree(int size_of_tree)
    {
        //calculate the height based on size.
        //create the tree, for each conjunction , alloc node, perfferably in recursive way.
        int height_of_new_tree = (int) ceil(log2(size_of_tree +1)) - 1;
        postOrderDelete(root, false);
        int sub_full_tree_Size=(int)pow((double)2,(double)(height_of_new_tree));
        int* remainder=new int(size_of_tree-(sub_full_tree_Size-1));
        //now we dont have anything.
        //we need to creat new root.
        size_of_tree--;
        root= new Node();
        root->height = height_of_new_tree;
        root->rank = size_of_tree;
        root->Tree_Creator_AUX(&size_of_tree, height_of_new_tree -1,remainder);//memory allocation?what do we do with it? :)
        delete remainder;
    }

    template<class T>
    int AVLRankTree<T>::getHeight(Node *ver)
    {
        return (!ver) ? NOT_EXIST : ver->height;
    }

    template<class T>
    int AVLRankTree<T>::balance(Node *ver)
    {
        if (!ver)
        {
            return 0;
        }
        return (this->getHeight(ver->left_son) - this->getHeight(ver->right_son));
    }

    template<class T>
    typename AVLRankTree<T>::Node *AVLRankTree<T>::easyCaseRemove(AVLRankTree<T>::Node *loc, bool &easy_case)
    {
        Node *ver ;
        easy_case = false;
        if (!(loc->right_son || loc->left_son))
        {
            if (loc == loc->father->left_son)
            {
                loc->father->left_son = nullptr;
            } else
            {
                loc->father->right_son = nullptr;
            }
            easy_case = true;
        }

        if (loc->left_son && !loc->right_son)
        {
            if (loc == loc->father->left_son)
            {
                loc->father->left_son = loc->left_son;
                loc->left_son->father = loc->father;
            } else
            {
                loc->father->right_son = loc->left_son;
                loc->left_son->father = loc->father;
            }
            easy_case = true;
        }

        if (!loc->left_son && loc->right_son)
        {
            if (loc == loc->father->left_son)
            {
                loc->father->left_son = loc->right_son;
                loc->right_son->father = loc->father;

            } else
            {
                loc->father->right_son = loc->right_son;
                loc->right_son->father = loc->father;
            }
            easy_case = true;
        }
        if(easy_case)
        {
            ver=loc->father;
            delete loc;
            return ver;
        }
        return nullptr;
    }


    template<class T>
    void AVLRankTree<T>::rootCaseRemove()
    {
        if (!(root->right_son) && !(root->left_son))
        {
            delete root;
            root = nullptr;
            return;
        }
        else if (!(root->right_son) && root->left_son)
        {
            Node *temp = root->left_son;
            delete root;
            root = temp;
            temp->father = nullptr;
            return;

        } else if (root->right_son && !(root->left_son))
        {
            Node *temp = root->right_son;
            delete root;
            root = temp;
            temp->father = nullptr;
            return;
        }
        Node *ver;
        swapWithNext(root, &ver);
        bool easyCase;
        Node* place_to_fix = easyCaseRemove(ver, easyCase);
        checkForRolls(place_to_fix);
    }

    template<class T>
    void AVLRankTree<T>::swapWithNext(Node *loc, Node** place)
    {
        Node* temp;
        if(loc->right_son) {
            temp = loc->right_son; //go right
            if(!temp->father)
                temp->father = loc;
            while (temp->left_son) {
                if(!temp->left_son->father)
                    temp->left_son->father = temp;
                temp = temp->left_son; //go strongly left
            }
        }
        else
        {
            temp = loc->left_son; //go left, if loc->left_son is nullptr then something went wrong
            if(!temp->father)
                temp->father = loc;
            while (temp->right_son) {
                if(!temp->right_son->father)
                    temp->right_son->father = temp;
                temp = temp->right_son; //go strongly left
            }
        }
        T *temp_value = temp->value;// Candidate value.
        temp->value = loc->value; //location value.
        loc->value = temp_value; //
        *place = temp;
    }


    template<class T>
    void AVLRankTree<T>::checkForRolls(Node *start)
    {
        Node* temp_father;
        while (start)
        {
            start->height = max(getHeight(start->right_son), getHeight(start->left_son)) + 1;
            start->rank = getRank(start->left_son) + getRank(start->right_son) + 1;
            temp_father = start->father;
            if (balance(start) > -2 && balance(start) < 2)
            {
                start = start->father;
                continue;
            } else
            {
                switch (balance(start))
                {
                    case 2:
                    {
                        if (balance(start->left_son) >= 0)
                        {
                            ll_roll(start);
                            start = temp_father;
                            continue;
                        }
                        lr_roll(start);
                        start = temp_father;
                        continue;
                    }
                    case -2:
                    {
                        if (balance(start->right_son) <= 0)
                        {
                            rr_roll(start);
                            start = temp_father;
                            continue;
                        }
                        rl_roll(start);
                        start = temp_father;
                        continue;
                    }
                }
            }
        }
    }

    static int max(int a, int b)
    {
        return (a >= b) ? a : b;
    }

    template<class T>
    void AVLRankTree<T>::ll_roll(Node *first_ubl)
    {
        Node *temp = first_ubl->left_son;
        if(first_ubl==root)
        {
            root=temp;
            temp->father=nullptr;
        }
        else //correct to son of the first_ubl father to be the right son
        {
            if(first_ubl->father->right_son == first_ubl)
                first_ubl->father->right_son = temp;
            else
                first_ubl->father->left_son = temp;
        }
        first_ubl->left_son = temp->right_son;
        if(temp->right_son)
        {
            temp->right_son->father=first_ubl;
        }
        temp->right_son = first_ubl;
        Node* temp_father=first_ubl->father;
        first_ubl->father=temp;
        temp->father=temp_father;
        first_ubl->height = max(getHeight(first_ubl->left_son), getHeight(first_ubl->right_son)) + 1;
        first_ubl->rank = getRank(first_ubl->left_son) + getRank(first_ubl->right_son) + 1;
        temp->height = max(getHeight(temp->left_son), getHeight(temp->right_son)) + 1;
        temp->rank = getRank(temp->left_son) + getRank(temp->right_son) + 1;
    }

    template<class T>
    void AVLRankTree<T>::lr_roll(Node *first_ubl)
    {
        Node* temp = first_ubl->left_son;
        rr_roll(temp);
        ll_roll(first_ubl);
    }


    template<class T>
    void AVLRankTree<T>::rl_roll(Node *first_ubl)
    {
        Node* temp = first_ubl->right_son;
        ll_roll(temp);
        rr_roll(first_ubl);
    }


    template<class T>
    void AVLRankTree<T>::rr_roll(Node *first_ubl)
    {
        Node *temp = first_ubl->right_son; //save the right son
        if(first_ubl==root)
        {
            root=temp;
            temp->father=nullptr;
        }
        else //correct to son of the first_ubl father to be the right son
        {
            if(first_ubl->father->right_son == first_ubl)
                first_ubl->father->right_son = temp;
            else
                first_ubl->father->left_son = temp;
        }
        first_ubl->right_son = temp->left_son;//

        if(temp->left_son)
        {
            temp->left_son->father=first_ubl;
        }
        temp->left_son = first_ubl;
        Node* temp_father=first_ubl->father;
        first_ubl->father=temp;
        temp->father=temp_father;
        first_ubl->height = max(getHeight(first_ubl->left_son), getHeight(first_ubl->right_son))+1;
        first_ubl->rank = getRank(first_ubl->left_son) + getRank(first_ubl->right_son) + 1;
        temp->height = max(getHeight(temp->left_son), getHeight(temp->right_son))+1;
        temp->rank = getRank(temp->left_son) + getRank(temp->right_son) + 1;
    }

    template<class T>
    T* AVLRankTree<T>::find(const T &val)
    {
        if(root==nullptr) //if root is nullptr whats the point in checking the whole tree.
        {
            return nullptr;
        }
        Node *loc;
        Node *father_of_loc;
        T* to_return= find_in_tree(root, val, &loc, &father_of_loc);
        return to_return;
    }

    template<class T>
    void AVLRankTree<T>::insert(T &val)
    {
        if (root == nullptr)
        {
            root = new Node(&val);
            size++;
            return;
        }
        Node *loc;
        Node *father_of_loc;
        if (find_in_tree(root, val, &loc, &father_of_loc))
        {

            throw ItemExist();
        }

        if (val <= *(father_of_loc->value))
        {
            father_of_loc->left_son =new Node(&val,father_of_loc);
            checkForRolls(father_of_loc->left_son);

        } else
        {
            father_of_loc->right_son = new Node(&val,father_of_loc);
            checkForRolls(father_of_loc->right_son);
        }
        size++;
    }

    template<class T>
    void AVLRankTree<T>::remove(const T &val)
    {
        Node *loc;
        Node *father_of_loc;
        Node *ver;
        T* value = find_in_tree(root, val, &loc, &father_of_loc);
        if (!value)
        {
            throw ItemNotExist();
        }
        size--;
        if (loc == root)
        {
            rootCaseRemove();
            return;
        }
        bool easy_case = false;
        ver = easyCaseRemove(loc, easy_case);
        if (easy_case)
        {
            checkForRolls(ver);
            return;
        }
        swapWithNext(loc, &ver);
        ver = easyCaseRemove(ver, easy_case);
        checkForRolls(ver);
    }

    template<class T>
    T** AVLRankTree<T>::inorderOut(int size)
    {
        T** values;
        if (!root)
            return nullptr;
        values=new T*[size];
        int index=0;
        inorderHelper(values, &index, root, size);
        return values;
    }

    template<class T>
    void AVLRankTree<T>::inorderHelper(T* values[] , int* index, Node *ver, int max_size)
    {
        if (!ver || *index >= max_size)
            return;
        inorderHelper(values, index, ver->left_son, max_size);
        if(*index >= max_size)
            return;
        values[(*index)++] = (ver->value); //need to implement an assignment operator for class Player
        if(*index >= max_size)
            return;
        inorderHelper(values, index, ver->right_son, max_size);
    }


    template<class T>
    void AVLRankTree<T>::inorderIn(T* values[] , int &index, Node *ver)
    {
        if (!ver)
            return;
        inorderIn(values, index, ver->left_son);
        ver->value = values[index++];
        inorderIn(values, index, ver->right_son);
    }

    template<class T>
    T* AVLRankTree<T>::findClosestFromBelow(const T &value)
    {
        if(!root)
            return nullptr;
        Node *loc;
        Node *father_of_loc;
        find_in_tree(root, value, &loc, &father_of_loc);
        if (loc->left_son)
        {
            Node* temp = loc->left_son;
            while(temp->right_son)
            {
                temp = temp->right_son;
            }
            return temp->value;
        }
        if (father_of_loc)
        {
            if(*(father_of_loc->value) <= *(loc->value))
                return father_of_loc->value;
        }
        return nullptr;
    }

    template<class T>
    int AVLRankTree<T>::getSize() const{
        return size;
    }

    template<class T>
    void AVLRankTree<T>::postOrderDelete(Node* ver, bool delete_values)
    {
        if(!ver)
            return;
        postOrderDelete(ver->left_son, delete_values);
        postOrderDelete(ver->right_son, delete_values);
        if(delete_values)
            delete ver->value;
        ver->father = nullptr;
        ver->value = nullptr;
        ver->right_son = nullptr;
        ver->left_son = nullptr;
        delete ver;
    }


    template<class T>
    void AVLRankTree<T>::inorderInsert(T** values, int size)
    {
        int index = 0;
        inorderIn(values, index, root);
    }

    template<class T>
    T *AVLRankTree<T>::findClosestFromAbove(const T &value)
    {
        if(!root)
            return nullptr;
        Node *loc;
        Node *father_of_loc;
        find_in_tree(root, value, &loc, &father_of_loc);
        if (loc->right_son)
        {
            return loc->right_son->value;
        }
        while (father_of_loc)
        {
            if(father_of_loc->value >= loc->value)
                return father_of_loc->value;
            loc = loc->father;
            father_of_loc = father_of_loc->father;
        }
        return nullptr;
    }

    template<class T>
    T *AVLRankTree<T>::GetLowesValue()
    {
        if (!root)
            return nullptr;
        Node *temp = root->left_son;
        if (!temp)
            return root->value;
        while (temp->left_son)
        {
            temp = temp->left_son;
        }
        return temp->value;
    }

    template<class T>
    int AVLRankTree<T>::getRank(AVLRankTree::Node *ver)
    {
        if(!ver)
            return 0;
        return ver->rank;
    }

    template<class T>
    int AVLRankTree<T>::between_to_places(T *lower_value, T *higher_value)
    {
        Node** location;
        Node** father;
        Node* lower = find_in_tree(root,*lower_value, location, father);
        if(!lower)
            lower = ClosestFromAbove(lower_value);
        Node* higher = find_in_tree(root, *higher_value, location, father);
        if(!higher)
            higher = ClosestFromBelow(higher_value);
        return (findIndex(higher)-findIndex(lower)+1);
    }

    template<class T>
    int AVLRankTree<T>::findIndex(AVLRankTree::Node *ver) const
    {
        if(!ver)
            return 0;
        int index = 0;
        Node* temp = root;
        while(temp != ver)
        {
            if(ver<= temp)
            {
                ver = ver->left_son;
                continue;
            }
            ver = ver->right_son;
            index += getRank(temp->left_son) + 1;
        }
        return (index + getRank(ver->left_son) + 1);
    }

    template<class T>
    typename AVLRankTree<T>::Node *AVLRankTree<T>::ClosestFromAbove(T *value) const
    {
        Node* temp = root;
        Node* candidate = nullptr;
        while(temp)
        {
            if(*(temp->value) <= *value)
            {
                temp = temp->right_son;
                continue;
            }
            candidate = temp;
            temp = temp->left_son;
        }
        return candidate;
    }

    template<class T>
    typename AVLRankTree<T>::Node *AVLRankTree<T>::ClosestFromBelow(T *value) const
    {
        Node* temp = root;
        Node* candidate = nullptr;
        while(temp)
        {
            if(*value <= *(temp->value))
            {
                temp = temp->left_son;
                continue;
            }
            candidate = temp;
            temp = temp->right_son;
        }
        return candidate;
    }
} //namespace wet2_dast


#endif // AVLRANKTREE_H_