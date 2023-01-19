// Kapital 1
#include <iostream>

enum e_gebaeudetyp {
    Leer, Wasser, Wind, Solar
};

// Erstellung eines Arrays

e_gebaeudetyp *ErstellungDesArrays(int _laenge, int _breite) {
    e_gebaeudetyp *pBaubereich = new e_gebaeudetyp[_laenge * _breite]();

    // Initialisierung
    for (int i = 0; i < _laenge * _breite; i++) {
        pBaubereich[i] = Leer;
    }

    return pBaubereich;
}

//ausgeben des aktuellen bauplans

void DisplayField(e_gebaeudetyp *_pBaubereich, int _laenge, int _breite) {
    for (int y = 0; y < _laenge; y++) {
        for (int x = 0; x < _breite; x++) {
            std::cout << _pBaubereich[y * _breite + x];

            if (x == _breite - 1) {
                std::cout << std::endl;
            }
        }
    }
}

// Prüfung Kollision!

bool Collision(e_gebaeudetyp *_pBaubereich, int _gebaeudeLaenge, int _gebaeudeBreite, int _posX, int _posY, int _breite) {
    bool collision = false;

    for (int y = 0; y < _gebaeudeLaenge; y++) {
        for (int x = 0; x < _gebaeudeBreite; x++) {
            if (_pBaubereich[(_posY + y) * _breite + (_posX + x)] != 0) {
                std::cout << "Kollision!" << std::endl;
                return true;
            }
        }
    }
    return false;

}

//gebäude setzen

void GebaeudeSetzen(e_gebaeudetyp *_pBaubereich, int _breite) {
    int gebaeudeTyp;
    int gebaeudeLaenge;
    int gebaeudeBreite;
    int positionX;
    int positionY;

    bool emptySpace = true;


    std::cout << "Gebaeudetyp: (1) Wasser | (2) Wind | (3) Solar" << std::endl;
    std::cin >> gebaeudeTyp;

    std::cout << "Gebaeude laenge: " << std::endl;
    std::cin >> gebaeudeLaenge;

    std::cout << "Gebauede breite: " << std::endl;
    std::cin >> gebaeudeBreite;

    std::cout << "Position X: " << std::endl;
    std::cin >> positionX;

    std::cout << "Position Y: " << std::endl;
    std::cin >> positionY;

    emptySpace = Collision(_pBaubereich, gebaeudeLaenge, gebaeudeBreite, positionX, positionY, _breite);

    if (emptySpace == false) {
        for (int y = 0; y < gebaeudeLaenge; y++) {
            for (int x = 0; x < gebaeudeBreite; x++) {
                switch (gebaeudeTyp) {
                    case 1:
                        _pBaubereich[(positionY + y) * _breite + (positionX + x)] = Wasser;
                        break;

                    case 2:
                        _pBaubereich[(positionY + y) * _breite + (positionX + x)] = Wind;
                        break;
                    case 3:
                        _pBaubereich[(positionY + y) * _breite + (positionX + x)] = Solar;
                }

            }
        }
    }
}

// Bereich löschen

void GebaeudeLoeschen(e_gebaeudetyp *_pBaubereich, int _breite) {
    int loeschenLaenge;
    int loeschenBreite;
    int positionX;
    int positionY;

    std::cout << "Loeschbereich laenge: " << std::endl;
    std::cin >> loeschenLaenge;

    std::cout << "Loeschbereich breite: " << std::endl;
    std::cin >> loeschenBreite;

    std::cout << "Position X: " << std::endl;
    std::cin >> positionX;

    std::cout << "Position Y: " << std::endl;
    std::cin >> positionY;

    for (int y = 0; y < loeschenLaenge; y++) {
        for (int x = 0; x < loeschenBreite; x++) {
            _pBaubereich[(positionY + y) * _breite + (positionX + x)] = Leer;


        }
    }
}

int main() {
    bool running = true;
    int laenge, breite = 0;
    int auswahl = 0;
    e_gebaeudetyp *pBaubereich = nullptr;

    std::cout << "Laenge: " << std::endl;
    std::cin >> laenge;

    std::cout << "Breite: " << std::endl;
    std::cin >> breite;

    pBaubereich = ErstellungDesArrays(laenge, breite);

    DisplayField(pBaubereich, laenge, breite);

    while (running) {
        std::cout << "(1) Gebaeude setzen | (2) Bereich Loeschen | (3) Ausgabe des Bauplans | (4) Beenden des Programms"
                  << std::endl;
        std::cin >> auswahl;

        switch (auswahl) {
            case 1:
                GebaeudeSetzen(pBaubereich, breite);
                break;
            case 2:
                GebaeudeLoeschen(pBaubereich, breite);
                break;
            case 3:
                DisplayField(pBaubereich, laenge, breite);
                break;
            case 4:
                running = false;
                break;
        }
    }

    delete pBaubereich;
}