#include <iostream>
#include <vector>
#include <list> 
#include <iterator> 
#include <fstream>

using namespace std;


struct Node
{
  int value;
  list<Node>::iterator below;
   Node(int v, list<Node>::iterator b){
   		value = v;
   		below = b;
   }
   Node(){} 
   Node(int v){
   		value = v;
   }


};


class SkipLists {
private:
	vector<list<Node>> skipList;
	int cost;
	int level;
	vector<int> insertCosts;
	vector<int> deleteCosts;
	vector<int> searchCosts;
public:
	int maxSize = 0;
	bool print;
	SkipLists(bool print);
	void searchAll();
	int getLevel(){return level;}
	void insert(int num);
	int getCost(){return cost;}
	int getAverageInsertCost();
	int getAverageSearchCost();
	int getAverageDeleteCost();
	bool deleteItem(int num);
	void deleteAll();
	bool deleteHelp(int num, list<Node>::iterator it, int height, bool check);
	bool search(int num);
	int length();
	void stack(int num, list<Node>::iterator loc);
	list<Node>::iterator insertPlace(int num, list<Node>::iterator it, int height);
	bool searchHelp(int num, list<Node>::iterator it, int height);
	vector<list<Node>> get(){return skipList;}
};

int getDigits(int num);
ostream& operator<<(ostream& out, SkipLists& skipList);
istream& operator>>(istream& in, SkipLists& skipList);