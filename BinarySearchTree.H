//
// Created by David on 11/3/2022.
//

#ifndef APA7_BINARYSEARCHTREE_H
#define APA7_BINARYSEARCHTREE_H

#include <iostream>
#include <string>
#include<cmath>

using namespace std;


template<class T>
struct Tnode {
    T nodeValue;
    Tnode<T> *Lchild = nullptr;
    Tnode<T> *Rchild = nullptr;
};


template<class T>
class BSTree {
private:

    Tnode<T> *tRoot = nullptr;

    void udeleteInternal(Tnode<T> *&a) {

        if(a->Rchild == nullptr && a->Lchild == nullptr)
        {
            a = nullptr;
            delete a;
            return;
        }
        else if(a->Lchild == nullptr && a->Rchild != nullptr)
        {
            a->nodeValue = a->Lchild->nodeValue;
            a->Rchild = nullptr;
            delete a->Lchild;
        }
        else if(a->Lchild != nullptr && a->Lchild == nullptr){
            a->nodeValue = a->Lchild->nodeValue;
            a->Lchild = nullptr;
            delete a->Lchild;
        }
        else{
            Tnode <T> *temp = a;
            Tnode <T> *trailing = nullptr;
            Tnode<T> *nextNode = nullptr;

            if(temp->Lchild->Rchild == nullptr){
                a->nodeValue = temp->Lchild->nodeValue;
                nextNode = temp->Lchild->Lchild;
                delete temp->Lchild;
                a->Lchild = nextNode;
            }


            else {
                temp = temp->Lchild;
                while (temp->Rchild != nullptr) {
                    trailing = temp;
                    temp = temp->Rchild;
                }
                a->nodeValue = temp->nodeValue;
                a->Rchild = nullptr;
                delete a->Rchild;
                delete temp;
            }

            }


    }


    void inOrderTraversal(Tnode<T> *a) {
        if (a != nullptr) {
            inOrderTraversal(a->Lchild);
            cout << a->nodeValue << endl;
            inOrderTraversal(a->Rchild);
        }
        return;
    }

    void preOrderTraversal(Tnode<T> *a) {
        if (a != nullptr) {
            cout << a->nodeValue << endl;
            preOrderTraversal(a->Lchild);
            preOrderTraversal(a->Rchild);
        }
        return;
    }

