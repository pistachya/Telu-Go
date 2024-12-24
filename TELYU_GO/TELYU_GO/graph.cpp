//
//  graph.cpp
//  TELYU_GO
//
//  Created by Fa Ainama Caldera S  on 19/12/24.
//

#include <iostream>
#include "graph.h"

using namespace std;

void CreateGraph(Graph &G) {
    G.Start = null;
}

Addr_Building AllocateBuilding(Infotype_Building infotype_building) {
    Addr_Building PBuilding;

    PBuilding = new Element_Building;
    PBuilding->Info = infotype_building;
    PBuilding->NextNode = null;
    PBuilding->FirstEdge = null;

    return PBuilding;
}

Addr_Road AllocateRoad(string buildingName, string roadName, int distance) {
    Addr_Road PRoad;

    PRoad = new Element_Road;
    PRoad->Info.buildingName = buildingName;
    PRoad->Info.roadName = roadName;
    PRoad->Info.distance = distance;
    PRoad->NextEdge = null;

    return PRoad;
}

void AddNewBuilding(Graph &G, Addr_Building PBuilding) {
    Addr_Building QBuilding;

    if (G.Start == null) {
        G.Start = PBuilding;
        return;
    }

    QBuilding = G.Start;
    while (QBuilding->NextNode != null) {
        QBuilding = QBuilding->NextNode;
    }

    QBuilding->NextNode = PBuilding;
    cout << "[INFO] - Berhasil Menambahkan Gedung Baru!" << endl;
}

void Delete_Building(Graph &G, Addr_Building &PBuilding) {
    if (G.Start == null) {
        cout << "[ERROR] - Graph kosong, tidak ada gedung yang dapat dihapus!" << endl;
        return;
    }

    if (PBuilding == null) {
        cout << "[ERROR] - Gedung yang dimaksud tidak ditemukan dalam graph!" << endl;
        return;
    }

    if (G.Start == PBuilding) {
        G.Start = PBuilding->NextNode;
        PBuilding->NextNode = null;
    } else {
        Addr_Building prev = G.Start;
        while (prev != null && prev->NextNode != PBuilding) {
            prev = prev->NextNode;
        }

        if (prev == null || prev->NextNode != PBuilding) {
            cout << "[ERROR] - Gedung yang akan dihapus tidak ditemukan dalam graph!" << endl;
            return;
        }

        prev->NextNode = PBuilding->NextNode;
        PBuilding->NextNode = null;
    }

    cout << "[INFO] - Gedung '" << PBuilding->Info << "' berhasil dihapus!" << endl;
}

void InsertLast_Road(Graph &G, Addr_Building PBuilding, Addr_Road PRoad) {
    Addr_Road P;

    if (PBuilding == null) {
        cout << "Node tidak ditemukan\n";
    }else if (PBuilding->FirstEdge == null) {
        PBuilding->FirstEdge = PRoad;
    }else {
        P = PBuilding->FirstEdge;
        while (P->NextEdge != null) {
            P = P->NextEdge;
        }

        P->NextEdge = PRoad;
    }
}

void DeleteFirst_Road(Graph &G, Addr_Building PBuilding, Addr_Road &PRoad) {
    if (G.Start == null) {
        cout << "Empty\n";
    }

    PRoad = PBuilding->FirstEdge;
    PBuilding->FirstEdge = PRoad->NextEdge;
    PRoad->NextEdge = null;
}

void DeleteLast_Road(Graph &G, Addr_Building PBuilding, Addr_Road &PRoad) {
    Addr_Road QRoad;

    if (G.Start == null) {
        cout << "Empty\n";
    }

    QRoad = null;
    PRoad = PBuilding->FirstEdge;
    while (PRoad->NextEdge != null) {
        QRoad = PRoad;
        PRoad = PRoad->NextEdge;
    }

    QRoad->NextEdge = null;
}

void DeleteAfter_Road(Graph &G, Addr_Building PBuilding, Addr_Road prec, Addr_Road &PRoad) {
    PRoad = prec->NextEdge;
    prec->NextEdge = PRoad->NextEdge;
    PRoad->NextEdge = null;
}

void Delete_Road(Graph &G, Addr_Building PBuilding, Addr_Road PRoad) {
    Addr_Road Rout;
    Addr_Road prec;

    if (PRoad == PBuilding->FirstEdge) {
        DeleteFirst_Road(G, PBuilding, Rout);
    }else if (PRoad->NextEdge == null) {
        DeleteLast_Road(G, PBuilding, Rout);
    }else {
        prec = PBuilding->FirstEdge;
        while (prec->NextEdge != PRoad) {
            prec = prec->NextEdge;
        }

        DeleteAfter_Road(G, PBuilding, prec, Rout);
    }
}

Addr_Building FindBuilding(Graph G, Infotype_Building data) {
    Addr_Building PBuilding;

    if (G.Start == null) {
        return null;
    }else {
        PBuilding = G.Start;
        while (PBuilding->Info != data && PBuilding->NextNode != null) {
            PBuilding = PBuilding->NextNode;
        }

        if (PBuilding->Info == data) {
            return PBuilding;
        }else {
            return null;
        }
    }
}

