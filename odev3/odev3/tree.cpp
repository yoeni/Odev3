#include "tree.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>

void Student::agacKur(string path)
{
	root = NULL;
	filePath = path;
	nodeSize = 0;
	agacYukle();
}

void Student::agacYukle()
{
	ifstream fileReader(filePath);

	string line = "";
	if (fileReader.is_open())
	{
		while (getline(fileReader, line)) {

			int numberIndex = 0;
			int nameIndex = line.find("\t") + 1;
			int surNameIndex = line.find_last_of(" ", line.length() - 3) + 1;

			Node* addedNode = new Node;
			addedNode->name = line.substr(nameIndex, surNameIndex - nameIndex - 1);
			addedNode->surName = line.substr(surNameIndex);
			addedNode->number = line.substr(numberIndex, nameIndex - numberIndex - 1);
			nodeEkle(addedNode);
		}
		fileReader.close();
	}
	else {
		cout << "FileReader acilmadi!" << endl;
	}
}

void Student::nodeEkle(Node* addedStudent)
{
	Node* rootPtr = root;
	int result;
	bool isAdded = false;
	addedStudent->rightNode = NULL;
	addedStudent->leftNode = NULL;
	if (root == NULL)
	{
		root = addedStudent;
		nodeSize++;
		return;
	}
	while ((rootPtr != NULL) && (!isAdded))
	{
		result = strcmp(addedStudent->number.c_str(), rootPtr->number.c_str());
		if (result < 0)
		{
			if (rootPtr->leftNode != NULL)
			{
				rootPtr = rootPtr->leftNode;
			}
			else
			{
				rootPtr->leftNode = addedStudent;
				isAdded = true;
			}
		}
		else if (result > 0)
		{
			if (rootPtr->rightNode != NULL)
			{
				rootPtr = rootPtr->rightNode;
			}
			else
			{
				rootPtr->rightNode = addedStudent;
				isAdded = true;
			}
		}
		else
		{
			std::cout << "Aðaç veri yapýsýna ayný veri eklenemez.";
		}
		if (isAdded)
		{
			nodeSize++;
		}
	}
}
 
void Student::ogrenciListele() {
	char secim = 0;;
	cout << "InOrdered listeleme yapmak icin: R" << endl;
	cout << "PreOrdered listeleme yapmak icin: I" << endl;
	cout << "PostOrdered listeleme yapmak icin: O" << endl;
	cout << "Secim: ";
	cin >> secim;

	if (secim == 'R' || secim == 'r')
	{
		inorderTara(root);
	}
	else if (secim == 'I' || secim == 'i')
	{
		preorderTara(root);
	}
	else if (secim == 'O' || secim == 'o')
	{
		postorderTara(root);
	}
	else
	{
		ogrenciListele();
	}

}

void Student::inorderTara(Node* root)
{
	if (root)
	{
		inorderTara(root->leftNode);
		cout << root->number << " " << root->name << " " << root->surName << endl;
		inorderTara(root->rightNode);
	}
}
void Student::preorderTara(Node* root)
{
	if (root)
	{
		cout << root->number << " " << root->name << " " << root->surName << endl;
		preorderTara(root->leftNode);
		preorderTara(root->rightNode);
	}
}
void Student::postorderTara(Node* root)
{
	if (root)
	{
		postorderTara(root->leftNode);
		postorderTara(root->rightNode);
		cout << root->number << " " << root->name << " " << root->surName << endl;
	}
}

