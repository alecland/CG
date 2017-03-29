#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define SIMU_DEPTH 25
#define BOMBS_COUNT 4

class Graph {
    public:
 
    map<int, map<int, int>> dist;
    map<int, map<int, int>> dist_opt;
    map<int, map<int, int>> next;
    int dimension;
   
    //class Link { public int a, b; Link (int a, int b) { this.a = a; this.b = b; } }
    Graph (map<int, map<int, int>>& p_dist, int p_dimension) {
        dist = p_dist;
        dimension = p_dimension;
        floyd_warshall();
    }
   
    void floyd_warshall () {
        int n = dimension;
        dist_opt.clear();
        next.clear();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                next[i][j] = j;
                dist_opt[i][j] = dist[i][j];
            }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (i != j)
                    for (int k = 0; k < n; k++) {
                        if (k != i && k != j && dist_opt[i][k]+dist_opt[k][j] < dist_opt[i][j] ) {
                            dist_opt[i][j] = dist_opt[i][k]+dist_opt[k][j];
                            next[i][j] = k;
                        }
                    }
            }
    }
 
};

class Factory;


class Troop {
    public:
    int id;
    int playerId;
    int cyborgsCount;
    int turnsCount;  
    int factoryFrom;
    int factoryTo;
   
    Troop () {} 
    Troop (int p_id, int p_cyborgsCount, int p_turnsCount, int p_from, int p_to) : playerId(p_id), cyborgsCount(p_cyborgsCount), turnsCount(p_turnsCount), factoryFrom(p_from), factoryTo(p_to) {}
};

class Factory {
    public:
    int id;
    int playerId;
    int cyborgsCount;
    int cyborgsProd;
    int dist[15];
    int virtualPop[SIMU_DEPTH];
    int virtualOwner[SIMU_DEPTH];
    int virtualProd[SIMU_DEPTH];
    bool isChecked[15];
    bool isAvailable; // Flag if already bombing this turn or defending
    bool isDisabled;
    vector<Troop> incomingTroops; 
    
    Factory () : playerId(0), cyborgsCount(0), cyborgsProd(0), isAvailable(true), isDisabled(false) {
        for (int i = 0; i < 15; i++) {
            if (i != id)
                dist[i] = -1;
        }
    }
    
    void printSimu() {
        for (int i = 0; i < SIMU_DEPTH; i++) {
            cerr << "Turn " << i << ": " << virtualPop[i] << "/" << virtualOwner[i] << "/" << virtualProd[i] << endl;
        }
    }
	
	void initSimu() {
	    virtualOwner[0] = playerId;
	    virtualProd[0] = cyborgsProd;
	    if (playerId != 1)
	        virtualPop[0] = - cyborgsCount;
	    else
	        virtualPop[0] = cyborgsCount;
	}
	
	void simuTurn(int p_turn) {
	    //cerr << "Simu turn " << p_turn << endl;
	    virtualOwner[p_turn] = virtualOwner[p_turn - 1];
	    virtualProd[p_turn] = virtualProd[p_turn - 1];
	    virtualPop[p_turn] = virtualPop[p_turn -1] + virtualOwner[p_turn] * virtualProd[p_turn];
	}
	
	void simuTroops(int p_turn) {
	    //cerr << "Simu troops " << p_turn << endl;
    	for (int j = 0; j < incomingTroops.size(); j++) {
    	    if (incomingTroops[j].turnsCount == p_turn) {
        	    if (virtualOwner[p_turn] == 0)
        	    {
        	        if (virtualPop[p_turn] >= incomingTroops[j].cyborgsCount) {
        	            virtualPop[p_turn] += incomingTroops[j].cyborgsCount;
        	        }
        	        else {
        	            int remainingTroops = incomingTroops[j].cyborgsCount - virtualPop[p_turn];
        	            virtualPop[p_turn] = 0;
        	            virtualPop[p_turn] += incomingTroops[j].playerId * remainingTroops;     
        	            virtualOwner[p_turn] = incomingTroops[j].playerId;
        	        }
        	    }
        	    else
        	    {
        	        virtualPop[p_turn] += incomingTroops[j].playerId * incomingTroops[j].cyborgsCount;
        	        if (virtualPop[p_turn] < 0)
        	            virtualOwner[p_turn] = -1;
        	        if (virtualPop[p_turn] > 0)
        	            virtualOwner[p_turn] = 1;
        	    }
    	    }		
		}
	}
	
	int getNextOwnerChange () {
	    for (int j = 1; j < SIMU_DEPTH; j++) {
	        if (virtualOwner[j] != playerId)
            {
                cerr << playerId << virtualOwner[j] << id << endl;
	            return j;
            }
	    }
	    return -1;
	}
    