Addr_Road FindRoad(Graph &G,Addr_Building PBuilding, string roadName) {
    Addr_Road PRoad = null;

    if (G.Start == null || PRoad == null) {
        return null;
    }else {
        PRoad = PBuilding->FirstEdge;
        while (PRoad->Info.roadName != roadName && PRoad->NextEdge != null) {
            PRoad = PRoad->NextEdge;
        }

        if (PRoad->Info.roadName == roadName) {
            return PRoad;
        }else {
            return null;
        }
    }
}

void ConnectingRoad(Graph &G, Infotype_Building building1, Infotype_Building building2, string roadName, int distance) {
    Addr_Building B1;
    Addr_Building B2;

    Addr_Road R1;
    Addr_Road R2;

    B1 = FindBuilding(G, building1);
    B2 = FindBuilding(G, building2);

    if (B1 != null && B2 != null) {
        R1 = AllocateRoad(B2->Info, roadName, distance);
        InsertLast_Road(G, B1, R1);

        R2 = AllocateRoad(B1->Info, roadName, distance);
        InsertLast_Road(G, B2, R2);
    }else {
        cout << "Edge tidak ditemukan!\n";
    }

}

void DisconnectingRoad(Graph &G, Infotype_Building building1, Infotype_Building building2) {
    Addr_Building B1;
    Addr_Building B2;

    Addr_Road R1;
    Addr_Road R2;

    B1 = FindBuilding(G, building1);
    B2 = FindBuilding(G, building2);

    if (B1 != null & B2 != null) {
        R1 = FindRoad(G, B1, building1);
        R2 = FindRoad(G, B2, building2);

        if (R1 != null && R2 != null) {

        }else {
            cout << "Edge tidak ditemukan!\n";
        }
    }else {
        cout << "Node tidak ditemukan!\n";
    }
}

Addr_TempList AllocateTempList(Infotype_TempList X) {
    Addr_TempList temp = new tempListElmt;

    temp->Info = X;
    temp->nextTempList = null;

    return temp;
}

void InsertLast_TempList(TempList &L, Addr_TempList P) {
    if (L.First == null) {
        L.First = P;
    }else {
        Addr_TempList last = L.First;
        while (last->nextTempList != null) {
            last = last->nextTempList;
        }

        last->nextTempList = P;
    }
}

bool IsBuildingVisited(TempList tempRouteList, string buildingName) {
    Addr_TempList temp = tempRouteList.First;

    while(temp->nextTempList) {
        if (temp->Info == buildingName) {
            return true;
        }

        temp = temp->nextTempList;
    }

    return false;
}

Addr_Road FindShortestRoute(Graph G, Addr_Building PBuilding, TempList tempRouteList) {
    Addr_Road PRoad = PBuilding->FirstEdge;
    Addr_Road shortest = PRoad;

    while (PRoad != null) {
        if (PRoad->Info.distance < shortest->Info.distance && !IsBuildingVisited(tempRouteList, PBuilding->Info)) {
            shortest = PRoad;
        }

        PRoad = PRoad->NextEdge;
    }

    return shortest;
}

void Djikstra(Graph G, Infotype_Building currentBuilding, Infotype_Building destinationBuilding, TempList tempRouteList) {
    if (currentBuilding == destinationBuilding) {
        cout << "Gedung" << currentBuilding << " adalah gedung terakhir\n";
        return;
    }

    Addr_Building current = FindBuilding(G, currentBuilding);
    Addr_Road shortest = FindShortestRoute(G, current, tempRouteList);

    if (shortest != null) {
        InsertLast_TempList(tempRouteList, AllocateTempList(shortest->Info.buildingName));
        cout << "Info gedung: " << shortest->Info.buildingName << endl;
        Djikstra(G, shortest->Info.buildingName, destinationBuilding, tempRouteList);
    }
}

void ShowAllGraph(Graph G) {
    Addr_Building B;
    Addr_Road R;

    if (G.Start != null) {
        B = G.Start;
        
        cout << "===================================" << endl;
        cout << "           PETA GRAF GEDUNG        " << endl;
        cout << "===================================" << endl;

        while (B != null) {
            cout << "Gedung: "<< B->Info << endl;

            if (B->FirstEdge != null) {
                cout << "  Koneksi:" << endl;
                
                R = B->FirstEdge;
                while (R != null) {
                    cout << "    -> Ke Gedung: " << R->Info.buildingName << endl;
                    cout << "       Jalan: " << R->Info.roadName << endl;
                    cout << "       Jarak: " << R->Info.distance << " m" << endl;
                    R = R->NextEdge;
                }
            }else {
                cout << " Tidak Ada Koneksi!" << endl;
            }

            cout << "-----------------------------------" << endl;
            B = B->NextNode;
        }
    }
}



