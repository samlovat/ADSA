#include <iostream>
using namespace std;
#include <string.h>

int tracker = 0;

class Node{
    private:
        string status;
        string value;
        Node* nextNode;
    public:
        //Constructor recursively makes 26 nodes by default
        Node(){ 
            //Preset Node value
            this->status = "never used"; 
            this->value = "";
            tracker++;
            if(tracker < 26){
                this->nextNode = new Node;
            }else{
                this->nextNode = nullptr;
            }
        }
        string getValue(){ return this->value; }
        void setValue(string newValue){ this->value = newValue; this->status = "occupied"; }
        string getStatus(){ return this->status; }
        Node* getNextNode(){ return this->nextNode; }
        void setNextNode(Node* newNode){ this->nextNode = newNode; }
        void kill(){ this->status = "tombstone"; this->setValue(""); }
};

class HashTable{
    private:
        Node* head;
    public:
        HashTable(){ 
            this->head = new Node; 
            Node* currNode = this->head;
            //Making last node point to head for cyclic behaviour of hash table
            while(currNode->getNextNode() != nullptr){
                currNode = currNode->getNextNode();
            }
            currNode->setNextNode(this->head);
        }
        Node* getHead(){ return this->head; }
        int compareCurrNode(Node* currNode, string findme){       //Helper function for Node* search()
            if(currNode->getValue() == ""){
                //If index is empty return 0
                return 0;
            }else if(currNode->getValue() == findme){ 
                //If index contains 'findme' return 1      
                return 1;
            }else{
                //If index contains another word return 2
                return 2;
            }
        }
        Node* search(string findme){
            // cout << "Working on " << findme << endl;
            int index;                          //Use numerical index by casting last char of 'findme' into integer
            Node* currNode = this->head;        //To point to the node currently being looked at
            index = (int)findme[findme.length() - 1];
            //Move to correct index
            for(int i = 97; i < index; i++){    //Start at i=97 because ASCII value of 'a' - 'z' is 97 - 122 
                currNode = currNode->getNextNode();
            }
                int found = 0;                  //Variable to track if 'findme' has been found, also counter so that while loop checks at most 26 Nodes 
                while(found != 26){
                    if(this->compareCurrNode(currNode, findme) != 2){
                        found = 26;
                        return currNode;
                    }else{
                        currNode = currNode->getNextNode();
                        found++;
                    }
                }
            return nullptr; 
        }
        void insert(string newNode){
            Node* indexForInsert = this->search(newNode);    //Where to place node 
            if(indexForInsert == nullptr){       //HashTable is full
                return;
            }else{
                indexForInsert->setValue(newNode);
            }
            return;
        }
        void del(string delNode){
            Node* indexForDelete = this->search(delNode);    //Where to place node 
            if(indexForDelete == nullptr){       //Node doesn't exist
                return;
            }else{
                indexForDelete->kill();
            }
            //Continue through nodes, if node value is <= 'delNode' move to deleted node and repeat
            Node* currNode = indexForDelete->getNextNode();
            int valueToBeReplaced;  //Tracks the index of empty node which is searching for a successor
            valueToBeReplaced = (int)delNode[delNode.length() - 1];
            int found = 0;          //While loop state variable
            while(found == 0){
                int index;
                string currValue = currNode->getValue();
                index = (int)currValue[currValue.length() - 1];
                if(index == 97){
                    return;             //We have done a cycle of table and repairing is complete
                }else if(currValue == ""){
                    return;             //Run into empty node, repairing terminated
                }
                if(index <= valueToBeReplaced){
                    indexForDelete->setValue(currValue);
                    currNode->kill();
                    indexForDelete = currNode;
                }
                currNode = currNode->getNextNode();
            }
        }
        void print(){
            Node* currNode = this->head;
            int lastNode = 0;
            while(lastNode == 0){
                if(currNode->getValue() != ""){
                    cout << currNode->getValue() << " ";
                }
                currNode = currNode->getNextNode();
                if(currNode == this->head){
                    lastNode = 1;
                }
            }
        }
};

int main(){
    HashTable* myHash = new HashTable;
    string input;                                                           //String to hold line of input
    int nowPrint = 0;                                                       //State variable for while loop
    string value;                                                           //String to hold numerical value before int conversion
    int counter = 0;                                                        //Counter to ensure 0 <= instructions <= 100
    while(nowPrint == 0){
        if(counter == 27){                                                 //If too many instructions, break out of while loop
            nowPrint = 1;
            break;
        }
        cin >> input;                                                       //Read user input
        if(input[0] == 'A'){
            value = input.substr(1);                                        //If instruction starts with 'A', split input to attain value 
            myHash->insert(value);                          //Insert new node
        }else if(input[0] == 'D'){
            value = input.substr(1);                                        //If instruction starts with 'D', split input to attain value 
            myHash->del(value);                             //Delete node 
        }else{
            nowPrint = 1;
        }                                               
        counter++;                                                          //Increase counter after an instruction
    }
    myHash->print();
    return 0;
}