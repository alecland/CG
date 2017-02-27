#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Factory {
    public:
    int id;
    int playerId;
    int cyborgsCount;
    int cyborgsProd;
    int dist[15];
    bool isChecked[15];
    
    Factory () : playerId(0), cyborgsCount(0), cyborgsProd(0) {}
    
    void reset() {
        for (int i = 0; i < 15; i++) {
            if (i != id)
                isChecked[i] = false;
        }        
    }
};

class Link {
    public:
    Factory* factoryFrom;
    Factory* factoryTo;
    int distance;
    
    Link (Factory* p_from, Factory* p_to, int p_dist) : factoryFrom(p_from), factoryTo(p_to), distance(p_dist) {}
};

class Troop {
    public:
    int id;
    int playerId;
    int cyborgsCount;
    int turnsCount;  
    Factory* factoryFrom;
    Factory* factoryTo;
    
    Troop (int p_id, int p_cyborgsCount, int p_turnsCount, Factory* p_from, Factory* p_to) : playerId(p_id), cyborgsCount(p_cyborgsCount), turnsCount(p_turnsCount), factoryFrom(p_from), factoryTo(p_to) {}
};

class Game {
    public:
    Link** links;
    Factory** factories;
    Troop* troops;
    int factoryCount;
    int linkCount;
    
    int getMorePopFactory(int p_playerId)
    {
        int maxCyborgPop = 0;
        int result = -1;
        for (int i = 0; i < factoryCount; i++) {
            if (factories[i]->playerId == p_playerId && factories[i]->cyborgsCount > maxCyborgPop) {
                result = i;
                maxCyborgPop = factories[i]->cyborgsCount;
            }
        }
        return result;
    }
    
    int getWorthyTarget(int p_playerId, int p_fromId) {
        int minCyborgPop = 50000;
        int maxProd = 3;
        int result = -1;
        while (result == -1 && maxProd != -1) {
            for (int i = 0; i < factoryCount; i++) {
                if (factories[i]->playerId != p_playerId 
                 && !factories[p_fromId]->isChecked[i]
                && factories[i]->cyborgsProd == maxProd
                && factories[i]->cyborgsCount < minCyborgPop)
                {
                    result = i;
                    maxProd = factories[i]->cyborgsProd;
                    minCyborgPop = factories[i]->cyborgsCount;
                }
                
            }
             maxProd--;
        }
        
        if (result != -1)
            factories[p_fromId]->isChecked[result] = true;
            
        return result;
    }
    
    void resetChecks() {
        for (int i = 0; i < factoryCount; i++) {
            factories[i]->reset();
        }
    }
};

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    Game game;    
    
    Factory** factories = new Factory*[15]; // Use the max number of factories
    cin >> game.factoryCount; cin.ignore();
    for (int i = 0; i < game.factoryCount; i++) {
        factories[i] = new Factory();
        factories[i]->id = i;
        factories[i]->dist[i] = 0;
        factories[i]->isChecked[i] = true;
    }
    game.factories = factories;
    
    Link** links = new Link*[98];
    cin >> game.linkCount; cin.ignore();
    
    for (int i = 0; i < game.linkCount; i++) {
        int factory1;
        int factory2;
        int distance;
        cin >> factory1 >> factory2 >> distance; cin.ignore();
        links[i] = new Link(factories[factory1], factories[factory2], distance);
        factories[factory1]->dist[factory2] = distance;
        factories[factory2]->dist[factory1] = distance;
    }
    game.links = links;

    int troopsCount;
    //Troop* troops = new Troop[200];
    // game loop
    while (1) {
        game.resetChecks();
        int entityCount; // the number of entities (e.g. factories and troops)
        cin >> entityCount; cin.ignore();
        for (int i = 0; i < entityCount; i++) {
            int entityId;
            string entityType;
            int arg1;
            int arg2;
            int arg3;
            int arg4;
            int arg5;
            cin >> entityId >> entityType >> arg1 >> arg2 >> arg3 >> arg4 >> arg5; cin.ignore();
            if (entityType.compare("FACTORY") == 0)
            {
                factories[entityId]->playerId = arg1;
                factories[entityId]->cyborgsCount = arg2;
                factories[entityId]->cyborgsProd = arg3;                
            }
            else
            {
                //cerr << entityId << endl;
                //Troop l_troop(arg1, arg4, arg5, factories[arg2], factories[arg3]);
                //troops[troopsCount] = l_troop
                //troops[troopsCount].id = entityId;
                //troopsCount++;
            }
            //game.troops = troops;
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        
        // Find my factories with the more cyborgs
        int from = game.getMorePopFactory(1);
        int to = -1;
        if (from != -1)
            to = game.getWorthyTarget(1, from);

        cout << "WAIT;";
        
        while (to != -1)
        {
            if (from != -1) {
                int troops = factories[to]->cyborgsCount + factories[from]->dist[to] * factories[to]->cyborgsProd + 1;
            
                // Any valid action, such as "WAIT" or "MOVE source destination cyborgs"
                if (factories[from]->cyborgsCount >= troops)
                {
                    cout << "MOVE " << from << " " << to << " " << troops << ";";
                    factories[from]->cyborgsCount -= troops;
                }
            }
            from = game.getMorePopFactory(1);
            if (from != -1)
                to = game.getWorthyTarget(1, from);
            else
                to = -1;
        }
        cout << "WAIT" << endl;
    }
}
