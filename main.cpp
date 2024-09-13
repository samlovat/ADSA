#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Node{
    private:
        int value;
    public:
        Node(int value_){
            this->value = value_;
            this->Right = nullptr;
            this->Left = nullptr;
            this->Parent = nullptr;
        }
        Node(int value_, Node* Parent_){ 
            this->value = value_; this->Parent = Parent_; this->Left = nullptr; this->Right = nullptr;
        }
        Node* Parent;
        Node* Left;
        Node* Right;
        int getValue(){ return this->value; }

        int getBalance(){
            int leftBalance = 0;
            int rightBalance = 0;
            if(Left != nullptr){
                leftBalance = Left->checkChildren(1);
            }
            if(Right != nullptr){
                rightBalance = Right->checkChildren(1);
            }
            // cout << "Left Balance: " << leftBalance << " Right Balance: " << rightBalance << endl;
            return leftBalance - rightBalance;
        }
        
        int checkChildren(int height){
            // cout << "This nodes val is: " << this->getValue() << endl;
            int leftHeight = height;
            int rightHeight = height;
            // cout << "L: " << leftHeight << " R: " << rightHeight << " H: " << height << endl;
            if(this->Left != nullptr){
                leftHeight++;
                // cout << leftHeight << endl;
                Left->checkChildren(leftHeight);
            }
            if(this->Right != nullptr){
                // cout << "Going right." << endl;
                rightHeight++;
                Right->checkChildren(rightHeight);
            }
            height = std::max(leftHeight, rightHeight);
            return height;
        }
};

class AVL{
    public:
        Node* Root;
        AVL(){ this->Root = nullptr; }

        /*void ins(int a){
            if(Root == nullptr){
                Root = new Node(a, nullptr);
                return;
            }
            Node* nextNode = nullptr;
            int found = 0;
            if(a > Root->getValue()){
                if(Root->Right != nullptr){
                    nextNode = Root->Right;
                }else{
                    Root->Right = new Node(a, Root);
                    found = 1;
                    return;
                }
            }else{
                if(Root->Left != nullptr){
                    nextNode = Root->Left;
                }else{
                    cout << "made new left node with val of " << a << endl;
                    Root->Left = new Node(a, Root);
                    found = 1;
                    return;
                }
            }
            while(found == 0){
                if(a > nextNode->getValue()){
                    if(nextNode->Right != nullptr){
                        nextNode = nextNode->Right;
                    }else{
                        nextNode->Right = new Node(a, nextNode);
                        found = 1;
                    }
                }else{
                    if(nextNode->Left != nullptr){
                        nextNode = nextNode->Left;
                    }else{
                        cout << "made new left node with val of " << a << endl;
                        nextNode->Left = new Node(a, nextNode);
                        found = 1;
                    }
                }
            }
            //Check for imbalances
            Node* prevNode = nextNode;
            //If statement checks if the node inserted was inserted to the Root, if so, no rebalances needed
            if(prevNode != nullptr){
                if(prevNode->Parent->getBalance() > 1){
                    cout << "Balance > 1" << endl;
                    if(a < prevNode->getValue()){
                        //LL Rotation
                        cout << "Balance of: " << prevNode->Parent->getBalance() << " LL Rotation Needed" << endl;
                        return;
                    }else{
                        //LR Rotation
                        cout << "Balance of: " << prevNode->Parent->getBalance() << " LR Rotation Needed" << endl;
                        return;
                    }
                }else if(prevNode->Parent->getBalance() < -1){
                    cout << "Balance < -1" << endl;
                    if(a < prevNode->getValue()){
                        //RL Rotation
                        cout << "Balance of: " << prevNode->Parent->getBalance() << " RL Rotation Needed" << endl;
                        RL(prevNode, prevNode->Parent, prevNode->Left);
                        return;
                    }else{
                        //RR Rotation
                        cout << "Balance of: " << prevNode->Parent->getBalance() << " RR Rotation Needed" << endl;
                        return;
                    }
                }
            }

        }*/

