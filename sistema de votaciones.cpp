#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <windows.h>

using namespace std;

struct Candidate {
    string name;
    string party;
    string platform;
    int votes;

    Candidate() : votes(0) {}
};

vector<Candidate> candidates;
set<string> voters;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearScreen() {
    system("cls");
}
void addCandidate() {
    clearScreen();
    setColor(14); // Texto amarillo
    Candidate candidate;
    cout << "Ingrese el nombre del candidato: ";
    cin.ignore();
    getline(cin, candidate.name);
    cout << "Ingrese el partido politico del candidato: ";
    getline(cin, candidate.party);
    cout << "Ingrese la plataforma del candidato: ";
    getline(cin, candidate.platform);
    candidates.push_back(candidate);
    cout << "Candidato agregado exitosamente.\n";
    setColor(15); // Resetear a texto blanco
    system("pause");
}
void vote() {
    clearScreen();
    setColor(11); 
    string voterID;
    cout << "Ingrese su ID de votante: ";
    cin >> voterID;

    if (voters.find(voterID) != voters.end()) {
        cout << "Ya ha votado previamente.\n";
        setColor(15); 
        system("pause");
        return;
    }

    if (candidates.empty()) {
        cout << "No hay candidatos registrados.\n";
        setColor(15); 
        system("pause");
        return;
    }
cout << "Candidatos disponibles:\n";
    for (size_t i = 0; i < candidates.size(); ++i) {
        cout << i + 1 << ". " << candidates[i].name << " - " << candidates[i].party << " - " << candidates[i].platform << endl;
    }

    int choice;
    cout << "Ingrese el numero del candidato por el que desea votar: ";
    cin >> choice;

    if (choice < 1 || choice > candidates.size()) {
        cout << "Opcion no valida.\n";
        setColor(15); 
        system("pause");
        return;
    }

    candidates[choice - 1].votes++;
    voters.insert(voterID);
    cout << "Voto registrado exitosamente.\n";
    setColor(15);
    system("pause");
}
void showResults() {
    clearScreen();
    setColor(10);
    if (candidates.empty()) {
        cout << "No hay candidatos registrados.\n";
        setColor(15);
        system("pause");
        return;
    }

    int totalVotes = 0;
    for (size_t i = 0; i < candidates.size(); ++i) {
        totalVotes += candidates[i].votes;
    }

    if (totalVotes == 0) {
        cout << "No se han registrado votos.\n";
        setColor(15); 
        system("pause");
        return;
    }
  cout << "Resultados de la eleccion:\n";
    for (size_t i = 0; i < candidates.size(); ++i) {
        double percentage = (static_cast<double>(candidates[i].votes) / totalVotes) * 100;
        cout << candidates[i].name << " - " << candidates[i].party << ": " << candidates[i].votes << " votos (" << percentage << "%)\n";
    }

    
    Candidate winner;
    int maxVotes = -1;
    for (size_t i = 0; i < candidates.size(); ++i) {
        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
            winner = candidates[i];
        }
    }

    cout << "El ganador es: " << winner.name << " del partido " << winner.party << " con " << winner.votes << " votos.\n";
    setColor(15); 
    system("pause");
}
void menu() {
    int choice;
    do {
        clearScreen();
        setColor(13); // Texto magenta
        gotoxy(0, 0);
        cout << "=============================================\n";
        gotoxy(0, 1);
        cout << "       Sistema de Votacion Electronico       \n";
        gotoxy(0, 2);
        cout << "=============================================\n";
        gotoxy(0, 3);
        cout << "1. Ingresar Candidatos\n";
        gotoxy(0, 4);
        cout << "2. Votaciones\n";
        gotoxy(0, 5);
        cout << "3. Mostrar Resultados\n";
        gotoxy(0, 6);
        cout << "4. Salir\n";
        gotoxy(0, 7);
        cout << "=============================================\n";
        gotoxy(0, 8);
        cout << "Seleccione una opcion: ";
        setColor(15);
        cin >> choice;
        switch (choice) {
            case 1:
                addCandidate();
                break;
            case 2:
                vote();
                break;
            case 3:
                showResults();
                break;
            case 4:
                setColor(12);
                cout << "Saliendo del sistema...\n";
                setColor(15);
                break;
            default:
                setColor(12);
                cout << "Opcion no valida. Intente de nuevo.\n";
                setColor(15); 
                system("pause");
                break;
        }
    } while (choice != 4);
}

int main() {
    menu();
    return 0;


