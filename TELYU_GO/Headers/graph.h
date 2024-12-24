//
//  graph.h
//  TELYU_GO
//
//  Created by Fa Ainama Caldera S  on 19/12/24.
//

#ifndef graph_h
#define graph_h

#define null nullptr

using namespace std;

typedef struct VertexElmt Element_Building;
typedef struct EdgeElmt Element_Road;

typedef Element_Building* Addr_Building;
typedef Element_Road* Addr_Road;

typedef struct tempListElmt Elmt_TempList;
typedef Elmt_TempList* Addr_TempList;

typedef string Infotype_TempList;

typedef string Infotype_Building;

typedef struct
{
    Addr_TempList First;
} TempList;

struct tempListElmt
{
    Infotype_TempList Info;
    Addr_TempList nextTempList;
};

struct Graph {
    Addr_Building Start;
};

struct Infotype_Road{
    string buildingName;
    string roadName;
    int distance; // weight atau bobot
};

struct VertexElmt {
    Infotype_Building Info;
    Addr_Building NextNode;
    Addr_Road FirstEdge;
};

struct EdgeElmt {
    Infotype_Road Info;
    Addr_Road NextEdge;
};

void CreateGraph(Graph &G);

Addr_Building AllocateBuilding(Infotype_Building infotype_building);

Addr_Road AllocateRoad(string buildingName, string roadName, int distance);

void AddNewBuilding(Graph &G, Addr_Building PBuilding);

// void AddNewRoad(Graph &G, Addr_Road PRoad); [OPTIONAL]

void Delete_Building(Graph &G, Addr_Building &PBuilding);

void InsertLast_Road(Graph &G, Addr_Building PBuilding, Addr_Road PRoad);

void DeleteFirst_Road(Graph &G, Addr_Building PBuilding, Addr_Road &PRoad);

void DeleteLast_Road(Graph &G, Addr_Building PBuilding, Addr_Road &PRoad);

void DeleteAfter_Road(Graph &G, Addr_Building PBuilding, Addr_Road prec, Addr_Road &PRoad);

void Delete_Road(Graph &G, Addr_Building PBuilding, Addr_Road PRoad);

Addr_Building FindBuilding(Graph G, Infotype_Building data);

Addr_Road FindRoad(Graph &G,Addr_Building PBuilding, string roadName);

void ConnectingRoad(Graph &G, Infotype_Building building1, Infotype_Building building2, string roadName, int distance);

void DisconnectingRoad(Graph &G, Infotype_Building building1, Infotype_Building building2);

Addr_TempList AllocateTempList(Infotype_TempList X);

void InsertLast_TempList(TempList &L, Addr_TempList P);

Addr_Road FindShortestRoute(Graph G, Addr_Building PBuilding, TempList tempRouteList);

bool IsBuildingVisited(TempList tempRouteList, string buildingName);

void Djikstra(Graph G, Infotype_Building from, Infotype_Building to, TempList tempRouteList);

void ShowAllGraph(Graph G);


#endif /* graph_h */