        void del(int a);
};

void LL(Node* Grandparent, AVL* Tree){
    Node* gpaPar = nullptr;
    Node* Parent = Grandparent->Left;
    Node* Child = Parent->Left;
    int gpaIsLeft = 0;
    int root = 0;
    if(Grandparent->Parent != nullptr){
        // cout << "GRANDPA HAS A PARENT here is gpa: " << Grandparent->getValue() << ": my parent is: " << Grandparent->Parent->getValue() << endl;
        gpaPar = Grandparent->Parent;
        //Check if gpa is right or left of its parent
        if(gpaPar->Left->getValue() == Grandparent->getValue()){
            gpaIsLeft = 1;
        }
    }else{
        //Reset root node 
        // cout << "RESETTING NODE" << endl;
        root = 1;
        Tree->Root = Parent;
    }
    if(root == 1){
        Grandparent->Left = Parent->Right;
        Grandparent->Parent = Parent;
        Parent->Right = Grandparent;
    }else{
        if(gpaIsLeft == 1){
            gpaPar->Left = Parent;
        }else{
            gpaPar->Right = Parent;
        }
        Grandparent->Left = Parent->Right;
        Grandparent->Parent = Parent;
        Parent->Right = Grandparent;
        Parent->Parent = gpaPar;
    }
    return;
}

void RR(Node* Grandparent, AVL* Tree){
    Node* gpaPar = nullptr;
    Node* Parent = Grandparent->Right;
    Node* Child = Parent->Right;
    int gpaIsLeft = 0;
    int root = 0;
    if(Grandparent->Parent != nullptr){
        // cout << "GRANDPA HAS A PARENT here is gpa: " << Grandparent->getValue() << ": my parent is: " << Grandparent->Parent->getValue() << endl;
        gpaPar = Grandparent->Parent;
        //Check if gpa is right or left of its parent
        if(gpaPar->Left->getValue() == Grandparent->getValue()){
            gpaIsLeft = 1;
        }
    }else{
        //Reset root node 
        // cout << "RESETTING NODE" << endl;
        root = 1;
        Tree->Root = Parent;
    }
    if(root == 1){
        Grandparent->Right = Parent->Left;
        Grandparent->Parent = Parent;
        Parent->Left = Grandparent;
    }else{
        if(gpaIsLeft == 1){
            gpaPar->Left = Parent;
        }else{
            gpaPar->Right = Parent;
        }
        Grandparent->Right = Parent->Left;
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
        // cout << "GRANDPA HAS A PARENT here is gpa: " << Grandparent->getValue() << ": my parent is: " << Grandparent->Parent->getValue() << endl;
        gpaPar = Grandparent->Parent;
        //Check if gpa is right or left of its parent
        if(gpaPar->Left->getValue() == Grandparent->getValue()){
            gpaIsLeft = 1;
        }
    }else{
        //Reset root node 
        // cout << "RESETTING NODE" << endl;
        root = 1;
        Tree->Root = Child;
    }
    if(root == 1){
        Grandparent->Left = Child->Right;
        Grandparent->Parent = Child;
        Parent->Parent = Child;
        Parent->Right = Child->Left;
        Child->Right = Grandparent;
        Child->Left = Parent;
    }else{
        if(gpaIsLeft == 1){
            gpaPar->Left = Parent;
        }else{
            gpaPar->Right = Parent;
        }
        Grandparent->Left = Child->Right;
        Grandparent->Parent = Child;
        Parent->Parent = Child;
        Parent->Right = Child->Left;
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
        // cout << "GRANDPA HAS A PARENT here is gpa: " << Grandparent->getValue() << ": my parent is: " << Grandparent->Parent->getValue() << endl;
        gpaPar = Grandparent->Parent;
        //Check if gpa is right or left of its parent
        if(gpaPar->Left->getValue() == Grandparent->getValue()){
            gpaIsLeft = 1;
        }
    }else{
        //Reset root node 
        // cout << "RESETTING NODE" << endl;
        root = 1;
        Tree->Root = Child;
    }
    if(root == 1){
        Grandparent->Right = Grandparent->Right->Left->Left;
        Grandparent->Parent = Child;
        Parent->Parent = Child;
        Parent->Left = Child->Right;
        Child->Left = Grandparent;
        Child->Right = Parent;
    }else{
        if(gpaIsLeft == 1){
            gpaPar->Left = Parent;
        }else{
            gpaPar->Right = Parent;
        }
        Grandparent->Right = Grandparent->Right->Left->Left;
        Grandparent->Parent = Child;
        Parent->Parent = Child;
        Parent->Left = Child->Right;
        Child->Parent = gpaPar;
        Child->Left = Grandparent;
        Child->Right = Parent;
    }
    return;
}

