#include <iostream>
#include "graph.h"

using namespace std;

void printMenu() {
    cout << "===================================" << endl;
    cout << "              MENU PILIHAN         " << endl;
    cout << "===================================" << endl;
    cout << " 1. Tambah Gedung di Telkom University" << endl;
    cout << " 2. Hapus Gedung di Telkom University" << endl;
    cout << " 3. Hubungkan Gedung ke Gedung Lainnya" << endl;
    cout << " 4. Putuskan Gedung" << endl;
    cout << " 5. Tampilkan Graph" << endl;
    cout << " 6. Tampilkan Jarak Semua Antar Gedung" << endl;
    cout << " 7. Cari Rute Tercepat" << endl;
    cout << " 0. Keluar" << endl;
    cout << "===================================" << endl;
    cout << "Pilih pilihan: ";
}

int main() {
    Graph Telkom_Map;

    string buildingName;
    string roadName;

    int distance;
    int choice;

    CreateGraph(Telkom_Map);

    try {
        do {
            printMenu();
            cin >> choice;

            switch (choice) {
                case 1: {
                    cout << "Masukan nama gedung baru: ";
                    cin >> buildingName;

                    AddNewBuilding(Telkom_Map, AllocateBuilding(buildingName));
                    break;
                }

                case 2: {
                    cout << "Masukan nama gedung yang ingin dihapus: ";
                    cin >> buildingName;

                    Addr_Building building = FindBuilding(Telkom_Map, buildingName);
                    Delete_Building(Telkom_Map, building);
                    break;
                }

                case 3: {
                    string building1;
                    string building2;

                    cout << "Masukan nama gedung pertama yang ingin dihubungi: ";
                    cin >> building1;

                    cout << "Masukan nama gedung kedua yang ingin dihubungi: ";
                    cin >> building2;

                    cout << "Masukan nama jalan antar gedung pertama dan kedua: ";
                    cin >> roadName;

                    cout << "Masukan jarak antar gedung pertama dan kedua: ";
                    cin >> distance;

                    ConnectingRoad(Telkom_Map, building1, building2, roadName, distance);
                    break;
                }

                case 4: {
                    cout << "Masukan nama gedung pertama yang ingin diputus: ";
                    string building1, building2;
                    cin >> building1;
                    
                    cout << "Masukan nama gedung kedua yang ingin diputus: ";
                    cin >> building2;
                    
                    DisconnectBuilding(Telkom_Map, building1, building2);
                    break;
                }

                case 5: {
                    ShowAllGraph(Telkom_Map);
                    break;
                }

                case 6: {
                    ShowAllDistances(Telkom_Map);
                    break;
                }

                case 7: {
                    string building1, building2;

                    cout << "Masukan nama gedung asal: ";
                    cin >> building1;

                    cout << "Masukan nama gedung tujuan: ";
                    cin >> building2;

                    TempList tempRouteList;
                    tempRouteList.First = null;

                    Djikstra(Telkom_Map, building1, building2, tempRouteList);
                    break;
                }

            }

        } while (choice != 0);
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
