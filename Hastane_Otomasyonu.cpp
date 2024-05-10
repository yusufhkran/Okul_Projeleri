#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
struct Hasta {
	int id;
	string isim;
	int yas;
	int oncelik;
	string teshis;
	string ameliyatBaslangic;
	string ameliyatBitis;
	Hasta* prev;
	Hasta* next;
	string ameliyatBilgisi;
	double ameliyatUcreti;
};

// Doktor tarafından eklenen hasta bilgilerinin kaydedildiği çift yönlü dairesel bağlı liste
class HastaKayitlari {
private:
	Hasta* head;
public:
	HastaKayitlari() : head(nullptr) {}

	Hasta* getHead() {
		return head;
	}

	bool isEmpty() {
		return head == nullptr;
	}
	// Doktor tarafından yapılan ameliyat silme işlemi
	void ameliyatSil(int id) {
		if (head == nullptr) {
			//head pointerını listede gezdirip ameliyat bilgisi olup olmadığını öğrenme işlemi
			cout << "Liste boş, silinecek ameliyat bulunamadı." << endl;
			return;
		}

		Hasta* temp = head;
		while (temp != nullptr) {
			if (temp->id == id) {
				// Ameliyat bilgisi olan hasta varsa yapılacak işlemler
				if (!temp->ameliyatBaslangic.empty() || !temp->ameliyatBitis.empty()) {
					temp->ameliyatBaslangic = "";
					temp->ameliyatBitis = "";
					cout << "Hastanın ameliyat bilgisi başarıyla silindi." << endl;
				}
				else {
					cout << "Hastanın ameliyat bilgisi zaten bulunmamaktadır." << endl;
				}
				return;
			}
			temp = temp->next;
			if (temp == head) {
				// Bir tur tamamlandı, liste sonuna gelindi
				break;
			}
		}
		cout << "ID'si " << id << " olan hastaya ait ameliyat bilgisi bulunamadı." << endl;
	}
	double ameliyatUcretiHesapla(int id) {
		if (head == nullptr) {
			cout << "Liste boş, ameliyat ücreti hesaplanamadı." << endl;
			return 0.0;
		}
		Hasta* temp = head;
		while (temp != nullptr) {
			if (temp->id == id) {
				// ID ' si girilen hastanın bilgilerini bulma
				double sabitUcret = 62000.0;
				double netUcret = 0.0;
				if (temp->yas < 18) {
					// 18 yaş altındaki hastalara farklı bir ücret uygulama if bloğu
					netUcret = sabitUcret * 0.7; // Sabit ücretin %70'i
				}
				else if (temp->yas >= 18 && temp->yas <= 65) {
					// 18 ile 65 yaş arasındaki hastalara standart bir ücret uygulama if bloğu
					netUcret = sabitUcret;
				}
				else {
					// 65 yaş üstündeki hastalara farklı bir ücret uygulama if bloğu
					netUcret = sabitUcret * 0.2; // Sabit ücretin %20'si
				}
				return netUcret;
			}
			temp = temp->next;
			if (temp == head) {
				// Bir tur tamamlandı, liste sonuna gelindi
				break;
			}
		}
		cout << "ID'si " << id << " olan hastaya ait ameliyat ücreti hesaplanamadı." << endl;
		return 0.0;
	}

