#include <cstdlib>
#include <iostream>
#include <string>
#include "sefer.h"
#include "yolcu.h"
#include <locale.h>
#include <fstream>
#include <sstream>
//ODEV GRUP CALISMASIDIR
//DUYGU ORHAN
//NİLAY BESLİ
int anaMenu();
void seferEkle(sefer seferler[],int boyut);
void seferListele(sefer seferler[],int boyut);
void biletSatis(sefer seferler[],yolcu yolcular[],int boyut);
void otobusDurumu(sefer seferler[],yolcu yolcular[],int boyut);
void seferOku(sefer seferler[],int boyut);
void seferYaz(sefer seferler[],int boyut);
void yolcuYaz(sefer seferler[],yolcu yolcular[],int boyut);
void yolcuSeferYaz(sefer seferler[],yolcu yolcular[],int boyut);
int seferSayisi();


sefer seferler[100];
yolcu yolcular[100];


int koltuk_sayi,koltuk_no,sefer_no,no;
string kalkis_y,varis_y;
string ad,soyad;    
using namespace std;

// ANA MENU
int anaMenu(){
	string secilen;
	int sec=0;
	cout<<endl;
	cout<<"**********************************"<<endl;
	cout<<"*****         ANA MENU       *****"<<endl;
	cout<<"*****   1-)Sefer Listeleme   *****"<<endl;
	cout<<"*****   2-)Sefer Ekleme      *****"<<endl;
	cout<<"*****   3-)Bilet Islemleri   *****"<<endl;
  cout<<"*****   4-)Otobus Durumu     *****"<<endl;
	cout<<"*****   5-)Cikis             *****"<<endl;
	cout<<"**********************************"<<endl;
	cout<<"Secim : ";
	cin>>secilen;
	stringstream(secilen)>>sec;	// string degeri secim olan int'e aktarma
	return sec;
}

int seferSayisi(int boyut){
	int seferSay=0;
	for(int i=1;i<=boyut;i++){
		if(seferler[i].getSeferNo()!=0)//eger i.terimde sefer no varsa
			seferSay++;                 //seferi artır
	}
	return seferSay;
}

//sefer ekleme fonksiyonu
void seferEkle(sefer seferler[],int boyut){

	int bulundu=0,indis=0;
	// bos indisi bul
	for(int i=1;i<=boyut;i++){
		if(seferler[i].getSeferNo()==0){
			indis=i;
			break;
		}   
	} //bos indis bulundu
	// daha önce almayan sefer no bul
		do{
			bulundu=0;
			cout<<"Sefer no : ";
			cin>>sefer_no;
			if(sefer_no<=0){
				cout<<"Sefer numarası 0 veya küçük olamaz"<<endl;
				bulundu=1;
			}
			if(sefer_no>0){
				for(int i=1;i<=boyut;i++){
					// sefer no daha onceden alinmis mi diye kontrol ediyoruz
					if(seferler[i].getSeferNo()==sefer_no){
						cout<<"Bu sefer daha onceden alinmis"<<endl;
						bulundu=1;
					}
				}
			}
		}while(bulundu==1);


	// bos sefer no'ya kullanıcıdan alınan veriler girilir
	seferler[indis].setSeferNo(sefer_no);//i. sefere sefer no atanır
	cout<<"Kalkis yeri : ";
	cin>>kalkis_y;
	seferler[indis].setKalkisYeri(kalkis_y);//i. sefere kalkış yeri atanır
	cout<<"Varis yeri : ";
	cin>>varis_y;
	seferler[indis].setVarisYeri(varis_y);//i. sefere varış yeri atanır

	seferler[indis].setKoltukSayisi(33);//i. indise koltuk sayısı atanır
	cout<<"YUKARIDAKI BILGILERE SAHIP YENI SEFER KAYDI OLUSTURULDU"<<endl<<endl;
	seferListele(seferler,100);

}

