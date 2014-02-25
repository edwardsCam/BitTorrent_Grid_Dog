#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <unordered_set>

class Tile {

private:

	const int const_MAX;
	int x;
	int y;

public:

	Tile (int a, int b, const int m):const_MAX(m) {x = a; y = b;}
	int max()  const {return const_MAX;}
	int getX() const {return x;}
	int getY() const {return y;}
	int hash() {return (51 + knuth(x)) * 51 + knuth(y) + y;} //hash tile to int
	int knuth(int i) {return i*2654435761 % 4294967296;}
	bool isValid() {return getSum() <= const_MAX;}

	int getSum() {
		int sum = 0;
		for (int n = 0; n < 2; n++) {
			int copy;
			if (n == 0) copy = abs(x);			
			else copy = abs(y);

			int digits = (int)log10((float)copy) + 1;
			for (int i = digits - 1; i > 0; i--) {
				int divisor = (int)pow((float)10, i);
				int digit = copy / divisor;
				sum+=digit;
				if (sum > const_MAX) return const_MAX+1; //exit early if over max
				copy -= digit * divisor;
			}
			sum+=copy;
		}
		return sum;
	}
	/*
	getAdjacent
	returns adjacent tile in the indicated direction
	*/
	Tile * getAdjacent(int dir) {
		switch (dir) {
		case 0:
			return new Tile(x, y+1, const_MAX);
		case 1:
			return new Tile(x+1, y, const_MAX);
		case 2:
			return new Tile(x, y-1, const_MAX);
		case 3:
			return new Tile(x-1, y, const_MAX);
		}
		return NULL;
	}
	std::string toString() {
		std::stringstream ss;
		ss << "(" << x << "," << y << ")";
		return ss.str();
	}

};