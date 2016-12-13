#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sys/time.h>
#include <math.h>

#pragma GCC optimize("Ofast")

using namespace std;

#define PI 3.14159265358979323846
#define INT_MAX 32767
#define PODS_NB 4
#define MAX_MOVES 6
#define MAX_POP 1


class Unit;

class Position
{
public:
	double x;
	double y;

	Position(int px, int py)
	{
		x = (double)px;
		y = (double)py;
	}

	Position(double px, double py)
	{
		x = px;
		y = py;
	}

	void set(int px, int py)
	{
		x = (double)px;
		y = (double)py;
	}

	double distance2(Position& p) {
		return (x - p.x)*(x - p.x) + (y - p.y)*(y - p.y);
	}

	double distance(Position& p) {
		return sqrt(distance2(p));
	}

	Position closest(const Position& a, const Position& b)
	{
		double da = b.y - a.y;
		double db = a.x - b.x;
		double c1 = db*a.x + da*a.y;
		double c2 = -db*x + da*y;
		double det = da*da + db*db;
		double cx = 0;
		double cy = 0;

		if (det != 0) {
			cx = (da*c1 - db*c2) / det;
			cy = (da*c2 + db*c1) / det;
		}
		else {
			// Le point est d�j� sur la droite
			cx = x;
			cy = y;
		}

		return Position(cx, cy);
	}

	bool operator==(Position& p)
	{
		return (x == p.x && y == p.y);
	}
};

class Move
{
public:
	Position pos;
	int thrust; // Entre 0 et 100

	Move(int px, int py, int pt) : pos(px, py), thrust(pt)
	{
	}

	Move() : pos(0, 0), thrust(0)
	{
	}

	Move(Move const& move) : pos(move.pos), thrust(move.thrust)
	{
	}

	void mutate(double amplitude)
	{
		// X mutation. Entre -2000 et 18000
		int Xmin = pos.x - 18000 * amplitude;
		int Xmax = pos.x + 18000 * amplitude;

		if (Xmin < -2000)
			Xmin = -2000;
		if (Xmax > 18000)
			Xmax = 18000;

		pos.x = rand() % (Xmax - Xmin + 1) + Xmin;

		// Y mutation. Entre -2000 et 11000
		int Ymin = pos.y - 18000 * amplitude;
		int Ymax = pos.y + 18000 * amplitude;

		if (Ymin < -2000)
			Ymin = -2000;
		if (Ymax > 11000)
			Ymax = 11000;

		pos.y = rand() % (Ymax - Ymin + 1) + Ymin;

		// Thrust mutation
		int Tmin = thrust - 100 * amplitude;
		int Tmax = thrust + 100 * amplitude;

		if (Tmin < 0) {
			Tmin = 0;
		}

		if (Tmax > 100) {
			Tmax = 100;
		}
		
		thrust = rand() % (Tmax - Tmin + 1) + Tmin;
		if (thrust < 25)
		    thrust = 0;
		else if (thrust > 75)
		    thrust = 100;
		else
		    thrust = 100 * (thrust - 25) / 100;
		//thrust = 100;
	}


	void output()
	{
		cout << pos.x << " " << pos.y << " " << thrust << endl;
	}
};

class Solution
{
public:
	Move* moves[MAX_MOVES];
	int score;

	Solution() : score(0)
	{
	}

	Solution(Solution const& sol) : score(sol.score)
	{
		for (int i = 0; i < MAX_MOVES; i++)
		{
			moves[i] = new Move(*sol.moves[i]);
		}
	}

	void initialize(int x, int y, int thrust)
	{
		for (int i = 0; i < MAX_MOVES; i++)
		{
			moves[i] = new Move(x, y, thrust);
		}
	}

	void randomize(double coeff)
	{
		for (int i = 0; i < MAX_MOVES; i++)
		{
			moves[i]->mutate(coeff);
		}
	}

	void retrieve()
	{
		delete moves[0];
		for (int i = 0; i < MAX_MOVES - 1; i++)
		{
			moves[i] = moves[i + 1];
		}
		moves[MAX_MOVES - 1] = new Move(*moves[MAX_MOVES - 2]);
	}

