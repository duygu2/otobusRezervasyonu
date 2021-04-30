#include <iostream>
#include <string>

#ifndef YOLCU_H
#define YOLCU_H
#include "sefer.h"
using namespace std;

class yolcu:public sefer{
	private:
		string Ad;
		string Soyad;
		int KoltukNo;
		int YolcuNo;
	public:
		yolcu();
		yolcu(string ad,string s,int kno,int yno);
		yolcu(int sn,int yn,string ky,string vy,int kn,string ad,string soyad);

		void setAd(string ad);
		string getAd();
		void setSoyad(string s);
		string getSoyad();
		void setKoltukNo(int kno);
		int getKoltukNo();
		void setYolcuNo(int yno);
		int getYolcuNo();
		void yolcuYaz();
		void yolcuKayitYaz();
};

#endif