//oluşturduğumuz seferleri görüntüler
void seferListele(sefer seferler[],int boyut){
  int yn,x=1;
	int seferSay=seferSayisi(100);//sefer eklede elde edilen sefer sayısını verir
  ifstream seferOku("seferler.txt",ios::in);
  while(seferOku>>sefer_no>>koltuk_sayi>>kalkis_y>>varis_y){
		sefer gecici(sefer_no,yn,kalkis_y,varis_y);
		seferler[x]=gecici;
		x++;
	}
	if(seferSay!=0){
		cout<<endl<<"SEFER NO   KOLTUK SAYISI  KALKIS YERI  VARIS YERI"<<endl<<endl;
		for(int i=1;i<=boyut;i++){
			if(seferler[i].getSeferNo()!=0){//sefer no'nun olup olmadığını kontrol eder
				seferler[i].seferOku();

			}
		}
	}
	else
		cout<<"SEFER KAYDI BULUNAMADI"<<endl;
}

//bilet satış işlemini gerçekleştirir
void biletSatis(sefer seferler[],yolcu yolcular[],int boyut){
  int yno,i=1,bulundu=0,satisIndis=-1;

	cout<<endl<<endl;
	seferListele(seferler,100);
	cout<<endl<<endl;
	cout<<"Lutfen bilet almak istediginiz sefer no'yu giriniz : ";
	cin>>sefer_no;

	if(sefer_no>0){
		// indisi bul
		for(int i=1;i<=boyut;i++){
			if(seferler[i].getSeferNo()==sefer_no){//dizideki i. eleman sefer no'ya eşit mi
				satisIndis=i;//aranan indis bulundu
				break;
			}
		}

		// sefer'deki tüm koltuklar dolu mu ?
		int koltukSay=0;
		for(int i=1;i<=boyut;i++){
			if(yolcular[i].getSeferNo()==sefer_no)
				koltukSay++;//i.indisteki kaç yolcunun sefer no'su eşittir,eşitse bir arttır
		}
		if(koltukSay>=seferler[satisIndis].getKoltukSayisi())//otobusun bos mu dolu mu olduğuna bakar
			cout<<"BU SEFERDEKI TÜM KOLTUKLAR SATILMIS"<<endl;
		else{
			// boyle bir sefer var demektir
			if(satisIndis!=-1){
				// bos olan yolcu numarasını bul
				for(int i=1;i<=boyut;i++){
					if(yolcular[i].getYolcuNo()==0){
						yno=i;//boş olan yolcu nosu bulundu
						break;
					}
				}
				yolcular[yno].setYolcuNo(yno);//yolcu no set metodu ile alınır
				cout<<"Adiniz : ";
				cin>>ad;
				yolcular[yno].setAd(ad);//ad,set metodu ile alınır
				cout<<"Soyadiniz : ";
				cin>>soyad;
				yolcular[yno].setSoyad(soyad);//soyad,metodu ile alınır

				cout<<"Toplam "<<seferler[satisIndis].getKoltukSayisi()<<" adet koltugumuz bulunmaktadir.."<<endl;//istenilen indisteki kadar koltuk vardır
				do{
					bulundu=0;
					cout<<"Koltuk numaraniz : ";
					cin>>koltuk_no;
					if(koltuk_no>0){
						for(int i=1;i<=boyut;i++){
							// koltuk daha onceden alinmis mi ?
							if(yolcular[i].getKoltukNo()==koltuk_no && yolcular[i].getSeferNo()==sefer_no){//koltuk numarı daha önceden alınmış mı diye kontrol ediyor
								cout<<"Bu koltuk daha onceden alinmis"<<endl;
								bulundu=1;
							}
							// girilen deger uygun mu ?
							if(koltuk_no>seferler[satisIndis].getKoltukSayisi() || koltuk_no<0){
								bulundu=2;
							}
						}
					}
					else
						cout<<"Koltuk no 0'dan büyük olmalidir"<<endl;
					if(bulundu==2) cout<<"Bu numarada koltuk bulunmamaktadir!!"<<endl;
				}
        while( koltuk_no<=0 || bulundu==1 || bulundu==2);
   
				yolcular[yno].setKoltukNo(koltuk_no);//yolcular dizise koltuk numaramız konulunuyor

				// sefer bilgilerini yolcu bilgilerine kaydediyoruz
				yolcular[yno].setSeferNo(sefer_no);
				yolcular[yno].setKalkisYeri(seferler[satisIndis].getKalkisYeri());
				yolcular[yno].setVarisYeri(seferler[satisIndis].getVarisYeri());

				yolcular[yno].yolcuKayitYaz();
				cout<<endl<<"Yukaridaki bilgilere ait bilet satis islemi basariyla gerceklesti..\nYine bekleriz.."<<endl;
			}
			else
				cout<<"Boyle bir sefer yok"<<endl;
		}
	}
	else if(sefer_no<=0)
		cout<<"Sefer no 0' dan büyük olmalidir"<<endl;
}

