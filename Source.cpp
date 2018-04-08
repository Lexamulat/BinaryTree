#include<iostream>
#include <ctime>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;



struct node // структура для представления узлов дерева
{
	int key;
	unsigned int height=0;
	node* left=nullptr;
	node* right=nullptr;
	
};
node* current = nullptr;

int up = 0;
void print(node* head, int up) {

	if (head)
	{

		print(head->right, up + 1);
		for (int i = 0; i< up; i++) cout << "   ";
		cout << head->key << endl;
		print(head->left, up + 1);
	}


}


void StraightPrint(node *head)
{
	if (head == NULL)   {
		return;
	}
	StraightPrint(head->left);
	StraightPrint(head->right);

	cout << head->key << " ";
}


//void SimmHeight(node *head){  //ща буим height заполнять (в обратном порядке)
//
//	if (head == NULL)   // Базовый случай
//	{
//		return;
//	}
//	SimmHeight(head->left);  
//	SimmHeight(head->right);
//	// тут делать ченить над
//	if ((head->left == nullptr) && (head->right == nullptr)) {
//		head->height = 0;
//	}
//	else { 
//		//(hl>hr ? hl : hr) + 1;
//		//(head->left == nullptr ? head->height = (head->right->height)+1 : head->height = (head->left->height)+1);
//		if (head->left == nullptr)  head->height = (head->right->height) + 1;
//		else if (head->right == nullptr) head->height = (head->left->height) + 1;
//		if (head->height == -1) {
//			(head->left->height > head->right->height ? head->height = (head->left->height) + 1 : head->height = (head->right->height) + 1);
//		}
//	}
//	cout << endl;
//	cout << head->key;
//	cout << "(" << head->height << ")"<< endl;
//}

unsigned int height(node*&head) {
	//if (!head) head->height = 0;
	return head ? head->height : 0;
}

void fixheight(node *&head) {
	unsigned int hl, hr;
	hl = height(head->left);
	hr = height(head->right);
	head->height= (hl>hr ? hl : hr) + 1;
}

void LeftRotate(node* &head) {
	//cout << "LEFTrot around-----" << endl;
//	cout << head->key << endl;
//	cout << "--------------" << endl;
	node* p = head->right;
	if (p == nullptr)head->right = nullptr;
    head->right = p->left;
	p->left = head;

	fixheight(head);
	fixheight(p);

	head = p;

	//return p;
}

void RightRotate(node* &head) {
	//cout << "RIGHrot around-----" << endl;
	//cout << head->key << endl;
	//cout << "--------------" << endl;
	node* q = head->left;
	if (q == nullptr)head->left = nullptr;
	head->left = q->right;
	q->right = head;
	fixheight(head);
	fixheight(q);

	head = q;

	//return q;
	//надобы высоты поменять
}

void Balance(node *&head) {
	int bfactor = 0;
	if (head == NULL)   // Базовый случай
	{
		return;
	}
	Balance(head->left);
	Balance(head->right);
	fixheight(head);
	//SimmHeight(head);

	//bfactor = head->right->height - head->left->height;
	bfactor = height(head->right) - height(head->left);
	//cout << head->key << endl;

	if (bfactor == 2) {
		if (height(head->right->left) <= height(head->right->right)) {
			LeftRotate(head);
		
			return;
		}
		else {
			RightRotate(head->right);
			
			LeftRotate(head);
			
			return;
		}
	}
	if (bfactor == -2) {
		if (height(head->left->left) > height(head->left->right)) {
			RightRotate(head);
			
			return;
		}
		else {
			LeftRotate(head->left);
			
			RightRotate(head);
		
			return;
		}
	}
}


void Create(node*& head,node*& temp, node*& current) {
	if (head == nullptr) {
		head = temp;
		current = head;
		head->key = temp->key;
		return;
	}
	else {
		if (temp->key< current->key) {
			if (current->left == nullptr) {
				current->left = temp;
				//cout << "-----add-" << endl;
				//print(head,up);
				//cout << "---------------" << endl;
				Balance(head);
				//cout << "----add  i balance-" << endl;
				//print(head, up);
				//cout << "---------------" << endl;
				current = head;

			//	 SimmHeight(head);
				return;
			}
			else {
				current = current->left;
				Create(head, temp, current);
			}
				}
		else {
			if (current->right == nullptr) {
				current->right = temp;
				
			//	cout << "-----add-" << endl;
				//print(head, up);
			//	cout << "---------------" << endl;
				Balance(head);
			//	cout << "-----add i balance-" << endl;
			//	print(head, up);
			//	cout << "---------------" << endl;
				current = head;

			//	SimmHeight(head);
				return;
			}
			else {
				current = current->right;
				Create(head, temp, current);
			}
		}
	
	}
}


void Generate(node*& head) {
	//а-лев b-пра
	//rand() % (b - a + 1) + a;

	node* temp = new node;

	temp->key = rand() % 100 + 1;
	
	Create(head, temp, current);
	
	{/*	node* temp1 = new node;

	node* temp2 = new node;
	node* temp3 = new node;
	node* temp4 = new node;
	node* temp5 = new node;
	node* temp6 = new node;
	node* temp7 = new node;

	temp1->key = 7;
	temp2->key = 36;
	temp3->key = 32;
	temp4->key = 33;
	temp5->key = 60;
	temp6->key = 67;
	temp7->key = 84;

	Create(head, temp1, current);
	Create(head, temp2, current);
	Create(head, temp3, current);
	Create(head, temp4, current);
	Create(head, temp5, current);
	Create(head, temp6, current);
	Create(head, temp7, current);*/}
}