	void ekle(int id, const string& isim, int yas, int oncelik, const string& teshis, const string& ameliyatBaslangic, const string& ameliyatBitis) {
		//Burada da gerekli parametreleri alıp , hastayı düğüme ekliyoruz
		Hasta* newNode = new Hasta(); 
		newNode->id = id;
		newNode->isim = isim;
		newNode->yas = yas;
		newNode->oncelik = oncelik;
		newNode->teshis = teshis;
		newNode->ameliyatBaslangic = ameliyatBaslangic;
		newNode->ameliyatBitis = ameliyatBitis;
		newNode->prev = nullptr;
		newNode->next = nullptr;

		if (head == nullptr) {
			head = newNode;
			head->next = head;
			head->prev = head;
		}
		else {
			Hasta* temp = head->prev;
			temp->next = newNode;
			newNode->prev = temp;
			newNode->next = head;
			head->prev = newNode;
		}
	}
	// Hastaları yazdırma
	void yazdir() {
		if (isEmpty()) {
			cout << "Kayıt bulunamadı." << endl;
			return;
		}

		Hasta* temp = head;
		do {
			cout << "ID: " << temp->id << ", İsim: " << temp->isim << ", Yaş: " << temp->yas << ", Hasta Önceliği (1-10): " << temp->oncelik << ", Teşhis: " << temp->teshis << ", Ameliyat Başlangıç: " << temp->ameliyatBaslangic << ", Ameliyat Bitiş: " << temp->ameliyatBitis << endl;

			temp = temp->next;
		} while (temp != head);
	}
	// ID ' si girilen hastanın öncelik durumunu yazdırma
	void yazdirIdOncelik() {
		if (isEmpty()) {
			cout << "Kayıt bulunamadı." << endl;
			return;
		}

		Hasta* temp = head;
		do {
			cout << "ID: " << temp->id << ", Öncelik: " << temp->oncelik << endl;
			temp = temp->next;
		} while (temp != head);
	}
	// ID ' si girilen hastanın ameliyat bilgilerini yazdırma
	void yazdirAmeliyat() {
		if (isEmpty()) {
			cout << "Kayıt bulunamadı." << endl;
			return;
		}

		Hasta* temp = head;
		bool ameliyatYapildi = false;
		do {
			if (!temp->ameliyatBaslangic.empty() && !temp->ameliyatBitis.empty()) {
				cout << "ID: " << temp->id << ", Ameliyat Başlangıç: " << temp->ameliyatBaslangic << ", Ameliyat Bitiş: " << temp->ameliyatBitis << endl;
				ameliyatYapildi = true;
			}
			temp = temp->next;
		} while (temp != head);

		if (!ameliyatYapildi) {
			cout << "Ameliyat hastası bulunamadı." << endl;
		}
	}
	// ID ' si girilen hastayı silme fonksiyonu
	void hastaSil(int id) {
		if (head == nullptr) {
			cout << "Liste boş, silinecek hasta bulunamadı." << endl;
			return;
		}

		Hasta* temp = head;
		while (temp != nullptr) {
			if (temp->id == id) {
				// Silinecek hasta bulundu
				if (temp->next == temp) {
					// Tek bir hasta varsa
					delete temp;
					head = nullptr;
				}
				else {
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
					if (temp == head) {
						// Silinen hasta baştaki hasta ise head'i güncelle
						head = temp->next;
					}
					delete temp;
				}
				cout << "Hasta başarıyla silindi." << endl;
				return;
			}
			temp = temp->next;
			if (temp == head) {
				// Bir tur tamamlandı, liste sonuna gelindi
				break;
			}
		}
		cout << "ID'si " << id << " olan hasta bulunamadı." << endl;
	}
	// ID ' si girilen hastaya ameliyat bilgisi ekleme
	void ameliyatEkle(int id, const string& ameliyatBaslangic, const string& ameliyatBitis) {
		Hasta* temp = head;
		while (temp != nullptr) {
			if (temp->id == id) {
				// İlgili hastanın bilgilerini güncelle
				temp->ameliyatBaslangic = ameliyatBaslangic;
				temp->ameliyatBitis = ameliyatBitis;
				cout << "Ameliyat başarıyla eklendi." << endl;
				return;
			}
			temp = temp->next;
		}
		cout << "ID'si " << id << " olan hasta bulunamadı." << endl;
	}
};



struct Node {
	int numara;
	string islem;
	Node* prev;
	Node* next;
	int oncelik, id, yas; 
	string teshis, isim; 
	string ameliyatBaslangic; 
	string ameliyatBitis;
};
//Hastaların yapacağı işlemler için çift yönlü dairesel bağlı liste sınıfı oluşturma
class ciftYonluDaireselBagliListe {
private:
	Node* head;
public:
	ciftYonluDaireselBagliListe() : head(nullptr) {}
	Node* getHead() {
		return head;
	}

	bool isEmpty() {
		return head == nullptr;
	}
	// Hasta işlemi ekleme
	void ekle(int numara, string islem) {
		Node* newNode = new Node();
		newNode->numara = numara;
		newNode->islem = islem;
		newNode->prev = nullptr;
		newNode->next = nullptr;

		if (head == nullptr) {
			head = newNode;
			head->next = head;
			head->prev = head;
		}
		else {
			Node* temp = head->prev;
			temp->next = newNode;
			newNode->prev = temp;
			newNode->next = head;
			head->prev = newNode;
		}
	}
	// Hasta işlemlerini yazdırma
	void yazdir() {
		if (head == nullptr) {
			cout << "Liste boş." << endl;
			return;
		}

		Node* temp = head;
		do {
			cout << setw(17) << temp->numara << ". Islem: " << temp->islem << endl;
			temp = temp->next;
		} while (temp != head);
	}
};
	// Doktor işlemleri için çift yönlü bağlı liste 