void yolcuSeferYaz(sefer seferler[],yolcu yolcular[],int boyut){
ofstream yolcuSeferYaz("yolcuSefer.txt",ios::app);
	// yolcu dosyası olusmadıysa
	if(!yolcuSeferYaz){
		cout<<"DOSYA OLUSTURULAMADI"<<endl;
		exit(1);
	}
	// sefer ve yolcuları dosyaya yazan dongü
	for(int i=1;i<=boyut;i++){
		if(seferler[i].getSeferNo()!=0){
			yolcuSeferYaz<<"------------------------------------------------------"<<endl;
			yolcuSeferYaz<<"SeferNo - KoltukSayisi - KalkisYeri - VarisYeri - Sofor adi - Kalkis Saati - Varis Saati "<<endl;
			yolcuSeferYaz<<seferler[i].getSeferNo()<<"   "
						 <<seferler[i].getKoltukSayisi()<<"   "
						 <<seferler[i].getKalkisYeri()<<"   "
						 <<seferler[i].getVarisYeri()<<"  "<<endl;
			yolcuSeferYaz<<endl<<"Ad - Soyad - KoltukNo"<<endl;
			// o seferdeki toplam yolcu sayısı kadar dön
			for(int j=1;j<=boyut;j++){
				if(yolcular[j].getYolcuNo()!=0 && yolcular[j].getSeferNo()==i){
					yolcuSeferYaz<<yolcular[j].getAd()<<"   "
								 <<yolcular[j].getSoyad()<<"   "
								 <<yolcular[j].getKoltukNo()<<endl;
				}
			}
			yolcuSeferYaz<<endl;
		}
	}
}


void seferOku(sefer seferler[],int boyut){
  ifstream seferOku("seferler.txt",ios::in);//dosyayı okuyacağız
	
	// gecici degiskenler
	int x=1,seferSayisi=0;

	// dosyadan oku seferler nesne dizisine yaz
	while(seferOku>>no>>koltuk_sayi>>kalkis_y>>varis_y){//seferoku'da bilgi okur
		sefer gecici(no,koltuk_sayi,kalkis_y,varis_y);
		seferler[x]=gecici;//geçiçi olarak aldığı bilgileri diziye atar
		x++;
	}
	seferOku.close();//dosya kapandı

	cout<<"SEFERLER DOSYADAN OKUNDU";
  
	// toplam sefer sayısını bulur
	for(int i=1;i<=33;i++){
		if(seferler[i].getSeferNo()!=0)
			seferSayisi++;
	}
	// sefer bilgilerini yaz
	cout<<endl<<"TOPLAM "<<seferSayisi<<" ADET SEFER BULUNMAKTADIR";

}

void seferYaz(sefer seferler[],int boyut){
  ofstream seferYaz("seferler.txt",ios::out);//seferleri yazan metot açılır
	// seferler yazılamadıysa
	if(!seferYaz){//dosyanın açılıp açılmadığı kontrol edilir.
		cout<<"SEFER YAZ DOSYA ACILAMADI!!"<<endl;
		exit(1);
	}

	// sefer bilgilerini dosyaya yaz
	for(int i=1;i<=boyut;i++){
		if(seferler[i].getSeferNo()!=0){
			seferYaz<<seferler[i].getSeferNo()<<" "
					<<seferler[i].getKoltukSayisi()<<" "
					<<seferler[i].getKalkisYeri()<<" "
					<<seferler[i].getVarisYeri()<<endl;
		}
	}
	seferYaz.close();
}