	~Solution()
	{
		for (int i = 0; i < MAX_MOVES; i++)
		{
			delete moves[i];
		}
	}
};

class Collision
{
public:
	Unit* a;
	Unit* b;
	double t;

	Collision(Unit* u1, Unit* u2, double pt) : a(u1), b(u2), t(pt)
	{
	}

};

class Unit : public Position
{
public:
	int id;
	double r;
	double vx;
	double vy;

	Unit(int px, int py) : Position(px, py)
	{
	}

	Unit(): Position(0,0)
	{
	}
	
	virtual void bounce(Unit* u)
	{
		// To be overloaded
	}

	Collision* collision(Unit* u) {
		// Distance carr�
		float dist = distance2(*u);

		// Somme des rayons au carr�
		float sr = (r + u->r)*(r + u->r);

		// On prend tout au carr� pour �viter d'avoir � appeler un sqrt inutilement. C'est mieux pour les performances

		if (dist < sr) {
			// Les objets sont d�j� l'un sur l'autre. On a donc une collision imm�diate
			return new Collision(this, u, 0.0);
		}

		// Optimisation. Les objets ont la m�me vitesse ils ne pourront jamais se rentrer dedans
		if (vx == u->vx && vy == u->vy) {
			return NULL;
		}

		// On se met dans le r�f�rentiel de u. u est donc immobile et se trouve sur le point (0,0) apr�s �a
		float lx = x - u->x;
		float ly = y - u->y;
		Position myp(x, y);
		float lvx = vx - u->vx;
		float lvy = vy - u->vy;
		Position up(0, 0);

			// On cherche le point le plus proche de u (qui est donc en (0,0)) sur la droite d�crite par notre vecteur de vitesse
			Position p = up.closest(myp, Position(x + vx, y + vy));

		// Distance au carr� entre u et le point le plus proche sur la droite d�crite par notre vecteur de vitesse
		float pdist = up.distance2(p);

		// Distance au carr� entre nous et ce point
		float mypdist = distance2(p);

		// Si la distance entre u et cette droite est inf�rieur � la somme des rayons, alors il y a possibilit� de collision
		if (pdist < sr) {
			// Notre vitesse sur la droite
			float length = sqrt(vx*vx + vy*vy);

			// On d�place le point sur la droite pour trouver le point d'impact
			float backdist = sqrt(sr - pdist);
			p.x = p.x - backdist * (lvx / length);
			p.y = p.y - backdist * (lvy / length);

			// Si le point s'est �loign� de nous par rapport � avant, c'est que notre vitesse ne va pas dans le bon sens
			if (distance2(p) > mypdist) {
				return NULL;
			}

			pdist = p.distance(myp);

			// Le point d'impact est plus loin que ce qu'on peut parcourir en un seul tour
			if (pdist > length) {
				return NULL;
			}

			// Temps n�cessaire pour atteindre le point d'impact
			float t = pdist / length;

			return new Collision(this, u, t);
		}

		return NULL;
	}
};

class Checkpoint : public Unit
{
public:
	Checkpoint(int px, int py) : Unit(px, py)
	{

	}

	Checkpoint() : Unit(0, 0)
	{

	}
};

class Pod : public Unit
{
public:
	double angle;
	int nextCheckpointId;
	int checked;
	int timeout;
	bool shield;
	bool isRunner;
	bool isChaser;
	Checkpoint* checkpointList;
	int nbCheckpoint;

	Pod(int px, int py, Checkpoint* pcheckpointList, int pnbCheckpoint) : Unit(px, py), checkpointList(pcheckpointList), isRunner(false), isChaser(false), shield(false), timeout(0), checked(0), nextCheckpointId(0), nbCheckpoint(pnbCheckpoint)
	{
	}

	void setAngle(Position p)
	{
		angle = getAngle(p);
	}

	double getAngle(Position p)
	{
		double d = distance(p);
		double dx = (p.x - x) / d;
		double dy = (p.y - y) / d;

		// Trigonom�trie simple. On multiplie par 180.0 / PI pour convertir en degr�.
		double a = acos(dx) * 180.0 / PI;

		// Si le point qu'on veut est en dessus de nous, il faut d�caler l'angle pour qu'il soit correct.
		if (dy < 0) {
			a = 360.0 - a;
		}

		return a;
	}

