#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Node{                                                                 //Node Class
    private:
        int value;
    public:
        Node(int value_, Node* Parent_){                                    //Constructor
            this->value = value_; this->Parent = Parent_; this->Left = nullptr; this->Right = nullptr; 
        }
        Node* Parent;                                                       //Neighbouring Nodes
        Node* Left;
        Node* Right;
        int getValue(){ return this->value; }                               //Node Value getter and setter
        void setValue(int value_){ this->value = value_; }
        
        int getBalance(){                                                   //Function to return balance factor of a node
            int leftBalance = 0;
            int rightBalance = 0;
            if(this->Left != nullptr){                                      //If left child exists, check its height with checkChildren()
                leftBalance = this->Left->checkChildren();
            }
            if(this->Right != nullptr){                                     //If right child exists, check its height with checkChildren()
                rightBalance = this->Right->checkChildren();
            }
            return leftBalance - rightBalance;                              //Return the left height - right height
        }
        
        int checkChildren(){                                                //Function to return max height of a node's children                       
            int leftHeight = 0;
            int rightHeight = 0;            
            if(this->Right == nullptr && this->Left == nullptr){            //Base case
                return 1;
            }
            if(this->Right != nullptr){                                     //If right child exists, recursively call checkChildren()
                rightHeight = 1 + this->Right->checkChildren();
            }
            if(this->Left != nullptr){                                      //If left child exists, recursively call checkChildren()
                leftHeight = 1 + this->Left->checkChildren();
            }
            int max = std::max(leftHeight, rightHeight);                    //Return the maximum of left and right heights
            return max;
        }
};

void inorder(Node* currNode){                                               //Prints AVL tree at currNode in 'inorder'
    if(currNode == nullptr){                                                //Print EMPTY if given node is a nullptr
        cout << "EMPTY" << endl;
        return;
    }

    if(currNode->Left != nullptr){                                          //If left child exists, recursive call on left
        inorder(currNode->Left);
    }
    cout << currNode->getValue() << " ";                                    //Print this node
    if(currNode->Right != nullptr){                                         //If right child exists, recursive call on right
        inorder(currNode->Right);
    }
    return;
}

void postorder(Node* currNode){                                             //Prints AVL tree at currNode in 'postorder'
    if(currNode == nullptr){                                                //Print EMPTY if given node is a nullptr
        cout << "EMPTY" << endl;
        return;
    }

    if(currNode->Left != nullptr){                                          //If left child exists, recursive call on left
        postorder(currNode->Left);
    }
    if(currNode->Right != nullptr){                                         //If right child exists, recursive call on right
        postorder(currNode->Right);
    }
    cout << currNode->getValue() << " ";                                    //Print this node
    return;
}

void preorder(Node* currNode){                                              //Prints AVL tree at currNode in 'preorder'
    if(currNode == nullptr){                                                //Print EMPTY if given node is a nullptr
        cout << "EMPTY" << endl;
        return;
    }
    cout << currNode->getValue() << " ";                                    //Print this node
    if(currNode->Left != nullptr){                                          //If left child exists, recursive call on left
        preorder(currNode->Left);
    }
    if(currNode->Right != nullptr){                                         //If right child exists, recursive call on right
        preorder(currNode->Right);
    }
    return;
}

class AVL{                                                                  //AVL Class, tracks the root of node structure
    public:
        Node* Root;                             
        AVL(){ this->Root = nullptr; }                          //Constructor only instantiates empty tree. Root creation is made with insert()
};

