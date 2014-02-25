#include "Tile.h"

struct Comparison {
	bool operator() (const Tile * t1, const Tile * t2) const {
		if (t1->getX() == t2->getX())
			return t1->getY() < t2->getY();
		return t1->getX() < t2->getX();
	}
};

class TileList {

private:

	std::map<int, Tile*> marked;                //hash table containing all visited (aka "marked") tiles
	std::set<Tile*, Comparison> marked_ordered; //a sorted copy of the hash table
	std::unordered_set<Tile*> unmarked;         //contains valid tiles that have not been visited yet	

public:

	int size() {return marked.size();}          //number of visited tiles

	/*
	popUnmarked
	pulls the first element from unmarked set
	hashes it and places it into the marked set
	returns that tile
	*/
	Tile * popUnmarked() {
		Tile * t = *unmarked.begin();
		unmarked.erase(unmarked.begin());
		if (!contains(t))
			marked[t->hash()] = t;
		return t;
	}

	
	//tests whether the tile has already been visited
	bool contains(Tile * t) {
		int h = t->hash();
		if (marked[h] == NULL) {
			marked.erase(h);
			return false;
		}
		return true;
	}
	bool hasUnmarked() {return unmarked.size() > 0;}
	void pushUnmarked(Tile * t) {unmarked.insert(t);}
	void sort() {
		for (std::map<int, Tile*>::iterator it = marked.begin(); it != marked.end(); it++)	
			marked_ordered.insert(it->second);	
	}
	void print() {
		std::ofstream of;
		of.open("Tiles.txt");
		for(std::set<Tile*>::iterator it = marked_ordered.begin(); it != marked_ordered.end(); it++)			
			of << (*it)->toString() << std::endl;
	}

};