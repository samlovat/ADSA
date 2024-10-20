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
            this->distance = 0;    //In the eventual Jarnik-Prim Alogrithm, edges are kept if they have the largest destruction cost, this therefore starts at 0
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
        int runningCost;
    public:
        Map(vector<Node*> newNodes){
            this->Nodes = newNodes;
            if(Nodes.size() == 1){
                this->runningCost = 0;
                return;
            }
            
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
                        if(costASCII < minBuildCost && costASCII != 0){
                            minBuildCost = costASCII;
                            minNode = Nodes[i];
                            //cout << "1" << endl;
                            parentNode = currNode;
                            index = i;
                        }
                    }
                }
                if(linkExisted == 0 && theMap.size() == (size_t)(mapIndexer + 1)){
                    theMap.push_back(minNode);
                    Nodes[index] = nullptr;                    
                    //parentNode->setLinks(parentNode->getLinks()) but add the link between parentNode and minNode
                    // cout << "2" << endl;
                    string newLink = parentNode->getLinks();
                    newLink[index] = '1';
                    // cout << "3" << endl;
                    parentNode->setLinks(newLink);
                    //minNode->setLinks(minNode->getLinks()) but ^^
                    newLink = minNode->getLinks();
                    // cout << "4" << endl;
                    // for(size_t i = 0; i < parentNode->getBuildCosts().length(); i++){
                    //     if(parentNode->getBuildCosts()[i] == 'A'){
                    //         index = i;
                    //         break;
                    //     }
                    // }
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
            //Start from start of node list and use Jarnik-Prim Algorithm to keep only adjacent edges with the largest destruction cost
            //(as opposed to the smallest distance)
            currNode = Nodes[0];
            int maxDestCost = 0;
            int finalDestCost = 0;
            // cout << "Original maxDestCost: " << maxDestCost << endl;
            theMap.clear();
            theMap.push_back(currNode);
            while(currNode != nullptr){
                if(currNode->getDistance() != 53){
                    maxDestCost += currNode->getDistance();
                }
                // cout << "MaxDestCost: " << maxDestCost << endl;
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
                        if(costASCII > Nodes[i]->getDistance()){
                            // cout << "Setting Parent" << endl;
                            Nodes[i]->setDistance(costASCII);
                            // cout << "Setting distance of node to " << Nodes[i]->getDistance() << endl;
                            finalDestCost += Nodes[i]->getDistance();
                            Nodes[i]->setParent(currNode);
                            vector<Node*>::iterator j;
                            if(theMap.empty()){
                                theMap.push_back(Nodes[i]);
                                // cout << "Pushed back first node" << endl;
                            }else{
                                int inserted = 0;
                                for(j = theMap.begin(); j != theMap.end(); j++){
                                    // cout << "begun iteration for theMap of size: " << theMap.size() << endl;
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
                    // cout << "cont" << endl;
                    currNode = theMap[theMap.size()-1];
                }
            }
            // cout << "Final MaxDestCost: " << maxDestCost << " and runningCost pre maxDestCost " << runningCost << " and finalCostDest " << finalDestCost << endl;
            this->runningCost += finalDestCost - maxDestCost;
            // currNode = Nodes[Nodes.size() - 1];
            // int treePath = 0;
            // int counter = 0;
            // while(counter != Nodes.size()){
            //     for(int i = 0; i < Nodes.size(); i++){
            //         for(int j = 0; j < Nodes[i]->getParent()->getBuildCosts().length(); j++){
            //             if(currNode->getParent()->getBuildCosts()[j] == 'A'){
            //                 // treePath = j;

            //                 break;
            //             }
            //         }
            //         if(currNode->getLinks()[i] == '1'){
            //             if(i != treePath){
            //                 runningCost += currNode->getDestroyCosts()[i];
            //                 string newLinks = currNode->getLinks();
            //                 newLinks[i] = '0';
            //                 currNode->setLinks(newLinks);
            //                 newLinks = Nodes[i]->getLinks();
            //                 newLinks[Nodes.size() - 1 - counter] = '0';
            //                 Nodes[i]->setLinks(newLinks);
            //             }
            //         }
            //     }
            //     counter++;
            //     if(counter != Nodes.size()){
            //         currNode = Nodes[Nodes.size() - 1 - counter];
            //     }
            // }
        }
        void print(){
            // int nodeindex;
            // for(size_t i = 0; i < Nodes.size(); i++){
            //     if(Nodes[i]->getParent() != nullptr){
            //         for(size_t j = 0; j < Nodes[i]->getParent()->getBuildCosts().size(); j++){
            //                 if(Nodes[i]->getParent()->getBuildCosts()[j] == 'A'){
            //                     nodeindex = j;
            //                 }
            //         }
            //     }else{
            //         nodeindex = 100;
            //     }
            //     // cout << nodeindex << " | " << Nodes[i]->getDistance() << endl;
            // }
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