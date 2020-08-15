#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

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
private:
    friend class Jugador;

public:
    static void Jugar(int numjugadores)
    {
        vector<string> cartas;

        vector<Jugador *> jugadores;
        string nombreJugador;
        vector<string> cartasjug;
        cartas = {"A | DM", "2 | DM", "3 | DM", "4 | DM", "5 | DM", "6 | DM", "7 | DM", "8 | DM", "9 | DM", "10 | DM", "J | DM", "Q | DM", "K | DM",
                  "A | CP", "2 | CP", "3 | CP", "4 | CP", "5 | CP", "6 | CP", "7 | CP", "8 | CP", "9 | CP", "10 | CP", "J | CP", "Q | CP", "K | CP",
                  "A | CR", "2 | CR", "3 | CR", "4 | CR", "5 | CR", "6 | CR", "7 | CR", "8 | CR", "9 | CR", "10 | CR", "J | CR", "Q | CR", "K | CR",
                  "A | TR", "2 | TR", "3 | TR", "4 | TR", "5 | TR", "6 | TR", "7 | TR", "8 | TR", "9 | TR", "10 | TR", "J | TR", "Q | TR", "K | TR"};
        cout << "Ingrese el nombre del jugador: ";
        cin >> nombreJugador;
        for (int i = 0; i < 3; i++)
        {
            cartasjug.push_back(TomarCarta(cartas));
        }
        int temPuntuacion = Sumarpuntuacion(cartasjug, 0, 0, cartas);
        jugadores.push_back(new Jugador(nombreJugador, cartasjug, temPuntuacion));
        temPuntuacion = 0;
        cout << nombreJugador << ": ";
        Imprimirbaraja(cartasjug);

        //Creacion de bots
        for (int i = 0; i < numjugadores; i++)
        {
            //cout<< "Bot "<<endl;
            nombreJugador = "bot-";
            nombreJugador += i;

            cartasjug.clear();
            for (int i = 0; i < 3; i++)
            {
                cartasjug.push_back(TomarCarta(cartas));
            }
            temPuntuacion = Sumarpuntuacion(cartasjug, 0, 0, cartas);
            
            //cout << "TEmPuntua : " << jugadores.at(0)->puntuacion <<endl;
            jugadores.push_back(new Jugador(nombreJugador, cartasjug, temPuntuacion));
            temPuntuacion= 0;
        }

        int tomarcar = 1;
        while (tomarcar == 1)
        {
            temPuntuacion = 0; 
            cout << "Tomar otra carta? [1 -si | 2 -no]: ";
            cin >> tomarcar;
            Imprimirbaraja(jugadores.at(0)->baraja);
            if (tomarcar == 1)
            {
                jugadores.at(0)->baraja.push_back(TomarCarta(cartas));
                temPuntuacion = Sumarpuntuacion(jugadores.at(0)->baraja, 0, 0, cartas);
                jugadores.at(0)->puntuacion = temPuntuacion;
                cout << "Puntua : " << jugadores.at(0)->puntuacion;
                Imprimirbaraja(jugadores.at(0)->baraja);
            }
            
        }
    cout << "Puntua : " << jugadores.at(0)->puntuacion;
        for (int i = 1; i < numjugadores; i++)
        {
            temPuntuacion = 0;

            while (DecisionBot(jugadores.at(i)->puntuacion) == 1)
            {
                
                jugadores.at(i)->baraja.push_back(TomarCarta(cartas));
                temPuntuacion = Sumarpuntuacion(jugadores.at(i)->baraja, 0, 0, cartas);
                jugadores.at(i)->puntuacion = temPuntuacion;
            }
            cout << "Baraja Bot: " << i;
            Imprimirbaraja(jugadores.at(i)->baraja);
            cout << endl;
        }

        for (size_t i = 0; i < jugadores.size(); i++)
        {
            for (int j = 0; j < 31; j++)
            {
                if (j == jugadores.at(i)->puntuacion)
                {
                    cout << jugadores.at(i)->nombre << ": puntos: " << jugadores.at(i)->puntuacion << endl;
                    break;
                }
            }
            if (jugadores.at(i)->puntuacion > 31)
            {
                cout << jugadores.at(i)->nombre << i <<  ": puntos: " << jugadores.at(i)->puntuacion << endl;
            }
        }
    }

    static int DecisionBot(int points)
    {
        int numeroRand = rand() % 31, probabilidad = 31 - points;
        if (numeroRand <= probabilidad && numeroRand > 0)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }

    static string TomarCarta(vector<string> crts)
    {
        int num = rand() % 52;
        //cout << "Ran: " << num <<endl;
        string carta = crts[num];
        crts.erase(crts.begin() + num);
        return carta;
    }

    static int Sumarpuntuacion(vector<string> cartasP, int flag, int puntua, vector<string> cartasT)
    {
        //cout << "\n &Punt" << puntua<<endl;
        if (flag < cartasP.size())
        {
            //cout << "entra";
            string flag2 = cartasP.at(flag);
            //cout << "\n  %Flag2: " << flag2<< endl;
            if (flag2[0] == 'A')
            {
                puntua += 1;
                //cout << "A" <<endl;
            }
            else if (flag2[0] == 'J')
            {
                puntua += 11;
                //cout << "j" <<endl;
            }
            else if (flag2[0] == 'Q')
            {
                puntua += 12;
                //cout << "q" <<endl;
            }
            else if (flag2[0] == 'K')
            {
                puntua += 13;
                //cout << "k" <<endl;
            }
            else
            {
                puntua += (int)flag2[0] - 48;
                //cout << "num" <<endl;
            }
            //cout << " \nPunta" << puntua<< endl;
            Sumarpuntuacion(cartasP, flag + 1, puntua, cartasT);
            //cout << "Punt" << puntua;
        }
        else
        {
            //cout << "Punt" << puntua;
            return puntua;
        }
    }

    static void Imprimirbaraja(vector<string> baraja)
    {
        cout << "Baraja: [ ";
        for (int i = 0; i < baraja.size(); i++)
        {
            cout << baraja[i] << ", ";
        }
        cout << "] \n";
    }
};

int main()
{
    srand(time(NULL));
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