void LL(Node* Grandparent, AVL* Tree){                                      //Left Left Rotation
    Node* gpaPar = nullptr;                                                 //Track parent of given grandparent
    Node* Parent = Grandparent->Left;                                       //Track child of granpdarent        
    int gpaIsLeft = 0;                                                      //Member var to track if grandparent is a left or right child
    int root = 0;                                                           //Tracks if granparent is a root node
    if(Grandparent->Parent != nullptr){                                     
        gpaPar = Grandparent->Parent;                                       //If grandparent has a parent, gpaPar is assigned
        if(gpaPar->Left != nullptr){                                        
            if(gpaPar->Left->getValue() == Grandparent->getValue()){        
                gpaIsLeft = 1;                                              //gpaIsLeft state var is assigned accordingly
            }
        }
    }else{
        root = 1;                                                           //If granparent has no parent, set root to 1 (it's a root node)
        Tree->Root = Parent;                                                //Reassign AVL Tree's root to Parent 
    }
    if(root == 0){                                                          //If Granparent is not root set its parent's correct child pointer to Parent
        if(gpaIsLeft == 1){                                                 
            gpaPar->Left = Parent;
        }else{
            gpaPar->Right = Parent;
        }
    }
    Grandparent->Left = Parent->Right;                                      //Assign granparent's left child pointer to point at parent's right child
    if(Parent->Right != nullptr){
        Parent->Right->Parent = Grandparent;                                //If Parent has right node, assign grandparent as its new parent
    }        
    Grandparent->Parent = Parent;                                           //Reassign granparent's parent
    Parent->Right = Grandparent;                                            //Reassign Parent's children pointers
    Parent->Parent = gpaPar;
    return;
}

void RR(Node* Grandparent, AVL* Tree){                                      //Right Right Rotation
    Node* gpaPar = nullptr;                                                 //Track parent of given grandparent
    Node* Parent = Grandparent->Right;                                      //Track child of granpdarent 
    int gpaIsLeft = 0;                                                      //Member var to track if grandparent is a left or right child
    int root = 0;                                                           //Tracks if granparent is a root node
    if(Grandparent->Parent != nullptr){
        gpaPar = Grandparent->Parent;                                       //If grandparent has a parent, gpaPar is assigned
        if(gpaPar->Left != nullptr){                                        
            if(gpaPar->Left->getValue() == Grandparent->getValue()){
                gpaIsLeft = 1;                                              //gpaIsLeft state var is assigned accordingly
            }
        }
    }else{
        root = 1;                                                           //If granparent has no parent, set root to 1 (it's a root node)
        Tree->Root = Parent;                                                //Reassign AVL Tree's root to Parent
    }
    if(root == 0){                                                          //If Granparent is not root set its parent's correct child pointer to Parent
        if(gpaIsLeft == 1){
            gpaPar->Left = Parent;
        }else{
            gpaPar->Right = Parent;
        }
    }
    Grandparent->Right = Parent->Left;                                      //Assign granparent's right child pointer to point at parent's left child
    if(Parent->Left != nullptr){
        Parent->Left->Parent = Grandparent;                                 //If Parent has left node, assign grandparent as its new parent
    }
    Grandparent->Parent = Parent;                                           //Reassign granparent's parent
    Parent->Left = Grandparent;                                             //Reassign Parent's children pointers
    Parent->Parent = gpaPar;            
    return;
}

void LR(Node* Grandparent, AVL* Tree){                                      //Left Right Rotation
    Node* gpaPar = nullptr;                                                 //Track parent of given grandparent
    Node* Parent = Grandparent->Left;                                       //Track child of granpdarent 
    Node* Child = Parent->Right;                                            //Track grandchild of grandparent
    int gpaIsLeft = 0;                                                      //Member var to track if grandparent is a left or right child
    int root = 0;                                                           //Tracks if granparent is a root node
    if(Grandparent->Parent != nullptr){
        gpaPar = Grandparent->Parent;                                       //If grandparent has a parent, gpaPar is assigned
        if(gpaPar->Left != nullptr){
            if(gpaPar->Left->getValue() == Grandparent->getValue()){
                gpaIsLeft = 1;                                              //gpaIsLeft state var is assigned accordingly
            }
        }
    }else{
        root = 1;                                                           //If granparent has no parent, set root to 1 (it's a root node)
        Tree->Root = Child;                                                 //Reassign AVL Tree's root to Parent
    }
    if(root == 0){                                                          //If Granparent is not root set its parent's correct child pointer to Parent
        if(gpaIsLeft == 1){
            gpaPar->Left = Child;
        }else{
            gpaPar->Right = Child;
        }
    }        
    Grandparent->Left = Child->Right;                                       //Assign Granparent's left child pointer to point at Child's right child
    if(Child->Right != nullptr){
        Child->Right->Parent = Grandparent;                                 //If Child has right node, assign Grandparent as its new parent
    }
    Grandparent->Parent = Child;                                            //Reassign granparent's parent
    Parent->Parent = Child;                                                 //Reassign Parent's parent
    Parent->Right = Child->Left;                                            //Reassign Parent's right child pointer
    if(Child->Left != nullptr){
        Child->Left->Parent = Parent;                                       //If Child has left node, assign Parent as its parent
    }
    Child->Parent = gpaPar;                                                 //Reassign Child's parent pointer
    Child->Right = Grandparent;                                             //Reassign Child's children pointers
    Child->Left = Parent;
    return;
}

