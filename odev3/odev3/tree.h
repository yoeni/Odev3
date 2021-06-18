#include "student.h"
#include <fstream>

using namespace std;

// Aðaç yapýsý 
struct Student
{
	Node* root;
	int nodeSize;
	string filePath;
	ofstream fileWriter;
	void agacTemizle(Node*);
	void agacYukle();
	void nodeEkle(Node*);
	void nodeSil(Node**);
	void dosyayaYaz();
	void preorderYaz(Node*);
	void agacKur(string path);
	void ogrenciSil();
	void ogrenciListele();
	void inorderTara(Node* root);
	void preorderTara(Node* root);
	void postorderTara(Node* root);
	void ogrenciAra(string ogrenciNo);
	void ilkDerinlikAra(string number);
	void ilkGenislikAra(string number);
	void agacKapat();
};