class ciftYonluBagliListe {
private:
	Node* head;
	Node* tail;
public:
	ciftYonluBagliListe() :head(NULL), tail(NULL) {}
	// Doktor işlemi ekleme
	void ekle(int numara, string islem) {
		Node* newNode = new Node();
		newNode->numara = numara;
		newNode->islem = islem;
		newNode->prev = NULL;
		newNode->next = NULL;
		if (head == NULL) {
			head = newNode;
			tail = newNode;
		}
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	}
	// Doktor işlemlerini yazdırma
	void yazdir() {
		Node* temp = head;
		int secimDoktor;
		while (temp != NULL) {
			cout << setw(17) << temp->numara << ". Islem: " << temp->islem << endl;
			temp = temp->next;
		}
	}
};
//*****************************************
//Doktor işlemlerini ekleme sınıfı
class elemanEkleme {
private:
	// Doktor işlemleri için oluşturduğum çift yönlü bağlı listeyi pointer olarak "liste" değişkenine atadım
	ciftYonluBagliListe* liste;
public:
	elemanEkleme(ciftYonluBagliListe* l) : liste(l) {}
	void elemanlariEkle() {
		liste->ekle(1, "Hasta Ekle");
		liste->ekle(2, "ID bilgisi kullanarak hasta sil");
		liste->ekle(3, "Hasta detayları getir");
		liste->ekle(4, "Ameliyat ekle");
		liste->ekle(5, "Ameliyat sil");
		liste->ekle(6, "Ameliyat detaylarını getir");
		liste->ekle(7, "ID’ye göre ameliyat ücretini hesapla");
		liste->ekle(8, "Ana menüye dön");
		liste->ekle(9, "Çıkış");
	}
};
//*****************************************
// Hasta işlemlerini eklemek için oluşturduğum sınıf
HastaKayitlari hastaKayitlari;
class elemanEklemeHasta {
private:
	// Hasta işlemleri için oluşturduğum çift yönlü dairesel bağlı listeyi pointer olarak "liste" değişkenine atadım
	ciftYonluDaireselBagliListe* liste;
public:
	elemanEklemeHasta(ciftYonluDaireselBagliListe* l) : liste(l) {}
	void elemanlariEkle() {
		liste->ekle(1, "Hastane Doktorlarını Yazdır");
		liste->ekle(2, "Tüm Hastaları Yazdır");
		liste->ekle(3, "Ameliyat Hastalarını Yazdır");
		liste->ekle(4, "Tüm Hastaların Öncelik Puanlarını Yazdır");
		liste->ekle(5, "Ana Menüye Dön");
		liste->ekle(6, "Çıkış");
	}
};
//********************************************
	// Hasta işlemlerini , main'den aldığım secim parametresini sticth case yapısıyla yazdırdım
	// Seçili işlemin numarasına göre Hasta işlemlerinin yapıldığı çift yönlü dairesel bağlı listenin fonksiyonlarını kullanarak işlemleri gerçekleştirdim