    void reset() {
        for (int i = 0; i < 15; i++) {
            if (i != id)
                isChecked[i] = false;
            incomingTroops.clear();
        }   
        isAvailable = true;
    }  
    
};

class Action {
    public:
    int cyborgsNeeded;
    Factory* target;
    int score;
    int turn;
    
    Action (int p_turn, int p_cyborgs, Factory* p_target) : turn(p_turn), cyborgsNeeded(p_cyborgs), target(p_target) {}
    
    virtual void setScore() {return;}
    virtual void output() {return;}
};

class Move : public Action {
    public:
    vector<Factory*> availableFactories;
    
    Move (int p_turn, int p_cyborgs, Factory* p_target, vector<Factory*>& p_availFactories) : Action(p_turn, p_cyborgs, p_target), availableFactories(p_availFactories) {}
    
    void setScore() {
        score = target->virtualProd[turn] * 10;
		score -= turn;
		if (target->virtualOwner[turn] != 0)
		    score -= cyborgsNeeded / 5;
		else 
		    score -= cyborgsNeeded - 1;				
    }
    
    void output() {
        int sourceCount = 0;
        bool isDone = false;
        cerr << "move to be played: " << target->id << " " << cyborgsNeeded << " " << turn << endl;
        while (sourceCount < availableFactories.size() && !isDone) {
            if (cyborgsNeeded <= availableFactories[sourceCount]->virtualPop[turn]) {
                cout << "MOVE " << availableFactories[sourceCount]->id << " " << target->id << " " << cyborgsNeeded << ";";
                isDone = true;
                // Update virtualXXX pour les factories
            }
            else {
                cout << "MOVE " << availableFactories[sourceCount]->id << " " << target->id << " " << availableFactories[sourceCount]->virtualPop[turn] << ";";
            }
            sourceCount++;
        }
    }
};

class Increase : public Action {
    public:
    void setScore() {
    if (target->cyborgsProd < 3)
        if (target->virtualPop[0] > 10 && target->virtualPop[0] > 1)
        score = 1; // Prod + 1 --> 10 - 10 troops needed + 1 for production this turn.		
    }
};


class Link {
    public:
    Factory* factoryFrom;
    Factory* factoryTo;
    int distance;
    
    Link (Factory* p_from, Factory* p_to, int p_dist) : factoryFrom(p_from), factoryTo(p_to), distance(p_dist) {}
};

class Bomb {
    public:
    int factoryFrom;
    int factoryTo;
	int playerId;
    int distance;
	int id;
    
    Bomb () : playerId(0), factoryFrom(-1), factoryTo(-1), distance(0) {}
};


class Game {
    public:
    Link** links;
    Factory** factories;
    Troop* troops;
    Graph* graph;
	Bomb bombs[BOMBS_COUNT];
	vector<Move> movePool;
	
    int opBase;
    int factoryCount;
    int linkCount;
    int troopsCount;
    int myBombsCount;
    int opBombsCount;
    int myCyborgsCount;
    int opCyborgsCount;
    
    Game() : myBombsCount(2), opBombsCount(2), myCyborgsCount(0), opCyborgsCount(0), opBase(-1) {}
        
    int getMorePopFactory(int p_playerId)
    {
        int maxCyborgPop = 0;
        int result = -1;
        for (int i = 0; i < factoryCount; i++) {
            if (factories[i]->playerId == p_playerId
            && factories[i]->isAvailable
            && factories[i]->cyborgsCount > maxCyborgPop) {
                result = i;
                maxCyborgPop = factories[i]->cyborgsCount;
            }
        }
        return result;
    }
    
    void simulateTroops() {
        for (int i = 0; i < factoryCount; i++) {
            factories[i]->initSimu(); // set virtualPop[0]
            for (int j = 1; j < SIMU_DEPTH; j++) {
                factories[i]->simuTurn(j);
     			factories[i]->simuTroops(j);
            }
        }
        cerr << "end of simu" << endl;
    }
    
