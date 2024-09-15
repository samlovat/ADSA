#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Node{
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

void inorder(Node* currNode){
    if(currNode == nullptr){
        cout << "EMPTY" << endl;
        return;
    }

    if(currNode->Left != nullptr){
        inorder(currNode->Left);
    }
    cout << currNode->getValue() << " ";
    if(currNode->Right != nullptr){
        inorder(currNode->Right);
    }
    return;
}

void postorder(Node* currNode){
    if(currNode == nullptr){
        cout << "EMPTY" << endl;
        return;
    }

    if(currNode->Left != nullptr){
        postorder(currNode->Left);
    }
    if(currNode->Right != nullptr){
        postorder(currNode->Right);
    }
    cout << currNode->getValue() << " ";
    return;
}

void preorder(Node* currNode){
    if(currNode == nullptr){
        cout << "EMPTY" << endl;
        return;
    }

    //Print this node
    cout << currNode->getValue() << " ";

    //if left {print left}
    if(currNode->Left != nullptr){
        preorder(currNode->Left);
    }
    //if right{print right}
    if(currNode->Right != nullptr){
        preorder(currNode->Right);
    }
    return;
}

class AVL{
    public:
        Node* Root;
        AVL(){ this->Root = nullptr; }
};

void LL(Node* Grandparent, AVL* Tree){
    Node* gpaPar = nullptr;
    Node* Parent = Grandparent->Left;
    int gpaIsLeft = 0;
    int root = 0;
    if(Grandparent->Parent != nullptr){
        gpaPar = Grandparent->Parent;
        //Check if Grandpa is right or left of its parent
        if(gpaPar->Left != nullptr){
            if(gpaPar->Left->getValue() == Grandparent->getValue()){
                gpaIsLeft = 1;
                
            }
        }
    }else{
        //Reset root node 
        root = 1;
        Tree->Root = Parent;
    }
    if(root == 1){
        Grandparent->Left = Parent->Right;
        if(Parent->Right != nullptr){
            Parent->Right->Parent = Grandparent;
        }
        Grandparent->Parent = Parent;
        Parent->Right = Grandparent;
        Parent->Parent = gpaPar;
    }else{
        if(gpaIsLeft == 1){
            gpaPar->Left = Parent;
        }else{
            gpaPar->Right = Parent;
        }
        Grandparent->Left = Parent->Right;
        if(Parent->Right != nullptr){
            Parent->Right->Parent = Grandparent;  
        }        
        Grandparent->Parent = Parent;
        Parent->Right = Grandparent;
        Parent->Parent = gpaPar;
    }
    return;
}

void RR(Node* Grandparent, AVL* Tree){
    Node* gpaPar = nullptr;
    Node* Parent = Grandparent->Right;
    int gpaIsLeft = 0;
    int root = 0;
    if(Grandparent->Parent != nullptr){
        gpaPar = Grandparent->Parent;
        //Check if gpa is right or left of its parent
        if(gpaPar->Left != nullptr){
            if(gpaPar->Left->getValue() == Grandparent->getValue()){
                gpaIsLeft = 1;
            }
        }
    }else{
        //Reset root node 
        root = 1;
        Tree->Root = Parent;
    }
    if(root == 1){
        Grandparent->Right = Parent->Left;
        if(Parent->Left != nullptr){
            Parent->Left->Parent = Grandparent;
        }
        Grandparent->Parent = Parent;
        Parent->Left = Grandparent;
        Parent->Parent = gpaPar;
    }else{
        if(gpaIsLeft == 1){
            gpaPar->Left = Parent;
        }else{
            gpaPar->Right = Parent;
        }
        Grandparent->Right = Parent->Left;
        if(Parent->Left != nullptr){
            Parent->Left->Parent = Grandparent;
        }
        
        Grandparent->Parent = Parent;
        Parent->Left = Grandparent;
        Parent->Parent = gpaPar;    
        
    }
    return;
}