	double diffAngle(Position p)
	{
		double a = getAngle(p);

		// Pour connaitre le sens le plus proche, il suffit de regarder dans les 2 sens et on garde le plus petit
		// Les op�rateurs ternaires sont la uniquement pour �viter l'utilisation d'un operateur % qui serait plus lent
		double right = angle <= a ? a - angle : 360.0 - angle + a;
		double left = angle >= a ? angle - a : angle + 360.0 - a;

		if (right < left) {
			return right;
		}
		else {
			// On donne un angle n�gatif s'il faut tourner � gauche
			return -left;
		}
	}

	void rotate(Position p)
	{
		double a = diffAngle(p);

		// On ne peut pas tourner de plus de 18� en un seul tour
		if (a > 18.0) {
			a = 18.0;
		}
		else if (a < -18.0) {
			a = -18.0;
		}

		angle += a;

		// L'op�rateur % est lent. Si on peut l'�viter, c'est mieux.
		if (this->angle >= 360.0) {
			this->angle = this->angle - 360.0;
		}
		else if (this->angle < 0.0) {
			this->angle += 360.0;
		}
	}

	void boost(int thrust)
	{
		if (shield) {
			return;
		}

		// Conversion de l'angle en radian
		double ra = angle * PI / 180.0;

		// Trigonom�trie
		vx += cos(ra) * thrust;
		vy += sin(ra) * thrust;
	}

	void move(double t)
	{
		x += vx * t;
		y += vy * t;
	}

	void end()
	{
		x = round(x);
		y = round(y);
		vx = (int)(vx * 0.85);
		vy = (int)(vy * 0.85);

		// N'oubliez pas que le timeout descend de 1 chaque tour. Il revient � 100 quand on passe par un checkpoint
		timeout -= 1;
	}

	void play(Position p, int thrust)
	{
		rotate(p);
		boost(thrust);
		move(1.0);
		end();
		//dump();
	}

	void bounce(Checkpoint c)
	{
		// Reset Pod timeout
		timeout = 100;

		incrementCheckpointId();
		checked++;
	}

	void bounce(Pod* u)
	{		
		// Si un pod a son bouclier d'activ�, sa masse est de 10, sinon elle est de 1
		double m1 = shield ? 10 : 1;
		double m2 = u->shield ? 10 : 1;

		// Si les masses sont �gales, le coefficient sera de 2. Sinon il sera de 11/10
		double mcoeff = (m1 + m2) / (m1 * m2);

		double nx = x - u->x;
		double ny = y - u->y;

		// Distance au carr� entre les 2 pods. Cette valeur pourrait �tre �crite en dure car ce sera toujours 800�
		double nxnysquare = nx*nx + ny*ny;

		double dvx = vx - u->vx;
		double dvy = vy - u->vy;

		// fx et fy sont les composantes du vecteur d'impact. product est juste la pour optimiser
		double product = nx*dvx + ny*dvy;
		double fx = (nx * product) / (nxnysquare * mcoeff);
		double fy = (ny * product) / (nxnysquare * mcoeff);

		// On applique une fois le vecteur d'impact � chaque pod proportionnellement � sa masse
		vx -= fx / m1;
		vy -= fy / m1;
		u->vx += fx / m2;
		u->vy += fy / m2;

		// Si la norme du vecteur d'impact est inf�rieur � 120, on change sa norme pour le mettre � 120
		double impulse = sqrt(fx*fx + fy*fy);
		if (impulse < 120.0) {
			fx = fx * 120.0 / impulse;
			fy = fy * 120.0 / impulse;
		}

		// On applique une deuxi�me fois le vecteur d'impact � chaque pod proportionnellement � sa masse
		vx -= fx / m1;
		vy -= fy / m1;
		u->vx += fx / m2;
		u->vy += fy / m2;

		// C'est l'un des rares endroits o� avoir une classe Vector aurait rendu le code beaucoup plus lisible.
		// Mais cet endroit est appell� beaucoup trop souvent dans mon code pour que je me permette de le rendre plus lisible au prix de la performance		
	}

	void incrementCheckpointId()
	{
		nextCheckpointId++;
		if (nextCheckpointId == nbCheckpoint)
			nextCheckpointId = 0;
	}