    int getWorthyBombTarget() {
        int maxProd = 1;
        int result = -1;
        if (myBombsCount != 0) {
            for (int i = 0; i < factoryCount; i++) {
                if (factories[i]->playerId == -1
                && factories[i]->cyborgsProd > maxProd
                && !factories[i]->isDisabled) {
                    result = i;
                    maxProd = factories[i]->cyborgsProd;
                }
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
                if (factories[i]->playerId == p_playerId 
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
    
    int getWorthyTarget(int p_fromId) {
        int maxScore = -5000;               
        int result = -1;

        for (int i = 0; i < factoryCount; i++) {
            int score = 0;
            score += factories[i]->cyborgsProd * 5;
            if (factories[i]->playerId == 0)
                score -= factories[i]->cyborgsCount;
            //else if (factories[i]->playerId == -1)
            //    score -= factories[i]->cyborgsCount;
            if (factories[i]->playerId == 1)
                score -= 50000;
            score -= graph->dist_opt[p_fromId][i];
            if (factories[p_fromId]->isChecked[i])
                score -= 50000;
            
            if (score > maxScore) {
                result = i;
                maxScore = score;
            }
        }

        cerr << p_fromId << " " << result << " " << maxScore << endl;
        if (result != -1)
            factories[p_fromId]->isChecked[result] = true;
            
        return result;
    }
    
    int getWorthyIncrease() {
        int maxDist = 0;
        int result = -1;
        if (myCyborgsCount > opCyborgsCount + 10) {
            for (int i = 0; i < factoryCount; i++) {            
                if (factories[i]->playerId == 1 
                && factories[i]->cyborgsCount > 10
                && factories[i]->cyborgsProd != 3
                && factories[i]->isAvailable
                && graph->dist_opt[i][opBase] > maxDist)
                {
                    maxDist = graph->dist_opt[i][opBase];
                    result = i;
                }
            }
        }
        return result;
    }
    
    int disableDefendingFactories() {
        for (int i = 0; i < factoryCount; i++) {            
            if (factories[i]->playerId == 1) {
				int cyborgsCount = factories[i]->cyborgsCount;
                
            	if (cyborgsCount < 0)
			        factories[i]->isAvailable = false;
			    else 
			         factories[i]->cyborgsCount = cyborgsCount;
			    cerr << "cyborgsCount = " << i << " : " << cyborgsCount << endl;
            }
        }
    }
    
    int getClosestFactory(int p_playerId, int p_factoryId) {
        int minDist = 50000;
        int result = -1;
        for (int i = 0; i < factoryCount; i++) {
            cerr << factories[p_factoryId]->playerId << " " << factories[p_factoryId]->dist[i] << endl;
            if (p_factoryId != factories[i]->id
            && factories[i]->playerId == p_playerId
            && factories[p_factoryId]->dist[i] > 0
            && factories[p_factoryId]->dist[i] < minDist)
            {
                minDist = graph->dist_opt[p_factoryId][i];
                result = i;
            }
        }
        return result;
    }
    
    void getFactoriesInRange(int p_factoryId, int p_range, vector<Factory*>& p_factoriesInRange) {
        for (int i = 0; i < factoryCount; i++) {            
            if (p_factoryId = factories[i]->id
            && factories[i]->playerId == 1
            && factories[p_factoryId]->dist[i] > 0
            && factories[p_factoryId]->dist[i] <= p_range
            && factories[p_factoryId]->virtualPop[p_range] > 0)
            {
                p_factoriesInRange.push_back(factories[i]);
            }
        }
    }
    
    int getAvailableTroops(int p_turn, vector<Factory*>& p_factoriesInRange) {
        int result = 0;
        for (int i = 0; i < p_factoriesInRange.size(); i++) {
            result += p_factoriesInRange[i]->virtualPop[p_turn];
        }
        return result;
    }
    
    void reset() {
        for (int i = 0; i < factoryCount; i++) {
            factories[i]->reset();
            if (factories[i]->playerId == -1)
                opCyborgsCount += factories[i]->cyborgsCount;
            if (factories[i]->playerId == 1)
                myCyborgsCount += factories[i]->cyborgsCount;
        }
        
        for (int i = 0; i < troopsCount; i++) {
            if (troops[i].playerId == -1)
                opCyborgsCount += troops[i].cyborgsCount;
            if (troops[i].playerId == 1)
                myCyborgsCount += troops[i].cyborgsCount;
        }
		
		for (int i = 0; i < BOMBS_COUNT; i++) {
            bombs[i].playerId = 0;
        }
        movePool.clear();
    }
    
    void defend(int p_turn, int factory_id) {
        cerr << "defend factory " << factory_id << endl;
        vector<Factory*> factoriesInRange;
		getFactoriesInRange(factory_id, p_turn, factoriesInRange);
		int availableTroops = getAvailableTroops(p_turn, factoriesInRange);
		if (availableTroops >= - factories[factory_id]->virtualPop[p_turn]) {
			Move l_move(p_turn, - factories[factory_id]->virtualPop[p_turn], factories[factory_id], factoriesInRange);
			l_move.setScore();
			movePool.push_back(l_move);
			cerr << "move pushed" << endl;
		}
    }
    
    int getBestMove() {
        cerr << "getBestMove" << endl;
        int result = -1;
        int bestScore = -1;
        for (int i = 0; i < movePool.size(); i++) {
            if (movePool[i].score > bestScore) {
                bestScore = movePool[i].score;
                result = i;
            }
        }
        
        return result;
    }
    
    void play() {
        simulateTroops();
        
        for (int i = 0; i < factoryCount; i++) {
        	if (factories[i]->playerId == 1) {
        		int turnChange = factories[i]->getNextOwnerChange();
        		if (turnChange != -1) {
        			defend(turnChange, i);
        		}
        		else 
        		{
        		    
        		}
        	}
        }
        
        int bestMoveIdx = getBestMove();
        if (bestMoveIdx != -1) {
            cerr << "best move: " << bestMoveIdx << " target: " << movePool[bestMoveIdx].target->id << endl;
            cerr << "factories involved: " << movePool[bestMoveIdx].availableFactories.size() << endl;
            movePool[bestMoveIdx].output();
            movePool[bestMoveIdx].target->isAvailable = false;
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
    map<int, map<int, int>> dist;
    
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
        cerr << factory1 << " " << factory2 << " " << distance << endl;
        dist[factory1][factory2] = distance;
        dist[factory2][factory1] = distance;
    }
    
    Graph* graph = new Graph(dist, game.factoryCount);
    game.links = links;
    game.graph = graph;

    int troopsCount;
    Troop troops[200];
	Bomb bombs[4];
    // game loop
    int turn = 0;
    while (1) {
        game.reset();
        int entityCount; // the number of entities (e.g. factories and troops)
        int troopsCount = 0;
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
                if (arg3 >= factories[entityId]->cyborgsProd)
					factories[entityId]->cyborgsProd = arg3;
                if (turn == 0 && factories[entityId]->playerId == -1) {
                    game.opBase = entityId;
                }
            }
            else if (entityType.compare("TROOP") == 0)
            {
                Troop l_troop(arg1, arg4, arg5, arg2, arg3);
                troops[troopsCount] = l_troop;
                troops[troopsCount].id = entityId;
                troopsCount++;
                factories[l_troop.factoryTo]->incomingTroops.push_back(l_troop);
            }
			else if (entityType.compare("BOMB") == 0)
            {
                game.bombs[entityId].playerId = arg1;
				game.bombs[entityId].factoryFrom = arg2;
				game.bombs[entityId].factoryTo = arg3;
				game.bombs[entityId].distance = arg4;
                game.bombs[entityId].id = entityId;
            }
            game.troops = troops;
            game.troopsCount = troopsCount;
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        
        // Find my factories with the more cyborgs
        cout << "WAIT;";
        
        int bombTo = -1;
        bombTo = game.getWorthyBombTarget();
        if (bombTo != -1) {
            int bombFrom = game.getClosestFactory(1, bombTo);
            cout << "BOMB " << bombFrom << " " << bombTo << ";";
            factories[bombFrom]->isAvailable = false;
            factories[bombTo]->isDisabled = true;
            game.myBombsCount--;
        }
        
		//game.play();
		
        int increaseId = game.getWorthyIncrease();
        if (increaseId != -1)
        {
            cout << "INC " << increaseId << ";";
        }
        
        int from = game.getMorePopFactory(1);
        int to = -1;
        if (from != -1)
        {
            to = game.getWorthyTarget(from);
            //if (to == -1)
            //    to = game.getWorthyTarget(0, from);
        }

        while (to != -1)
        {
            if (from != -1) {
                int troops = 0;
                if (factories[to]->playerId == -1)
                    troops = factories[to]->cyborgsCount + factories[from]->dist[to] * (factories[to]->cyborgsProd);
                else
                    troops = factories[to]->cyborgsCount;
            
                // Any valid action, such as "WAIT" or "MOVE source destination cyborgs"
                //if (factories[graph->next[from][to]]->playerId == -1) {
                    if (factories[from]->cyborgsCount > troops)
                    {
                        cout << "MOVE " << from << " " << graph->next[from][to] << " " << troops << ";";
                        factories[from]->cyborgsCount -= troops;
                    }
                //}
                //else 
                //{
                //    cout << "MOVE " << from << " " << graph->next[from][to] << " " << troops << ";";
                //    factories[from]->cyborgsCount -= troops;
                //}
            }
            from = game.getMorePopFactory(1);
            if (from != -1)
            {
                to = game.getWorthyTarget(from);
                //if (to == -1)
                //    to = game.getWorthyTarget(0, from);
            }
            else
                to = -1;
        }
        cout << "WAIT" << endl;
        turn++;
    }
}