bool hastaIslem(int secim) {
	int yonSecim;
	switch (secim)
	{
	case 1:
		system("cls");
		cout << "Hastanemiz Doktorları : Yusuf Kıran " << endl;
		cout << "Hasta Menüsüne Dönmek İçin 1'i , Ana Menü'ye dönmek için 2'yi Tuşlayınız : " << endl;
		cin >> yonSecim;
		if (yonSecim == 1) {
			system("cls");
			return true;
		}
		else {
			return false;
		}
		break;
	case 2:
		system("cls");
		cout << "Tüm Hastalar:" << endl;
		hastaKayitlari.yazdir();
		cout << "Hasta Menüsüne Dönmek İçin 1'i , Ana Menü'ye dönmek için 2'yi Tuşlayınız : " << endl;
		cin >> yonSecim;
		if (yonSecim == 1) {
			system("cls");
			return true;
		}
		else {
			return false;
		}
		break;
	case 3:
		system("cls");
		cout << "Ameliyat Bekleyen Hastalırımızın ID ve Ameliyat Tarihleri : " << endl;
		hastaKayitlari.yazdirAmeliyat();
		cout << "Hasta Menüsüne Dönmek İçin 1'i , Ana Menü'ye dönmek için 2'yi Tuşlayınız : " << endl;
		cin >> yonSecim;
		if (yonSecim == 1) {
			system("cls");
			return true;
		}
		else {
			return false;
		}
		break;
	case 4:
		system("cls");
		cout << "Hasta ID'leri ve Öncelikleri : " << endl;
		hastaKayitlari.yazdirIdOncelik();
		cout << "Hasta Menüsüne Dönmek İçin 1'i , Ana Menü'ye dönmek için 2'yi Tuşlayınız : " << endl;
		cin >> yonSecim;
		if (yonSecim == 1) {
			system("cls");
			return true;
		}
		else {
			return false;
		}
		break;
	case 5:
		return false;
		break;
	case 6:
		exit(0);
		break;
	}
}
//********************************************************************
bool doktorIslem(int secim) {
	// Doktor işlemlerini , main'den aldığım secim parametresini sticth case yapısıyla yazdırdım
	// Seçili işlemin numarasına göre Doktor işlemlerinin yapıldığı hastaKayitlari isimli çift yönlü dairesel bağlı listenin fonksiyonlarını kullanarak işlemleri gerçekleştirdim
	double ucret;
	int yonSecim;
	int id, oncelik, yas;
	string isim, teshis, ameliyatBaslangic, ameliyatBitis;
	switch (secim) {
	case 1:
		cout << "Eklemek İstediğiniz Hastanın ID'sini Giriniz : "; cin >> id;
		cout << "Eklemek İstediğiniz Hastanın İsmini ve Soyismini Birleşik Olarak Giriniz : "; cin >> isim;
		cout << "Eklemek İstediğiniz Hastanın Yaşını Giriniz : "; cin >> yas;
		cout << "Eklemek İstediğiniz Hastanın Hastalık Derecesini 1-10 Arasında Bir Sayı Olacak Şekilde Kodlayınız : "; cin >> oncelik;
		cout << "Eklemek İstediğiniz Hastanın Teşhisini Giriniz : "; cin >> teshis;
		hastaKayitlari.ekle(id, isim, yas, oncelik, teshis, ameliyatBaslangic, ameliyatBitis);
		cout << "Hasta Eklendi..." << endl;
		cout << "Doktor Menüsüne Dönmek İçin 1'i , Ana Menü'ye dönmek için 2'yi Tuşlayınız : " << endl;
		cin >> yonSecim;
		if (yonSecim == 1) {
			system("cls");
			return true;
		}
		else {
			return false;
		}
		break;
	case 2:
		cout << "Silinecek Hastanın ID'sini Giriniz : "; cin >> id;
		hastaKayitlari.hastaSil(id);
		cout << "Hasta Silindi..." << endl;
		cout << "Doktor Menüsüne Dönmek İçin 1'i , Ana Menü'ye dönmek için 2'yi Tuşlayınız : " << endl;
		cin >> yonSecim;
		if (yonSecim == 1) {
			system("cls");
			return true;
		}
		else {
			return false;
		}
		break;

	case 3:
		system("cls");
		cout << "Hasta Detayları:" << endl;
		hastaKayitlari.yazdir();
		cout << endl;
		cout << endl;
		cout << "Doktor Menüsüne Dönmek İçin 1'i , Ana Menü'ye dönmek için 2'yi Tuşlayınız : " << endl;
		cin >> yonSecim;
		if (yonSecim == 1) {
			system("cls");
			return true;
		}
		else {
			return false;
		}
		break;

	case 4:
		cout << "Ameliyat Edilecek Hastanın ID'sini Giriniz : "; cin >> id;
		cout << "Ameliyat Edilecek Hastanın Ameliyat Başlangıç Tarihini Giriniz : "; cin >> ameliyatBaslangic;
		cout << "Ameliyat Edilecek Hastanın Ameliyat Bitiş Tarihini Giriniz : "; cin >> ameliyatBitis;
		hastaKayitlari.ameliyatEkle(id, ameliyatBaslangic, ameliyatBitis);
		break;
	case 5:
		cout << "Ameliyatı Silinecek Hastanın ID'sini Giriniz : "; cin >> id;
		hastaKayitlari.ameliyatSil(id);
		cout << id << " Numaralı ID'ye Sahip Olan Hastanın Ameliyat Bilgileri Silindi" << endl;
		cout << "Doktor Menüsüne Dönmek İçin 1'i , Ana Menü'ye dönmek için 2'yi Tuşlayınız : " << endl;
		cin >> yonSecim;
		if (yonSecim == 1) {
			system("cls");
			return true;
		}
		else {
			return false;
		}
		break;
	case 6:
		system("cls");
		cout << "Hasta Detayları:" << endl;
		hastaKayitlari.yazdir();
		cout << endl;
		cout << endl;
		cout << "Doktor Menüsüne Dönmek İçin 1'i , Ana Menü'ye dönmek için 2'yi Tuşlayınız : " << endl;
		cin >> yonSecim;
		if (yonSecim == 1) {
			return true;
		}
		else {
			return false;
		}
		break;
	case 7:
		system("cls");
		cout << "Ameliyat Ücretini Hesaplamak İstediğiniz Hastanın ID'sini Giriniz : "; cin >> id;
		ucret = hastaKayitlari.ameliyatUcretiHesapla(id);
		cout << "\033[1;33m" << "                          *****************Kıran Hastanesi Ameliyat Ücretlendirme Detayları**********" << endl;
		cout << "\033[1;32m" << "        Hastanemizin Sabit Ameliyat Ücreti 62 000 TL'dir . 0-18 Yaş Arası Hastalarımız İçin %70 İndirim " << endl;
		cout << "\033[1;32m" << "        65 Yaş ve Üstü Hastalarımız İçin %20 İndirim Uygulamaktayız. 18-65 Yaş Arası Hastalarımız İçin Sabit Ücret Geçerlidir . " << "\033[0m" << endl;
		cout << "Ameliyat Ücreti: " << ucret << endl;
		cout << "Doktor Menüsüne Dönmek İçin 1'i , Ana Menü'ye dönmek için 2'yi Tuşlayınız : " << endl;
		cin >> yonSecim;
		if (yonSecim == 1) {
			system("cls");
			return true;
		}
		else {
			return false;
		}
		break;
	case 8:
		return false;
		break;
	case 9:
		exit(0);
		break;
	default:
		cout << "Geçersiz bir seçim yaptınız!" << endl;
		break;
	}
}
//**********************************************************************
// Bool fonksiyonunu doktor giriş yaparken çağırıp LogIn işlemlerini gerçekleştirdim
bool doktorGiris() {
	string dogruKullaniciAdi = "admin";
	string dogruSifre = "225";
	int girisHakki = 3;

	while (girisHakki > 0) {
		string girilenKullaniciAdi, girilenSifre;
		cout << setw(30) << "Kullanıcı Adı Giriniz : ";
		cin >> girilenKullaniciAdi;
		cout << setw(30) << "Şifre Giriniz : ";
		cin >> girilenSifre;

		if (girilenKullaniciAdi == dogruKullaniciAdi && girilenSifre == dogruSifre) {
			return true;
		}
		else {
			girisHakki--;
			if (girisHakki > 0) {
				system("cls");
				cout << "Kullanıcı Adı veya Şifre Hatalı . Tekrar Deneyiniz . Kalan Deneme Hakkınız :" << girisHakki << endl;
				cout << "Kullanıcı Adı : admin , Şifre İçin İpucu : 75'in 5'e Bölümünün Karesi..." << endl;
			}
			else {
				cout << "Giriş Hakkınız Tükendi. Program Sonlandırılıyor." << endl;
				return false;
			}
		}
	}
	return false; 
}