void RL(Node* Grandparent, AVL* Tree){                                      //Right Left Rotation
    Node* gpaPar = nullptr;                                                 //Track parent of given grandparent
    Node* Parent = Grandparent->Right;                                      //Track child of granparent 
    Node* Child = Parent->Left;                                             //Track grandchild of grandparent
    int gpaIsLeft = 0;                                                      //Member var to track if grandparent is a left or right child
    int root = 0;                                                           //Tracks if granparent is a root node
    if(Grandparent->Parent != nullptr){
        gpaPar = Grandparent->Parent;                                       //If grandparent has a parent, gpaPar is assigned
        if(gpaPar->Left != nullptr){
            if(gpaPar->Left->getValue() == Grandparent->getValue()){
                gpaIsLeft = 1;                                              //gpaIsLeft state var is assigned accordingly
            }
        }
    }else{
        root = 1;                                                           //If granparent has no parent, set root to 1 (it's a root node)
        Tree->Root = Child;                                                 //Reassign AVL Tree's root to Parent
    }
    if(root == 0){                                                          //If Granparent is not root set its parent's correct child pointer to Parent                                                 
        if(gpaIsLeft == 1){
            gpaPar->Left = Child;
        }else{
            gpaPar->Right = Child;
        }
    }
    Grandparent->Right = Child->Left;                                       //Assign Granparent's right child pointer to point at Child's left child
    if(Child->Left != nullptr){
        Child->Left->Parent = Grandparent;                                  //If Child has left node, assign Grandparent as its new parent
    }        
    Grandparent->Parent = Child;                                            //Reassign Granparent's parent
    Parent->Parent = Child;                                                 //Reassign Parent's parent
    Parent->Left = Child->Right;                                            //Reassign Parent's left child pointer
    if(Child->Right != nullptr){
        Child->Right->Parent = Parent;                                      //If Child has right node, assign Parent as its parent
    }        
    Child->Parent = gpaPar;                                                 //Reassign Child's parent pointer
    Child->Left = Grandparent;                                              //Reassign Child's children pointers
    Child->Right = Parent;
    return;
}

