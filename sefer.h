#ifndef SEFER_H
#define	SEFER_H
#include <string>
#include <iostream>

using namespace std;

// sefer class'i prototip header dosyasi

class sefer{
private:
	// private alan sadece class içi erisim
    int SeferNo;
    int KoltukSayisi;
    string KalkisYeri;
    string VarisYeri;
    
public:
	// parametreli ve paremetresiz constructor'lar
    sefer();
    sefer(int sn,int ks,string ky,string vy);
    // encapsulation

    void setSeferNo(int sn);
    int getSeferNo();
    void setKoltukSayisi(int ks);
    int getKoltukSayisi();
    void setKalkisYeri(string ky);
    string getKalkisYeri();
    void setVarisYeri(string vy);
    string getVarisYeri();
    
    // sefer print fonksiyonu
    void seferYaz();
    void seferOku();
};



#endif	/* SEFER_H */
