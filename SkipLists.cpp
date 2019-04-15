#include "SkipLists.h"
#include <iostream>
#include <vector>

SkipLists::SkipLists(bool p){
	srand(time(0));
	cost = 0;
	level = 1;
	print = p;
}

int SkipLists::length(){
	return skipList[0].size();
}

void SkipLists::insert(int num){
	cost = 0;
	level = 1;
	list<Node>::iterator loc;
	if(skipList.empty()){
		list<Node> nodes;
		nodes.push_back(Node(num));
		skipList.push_back(nodes);
		loc = skipList[0].begin();
	}else{
		loc = insertPlace(num, skipList[skipList.size()-1].begin(), skipList.size() -1);
	}
	cost++;
	stack(num, loc);
	insertCosts.push_back(cost);
}

int SkipLists::getAverageInsertCost(){
	int sum = 0;
	for(int i : insertCosts)
		sum += i;
	return sum / insertCosts.size();
}
int SkipLists::getAverageSearchCost(){
	int sum = 0;
	for(int i : searchCosts)
		sum += i;
	return sum / searchCosts.size();
}
int SkipLists::getAverageDeleteCost(){
	int sum = 0;
	for(int i : deleteCosts)
		sum += i;
	return sum / deleteCosts.size();
}


list<Node>::iterator SkipLists::insertPlace(int num, list<Node>::iterator it, int height){
	if(it != skipList[height].end()){
		if(num > (*it).value){
			while(it != skipList[height].end() && num > (*it).value) {it++; cost++;}
		}else{
			cost++;
			while(it != skipList[height].begin() && num < (*it).value) {it--; cost++;}
			if(num > (*it).value){
				it++;
			}
		}
	}
	cost++;
	if(height == 0){
		it = skipList[0].insert(it, Node(num));
		return it;		
	}else{
		if(it == skipList[height].end()){
			it--;
		}
		return insertPlace(num, (*it).below, --height);
	}
}


void SkipLists::stack(int num, list<Node>::iterator prev){
	int flip = rand() % 2;
	int count = 1;
	list<Node>::iterator it;
	while(flip == 1){
		count++;
		level++;
		flip = rand() % 2;
		cost++;
		if(skipList.size() < count){
			list<Node> nodes;
			nodes.push_back(Node(num, prev));
			skipList.push_back(nodes);
			prev = skipList[skipList.size()-1].begin();
		}else{
			it = skipList[count-1].begin();
			while(it != skipList[count -1].end() && num > (*it).value){
				it++;
			}
			prev = skipList[count -1].insert(it,Node(num, prev));


		}
	}
}

void SkipLists::deleteAll(){
	while(skipList.size() > 0 && skipList[0].size() > 0){
		if(print)
			cout << "Deleted: " << skipList[0].front().value << " ";
		deleteItem(skipList[0].front().value);
		if(print)
			cout << "Cost: " << cost << "\n";
	}
}

bool SkipLists::deleteItem(int num){
	cost = 0;
	bool didItDelete = deleteHelp(num, skipList[skipList.size()-1].begin(), skipList.size()-1, false);
	deleteCosts.push_back(cost);
	return didItDelete;
}

bool SkipLists::deleteHelp(int num, list<Node>::iterator it, int height, bool check){
	cost++;
	if(skipList[0].size() == 1 && num == skipList[0].front().value){
		skipList.clear();
		return true;
	}
	if(it != skipList[height].end()){
		cost++;
		if(num > (*it).value){
			while(it != skipList[height].end() && num > (*it).value) {it++; cost++;}
		}else if(num < (*it).value){
			cost++;
			while(it != skipList[height].begin() && num < (*it).value) {it--; cost++;}
			if(num > (*it).value){
				it++;
			}
		}
		if(it != skipList[height].end() && num == (*it).value){
			check = true;
			if(skipList[height].size() == 1)
				skipList.pop_back();
			else
				skipList[height].erase(it);
		}
	}
	if(height == 0){	
		return check;
	}else{
		if(!check && it == skipList[height].end()){
			it--;
		}
		return deleteHelp(num, (*it).below, --height, check);
	}
}

bool SkipLists::search(int num){
	cost = 0;
	bool check = searchHelp(num, skipList[skipList.size()-1].begin(), skipList.size() -1);
	searchCosts.push_back(cost);
	return check;
}

bool SkipLists::searchHelp(int num, list<Node>::iterator it, int height){
	if(it != skipList[height].end()){
		cost++;
		if(num > (*it).value){
			while(it != skipList[height].end() && num > (*it).value) {it++; cost++;}
		}else{
			while(it != skipList[height].begin() && num < (*it).value) {it--; cost++;}
			if(num > (*it).value)
				it++;
			cost++;
		}
		if(it != skipList[height].end() && num == (*it).value)
			return true;
	}

	if(height == 0){	
		return false;
	}else{
		if(it == skipList[height].end())
			it--;
		return searchHelp(num, (*it).below, --height);
	}
}

void SkipLists::searchAll(){
	for(Node y : skipList[0]){
		search(y.value);
		if(print)
			cout << "Search: " << y.value << " Cost: " << getCost() << endl;
	}
}
ostream& operator<<(ostream& out, SkipLists& skipList){
	vector<list<Node>> i = skipList.get();
	vector<Node> vec;

	for(Node g : i[0])
		vec.push_back(g);
	int count = 0;
	int digits;
	
	for(int y = i.size() -1; y >= 0; y--){
		list<Node>::iterator it = i[y].begin();
		while(it != i[y].end()){
			if((*it).value == vec[count].value){
				out << (*it).value << " ";
				it++;
			}else{
				digits = getDigits(vec[count].value);
				for(int b = 0; b < digits; b++)
					out << " ";
				out << " ";
			}
			count++;
			
		}
		count = 0;
		out << "\n";
	}

	
	

	return out;
}



int getDigits(int num){
	int cn = 0;
	while(num > 0){
		num = num / 10;
		cn ++;
	}
	return cn;
}

istream& operator>>(istream& in, SkipLists& skipList)
{
  int n;
  in >> n;
  while(in.good()){
    skipList.insert(n);
    if(skipList.print)
    	cout << "Inserting: " << n << " Cost: " << skipList.getCost() << " Level: "
    	 << skipList.getLevel() << endl;
    in >> n;
  }
  skipList.insert(n);
  if(skipList.print)
    cout << "Inserting: " << n << " Cost: " << skipList.getCost() << " Level: "
    	 << skipList.getLevel() << endl;
  

  return in;
}
