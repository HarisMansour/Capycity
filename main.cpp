//Kapital 2
#include <iostream>

//erstellung einer klasse Material

class Material {
private:
    float price;
public:
    void setPrice(float _price) {
        price = _price;
    }

    float getPrice() {
        return price;
    }
};

// alle leiten sich von der basisklasse
//jedes Material eigenen Preis

class Holz : public Material {
public:
    const char *name = "Holz";
    float price = 10.00;
};

class Metall : public Material {
public:
    const char *name = "Metall";
    float price = 15.00;
};

class Kunststoff : public Material {
public:
    const char *name = "Kunststoff";
    float price = 5.00;
};

//Ersetze die Enum der Gebäude durch eigenständige Klassen
// Diese sollen sich von einer Basisklasse Building ableiten.
//Jedes Gebäude soll ein Label besitzen, welches beim Ausdrucken des Plans angezeigt wird

class Building {
public:
    float grundPreis;
    char Label;

};

// wasser 2 metall 7 holz
// Wind 12 holz 10 kunststoff 2 metall
// solar 0 holz 20 kunststoff 10 metall
class WasserB : Building {
public:
    float grundPreis = 100.00;
    char label = 'W';
    int holz = 7;
    int metall = 2;
    int kunsstoff = 0;
};

class WindB : Building {
public:
    float grundPreis = 200.00;
    char label = 'I';
    int holz = 12;
    int metall = 2;
    int kunsstoff = 10;
};

class SolarB : Building {
public:
    float grundPreis = 250.00;
    char label = 'S';
    int holz = 0;
    int metall = 10;
    int kunsstoff = 20;
};

//kapsel die verwaltung innerhalb einer klasse namens CapycitySim

class CapycitySim {

public:
    char *ErstellungDesArrays(int _laenge, int _breite) {
        char *pBaubereich = new char[_laenge * _breite]();

        // Initialisierung
        for (int i = 0; i < _laenge * _breite; i++) {
            pBaubereich[i] = '0';
        }

        return pBaubereich;
    }

//Erweitere das Ausdrucken des Plans um die Darstellung der Gebäude mit ihren Labels, einer
//Auflistung der Gebäude sowie deren benötigter Materialien, dem Einzelpreis eines Gebäudes sowie
//dem Gesamtpreis von allen Gebäuden.

    void DisplayField(char *_pBaubereich, int _laenge, int _breite) {
        WasserB wasser;
        WindB wind;
        SolarB solar;

        int wasserGebaeude = 0;
        int windGebaeude = 0;
        int solarGebaeude = 0;

        for (int y = 0; y < _laenge; y++) {
            for (int x = 0; x < _breite; x++) {
                std::cout << _pBaubereich[y * _breite + x];

                if (_pBaubereich[y * _breite + x] == wasser.label) {
                    wasserGebaeude++;
                }

                if (_pBaubereich[y * _breite + x] == wind.label) {
                    windGebaeude++;
                }
                if (_pBaubereich[y * _breite + x] == solar.label) {
                    solarGebaeude++;
                }

                if (x == _breite - 1) {
                    std::cout << std::endl;
                }
            }
        }
        std::cout << std::endl;
        std::cout << "Flaeche Wasserkraftwerk: " << wasserGebaeude << " Preis: " << wasserGebaeude * wasser.grundPreis
                  << " | " << " Materialien: " << wasser.holz * wasserGebaeude << " holz, "
                  << wasser.metall * wasserGebaeude << " metall, " << wasser.kunsstoff * wasserGebaeude << " kunsstoff"
                  << std::endl;
        std::cout << "Flaeche Windkraftwerk:   " << windGebaeude << " Preis: " << windGebaeude * wind.grundPreis
                  << " | " << " Materialien: " << wind.holz * windGebaeude << " holz, " << wind.metall * windGebaeude
                  << " metall, " << wind.kunsstoff * windGebaeude << " kunsstoff" << std::endl;
        std::cout << "Flaeche Solarpanele:     " << solarGebaeude << " Preis: " << solarGebaeude * solar.grundPreis
                  << " | " << " Materialien: " << solar.holz * solarGebaeude << " holz, "
                  << solar.metall * solarGebaeude << " metall, " << solar.kunsstoff * solarGebaeude << " kunsstoff"
                  << std::endl;
        std::cout << "Gesamtpreis: " << (wasserGebaeude * wasser.grundPreis) + (windGebaeude * wind.grundPreis) +
                                        (solarGebaeude * solar.grundPreis) << std::endl;
        std::cout << std::endl;
    }

    bool Collision(char *_pBaubereich, int _gebaeudeLaenge, int _gebaeudeBreite, int _posX, int _posY, int _breite) {
        bool collision = false;

        for (int y = 0; y < _gebaeudeLaenge; y++) {
            for (int x = 0; x < _gebaeudeBreite; x++) {
                if (_pBaubereich[(_posY + y) * _breite + (_posX + x)] != '0') {
                    std::cout << "Kollision!" << std::endl;
                    return true;
                }
            }
        }
        return false;

    }

    void GebaeudeSetzen(char *_pBaubereich, int _breite) {
        int gebaeudeTyp;
        int gebaeudeLaenge;
        int gebaeudeBreite;
        int positionX;
        int positionY;

        WasserB wasser;
        WindB wind;
        SolarB solar;


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
                            _pBaubereich[(positionY + y) * _breite + (positionX + x)] = wasser.label;
                            break;
                        case 2:
                            _pBaubereich[(positionY + y) * _breite + (positionX + x)] = wind.label;
                            break;
                        case 3:
                            _pBaubereich[(positionY + y) * _breite + (positionX + x)] = solar.label;
                    }
                }
            }
        }
    }

    void GebaeudeLoeschen(char *_pBaubereich, int _breite) {
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
                _pBaubereich[(positionY + y) * _breite + (positionX + x)] = '0';


            }
        }
    }

private:

};

int main() {
    bool running = true;
    int laenge, breite = 0;
    int auswahl = 0;
    char *pBaubereich = nullptr;

    CapycitySim capy;

    std::cout << "Laenge: " << std::endl;
    std::cin >> laenge;

    std::cout << "Breite: " << std::endl;
    std::cin >> breite;

    pBaubereich = capy.ErstellungDesArrays(laenge, breite);

    capy.DisplayField(pBaubereich, laenge, breite);

    while (running) {
        std::cout << "(1) Gebaeude setzen | (2) Bereich Loeschen | (3) Ausgabe des Bauplans | (4) Beenden des Programms"
                  << std::endl;
        std::cin >> auswahl;

        switch (auswahl) {
            case 1:
                capy.GebaeudeSetzen(pBaubereich, breite);
                break;
            case 2:
                capy.GebaeudeLoeschen(pBaubereich, breite);
                break;
            case 3:
                capy.DisplayField(pBaubereich, laenge, breite);
                break;
            case 4:
                running = false;
                break;
        }
    }

    delete pBaubereich;
}