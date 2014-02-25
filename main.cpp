#include "TileList.h"

/*
getAdjacents
gets an unmarked tile, and checks each of 4 neighbors
if valid, pushes neighbors into unmarked set (if not already in it)
then "mark" the tile we checked from
*/
void getAdjacents(TileList & grid) {
	Tile * root = grid.popUnmarked(); //get the first unmarked tile
	for (int dir = 0; dir < 4; dir++) {
		Tile * neighbor = root->getAdjacent(dir);
		if (!grid.contains(neighbor) && neighbor->isValid())	//if the adjacent tile is not already marked, and is accessible, then add it
			grid.pushUnmarked(neighbor);
	}
}

int main() {

	TileList grid;
	Tile start = Tile(1000, 1000, 25);  //(x, y, max_sum)
	if (start.isValid())
		grid.pushUnmarked(&start); //add first tile to set

	std::cout << "Starting point: " << start.toString() << "      max = " << start.max() << std::endl;
	std::cout << "Working..." << std::endl << std::endl;

	int counter = 0;
	while(grid.hasUnmarked()) { //loop until unmarked set is empty
		getAdjacents(grid);
		if (++counter % 7500 == 0) std::cout << "tiles so far: " << grid.size() << "\r";
	}

	std::cout << "\r" << "Accessible tiles: " << grid.size() << std::endl << std::endl;

	std::cout << "Press enter to print to file" << std::endl;
	std::cin.get();

	std::cout << "Printing..." << std::endl;
	grid.sort();
	grid.print();
	
	std::cout << "Output printed to Tiles.txt" << std::endl;
	std::cout << "Enter to exit";
	std::cin.get();

}