void insert(Node* root, int value, AVL* Tree){
    if(Tree->Root == nullptr){
        Tree->Root = new Node(value);
        if(Tree->Root != nullptr){
            // cout << "NEWROOT: " << Tree->Root->getValue() << endl;
        }
        return;
    }
    if(value > root->getValue()){
        if(root->Right != nullptr){
            insert(root->Right, value, Tree);
        }else{
            root->Right = new Node(value, root);
        }
    }else{
        if(value < root->getValue()){
            if(root->Left != nullptr){
                insert(root->Left, value, Tree);
            }else{
                root->Left = new Node(value, root);
            }
        }
    }
    int balance = root->getBalance();
    if(balance > 1){
        if(root->Left->getBalance() >= 1){
            //LL
            cout << "LL" << endl;
            LL(root, Tree);
        }else{
            //LR
            cout << "LR" << endl;
            LR(root, Tree);
        }
    }else if(balance < -1){
        if(root->Right->getBalance() <= -1){
            //RR
            cout << "RR" << endl;
            RR(root, Tree);
        }else{
            //RL
            cout << "RL" << endl;
            RL(root, Tree);
        }
    }
    return;
}

void inorder(Node* currNode){
    if(currNode == nullptr){
        cout << "EMPTY" << endl;
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

int main(){

    AVL* myTree = new AVL;
    //Reading User Input
    string input;
    int nowPrint = 0;
    int valInt;
    int counter = 0;
    while(nowPrint == 0){
        if(counter == 100){
            nowPrint = 1;
            break;
        }
        cin >> input;
        valInt = 0;
        if(input[0] == 'A'){
            string value = input.substr(1);
            // cout << value << endl;
            for(int i = 0; i < value.length(); i++){
                valInt = valInt*10 + value[i] - '0';
            }
            // cout << valInt << endl;
            // cout << input[1] - '0' << endl;
            insert(myTree->Root , valInt, myTree);
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
    //Scanning first letter to discern whether user wants to insert or delete
    /*for(int i = 0; i < 9; i++){
        cin >> input;
        if(input[0] == 'A'){
            cout << input[1] - '0' << endl;
            insert(myTree->Root , input[1] - '0', myTree);
        }
    }
    // if(input[0] == 'A'){
    //     cout << input[1] - '0' << endl;
    //     insert(myTree->Root , input[1] - '0', myTree);
    // }else{

    // }
    // cout << "After insertion, root is: " << myTree->Root->getValue() << endl;
    // cin >> input;
    // cout << input << endl;

    // //Scanning first letter to discern whether user wants to insert or delete
    // if(input[0] == 'A'){
    //     cout << input[1] - '0' << endl;
    //     insert(myTree->Root , input[1] - '0', myTree);
    // }else{

    // }
    // cout << "After insertion, root is: " << myTree->Root->getValue() << endl;
    // cin >> input;
    // cout << input << endl;

    //Scanning first letter to discern whether user wants to insert or delete
    // if(input[0] == 'A'){
    //     cout << input[1] - '0' << endl;
    //     insert(myTree->Root , input[1] - '0', myTree);
    // }else{

    // }
    // cout << "After insertion, root is: " << myTree->Root->getValue() << endl;
    preorder(myTree->Root);
    */
    return 0;
}