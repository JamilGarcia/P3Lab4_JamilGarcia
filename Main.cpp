#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;
class Jugador
{
    friend class Jugar;
    friend class Juego;
    string nombre;
    vector<string> baraja;
    int puntuacion;

public:
    Jugador(string nombre, vector<string> baraja, int puntuacion)
    {
        this->nombre = nombre;
        this->baraja = baraja;
        this->puntuacion = puntuacion;
    }
};

class Juego
{
    friend class Jugador;

public:
    static void Jugar(int numjugadores)
    {
        string nombreJugador;
        vector<string> cartasjug;

        cout << "Ingrese el nombre del jugador: ";
        cin >> nombreJugador;
        for (int i = 0; i < 3; i++)
        {
            cartasjug.push_back(TomarCarta());
        }
        int temPuntuacion = Sumarpuntuacion(cartasjug, 0, 0);
        jugadores.push_back(new Jugador(nombreJugador, cartasjug, temPuntuacion));
        cout << nombreJugador << ": ";
        Imprimirbaraja(cartasjug);

        //Creacion de bots
        for (int i = 0; i < numjugadores; i++)
        {
            nombreJugador = "bot-" + i;
            cartasjug.clear();
            for (int i = 0; i < 3; i++)
            {
                cartasjug.push_back(TomarCarta());
            }
            temPuntuacion = Sumarpuntuacion(cartasjug, 0, 0);
            jugadores.push_back(new Jugador(nombreJugador, cartasjug, temPuntuacion));
        }

        cout << "Tomar otra carta? [1 -si | 2 -no]: ";
        int tomarcar, tomarbot;
        cin >> tomarcar;
        while (tomarcar == 1)
        {
            cout << "Tomar otra carta? [1 -si | 2 -no]: ";
            cin >> tomarcar;
            if (tomarcar == 1)
            {
                jugadores.at(0)->baraja.push_back(TomarCarta());
                temPuntuacion = Sumarpuntuacion(cartasjug, 0, 0);
                jugadores.at(0)->puntuacion = temPuntuacion;
            }
        }

        for (int i = 1; i < numjugadores; i++)
        {

            while (DecisionBot(jugadores.at(i)->puntuacion) == 1)
            {
                jugadores.at(i)->baraja.push_back(TomarCarta());
                temPuntuacion = Sumarpuntuacion(cartasjug, 0, 0);
                jugadores.at(i)->puntuacion = temPuntuacion;
            }
        }

        for (int i = 0; i < jugadores.size(); i++)
        {
            for (int j = 0; j < 31; j++)
            {
                if (j == jugadores.at(i)->puntuacion){
                    cout << jugadores.at(i)->nombre << ": puntos: " << jugadores.at(i)->puntuacion <<endl;
                    break;
                }
            }

            
        }
        
    }
};

vector<string> cartas = {"A | DM", "2 | DM", "3 | DM", "4 | DM", "5 | DM", "6 | DM", "7 | DM", "8 | DM", "9 | DM", "10 | DM", "J | DM", "Q | DM", "K | DM",
                         "A | CP", "2 | CP", "3 | CP", "4 | CP", "5 | CP", "6 | CP", "7 | CP", "8 | CP", "9 | CP", "10 | CP", "J | CP", "Q | CP", "K | CP",
                         "A | CR", "2 | CR", "3 | CR", "4 | CR", "5 | CR", "6 | CR", "7 | CR", "8 | CR", "9 | CR", "10 | CR", "J | CR", "Q | CR", "K | CR",
                         "A | TR", "2 | TR", "3 | TR", "4 | TR", "5 | TR", "6 | TR", "7 | TR", "8 | TR", "9 | TR", "10 | TR", "J | TR", "Q | TR", "K | TR"};

vector<Jugador *> jugadores;

int DecisionBot(int points)
{
    int numeroRand = rand() % 31, probabilidad = 31 - points;
    if (numeroRand <= probabilidad)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

string TomarCarta()
{
    int num = rand() % cartas.size();
    string carta = cartas[num];
    cartas.erase(remove(cartas.begin(), cartas.end(), carta));
    return carta;
}

int Sumarpuntuacion(vector<string> cartasP, int flag, int puntua)
{
    if (flag < cartasP.size())
    {
        string flag2 = cartas.at(flag);
        if (flag2[0] == 'A')
        {
            puntua += 1;
        }
        else if (flag2[0] == 'J')
        {
            puntua += 11;
        }
        else if (flag2[0] == 'Q')
        {
            puntua += 12;
        }
        else if (flag2[0] == 'K')
        {
            puntua += 13;
        }
        else
        {
            puntua += (int)flag2[0];
        }
        Sumarpuntuacion(cartasP, flag + 1, puntua);
    }
    else
    {
        return puntua;
    }
}

void Imprimirbaraja(vector<string> baraja)
{
    cout << "Baraja: [ ";
    for (int i = 0; i < baraja.size(); i++)
    {
        cout << baraja[i] << ", ";
    }
    cout << "] \n";
}

int main()
{
    char salir = 'n';
    while (salir == 'n')
    {
        int opcion;
        cout << "CALIBRE'S CASINO \n"
             << "1) Jugar 31 \n"
             << "0) Salir \n"
             << "Opcion: ";
        cin >> opcion;
        if (opcion == 1)
        {
            int numbots;

            cout << "Ingrese la cantidad de bots [1-9]";
            cin >> numbots;
            while (numbots > 9 && numbots < 0)
            {
                cout << "Ingrese la cantidad de bots [1-9]";
                cin >> numbots;
            }
            Juego::Jugar(numbots);
        }
    }
    return 0;
}