    void postOrderTraversal(Tnode<T> *a) {
        if (a != nullptr) {
            postOrderTraversal(a->Lchild);
            postOrderTraversal(a->Rchild);
            cout << a->nodeValue << endl;
        }
        return;
    }
    int heightInternal(Tnode<T> *p)
    {
        if(p != nullptr){
            int lh = heightInternal(p->Lchild);
            int rh = heightInternal(p->Rchild);
            if(lh > rh){
                return lh+1;
            }
            else{
                return rh+1;
            }
        }
        else
        {
            return -1;
        }
    }


public:
    bool search(T &a) {
        bool found;
        if (tRoot == nullptr) {
            cout << "error - empty tree";
            return false;
        } else {
            found = false;
            Tnode<T> *current = tRoot;
            while (current != nullptr && !found) {
                if (current->nodeValue == a) {
                    found = true;
                } else if (current->nodeValue > a) {
                    current = current->Lchild;
                } else {
                    current = current->Rchild;
                }
            }
            return found;
        }
    }
    int height() {
        return heightInternal(tRoot);
    }
    void printRohitLevel(Tnode<T>* node, int x, int level, int height, string& print, const int WIDTH) {
        if (node ==
            nullptr) {        //this node is empty so generates enough spaces based on which level the node is located on in relation to the level that must be printed and the height of the tree
            for (int i = 0; i < WIDTH * pow(2, height + 1 - level + x); i++)
                print += " ";
        } else if (x == 1) {        //the node is on the right level
            for (int i = 0; i < WIDTH * (pow(2, height + 1 - level)); i++)        //space to print before node
                print += " ";
            int val = node->nodeValue;
            string value = to_string(val);
            print += value;
            for (unsigned int i = 0;
                 i < (WIDTH - value.length()); i++)        //if the width of the node is less than WIDTH, prints spaces
                print += " ";
            for (int i = 0; i < WIDTH * (pow(2, height + 1 - level) - 1); i++)        //space to print after node
                print += " ";
        } else {
            printRohitLevel(node->Lchild, x - 1, level, height, print, WIDTH);
            printRohitLevel(node->Rchild, x - 1, level, height, print, WIDTH);
        }
    }
    void printRohit() {

        const int WIDTH = 3;		//must be greater than the max characters printed per node; for example, if printing 2 digit numbers, WIDTH should be >= 3
        const int GAP = 5;			//gap between each node
        int height = this->height();
        string lines[height+1];

        //generates a string for each level of the tree
        for(int i=1; i<=height+1; i++){
            string line;
            printRohitLevel(tRoot, i, i, height, line, WIDTH);
            lines[i-1] = line;
        }

        //removes the unnecessary spaces from the lines
        int space = 0;
        bool allSpace;
        for(unsigned int i=0; i<lines[0].length(); i++){
            allSpace = true;
            for(string line: lines){
                if(line.at(i) != ' '){
                    allSpace = false;
                }
            }
            if(allSpace){		//every line has a space at this index
                space += 1;
            }
            else{
                if(space > GAP){		//the space is too long and must be reduced to GAP
                    for(string& line: lines){
                        line.erase(i-space, space-GAP);
                    }
                    i-= (space-GAP);
                }
                else if(space < GAP && space>0){		//the space is too small and must be expanded to GAP
                    string spaces;
                    for(int j=0; j< (GAP-space); j++){
                        spaces += " ";
                    }
                    for(string& line: lines){
                        line.insert(i-space, spaces);
                    }
                    i += (GAP-space);
                }
                space = 0;
            }

        }

        //prints out each line
        for(string line: lines){
            cout << line << endl << endl << endl;
        }



    }
        void insert(T &a)
        {
            Tnode<T> *holder = new Tnode<T>;
            Tnode<T> *trailing = new Tnode<T>;
            holder->nodeValue = a;
            holder->Lchild = nullptr;
            holder->Rchild = nullptr;
            if (tRoot == nullptr) {
                tRoot = holder;
            } else {
                Tnode<T> *current = tRoot;
                while (current != nullptr) {
                    trailing = current;
                    if (current->nodeValue == a) {
                        cout << "Error duplicate" << endl;

                    } else if (current->nodeValue > a) {
                        current = current->Lchild;
                    }
                    else
                    {
                        current = current->Rchild;
                    }
                }
                if (trailing->nodeValue > a) {
                    trailing->Lchild = holder;
                } else  {
                    trailing->Rchild = holder;
                }
            }
            return;
        }

        void udelete(T &a)
        {
                bool found = false;
                if (tRoot == nullptr) {
                    cout << "empty tree";
                    return;
                } else {
                    Tnode<T> *current = tRoot;
                    Tnode<T> *trailing = tRoot;
                    while (current != nullptr && !found) {
                        if (current->nodeValue == a) {
                            found = true;
                        } else {
                            trailing = current;
                            if (current->nodeValue > a) {
                                current = current->Lchild;
                            } else {
                                current = current->Rchild;
                            }
                        }

                    }
                    if (current == nullptr) {
                        cout << "Node not found" << endl;
                        return;
                    } else if (trailing->nodeValue > a) {
                        udeleteInternal(trailing->Lchild);
                    } else if (trailing->nodeValue < a){
                        udeleteInternal(trailing->Rchild);
                    }
                    else
                        return;
                }


        }


        void inOrderTraversal()
        {
            inOrderTraversal(tRoot);
            return;
        }

        void preOrderTraversal() {
            preOrderTraversal(tRoot);
            return;
        }

        void postOrderTraversal() {
            postOrderTraversal(tRoot);
            return;
        }

};

#endif //APA7_BINARYSEARCHTREE_H
