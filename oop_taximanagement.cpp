#include <iostream>
#include <string>
#include <queue>
using namespace std;

class Driver{
private:
    string name;
    string car_brand;
    string car_type;
    string plate;
    string driver_id;
public:
    //constructor 
    Driver(string n, string car, string type, string plt, string id){
        name = n;
        car_brand = car;
        car_type = type;
        plate = plt;
        driver_id = id;
    }
    //setter
    void setname(string new_name){
        name = new_name;
    }
    void setbrand(string new_brand){
        car_brand = new_brand;
    }
    void settype(string new_type){
        car_type = new_type;
    }
    void setplate(string new_plate){
        plate = new_plate;
    }


    //getter
    string getName() const {
        return name; }
    string getCarBrand() const {
        return car_brand; }
    string getCarType() const { 
        return car_type; }
    string getPlate() const { 
        return plate; }
    string getDriverID() const { 
        return driver_id; }
};



//use circular linked list to search between drivers
class Node{
    public:
    Driver driver;
    Node* next;
    Node* prev;
   
    Node(Driver d) : driver(d), next(nullptr), prev(nullptr) {}
};

class circularLinkList{
    public:
    Node *head;
    Node* current;
    queue<Driver> order;
    circularLinkList() : head(nullptr), current(nullptr) {}

    void insert(Driver d) {
        Node* new_node = new Node(d);
        if (head == nullptr) {
            head = new_node;
            head->next = head;
            head->prev = head;
            current = head;
        } else {
            Node* last = head->prev;
            last->next = new_node;
            new_node->prev = last;
            new_node->next = head;
            head->prev = new_node;
        }

    }

    
    int displaynode() {
        char nav;
        if(head == nullptr){
            cout << "tidak ada data driver tersedia" << endl;
            cin.get();
            system("cls");
            return 0;
        }
        do{
        if(nav!='b'){
        cout << "ID Driver: " << current->driver.getDriverID() << endl;
        cout << "Nama: " << current->driver.getName() << endl;
        cout << "Mobil: " << current->driver.getCarBrand() << " " << current->driver.getCarType() << endl;
        cout << "Plat: " << current->driver.getPlate() << endl;
        cout << "Tekan x untuk next, z untuk back, tekan e untuk kembali ke menu" << endl;
        cout << "tekan b untuk edit, tekan c untuk hapus driver" << endl;
        }

        cin >> nav;
        cin.ignore();

        if(nav == 'x'){
            current = current->next;
        }
        else if(nav == 'z'){
            current = current->prev;
        }
        else if(nav == 'b'){
            string edited_value;
            char choice;

            cout << "Pilih data yang ingin diedit:" << endl;
            cout << "Nama(a)\nMerek Mobil(b)\nTipe Mobil(c)\nPlat (d)"<< endl;

            cin >> choice;
            cin.ignore();
            if (choice == 'a' || choice == 'A') {
                cout << "Masukkan nama baru: " << endl;
                getline(cin, edited_value);
                current->driver.setname(edited_value);
            } else if (choice == 'b' || choice == 'B') {
                cout << "Masukkan merk mobil baru: " << endl;
                getline(cin, edited_value);
                current->driver.setbrand(edited_value);
            } else if (choice == 'c' || choice == 'C') {
                cout << "Masukkan tipe mobil baru: " << endl;
                getline(cin, edited_value);
                current->driver.settype(edited_value);
            } else if (choice == 'd' || choice == 'D') {
                cout << "Masukkan plat nomor baru: " << endl;
                getline(cin, edited_value);
                current->driver.setplate(edited_value);
            } else {
                cout << "Pilihan tidak valid." << endl;
            }
            system("cls");
            return 0;
        }
        else if(nav == 'c'){
            Node* temp = current;
            if(temp == head){
                if(head->next == head){
                    head = nullptr;
                } else{
                    head = head->next;
                    head->prev = temp->prev;
                    temp->prev->next = head;
                }
            } else{
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }

            delete temp;
            cout << "Node berhasil dihapus." << endl;

            if (head != nullptr) {
                current = head;
            } else {
                current = nullptr;
            }
            return 0;
        }
    }while(nav != 'e');
}


    string id_maker(string nama, string brand, string plat){
        int digit1 = (int)(tolower(nama[0])) % 10; //cuma ambil digit pertama aja
        int digit2 = (int)(tolower(nama[1])) % 10;
        int digit3 = (int)(tolower(brand[0])) % 10;
        int digit4 = (int)(tolower(plat[0])) %10;

        string id = to_string(digit1) + to_string(digit2) + to_string(digit3) + to_string(digit4);

        return id;
    }



    void daftarkanSopir(){
        string nama, brand, type, plat, id;
        cout << "Masukkan Nama Driver: ";
        getline(cin, nama);
        cout << "Masukkan Merek Mobil: ";
        getline(cin, brand);
        cout << "Masukkan Tipe Mobil: ";
        getline(cin, type);
        cout << "Masukkan Plat Mobil: ";
        getline(cin, plat);
        id = id_maker(nama, brand, plat);

        Driver new_driver(nama, brand, type, plat, id);
        insert(new_driver);
        cout << "Driver baru dengan ID: " << id <<  " berhasil terdaftar!" << endl;
        cout << "Kembali ke menu admin..." << endl;
    }