//yolcu bilgilerini yazar
void yolcuYaz(sefer seferler[],yolcu yolcular[],int boyut){
// yolcular dosyasını olustur
	ofstream yolcuYaz("yolcular.txt",ios::app);
	if(!yolcuYaz){
		cout<<"YOLCULAR DOSYASI ACILAMADI"<<endl;
	}

	int yolcuSay=0;
	// toplam yolcu sayısını bul
	for(int i=1;i<=boyut;i++){
		if(yolcular[i].getYolcuNo()!=0)
			yolcuSay++;
	}
	// yolcu bilgilerini dosyaya yaz
	for(int i=1;i<=yolcuSay;i++){
		// yolcu no'su bos degilse yolcu var demektir onu dosyaya yaz
		if(yolcular[i].getYolcuNo()!=0){
			yolcuYaz<<yolcular[i].getSeferNo()<<" "
					<<yolcular[i].getYolcuNo()<<" "
					<<yolcular[i].getKalkisYeri()<<" "
					<<yolcular[i].getVarisYeri()<<" "
					<<yolcular[i].getKoltukNo()<<" "
					<<yolcular[i].getAd()<<" "
					<<yolcular[i].getSoyad()<<" "<<endl;
		}
	}
	yolcuYaz.close();
}


void otobusDurumu(sefer seferler[],yolcu yolcular[],int boyut){
    int yn,kn,x=1,yolcuSay=0;
	  string ky,vy,ad,soyad;
    ifstream yolcu("yolcular.txt");

    int sn,yno,kno,i=1,bulundu=0,satisIndis=-1;
    seferListele(seferler,100);

    cout<<"Lutfen gormek istediginiz sefer no'yu giriniz : ";
	    cin>>sn;
    if(sn>0){
		// indisi bul
		for(int i=1;i<=33;i++){
			if(seferler[i].getSeferNo()==sn){
				satisIndis=i;
				break;
			}
		}//seferi bulduk

		// seferdeki tüm koltuklar dolu mu ?
		for(int i=1;i<=33;i++){
      int koltukSay=0;
		  if(yolcular[i].getSeferNo()==sn){
				koltukSay++;
      }

    }

	  while(!yolcu.eof()){
    
    yolcu>>sn>>yno>>ky>>vy>>kno>>ad>>soyad;
         for(int j=1;j<=33;j++){
                    while(kno!=j){
                cout<<j<<". Musait\t";
                  if(j%4==0){
                cout<<"\n";
            }
                    break;
                }
            if(kno==j){
                cout<<kno<<". "<<ad<<"  ";
                    if(j%4==0){
                cout<<"\n";
            }
                yolcu>>sn>>yno>>ky>>vy>>kno>>ad>>soyad;
           }
 yolcu>>sn>>yno>>ky>>vy>>kno>>ad>>soyad;

         }
         break;
		}
    
     }
        
else
    cout<<"Oyle bir sefer olamaz!"<<endl;
  }

  
	// main program
int main(){
  setlocale(LC_ALL,"Turkish");	// türkçe karekter
	int secim=0;
  
	do{
		secim=anaMenu();
		switch(secim){
			case 1: seferOku(seferler,100);
          seferListele(seferler,100);
					break;

	    case 2: seferEkle(seferler,100);
      seferYaz(seferler,100);
					break;

			case 3: biletSatis(seferler,yolcular,100);
					yolcuYaz(seferler,yolcular,100);
          seferYaz(seferler,100);
					break;
            case 4: otobusDurumu(seferler, yolcular,100);
					break;
			case 5: cout<<"Program Kapaniyor!!"<<endl;
					
					
					break;
			default: cout<<"YANLIS SECIM LUTFEN YENIDEN SECIM YAPIN!!"<<endl<<endl;
			break;
		}
	}while(secim!=5);
	return 0;
}