#include "SkipLists.h"
#include <iostream>
#include <vector>

int main(){
	SkipLists skip(false);

	ifstream file;
	file.open("reverse.txt");

	file >> skip; //insert values

	skip.searchAll();
	skip.deleteAll();
	cout << "Reverse Average search cost: " << skip.getAverageSearchCost() << endl;
	cout << "Reverse Average insert cost: " << skip.getAverageInsertCost() << endl;
	cout << "Reverse Average delete cost: " << skip. getAverageDeleteCost() << endl;

	file.close();
	file.open("sorted.txt");

	file >> skip;

	skip.searchAll();
	skip.deleteAll();
	cout << "sorted Average search cost: " << skip.getAverageSearchCost() << endl;
	cout << "Sorted Average insert cost: " << skip.getAverageInsertCost() << endl;
	cout << "Sorted Average delete cost: " << skip. getAverageDeleteCost() << endl;
	file.close();
	file.open("random.txt");

	file >> skip;

	skip.searchAll();
	skip.deleteAll();
	cout << "Random Average search cost: " << skip.getAverageSearchCost() << endl;
	cout << "Random Average insert cost: " << skip.getAverageInsertCost() << endl;
	cout << "Random Average delete cost: " << skip. getAverageDeleteCost() << endl;
	cout << "\n\n\n";
	file.close();
	SkipLists skip2(true);

	file.open("4r");

	file >> skip2;
	cout << "\nThis is the small list: \n";
	cout << skip2;
	cout << "\nSearching\n";
	skip2.searchAll();
	cout << "\nDeleting:\n";
	skip2.deleteAll();
	cout << "Small Random Average search cost: " << skip2.getAverageSearchCost() << endl;
	cout << "Small Random Average insert cost: " << skip2.getAverageInsertCost() << endl;
	cout << "Small Random Average delete cost: " << skip2. getAverageDeleteCost() << endl;
	file.close();
}