	double runnerScore()
	{		
		int dist = distance(checkpointList[nextCheckpointId]);
		return checked * 50000 - dist;		
	}

	double chaserScore(Pod* opRunner)
	{
		return 80000.0 / ((distance(checkpointList[opRunner->nextCheckpointId]) + abs(diffAngle(*opRunner)*1000.0) + 1.0));
	}

	void update(int px, int py, int pvx, int pvy, int pangle, int pnextCheckpoint)
	{
		x = px;
		y = py;
		vx = pvx;
		vy = pvy;
		angle = pangle;
		nextCheckpointId = pnextCheckpoint;
	}

	void dump()
	{
		cerr << "x = " << x << endl;
		cerr << "y = " << y << endl;
		cerr << "vx = " << vx << endl;
		cerr << "vy = " << vy << endl;
		cerr << endl;
	}

};

void test(Pod** pods, Checkpoint** checkpoints) {
	for (int i = 0; i < PODS_NB; ++i) {
		pods[i]->rotate(Position(8000, 4500));
		pods[i]->boost(200);
	}

	//play(pods, checkpoints);
}

bool isCheckpointPresent(int x, int y, Checkpoint* list)
{
	bool result = false;
	for (int i = 0; i < 8; i++)
	{
		if ((int)list[i].x == x && (int)list[i].y == y)
		{
			result = true;
			break;
		}
	}
	return result;
}
int getCurrId(int x, int y, Position** list)
{
	bool currentId = 0;
	for (int i = 0; i < 8; i++)
	{
		if ((int)list[i]->x == x && (int)list[i]->y == y)
		{
			currentId = i;
			break;
		}
	}
	return currentId;
}

int getId(int x, int y, Position** list, int nbCheckpoints)
{
	return (getCurrId(x, y, list) + 1) % nbCheckpoints;
}

int getSpeed(int previousDist, int dist)
{
	int speed;
	if (previousDist != 0)
		speed = previousDist - dist;
	else
		speed = 0;
	
	return speed;
}