void Student::ogrenciSil(string ogrenciNo)
{

	Node* rootPtr = root, * upper = NULL;
	bool bulundu = false;
	char direction = 'k';
	while (rootPtr && !bulundu)
	{
		int result = strcmp(ogrenciNo.c_str(), rootPtr->number.c_str());
		if (result < 0)
		{
			upper = rootPtr;
			direction = 'l';
			rootPtr = rootPtr->leftNode;
		}
		else if (result > 0)
		{
			upper = rootPtr;
			direction = 'r';
			rootPtr = rootPtr->rightNode;
		}
		else
			bulundu = true;
		if (bulundu)
		{
			if (direction == 'l')
			{
				nodeSil(&upper->leftNode);
				cout << "Kayit Silindi\n";
			}
			else if (direction == 'r')
			{
				nodeSil(&upper->rightNode);
				cout << "Kayit Silindi\n";
			}
			else
				cout << "Kayit bulunamadi\n";
		}
	}
}
void Student::nodeSil(Node** deletedNode)
{
	Node* deletedNodePtr = *deletedNode, * q;
	if (deletedNodePtr == NULL)
	{
		*deletedNode = deletedNodePtr->leftNode;
		delete deletedNodePtr;
	}
	else if (deletedNodePtr->leftNode == NULL)
	{
		*deletedNode = deletedNodePtr->rightNode;
		delete deletedNodePtr;
	}
	else
	{
		for (q = deletedNodePtr->rightNode; q->leftNode; q = q->leftNode);
		q->leftNode = deletedNodePtr->leftNode;
		*deletedNode = deletedNodePtr->rightNode;
		delete deletedNodePtr;
	}
}

void Student::ogrenciAra(string ogrenciNo) {


	char secim;
	cout << "Ilk Derinlik Aramak icin : D" << endl;
	cout << "Ilk Genislik Aramak icin : G" << endl;
	cout << "Secim: ";
	cin >> secim;

	if (secim=='D'||secim=='d')
	{
		ilkDerinlikAra(ogrenciNo);
	}else if (secim == 'G' || secim == 'g')
	{
		ilkGenislikAra(ogrenciNo);
	}
	else
	{
		ogrenciAra(ogrenciNo);
	}
	cout <<endl;
}

// Ilk derinlik arama ile ögrenciyi arar
void Student::ilkDerinlikAra(string number)
{
	int counter = 0;
	Node* studentNode;
	stack<Node*> studentStack;
	studentStack.push(root);
	while (!studentStack.empty())
	{
		counter++;
		studentNode = studentStack.top();
		studentStack.pop();
		if (strcmp(number.c_str(), studentNode->number.c_str()) == 0)
		{
			cout << studentNode->number << " " << studentNode->name << " " << studentNode->surName << endl;
			cout << "Islem sayisi: "<< counter << endl;
			return;
		}
		if (studentNode->rightNode)
		{
			studentStack.push(studentNode->rightNode);
		}
		if (studentNode->leftNode)
		{
			studentStack.push(studentNode->leftNode);
		}
	}
}
void Student::ilkGenislikAra(string number)
{
	queue<Node*> queue;
	Node* p;
	int counter = 0;
	queue.push(root);
	while (!queue.empty())
	{
		counter++;
		p = queue.front();
		queue.pop();
		if (strcmp(number.c_str(), p->number.c_str()) == 0)
		{
			cout << p->number << " " << p->name << " " << p->surName << endl;
			cout << "Islem sayisi: " << counter << endl;
			return;
		}
		if (p->rightNode)
		{
			queue.push(p->rightNode);
		}
		if (p->leftNode)
		{
			queue.push(p->leftNode);
		}
	}
}

void Student::agacTemizle(Node* root)
{
	if (root)
	{
		if (root->leftNode != NULL)
		{
			agacTemizle(root->leftNode);
			root->leftNode = NULL;
		}
		if (root->rightNode != NULL)
		{
			agacTemizle(root->rightNode);
			root->rightNode = NULL;
		}
		delete root;
	}
}

void Student::dosyayaYaz()
{
	string number = filePath.substr(4);

	fileWriter.open("tree_" + number);
	if (fileWriter.is_open())
	{
		preorderYaz(root);
		fileWriter.close();
		cout << "Dosya basariyla olusuturldu!"<<endl;
	}

}

void Student::preorderYaz(Node* root) {

	if (root)
	{
		if (fileWriter.is_open())
		{
			fileWriter << root->number << " " << root->name << " " << root->surName << endl;
		}
		preorderYaz(root->leftNode);
		preorderYaz(root->rightNode);
	}
}

void Student::agacKapat()
{
	agacTemizle(root);
}