void LR(Node* Grandparent, AVL* Tree){
    Node* gpaPar = nullptr;
    Node* Parent = Grandparent->Left;
    Node* Child = Parent->Right;
    int gpaIsLeft = 0;
    int root = 0;
    if(Grandparent->Parent != nullptr){
        gpaPar = Grandparent->Parent;
        //Check if gpa is right or left of its parent
        if(gpaPar->Left != nullptr){
            if(gpaPar->Left->getValue() == Grandparent->getValue()){
                gpaIsLeft = 1;
            }
        }
    }else{
        //Reset root node 
        root = 1;
        Tree->Root = Child;
    }
    if(root == 1){
        Grandparent->Left = Child->Right;
        if(Child->Right != nullptr){
            Child->Right->Parent = Grandparent;
        }        
        Grandparent->Parent = Child;
        Parent->Parent = Child;
        Parent->Right = Child->Left;
        if(Child->Left != nullptr){
            Child->Left->Parent = Parent;
        }
        Child->Right = Grandparent;
        Child->Left = Parent;
        Child->Parent = gpaPar;
    }else{
        if(gpaIsLeft == 1){
            gpaPar->Left = Child;
        }else{
            gpaPar->Right = Child;
        }
        Grandparent->Left = Child->Right;
        if(Child->Right != nullptr){
            Child->Right->Parent = Grandparent;
        }
        Grandparent->Parent = Child;
        Parent->Parent = Child;
        Parent->Right = Child->Left;
        if(Child->Left != nullptr){
            Child->Left->Parent = Parent;
        }
        Child->Parent = gpaPar;
        Child->Right = Grandparent;
        Child->Left = Parent;
    }
    return;
}

void RL(Node* Grandparent, AVL* Tree){
    Node* gpaPar = nullptr;
    Node* Parent = Grandparent->Right;
    Node* Child = Parent->Left;
    int gpaIsLeft = 0;
    int root = 0;
    if(Grandparent->Parent != nullptr){
        gpaPar = Grandparent->Parent;
        //Check if gpa is right or left of its parent
        if(gpaPar->Left != nullptr){
            if(gpaPar->Left->getValue() == Grandparent->getValue()){
                gpaIsLeft = 1;
            }
        }
    }else{
        //Reset root node 
        root = 1;
        Tree->Root = Child;
    }
    if(root == 1){
        Grandparent->Right = Child->Left;
        if(Child->Left != nullptr){
            Child->Left->Parent = Grandparent;
        }       
        Grandparent->Parent = Child;
        Parent->Parent = Child;
        Parent->Left = Child->Right;
        if(Child->Right != nullptr){
            Child->Right->Parent = Parent;
        }        
        Child->Left = Grandparent;
        Child->Right = Parent;
        Child->Parent = gpaPar;
    }else{
        if(gpaIsLeft == 1){
            gpaPar->Left = Child;
        }else{
            gpaPar->Right = Child;
        }
        Grandparent->Right = Child->Left;
        if(Child->Left != nullptr){
            Child->Left->Parent = Grandparent;
        }        
        Grandparent->Parent = Child;
        Parent->Parent = Child;
        Parent->Left = Child->Right;
        if(Child->Right != nullptr){
            Child->Right->Parent = Parent;
        }        
        Child->Parent = gpaPar;
        Child->Left = Grandparent;
        Child->Right = Parent;
    }
    return;
}

void del(Node* root, int value, AVL* Tree){
    //Search to find node
    int isRoot = 0;
    int balance;
    //Check if tree is empty
    if(root == nullptr){
        return;
    }

    //Compare with currnode
    if(value < root->getValue() && root->Left != nullptr){
        del(root->Left, value, Tree);
    }else if(value > root->getValue() && root->Right != nullptr){
        del(root->Right, value, Tree);        
    }else if(value != root->getValue()){
        //Node doesn't exist
        return;
    }else{
        //Time to delete
        Node* rootParent;
        if(root->Parent != nullptr){
            rootParent = root->Parent;
        }else{
            isRoot = 1;
            rootParent = nullptr;
        }
        if(root->Left != nullptr && root->Right != nullptr){
        //deletee node has left and right leaves
            int goLeft = 1;
            Node* currNode = root->Left;
            int max = currNode->getValue();
            while(goLeft == 1){
                //Search for closest node on left
                if(currNode->Right != nullptr){
                    currNode = currNode->Right;
                    max = std::max(max, currNode->getValue());
                }else{
                    goLeft = 0;
                }
            }
            root->setValue(max);
            del(root->Left, max, Tree);
        }else if(root->Left != nullptr && root->Right == nullptr){
        //deletee node has only left leaf
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

void insert(Node* root, int value, AVL* Tree){
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

int main(){

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