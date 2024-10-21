#include <iostream>
using namespace std;
#include <string.h>
#include <vector>
#include <sstream>

class Node{                 //Node class, represents one Node/City and its associated roads and costs
    private:
        int distance;               //For Jarnik-Prim Algorithm
        string links;               //Contains roads between Nodes
        string buildCost;           //Cost to build roads
        string destroyCost;         //Cost to destroy roads
    public:
        Node(string _links, string _buildCost, string _destroyCost){    //Default Constructor
            this->links = _links;                                   
            this->buildCost = _buildCost;
            this->destroyCost = _destroyCost;
            this->distance = 0;    //In the eventual Jarnik-Prim Alogrithm, edges are kept if they have the largest destruction cost, this therefore starts at 0
        }
        //Getters and Setters
        int getDistance(){return this->distance;}
        void setDistance(int newDistance){this->distance = newDistance;}
        string getLinks(){return this->links;}
        void setLinks(string newLinks){this->links = newLinks;}
        string getBuildCosts(){return this->buildCost;}
        void setBuildCosts(string newBuildCosts){this->buildCost = newBuildCosts;}
        string getDestroyCosts(){return this->destroyCost;}
        void setDestroyCosts(string newDestroyCosts){this->destroyCost = newDestroyCosts;}
};

class Map{              //Map class, contains all cities and road relationships
    private:
        vector<Node*> Nodes;    //Vector of all Nodes to refer to
        int runningCost;        //Running total of cost required in road optimisation
    public:
        Map(vector<Node*> newNodes){
            this->Nodes = newNodes;
        }
        void connectNodes(){
            if(Nodes.size() == 1){
                this->runningCost = 0;
                return;
            }
            vector<Node*> newNodes = Nodes;
            //Collect Strongly Connected Groups
            Node* currNode = Nodes[0];
            vector<Node*> theMap;
            theMap.push_back(currNode);
            Nodes[0] = nullptr;
            int minBuildCost = 53;
            int mapIndexer = 0;
            int linkExisted = 0;
            int runningCost = 0;
            Node* minNode;
            Node* parentNode = nullptr;
            int index = -1;
            while(currNode != nullptr){
                for(size_t i = 0; i < currNode->getLinks().length(); i++){
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
                        if(costASCII < minBuildCost){
                            minBuildCost = costASCII;
                            minNode = Nodes[i];
                            parentNode = currNode;
                            index = i;
                        }
                    }
                }
                if(linkExisted == 0 && theMap.size() == (size_t)(mapIndexer + 1)){
                    theMap.push_back(minNode);
                    Nodes[index] = nullptr;                    
                    //parentNode->setLinks(parentNode->getLinks()) but add the link between parentNode and minNode
                    string newLink = parentNode->getLinks();
                    newLink[index] = '1';
                    parentNode->setLinks(newLink);
                    //minNode->setLinks(minNode->getLinks()) but ^^
                    newLink = minNode->getLinks();
                    for(size_t i = 0; i < newNodes.size(); i++){
                        if(parentNode->getBuildCosts() == newNodes[i]->getBuildCosts()){
                            index = i;
                        }
                    }
                    newLink[index] = '1';
                    minNode->setLinks(newLink);
                    mapIndexer = 0;
                    linkExisted = 0;
                    runningCost += minBuildCost;
                    minBuildCost = 53;
                }else if(linkExisted == 0 && theMap.size() > (size_t)(mapIndexer + 1)){
                    mapIndexer++;
                    currNode = theMap[mapIndexer];
                    continue;
                }else if(linkExisted == 1){
                    mapIndexer = 0;
                    minBuildCost = 53;
                    linkExisted = 0;
                }
                int finished = 1;
                for(size_t i = 0; i < Nodes.size(); i++){
                    if(Nodes[i] != nullptr){
                        finished = 0;
                    }
                }
                if(finished == 1){
                    currNode = nullptr;
                }else{
                    parentNode = nullptr;
                    currNode = theMap[mapIndexer];
                }
            }
            this->runningCost = runningCost;
            this->Nodes = newNodes;
        }
        void deleteRoads(){
            if(Nodes.size() == 1){
                this->runningCost = 0;
                return;
            }
            //Start from start of node list and use Jarnik-Prim Algorithm to keep only adjacent edges with the largest destruction cost
            //(as opposed to the smallest distance)
            Node* currNode = Nodes[0];
            int maxDestCost = 0;
            int finalDestCost = 0;
            vector<Node*> theMap;
            theMap.push_back(currNode);
            while(currNode != nullptr){
                if(currNode->getDistance() != 53){
                    maxDestCost += currNode->getDistance();
                }
                currNode->setDistance(53);
                theMap.pop_back();
                for(size_t i = 0; i < currNode->getLinks().length(); i++){
                    if(currNode->getLinks()[i] == '1'){
                        char destCost = currNode->getDestroyCosts()[i];
                        int costASCII = (int)destCost;
                        if(costASCII <= 90){
                            costASCII = costASCII - 65;
                        }else{
                            costASCII = costASCII - 71;
                        }
                        if(costASCII > Nodes[i]->getDistance() || (costASCII == 0 && Nodes[i]->getDistance() == 0)){
                            Nodes[i]->setDistance(costASCII);
                            finalDestCost += Nodes[i]->getDistance();
                            for(size_t k = 0; k < theMap.size(); k++){
                                if(Nodes[i]->getBuildCosts() == theMap[k]->getBuildCosts()){
                                    theMap.erase(theMap.begin() + k);
                                }
                            }
                            vector<Node*>::iterator j;
                            if(theMap.empty()){
                                theMap.push_back(Nodes[i]);
                            }else{
                                int inserted = 0;
                                for(j = theMap.begin(); j != theMap.end(); j++){
                                    if(Nodes[i]->getDistance() < (*j)->getDistance()){
                                        theMap.insert(j, Nodes[i]);
                                        inserted = 1;
                                        break;
                                    }
                                }
                                if(inserted == 0){
                                    theMap.push_back(Nodes[i]);
                                }
                            }
                        }else if(costASCII < Nodes[i]->getDistance() && Nodes[i]->getDistance() != 53){
                            finalDestCost += costASCII;
                        }
                    }
                }
                if(theMap.empty()){
                    currNode = nullptr;
                }else{
                    currNode = theMap[theMap.size()-1];
                }
            }
            this->runningCost += finalDestCost - maxDestCost;
        }
        void print(){
            cout << this->runningCost << endl;
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
    myMap.connectNodes();
    myMap.deleteRoads();
    myMap.print();
    return 0;
}