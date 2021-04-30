#include <iostream>
#include <string>
#include "yolcu.h"
#include "sefer.h"
using namespace std;

yolcu::yolcu(){
	setAd("");
	setSoyad("");
	setKoltukNo(0);
	setYolcuNo(0);
}

yolcu::yolcu(string ad,string s,int kno,int yno){
	setAd(ad);
	setSoyad(s);
	setKoltukNo(kno);
	setYolcuNo(yno);
}

yolcu::yolcu(int sn,int yn,string ky,string vy,int kn,string ad,string soyad){
	sefer::setSeferNo(sn);
	sefer::setVarisYeri(vy);
	sefer::setKalkisYeri(ky);
	setYolcuNo(yn);
	setKoltukNo(kn);
	setAd(ad);
	setSoyad(soyad);
}

// Ad degiskeni set&get
void yolcu::setAd(string ad){
	this->Ad=ad;
}
string yolcu::getAd(){
	return this->Ad;
}

// Soyad degiskeni set&get
void yolcu::setSoyad(string s){
	this->Soyad=s;
}
string yolcu::getSoyad(){
	return this->Soyad;
}

// Koltuk Numarasi set&get
void yolcu::setKoltukNo(int kno){
	this->KoltukNo=kno;
}
int yolcu::getKoltukNo(){
	return this->KoltukNo;
}

// Yolcu Numarasý set&get
void yolcu::setYolcuNo(int yno){
	this->YolcuNo=yno;
}
int yolcu::getYolcuNo(){
	return this->YolcuNo;
}

// yolcu bilgilerini ekrana yazan fonksiyon
void yolcu::yolcuYaz(){
	cout<<getAd()<<"   "<<getSoyad()<<"   "<<getKoltukNo()<<endl;
}

// yolcu kayýt oldugunda yazdýran fonksiyon
void yolcu::yolcuKayitYaz(){
  
	cout<<"SeferNo - KoltukNo - KalkisYeri - VarisYeri - Ad - Soyad"<<endl;
	cout<<getSeferNo()<<"   "<<getKoltukNo()<<"   "
	<<getKalkisYeri()<<"   "<<getVarisYeri()<<"   "
	<<getAd()<< "   "<<getSoyad()<<"   "<<endl;
}