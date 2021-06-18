#include <iostream>
#include "tree.h"

Student data1;
Student data2;
Student data3;
void dataPr(bool kur);
bool secimAl(char secim);
Student* dataAl();

int main()
{
    dataPr(true);

    bool bitir = false;
    while (!bitir)
    {
        char secim;
        cout << "Asagidaki islemlerden birini seciniz..." << endl;
        cout << endl;
        cout << "Arama yapmak icim: A" << endl;
        cout << "Listeyi ekrana yazdirmak icin: L" << endl;
        cout << "Ogrenci silmek icin: S" << endl;
        cout << "Dosyaya yazmak icin: Y" << endl;
        cout << "Cikis icin: C" << endl;
        cout << endl;

        cout << "Secim: ";
        cin >> secim;

        bitir = secimAl(secim);
    }
    dataPr(false);
}
void dataPr(bool kur) {
    if (kur)
    {
        data1.agacKur("data1.txt");
        data2.agacKur("data2.txt");
        data3.agacKur("data3.txt");
    }
    else
    {
        data1.agacKapat();
        data2.agacKapat();
        data3.agacKapat();
    }
}
bool secimAl(char secim)
{
    bool devam = false;
    Student* tree;
    if (secim == 'A' || secim == 'a')
    {
        tree = dataAl();
        string ogrenciNo;
        cout << "Ogrenci numarasi: ";
        cin >> ogrenciNo;

        tree->ogrenciAra(ogrenciNo);
    }
    else if (secim == 'L' || secim == 'l')
    {
        tree = dataAl();
        tree->ogrenciListele();
    }
    else if (secim == 'S' || secim == 's')
    {
        tree = dataAl();
        string ogrenciNo;
        cout << "Ogrenci numarasi: ";
        cin >> ogrenciNo;
        tree->ogrenciSil(ogrenciNo);
    }
    else if (secim == 'Y' || secim == 'y')
    {
        tree = dataAl();
        tree->dosyayaYaz();
    }
    else if (secim == 'C' || secim == 'c')
    {
        devam = true;
    }
    else
    {
        cout << "Secim: ";
        cin >> secim;
        devam = secimAl(secim);
    }
    return devam;
}
Student* dataAl() {
    char secim;

    cout << "Islem yapmak istediginiz dosyayi seciniz: " << endl;
    cout << "data1.txt icin: 1" << endl;
    cout << "data2.txt icin: 2" << endl;
    cout << "data3.txt icin: 3" << endl << endl;
    cout << "Secim: ";
    cin >> secim;

    switch (secim)
    {
    case '1': return &data1; break;
    case '2': return &data2; break;
    case '3': return &data3; break;
    default:
        dataAl();
        break;
    }
}