void del(Node* root, int value, AVL* Tree){                                 //Function to delete a node
    int isRoot = 0;                                                         //State var to track if node given is a root node
    int balance;                                                            //Var to hold node balance when rebalancing
    if(root == nullptr){
        return;                                                             //Return if tree is empty
    }
    if(value < root->getValue() && root->Left != nullptr){                  //Recursively search through tree 
        del(root->Left, value, Tree);
    }else if(value > root->getValue() && root->Right != nullptr){
        del(root->Right, value, Tree);        
    }else if(value != root->getValue()){
        return;                                                             //Node doesn't exist, therefore return
    }else{                                                                  //Node was found, time to delete
        Node* rootParent;                                                   //Track root's parent (root is the found node to be deleted)
        if(root->Parent != nullptr){
            rootParent = root->Parent;                                      //If root has a parent assign rootParent
        }else{
            isRoot = 1;                                                     //If no parent, the node to be deleted is a root node
            rootParent = nullptr;                                           //Assign rootParent and isRoot accordingly
        }
        if(root->Left != nullptr && root->Right != nullptr){                //Deletee node has left and right leaves
            int goLeft = 1;                                                 //State variable for following while loop
            Node* currNode = root->Left;                                    //Var to track the node closest to deletee which is smaller than it
            int max = currNode->getValue();                                 //Track's the value of currNode
            while(goLeft == 1){
                if(currNode->Right != nullptr){
                    currNode = currNode->Right;                             //If right child exists, currNode moves down
                    max = currNode->getValue();              //Reassign max to the 
                }else{
                    goLeft = 0;
                }
            }
            root->setValue(max);
            del(root->Left, max, Tree);
        }else if(root->Left != nullptr && root->Right == nullptr){          //Deletee node has only left leaf
            if(isRoot == 0){
                if(rootParent->Right != nullptr){
                    if(rootParent->Right->getValue() == root->getValue()){
                        rootParent->Right = root->Left;
                    }else{
                        rootParent->Left = root->Left;
                    }
                }else{
                    rootParent->Left = root->Left;
                }
            }else{
                Tree->Root = root->Left;
            }
            root->Left->Parent = rootParent;
            delete root;
            return;
        }else if(root->Left == nullptr && root->Right != nullptr){
        //deletee node has only right leaf
            if(isRoot == 0){
                if(rootParent->Right != nullptr){
                    if(rootParent->Right->getValue() == root->getValue()){
                        rootParent->Right = root->Right;
                    }else{
                        rootParent->Left = root->Right;          
                    }
                }else{
                    rootParent->Left = root->Right;
                }
            }else{
                Tree->Root = root->Right;
            }
            root->Right->Parent = rootParent;

            delete root;
            return;
        }else{
        //deletee has no leaves
            if(isRoot == 0){
                if(rootParent->Right != nullptr){
                    if(rootParent->Right->getValue() == root->getValue()){
                        rootParent->Right = nullptr;
                    }else{
                        rootParent->Left = nullptr;
                    }
                }else{
                    rootParent->Left = nullptr;
                }
            }else{
                Tree->Root = nullptr;
            }
            delete root;
            return;
        }
    }
    balance = root->getBalance();
    if(balance > 1){
        if(root->Left->getBalance() >= 0){
            LL(root, Tree);
        }else{
            LR(root, Tree);
        }
    }else if(balance < -1){
        if(root->Right->getBalance() <= 0){
            RR(root, Tree);
        }else{
            RL(root, Tree);
        }
    }
    return;
}

void insert(Node* root, int value, AVL* Tree){                              //Function to insert a node
    if(Tree->Root == nullptr){
        Tree->Root = new Node(value, nullptr);
        return;
    }
    if(value > root->getValue()){
        if(root->Right != nullptr){
            insert(root->Right, value, Tree);
        }else{
            root->Right = new Node(value, root);
        }
    }else if(value < root->getValue()){
        if(root->Left != nullptr){
            insert(root->Left, value, Tree);
        }else{
            root->Left = new Node(value, root);
        }
    }else{
        //Already exists in tree
        return;
    }
    int balance = root->getBalance();
    if(balance > 1){
        if(root->Left->getBalance() >= 0){
            LL(root, Tree);
        }else{
            LR(root, Tree);
        }
    }else if(balance < -1){
        if(root->Right->getBalance() <= 0){
            RR(root, Tree);
        }else{
            RL(root, Tree);
        }
    }
    return;
}

int main(){                                                                 //main

    AVL* myTree = new AVL;
    //Reading User Input
    string input;
    int nowPrint = 0;
    int valInt;
    int counter = 0;
    while(nowPrint == 0){
        if(counter == 101){
            nowPrint = 1;
            break;
        }
        cin >> input;
        valInt = 0;
        if(input[0] == 'A'){
            string value = input.substr(1);
            for(size_t i = 0; i < value.length(); i++){
                valInt = valInt*10 + value[i] - '0';
            }
            insert(myTree->Root , valInt, myTree);
        }else if(input[0] == 'D'){
            string value = input.substr(1);
            for(size_t i = 0; i < value.length(); i++){
                valInt = valInt*10 + value[i] - '0';
            }
            del(myTree->Root , valInt, myTree);
        }else if(input == "PRE"){
            preorder(myTree->Root);
            nowPrint = 1;
        }else if(input == "POST"){
            postorder(myTree->Root);
            nowPrint = 1;
        }else if(input == "IN"){
            inorder(myTree->Root);
            nowPrint = 1;
        }
        counter++;
    }
    return 0;
}