int main() {
	setlocale(LC_ALL, "Turkish");

	// Hasta işlemleri listesi
	ciftYonluDaireselBagliListe* hastaIslemListesi = new ciftYonluDaireselBagliListe();
	//Hasta işlem ekleme
	elemanEklemeHasta elemanEklemeHasta(hastaIslemListesi);
	elemanEklemeHasta.elemanlariEkle();
	// Doktor işlemleri listesi
	ciftYonluBagliListe* doktorIslemListesi = new ciftYonluBagliListe();
	elemanEkleme elemanEklemeDoktor(doktorIslemListesi);
	elemanEklemeDoktor.elemanlariEkle();
	int secim;
	bool donus = false;
	do {
		cout << setw(20) << "**************Kıran Hastanesi'ne Hoşgeldiniz**************" << endl;
		cout << setw(10) << "Doktor Girişi için 1'i , Hasta Girişi İçin 2'yi Tuşlayınız" << endl;
		cin >> secim;

		if (secim == 1) {
			if (doktorGiris()) {
				system("cls");
				doktorIslemListesi->yazdir();

				while (true) {
					int secimDoktor;
					cout << "Yapmak istediğiniz işlemi seçiniz : ";
					cin >> secimDoktor;

					if (doktorIslem(secimDoktor)) {
						doktorIslemListesi->yazdir();
					}
					else {
						system("cls");
						break; // Ana menüye dön
					}
				}
			}
			else {
				exit(0);
			}
		}
		else if (secim == 2) {
			system("cls");
			hastaIslemListesi->yazdir();
			while (true) {
				int secimHasta;
				cout << "Yapmak istediğiniz işlemi seçiniz : ";
				cin >> secimHasta;
				if (hastaIslem(secimHasta)) {
					hastaIslemListesi->yazdir();
				}
				else{
					system("cls");
					break;
				}
			}

		}
		else {
			cout << "Hatalı İşlem Yapıldı...";
		}
	} while (true);


	// Bellekten temizleme işlemi
	delete doktorIslemListesi;
	delete hastaIslemListesi;

	return 0;
}