/**
* Auto-generated code below aims at helping you parse
* the standard input according to the problem statement.
**/
int main()
{
	// Initialize
	Solution* runnerSolutions[MAX_POP];
	Solution* chaserSolutions[MAX_POP];
	Checkpoint checkpoints[8];
	for (int i = 0; i < MAX_POP; i++)
	{
		runnerSolutions[i] = new Solution();
		chaserSolutions[i] = new Solution();
	}
	int laps;
	cin >> laps; cin.ignore();
	int checkpointCount;
	cin >> checkpointCount; cin.ignore();
	for (int i = 0; i < checkpointCount; i++) {
		int checkpointX;
		int checkpointY;
		cin >> checkpointX >> checkpointY; cin.ignore();
		checkpoints[i].set(checkpointX, checkpointY);
	}
	Pod* pods[PODS_NB];
	for (int i = 0; i < PODS_NB; i++)
	{
		pods[i] = new Pod(0, 0, checkpoints, checkpointCount);
	}
		
	// game loop
	int simu = 0;
	int turn = 0;
	while (1) {
		// Timer init
		struct timeval tbegin, tend;
		double texec = 0.;
		turn++; // new turn start
		for (int i = 0; i < 2; i++) {
			int x;
			int y;
			int vx;
			int vy;
			int angle;
			int nextCheckPointId;
			cin >> x >> y >> vx >> vy >> angle >> nextCheckPointId; cin.ignore();
			pods[i]->update(x, y, vx, vy, angle, nextCheckPointId);
		}
		for (int i = 2; i < PODS_NB; i++) {
			int x; // x position of your pod
			int y; // y position of your pod
			int vx; // x speed of your pod
			int vy; // y speed of your pod
			int angle;
			int nextCheckPointId; // int: id of the next check point in the list
			cin >> x >> y >> vx >> vy >> angle >> nextCheckPointId; cin.ignore();
			pods[i]->update(x, y, vx, vy, angle, nextCheckPointId);
		}

		// Start simulation
		if (turn == 1)
		{
			runnerSolutions[0]->initialize(pods[0]->checkpointList[pods[0]->nextCheckpointId].x, pods[0]->checkpointList[pods[0]->nextCheckpointId].y, 100);
			chaserSolutions[0]->initialize(pods[3]->x, pods[3]->y, 100);
		}
		else
		{
			runnerSolutions[0]->retrieve();
			chaserSolutions[0]->initialize(pods[3]->x, pods[3]->y, 100);
		}
		Pod tmpRunnerPod = *pods[0];
		Pod tmpChaserPod = *pods[1];
		for (int i = 0; i < MAX_MOVES; i++)
		{
			tmpRunnerPod.play(runnerSolutions[0]->moves[i]->pos, runnerSolutions[0]->moves[i]->thrust);
			tmpChaserPod.play(chaserSolutions[0]->moves[i]->pos, chaserSolutions[0]->moves[i]->thrust);
			if (tmpRunnerPod.distance2(checkpoints[tmpRunnerPod.nextCheckpointId]) < 302500)
			{
				tmpRunnerPod.checked++;
				tmpRunnerPod.incrementCheckpointId();

			}
		}
		runnerSolutions[0]->score = tmpRunnerPod.runnerScore();
		chaserSolutions[0]->score = tmpChaserPod.chaserScore(pods[3]);
		cerr << "init solution score = " << chaserSolutions[0]->score << endl;

		// Generate population
		gettimeofday(&tbegin, NULL);
		simu = 0;
		while (texec < 145)
		{
			simu++;

			Pod tmpRunnerPod = *pods[0];
			Pod tmpChaserPod = *pods[1];
			Solution* tmpRunnerSol = new Solution(*runnerSolutions[rand() % MAX_POP]);
			Solution* tmpChaserSol = new Solution(*chaserSolutions[rand() % MAX_POP]);
			tmpRunnerSol->randomize(145.0 / (145.0 + 9 * texec));
			tmpChaserSol->randomize(145.0 / (145.0 + 9 * texec));
			for (int i = 0; i < MAX_MOVES; i++)
			{
				tmpRunnerPod.play(tmpRunnerSol->moves[i]->pos, tmpRunnerSol->moves[i]->thrust);
				tmpChaserPod.play(tmpChaserSol->moves[i]->pos, tmpChaserSol->moves[i]->thrust);
				if (tmpRunnerPod.nextCheckpointId != checkpointCount && tmpRunnerPod.distance2(checkpoints[tmpRunnerPod.nextCheckpointId]) < 302500)
				{
					tmpRunnerPod.checked++;
					tmpRunnerPod.incrementCheckpointId();
				}
			}
			tmpRunnerSol->score = tmpRunnerPod.runnerScore();
			tmpChaserSol->score = tmpChaserPod.chaserScore(pods[3]);

			if (tmpRunnerSol->score > runnerSolutions[0]->score)
			{
				delete runnerSolutions[0];
				runnerSolutions[0] = tmpRunnerSol;
				//cerr << "new solution score = " << solutions[0]->score << " " << tmpPod.nextCheckpointId << endl;
			}
			else
			{
				delete tmpRunnerSol;
			}

			if (tmpChaserSol->score > chaserSolutions[0]->score)
			{
				delete chaserSolutions[0];
				chaserSolutions[0] = tmpChaserSol;
				cerr << "new solution score = " << chaserSolutions[0]->score << endl;
			}
			else
			{
				delete tmpChaserSol;
			}

			gettimeofday(&tend, NULL);
			texec = ((double)(1000 * (tend.tv_sec - tbegin.tv_sec) + ((tend.tv_usec - tbegin.tv_usec) / 1000)));
		}

		//cerr << simu << endl;

		if (turn == 1)
		{
			cout << pods[0]->checkpointList[pods[0]->nextCheckpointId].x << " " << pods[0]->checkpointList[pods[0]->nextCheckpointId].y << " BOOST" << endl;
			cout << pods[1]->checkpointList[pods[1]->nextCheckpointId + 1].x << " " << pods[1]->checkpointList[pods[1]->nextCheckpointId + 1].y << " 100" << endl;
		}
		else
		{
			runnerSolutions[0]->moves[0]->output();
			chaserSolutions[0]->moves[0]->output();
		}
	}
}