void Rec(node*& Current, int num, bool &b) {

	if (num == Current->key) {

		cout << "detected" << endl;
		b = 1;
	}
	else {
		if (num < Current->key) {
			if (Current->left == nullptr) {
				cout << "disappeard" << endl;
			}
			else {
				Current = Current->left;
				Rec(Current, num, b);

			}
		}


		if (num > Current->key) {
			if (Current->right == nullptr) {
				cout << "disappeard" << endl;
			}
			else {
				Current = Current->right;
				Rec(Current, num, b);
			}

		}


	}

}

node* FindMin(node*& p) 
{
	return p->left ? FindMin(p->left) : p;
}
node* removemin(node*& p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)return p->right;
	p->left = removemin(p->left);
	Balance(p);
	return p;
}

//void DeleteKey(node*& hip) {
//	bool b = 0;
//	int num;
//	node * Current = hip;
//	if (hip == nullptr) {
//		cout << "Empty" << endl;
//		return;
//	}
//
//	cout << "enter deleted key" << endl;
//	cin >> num;
//	Rec(hip, num,b);
//	
//	if (b == 0) {
//		return;
//	}
//	else {
//		node* left = hip->left;
//		node* right = hip->right;
//		//node*nw = head;
//		
//		if (right == nullptr && left==nullptr) {
//
//			hip=nullptr;
//			
//			return;
//
//		}
//		else {
//		node* min= FindMin(right);
//		min->right = removemin(right);
//		min->left = left;
//		Balance(min);
//		Current = min;
//		}
//	
//	}
//	Balance(Current);
//}

node* remove(node* p, int k) // удаление ключа k из дерева p
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* min = FindMin(r);
		min->right = removemin(r);
		min->left = q;
		// Balance(min);
		 return min;
	}
	//Balance(p);
	return p;
}


//node* DeleteKey(node* head, int num) {
//	//node* nw;
//	if (head == nullptr) {
//		cout << "Empty" << endl;
//		exit(0);
//	}
//	if (num < head->key) {
//		if (head->left == nullptr) {
//			cout << "disappeard" << endl;
//			exit(0);
//		}
//		else {
//
//			DeleteKey(head->left, num);
//		}
//	}
//	else if (num > head->key) {
//		if (head->right == nullptr) {
//			cout << "disappeard" << endl;
//			exit(0);
//		}
//		else DeleteKey(head->right, num);
//	}
//	if (num == head->key) {
//		node* left = head->left;
//		node* right = head->right;
//		
//		if (right == nullptr) {
//			node* nw = head;
//			delete nw;
//			return right;
//		}
//		node* min = FindMin(right);
//		min->right = removemin(right);
//		min->left = left;
//		Balance(min);
//		return min;
//	}
//	// Balance(head);
//	 //return head;
//}


void SearchKey(node*& head) {
	bool b;
	if (head == nullptr) {
		cout << "Empty" << endl;
		return;
	}
	int num;
	cout << "what are you looking for" << endl;
	cin >> num;
	node * Current = head;
	Rec(Current, num,b);

}

void AddKey(node*& head) {
	int num;
	node* temp = new node;
	cout << "Enter key" << endl;
	cin >> num;
	temp->key = num;
	Create(head, temp, current);

}

void Search(node*& head) {
	bool b = 0;
	int num = 0;
	cout << "what are you looking for" << endl;
	cin >> num;
	node* Current=head;
	Rec(Current,num,b);
	cout << Current->key;
	cout << endl;
	StraightPrint(Current);

}


int main() {
	int choice;
	srand(time(0));
	int level = 0;
	node* head = nullptr;
	node*u;
	for (int i = 0; i < 10; i++) {
		Generate(head);
	}
	//current = head;

	//print(head,up);
	//cout << "-----------------------------";
	//StraightPrint(head);
	//SimmHeight(head);
	//cout << endl;
//	Search(head);

	//AddKey(head);
	//SearchKey(head);
	//int num;
	//cout << "---" << endl;
	//cin >> num;
	//u=remove(head,num);
	//Balance(u);
	//DeleteKey(head);
	//Balance(head);
	//head = u;
	//print(head, up);
	
	//cout << "eeeeee changes" << endl;

	//Balance(head);

	//print(head, up);
	//cout << "-----------------------------";

	while (1) {
		cout << "Menu" << endl;
		cout << "(1)Print\n"
			<< "(2)Add elem\n"
			<< "(3)Del elem\n"
			<< "(4) Search\n"
			<< "(5) back\n"
			<< "(6)Exit\n";
		cin >> choice;
		switch (choice) {
		case 1: {
			print(head,up);
			break;

		}
		case 2: {
			AddKey(head);
			break;

		}
		case 3: {
			int num;
			cout << "enter deleted key" << endl;
			cin >> num;
			u=remove(head,num);
			Balance(u);
			head = u;
			print(head, up);
			break;
		}
		case 4: {
			SearchKey(head);
			break;
		}
		case 5: {
			Search(head);
			break;
		}
		case 6: {
			return 0;

		}
		default: {
			cout << "incorrect expression\n"
				<< "try again\n";
		}
		}
	}



	system("pause");
    return 0;
}