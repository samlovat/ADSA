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
        Map(vector<Node*> newNodes){    //Default Constructor
            this->Nodes = newNodes;
            this->runningCost = 0;
        }
        void connectNodes(){            //Iterates through Nodes and constructs the minimum cost roads so that there is a path to and from each Node
            if(Nodes.size() == 1){      //If only 1 node, cost is 0, return
                this->runningCost = 0;
                return;
            }
            vector<Node*> newNodes = Nodes;     //Copy of Nodes to refer to later
            Node* currNode = Nodes[0];          //Node pointer to iterate 
            vector<Node*> theMap;               //Vector to move nodes once they are dealt with
            theMap.push_back(currNode);         
            Nodes[0] = nullptr;                 //Delete currNode from Nodes vector (This is why newNodes exists)
            int minBuildCost = 53;              //Variable to track road with smallest construction cost. Begins at 53 since 'z = 51'
            int mapIndexer = 0;                 //theMap iterator
            int linkExisted = 0;                //Variable to track if an existing road is found
            Node* minNode;                      //Tracks the node which boasted the road with smallest construction cost
            Node* parentNode = nullptr;         //Tracks parent of new road to access and alter links (its road list)      
            int index = -1;                     //Tracks index of min Node
            while(currNode != nullptr){
                for(size_t i = 0; i < currNode->getLinks().length(); i++){
                    if(currNode->getLinks()[i] == '1'){         //If road exists and the destination Node hasn't 
                        if(Nodes[i] != nullptr){                //been moved to theMap, add to theMap and delete
                            theMap.push_back(Nodes[i]);         //from Nodes.
                            Nodes[i] = nullptr;
                            linkExisted = 1;                    //Set state variable to reflect that an existing 
                        }                                       //road was found
                    }else if(currNode->getLinks()[i] == '0' && Nodes[i] != nullptr){    //If road doesn't exist, and if Node hasn't been moved. (this also checks for when trying to check a Node's road to itself)
                        char cost = currNode->getBuildCosts()[i];   
                        int costASCII = (int)cost;
                        if(costASCII <= 90){                //Cast construction cost to integer value
                            costASCII = costASCII - 65;
                        }else{
                            costASCII = costASCII - 71;
                        }
                        if(costASCII < minBuildCost){       //If new min is found, change all associated 
                            minBuildCost = costASCII;       //tracker variables
                            minNode = Nodes[i];
                            parentNode = currNode;
                            index = i;
                        }
                    }
                }
                if(linkExisted == 0 && theMap.size() == (size_t)(mapIndexer + 1)){  //If there were no existing roads and we have iterated through all nodes in theMap
                    theMap.push_back(minNode);                  //Construct new min road and add to theMap
                    Nodes[index] = nullptr;                     //Remove from Nodes
                    string newLink = parentNode->getLinks();    //Change parentNode's links(road) information to
                    newLink[index] = '1';                       //add new construction
                    parentNode->setLinks(newLink);
                    newLink = minNode->getLinks();
                    for(size_t i = 0; i < newNodes.size(); i++){    //Compare parentNode's buildcosts to newNodes to find index of parentNode
                        if(parentNode->getBuildCosts() == newNodes[i]->getBuildCosts()){
                            index = i;
                        }
                    }
                    newLink[index] = '1';
                    minNode->setLinks(newLink);     //Using parentNode index, set new links of minNode
                    mapIndexer = 0;                 //Reset mapIndex iterator 
                    linkExisted = 0;                //Reset State variables 
                    minBuildCost = 53;                    
                    this->runningCost += minBuildCost;      //Add construction to runningcost               
                }else if(linkExisted == 0 && theMap.size() > (size_t)(mapIndexer + 1)){ 
                    mapIndexer++;                   //If no existing roads found but there are more theMap Nodes 
                    currNode = theMap[mapIndexer];  //to iterate, move on to next Node
                    continue;
                }else if(linkExisted == 1){         //If existing link was found, reset tracking variables
                    mapIndexer = 0;
                    minBuildCost = 53;
                    linkExisted = 0;
                }
                int finished = 1;                   //State variable to check if all Nodes have been checked 
                for(size_t i = 0; i < Nodes.size(); i++){
                    if(Nodes[i] != nullptr){        //If Nodes isn't empty, finished = 0
                        finished = 0;
                    }
                }
                if(finished == 1){
                    currNode = nullptr;             //End while loop
                }else{
                    parentNode = nullptr;           //Reset ParentNode and move to next Node in theMap
                    currNode = theMap[mapIndexer];
                }
            }
            this->Nodes = newNodes;                 //Refill Nodes member variable
        }
        void deleteRoads(){             //Iterates through existing roads and only keeps roads with maximum destructionCost
            if(Nodes.size() == 1){
                this->runningCost = 0;  //If only 1 node, cost is 0, return
                return;
            }
            //Start from start of node list and use Jarnik-Prim Algorithm to keep only adjacent edges with the 
            //largest destruction cost (as opposed to the smallest distance)
            Node* currNode = Nodes[0];
            int maxDestCost = 0;        //Tracks the total destruction cost of all remaining roads after algorithm 
            int finalDestCost = 0;      //Tracks the total destruction cost of all roads before destruction. The difference between these two will equal the cost of all destructions.
            vector<Node*> priorityQueue;       //Priority queue to track Nodes for algorithm
            priorityQueue.push_back(currNode);
            while(currNode != nullptr){
                if(currNode->getDistance() != 53){
                    maxDestCost += currNode->getDistance();     //Add accepted road's destruction cost to maxDestCost
                }
                priorityQueue.pop_back();               //remove from queue 
                currNode->setDistance(53);              //Set node's distance to 53 (this can never be changed afterwards)
                for(size_t i = 0; i < currNode->getLinks().length(); i++){
                    if(currNode->getLinks()[i] == '1'){     //If road exists
                        char destCost = currNode->getDestroyCosts()[i];
                        int costASCII = (int)destCost;
                        if(costASCII <= 90){            //Cast destruction cost to correct integer 
                            costASCII = costASCII - 65;
                        }else{
                            costASCII = costASCII - 71;
                        }
                        if(costASCII > Nodes[i]->getDistance() || (costASCII == 0 && Nodes[i]->getDistance() == 0)){    //If cost is greater than the Node's current distance, or if both are equal to 0 
                            Nodes[i]->setDistance(costASCII);           //Set new distance 
                            finalDestCost += Nodes[i]->getDistance();   //Add to total dest cost
                            for(size_t k = 0; k < priorityQueue.size(); k++){
                                if(Nodes[i]->getBuildCosts() == priorityQueue[k]->getBuildCosts()){
                                    priorityQueue.erase(priorityQueue.begin() + k);         //If Node whose distance was changed exists in the priority queue already, delete it to avoid duplication upon insertion
                                }
                            }
                            vector<Node*>::iterator j;
                            if(priorityQueue.empty()){
                                priorityQueue.push_back(Nodes[i]);      //If queue is empty, push_back
                            }else{
                                int inserted = 0;
                                for(j = priorityQueue.begin(); j != priorityQueue.end(); j++){
                                    if(Nodes[i]->getDistance() < (*j)->getDistance()){
                                        priorityQueue.insert(j, Nodes[i]);          //Iterates through queue to ensure node is inserted based on its distance
                                        inserted = 1;
                                        break;
                                    }
                                }
                                if(inserted == 0){                          
                                    priorityQueue.push_back(Nodes[i]);      //If distance wasn't smaller than 
                                }
                            }
                        }else if(costASCII < Nodes[i]->getDistance() && Nodes[i]->getDistance() != 53){
                            finalDestCost += costASCII;
                        }
                    }
                }
                if(priorityQueue.empty()){
                    currNode = nullptr;
                }else{
                    currNode = priorityQueue[priorityQueue.size()-1];
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