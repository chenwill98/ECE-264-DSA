#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
using namespace std;

class SimpleList {
private:
	string listName;

protected:
	struct node {
		int data;
		node *next;
	}; 

public:
	SimpleList(){}
    SimpleList(string setName){
    	head=NULL;
      	tail=NULL;
    	listName = setName;
    }
    virtual void pop() = 0;
	virtual void push() = 0;
	string getName(){
		return listName;
	}
	void insertStart(int value) {
		node *temp=new node;
    	temp->data=value;
    	temp->next=head;
    	head=temp;
	}
	void insertEnd(int value) {
		node *temp=new node;
		temp->data=value;
		temp->next=NULL;
		if(head==NULL) {
			head=temp;
			tail=temp;
			temp=NULL;
		}
		else {	
			tail->next=temp;
			tail=temp;
		}
	}
	void removeStart() {
		node *temp=new node;
		temp=head;
		cout << head->data;
		head=head->next;
		delete temp;
	}
private:
	node *head, *tail;

};

class Stack: public SimpleList {
public:
	
	/* int pop() {

	}
	void push(int value) {
		
	} */
};

class Queue: public SimpleList {
public:
	
	/* void pop() {

	}
	void push(int value) {

	} */
};

/*list<SimpleList<int> *> listSLi; //all integer stacks and queues
list<SimpleList<double> *> listSLd; //all double stacks and queues
list<SimpleList<string> *> listSLs; //all string stacks and queues */
bool exists(string name) {
	return 0;
}

void fileOutput(string name, string input){
	ofstream File;
	File.open(name.c_str(), std::ios::app);
	File << input;
}

void command(vector<string> inputs, string outName) {
	string name, type, value, outString;

	for(int i = 0; i <  inputs.size(); i++) {
		name = inputs[++i];

		if (inputs[i-1] == "create") {

			if(exists(name)) { 
				i++;
				outString = "ERROR: This name already exists!";
			} else {
				type = inputs[++i];
				outString = "PROCESSING COMMAND: create " + name + " " + type + '\n';
			}

		} else if (inputs[i-1] == "push") {

			if(1) { //obviously switch with exists(name)
				value = string(inputs[++i]);
				outString = "PROCESSING COMMAND: push " + name + " " + value + '\n';
			} else {
				outString = "ERROR: This list is empty!";
			}

		} else if (inputs[i-1] == "pop") {

			if(1) { //obviously switch with exists(name)
				outString = "PROCESSING COMMAND: pop " + name + '\n' + "Value popped: " + '\n';
			} else {
				outString = "ERROR: This list is empty!";
			}

		}
		 
		fileOutput(outName.c_str(), outString.c_str());
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
