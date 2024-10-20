#include <iostream>
using namespace std;
#include <string.h>
#include <vector>
#include <sstream>

class Node{
    private:
        Node* parent;
        int distance;
        string links;
        string buildCost;
        string destroyCost;
    public:
        Node(string _links, string _buildCost, string _destroyCost){
            this->links = _links;
            this->buildCost = _buildCost;
            this->destroyCost = _destroyCost;
            this->parent = nullptr;
            this->distance = 52;    //This acts as the distance being infinity since the largest build cost is z = 51
        }
        //Getters and Setters
        Node* getParent(){return this->parent;}
        void setParent(Node* newParent){this->parent = newParent;}
        int getDistance(){return this->distance;}
        void setDistance(int newDistance){this->distance = newDistance;}
        string getLinks(){return this->links;}
        void setLinks(string newLinks){this->links = newLinks;}
        string getBuildCosts(){return this->buildCost;}
        void setBuildCosts(string newBuildCosts){this->buildCost = newBuildCosts;}
        string getDestroyCosts(){return this->destroyCost;}
        void setDestroyCosts(string newDestroyCosts){this->destroyCost = newDestroyCosts;}
};

class Map{
    private:
        vector<Node*> Nodes;
        vector<vector<Node*>> connectedGroups;
    public:
        Map(vector<Node*> newNodes){
            this->Nodes = newNodes;
            
            //Collect Strongly Connected Groups
            Node* currNode = Nodes[0];
            vector<Node*> theMap;
            theMap.push_back(currNode);
            Nodes[0] = nullptr;
            int minBuildCost = 53;
            int mapIndexer = 0;
            int linkExisted = 0;
            int runningCost = 0;
            while(currNode != nullptr){
                Node* minNode;
                Node* parentNode;
                int index;
                for(int i = 0; i < currNode->getLinks().length(); i++){
                    if(currNode->getLinks()[i] == '1'){
                        if(Nodes[i] != nullptr){
                            theMap.push_back(Nodes[i]);
                            Nodes[i] = nullptr;
                            linkExisted = 1;
                        }
                    }else if(currNode->getLinks()[i] == '0' && Nodes[i] != nullptr){
                        char cost = currNode->getBuildCosts()[i];
                        int costASCII = (int)cost;
                        if(costASCII <= 90){
                            costASCII = costASCII - 65;
                        }else{
                            costASCII = costASCII - 71;
                        }
                        if(costASCII < minBuildCost && costASCII != 0){
                            minBuildCost = costASCII;
                            minNode = Nodes[i];
                            parentNode = currNode;
                            index = i;
                        }
                    }
                }
                if(linkExisted == 0 && theMap.size() == mapIndexer + 1){
                    theMap.push_back(minNode);
                    Nodes[index] = nullptr;
                    //parentNode->setLinks(parentNode->getLinks()) but add the link between parentNode and minNode
                    string newLink = parentNode->getLinks();
                    newLink[index] = '1';
                    parentNode->setLinks(newLink);
                    //minNode->setLinks(minNode->getLinks()) but ^^
                    newLink = minNode->getLinks();
                    for(int i = 0; i < parentNode->getBuildCosts().length(); i++){
                        if(parentNode->getBuildCosts()[i] == 'A'){
                            index = i;
                            break;
                        }
                    }
                    newLink[index] = '1';
                    minNode->setLinks(newLink);
                    mapIndexer = 0;
                    linkExisted = 0;
                    runningCost += minBuildCost;
                    minBuildCost = 53;
                }else if(linkExisted == 0 && theMap.size() > mapIndexer + 1){
                    mapIndexer++;
                }else if(linkExisted == 1){
                    mapIndexer = 0;
                    minBuildCost = 53;
                    linkExisted = 0;
                }
                int finished = 1;
                for(int i = 0; i < Nodes.size(); i++){
                    if(Nodes[i] != nullptr){
                        finished = 0;
                    }
                }
                if(finished == 1){
                    currNode = nullptr;
                }else{
                    currNode = theMap[mapIndexer];
                }
            }
            this->Nodes = newNodes;
        }
        void print(){
            for(int i = 0; i < Nodes.size(); i++){
                cout << Nodes[i]->getLinks() << endl;
            }
        }

};

int main(){
    //Read input
    string input, tok;                              //Input line and token variables
    vector<string> tokens, build, destroy;          //Vector to contain strings around each delimiter (comma)
    
    //Tokenise arrays into vectors for node information
    cin >> input;
    stringstream myStream(input);                   //To read input as stream and tokenise
    while(getline(myStream, tok, ',')){
        tokens.push_back(tok);
    }
    cin >> input;
    myStream.clear();                               //Clear for next input
    myStream.str(input);                            //Fill with new input
    while(getline(myStream, tok, ',')){
        build.push_back(tok);
    }
    cin >> input;
    myStream.clear();                               
    myStream.str(input); 
    while(getline(myStream, tok, ',')){
        destroy.push_back(tok);
    }

    vector<Node*> myNodes;    
    for(size_t i = 0; i < tokens.size(); i++){
        myNodes.push_back(new Node(tokens[i], build[i], destroy[i]));
    }
    Map myMap(myNodes);
    myMap.print();
    // vector<string>::iterator itr;
    // for(auto itr = tokens.begin(); itr != tokens.end(); itr++){
    //     cout << *itr << endl;
    // }
    // for(auto itr = build.begin(); itr != build.end(); itr++){
    //     cout << *itr << endl;
    // }
    // for(auto itr = destroy.begin(); itr != destroy.end(); itr++){
    //     cout << *itr << endl;
    // }

    //Collect Strongly Linked Components

    return 0;
}