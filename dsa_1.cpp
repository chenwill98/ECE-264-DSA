//William Chen ECE-264

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

template <class T>
class SimpleList {
protected:
	class node {
	public:
		T data;
		node *next;
	}; 
	node *head, *tail;
	string listName;

public:
	SimpleList(){}
    SimpleList(string setName){
    	head = NULL;
      	tail = NULL;
    	listName = setName;
    }
    virtual T pop() = 0;
	virtual void push(T value) = 0;
	string getName(){
		return listName;
	}
	bool isEmpty() {
		if (head == NULL){
			return true;
		} else {
			return false;
		}
	}
	void insertStart(T value) {
		node *temp = new node;
    	temp->data = value;
    	temp->next = head;
    	head = temp;
	}
	void insertEnd(T value) {
		node *temp = new node;
		temp->data = value;
		temp->next = NULL;
		if(head == NULL) {
			head = temp;
			tail = temp;
			temp = NULL;
		}
		else {	
			tail->next = temp;
			tail = temp;
		}
	}
	T removeStart() {
		T value;
		node *temp=new node;
		value = head->data;
		temp = head;
		head = head->next;
		return value;
		delete temp;
		
		
	}
};

template <class T>
class Stack: public SimpleList<T> {
public:
	Stack(){}
    Stack(string setName){
    	SimpleList<T>::head = NULL;
      	SimpleList<T>::tail = NULL;
    	SimpleList<T>::listName = setName;
    }
	T pop() {
		return SimpleList<T>::removeStart();
	}
	void push(T value) {
		SimpleList<T>::insertStart(value);
	}
};

template <class T>
class Queue: public SimpleList<T> {
public:
	Queue(){}
    Queue(string setName){
    	SimpleList<T>::head = NULL;
      	SimpleList<T>::tail = NULL;
    	SimpleList<T>::listName = setName;
    }
	T pop() {
		return SimpleList<T>::removeStart();
	}
	void push(T value) {
		SimpleList<T>::insertEnd(value);
	}
};

bool exists(string name, vector<string> nameList) {
	for (int i=0; i < nameList.size(); i++) {
		if (name == nameList[i])
			return true;
	}
	return false;
}

void command(vector<string> inputs, string outName) {
	string name, obj, type, value;
	ofstream File;
	File.open(outName.c_str(), std::ios::app);
	vector<string> nameList;
	list<SimpleList<int> *> listSLi;
	list<SimpleList<double> *> listSLd;
	list<SimpleList<string> *> listSLs;
	SimpleList<int> *pSLi;
	SimpleList<double> *pSLd;
	SimpleList<string> *pSLs;

	for(int i = 0; i <  inputs.size(); i++) {
		name = inputs[++i];
		obj = name.at(0);
		if (inputs[i-1] == "create") {
			type = inputs[++i];
			File << "PROCESSING COMMAND: create " << name << " " << type << endl;
			if(exists(name, nameList)) { 
				File << "ERROR: This name already exists!" << endl;
		
			} else {
				nameList.push_back(name);
				if (obj == "i"){
					if (type == "stack"){
						pSLi = new Stack<int>(name);
					} else {
						pSLi = new Queue<int>(name);
					}
					listSLi.push_front(pSLi);
				} else if (obj == "d") {
					if (type == "stack"){
						pSLd = new Stack<double>(name);
					} else {
						pSLd = new Queue<double>(name);
					}
					listSLd.push_front(pSLd);
				} else if (obj == "s") {
					if (type == "stack"){
						pSLs = new Stack<string>(name);
					} else {
						pSLs = new Queue<string>(name);
					}
					listSLs.push_front(pSLs);
				}
			}

		} else if (inputs[i-1] == "push") {
			value = inputs[++i];
			File << "PROCESSING COMMAND: push " << name << " " << value << endl;
			if(exists(name, nameList)) { 
				if (obj == "i"){
					for (list<SimpleList<int> *>::iterator it = listSLi.begin(); it != listSLi.end(); it++){
						if ((*it)->getName() == name) {
							(*it)->push(atoi(value.c_str()));
						}

					}
					
				} else if (obj == "d") {
					for (list<SimpleList<double> *>::iterator it = listSLd.begin(); it != listSLd.end(); it++){
						if ((*it)->getName() == name) {
							(*it)->push(atof(value.c_str()));
						}
					}
				} else if (obj == "s") {
					for (list<SimpleList<string> *>::iterator it = listSLs.begin(); it != listSLs.end(); it++){
						if ((*it)->getName() == name) {
							(*it)->push(value);
						}
					}
				}
			} else {
				File << "ERROR: This name does not exist!" << endl;
			}

		} else if (inputs[i-1] == "pop") {
			File << "PROCESSING COMMAND: pop " << name << endl;
			if(exists(name, nameList)) {
				if (obj == "i"){
					for (list<SimpleList<int> *>::iterator it = listSLi.begin(); it != listSLi.end(); it++){
						if ((*it)->getName() == name) {
							if ((*it)->isEmpty()) {
								File << "ERROR: This list is empty!" << endl;
							} else {
								//cout << to_string((*it)->pop());
								File << "Value popped: " << (*it)->pop() << endl;
							}

						}
					}
				} else if (obj == "d") {
					for (list<SimpleList<double> *>::iterator it = listSLd.begin(); it != listSLd.end(); it++){
						if ((*it)->getName() == name) {
							if ((*it)->isEmpty()) {
								File << "ERROR: This list is empty!" << endl;
							} else {
								//popped = to_string((*it)->pop());
								File << "Value popped: " << (*it)->pop() << endl;
							}
						}
					}
				} else if (obj == "s") {
					for (list<SimpleList<string> *>::iterator it = listSLs.begin(); it != listSLs.end(); it++){
						if ((*it)->getName() == name) {
							if ((*it)->isEmpty()) {
								File << "ERROR: This list is empty!" << endl;
							} else {
								//popped = (*it)->pop();
								File << "Value popped: " << (*it)->pop() << endl;
							}
						}
					}
				}
			} else {
				File << "ERROR: This name does not exist!" << endl;
			}
		}
	}
}

void fileInput(string inName, string outName){
	string word;
	ifstream File; 
	vector<string> inputs;

	File.open(inName.c_str());
	while (File >> word)
	{
		inputs.push_back(word);
	}
    File.close();
    command(inputs, outName);
}

int main() {
	string fileNameIn, fileNameOut;

	cout << "Enter name of the input file: ";
	cin >> fileNameIn;
	cout << "Enter name of the output file: ";
	cin >> fileNameOut;
	fileInput(fileNameIn, fileNameOut); 

	return 0;
} 