    int lihatOrder(){
        char nav;
        if (order.empty()) {
        cout << "Tidak ada antrean order." << endl;
        } 
        else {
            cout << "Order yang sudah masuk: " << endl;
            while (!order.empty()){
                Driver d = order.front();

                cout << "Nama driver: " << d.getName() << endl;
                cout << "ID: "  << d.getDriverID() << endl;
                cout << "Mobil: " << d.getCarBrand() << d.getCarType() << endl;
                cout << "Plat nomor: " << d.getPlate() << endl;
                cout << "Accept (Y), Reject (N)" << endl;
                cin >> nav;
                if(nav == 'y' || nav == 'Y'){
                    order.pop();
                }
                else{
                    cout << "order ditolak" << endl;
                    order.pop();
                }
            }
        }
      }

      int countDrivers() {
        if (head == nullptr) {
            return 0; 
        } 

        int count = 0;
        Node* current = head;

        do {
            count++;
            current = current->next;
        } while (current != head);

        return count;
    }
    
};





class Administrator{
    private:
    string username_adm;
    int pin_adm;
    public:
    Administrator(){
        username_adm = "admin";
        pin_adm = 1234;
    }

    bool login(string username, int pin){
        if(username == username_adm){
            cout << "Login berhasil" << endl;
            return true;
        }
        else{
            cout <<"Password atau username anda salah" << endl;
            return false;
        }
    }


int admin_menu(circularLinkList& driverList) {
    int opsi;
    do {
        cout << "====== Selamat datang " << username_adm << " =======" << endl;
        cout << "Daftarkan driver (1)" << endl;
        cout << "Lihat orderan (2)" << endl;
        cout << "Lihat dan ubah data driver (3)" << endl;
        cout << "Kembali ke menu utama (0)" << endl;
        cout << "Pilih opsi: ";
        cin >> opsi;
        cin.ignore();

        switch (opsi) {
            case 1:
                driverList.daftarkanSopir();
                break;
            case 2:
                driverList.lihatOrder();
                break;
            case 3:
                driverList.displaynode();  
                break;
            case 0:
                cout << "Kembali ke menu utama..." << endl;

                break;
            default:
                cout << "Opsi tidak valid." << endl;
                break;
        }
    } while (opsi != 0); 
}
};

class User{
    private:
    string username;
   
    public:
    circularLinkList& driver;
    User(circularLinkList& drv) : driver(drv) {}
    //setter
    void setUsername(string uname){
        username = uname;
    }
    //getter
    string getUsername(){
        return username;
    }

    int Order(){
        char nav;
        if(driver.head == nullptr){
            cout << "tidak ada data driver tersedia" << endl;
            cin.get();
            system("cls");
            return 0;
        }

        do{
            cout << "ID Driver: " << driver.current->driver.getDriverID() << endl;
            cout << "Nama: " << driver.current->driver.getName() << endl;
            cout << "Mobil: " << driver.current->driver.getCarBrand() << " " << driver.current->driver.getCarType() << endl;
            cout << "Plat: " << driver.current->driver.getPlate() << endl;
            cout << "Tekan x untuk next, z untuk back, tekan e untuk kembali ke menu" << endl;
            cout << "tekan o untuk order" << endl;
            cin >> nav;
            cin.ignore();
            if(nav == 'x'){
                driver.current = driver.current->next;
            }
            else if(nav == 'z'){
                driver.current = driver.current->prev;
            }   
            else if(nav == 'o'){
                 char lanjut;
                 driver.order.push(driver.current->driver); 
                 cout << "Order berhasil ditambahkan ke antrian!" << endl;
                 cout << "Order lagi? (y/n)" << endl;
                 cin >> lanjut;
                 cin.ignore();
                 if(lanjut == 'n' || lanjut == 'N'){
                    cout << "Kembali ke menu utama..." << endl;
                break;
              }
            }
        }while(nav != 'e');

    }

    int userMenu(){
        circularLinkList list;
        char opsi;
        cout << "Selamat datang " << getUsername() << endl;
        cout << "Order (a)" << endl;
        cout << "Cek ketersediaan driver (b)" << endl;
        cout << "Kembali ke menu login (c)" << endl;
        cin >> opsi;
        if(opsi == 'a' || opsi =='A'){
            Order();
        }
        else if(opsi == 'b' || opsi == 'B'){
            int jumlah_driver = driver.countDrivers();
            cout << "Terdapat " << jumlah_driver << " tersedia untuk dipesan" << endl;
            cin.ignore();
            cin.get();
            system("cls");
            return userMenu();
        }else{
            return 0;
        }
        
    }
};

void welcome_menu(){
    cout << "Welcome to DriverIn" << endl;
    cout << "Login (1)" << endl;
    cout << "ADMIN (2)" << endl;
}


int main(){
    circularLinkList driverlist;
    Administrator admin;
    User user(driverlist);
    int opsi;
    string username, usr;
    int pin;
    do{
    welcome_menu();
    cin >> opsi;
    cin.ignore();
    switch(opsi){
        case 1: 
        cout << "Masukkan nama anda: " << endl;
        getline(cin, usr);
        user.setUsername(usr);
        user.userMenu();
        break;
        case 2:
        cout << "Masukkan username anda: " << endl;
        getline(cin, username);
        cout << "Masukkan pin anda: " << endl;
        cin >> pin;
        cin.ignore();
        if(admin.login(username, pin)){
            admin.admin_menu(driverlist);
        }
        break;
        case 3:

        case 4:
        //summon class administrator
        default:
        cout << " " << endl;
        }
    } while (opsi != 0);
    return 0;
}
