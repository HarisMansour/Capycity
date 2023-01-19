#include <iostream>
#include <map>

//funktor
class SafeStates
{
public:

    std::map <int, char*> safeStatesMap;

    void setSafeMap(int _index,  char* _pBaubereich, int _laenge, int _breite)
    {
        char* pBaubereich = new char[_laenge * _breite]();

        for (int i = 0; i < _laenge * _breite; i++)
        {
            pBaubereich[i] = _pBaubereich[i];
        }

        safeStatesMap.insert(std::make_pair(_index, pBaubereich));
    }

    char* getSafeMap(int _index)
    {
        return safeStatesMap[_index];
    }
};
SafeStates g_safestate;
int g_index = 0;

class Material
{
private:
    float price;
public:
    void setPrice(float _price)
    {
        price = _price;
    }

    float getPrice()
    {
        return price;
    }
};

class Holz : public Material
{
public:
    const char* name = "Holz";
    float price = 10.00;


};

class Metall : public  Material
{
public:
    const char* name = "Metall";
    float price = 15.00;
};

class Kunststoff : public  Material
{
public:
    const char* name = "Kunststoff";
    float price = 5.00;
};



class Building
{
public:
    float grundPreis;
    char Label;

    // Das Array der Materialien
    const char* Materialien[1000];

    //  die map der Materialien
    std::map <int, int> materialienMap;

    void setMaterialMap(int _material, int _value)
    {
        materialienMap.insert(std::make_pair(_material, _value));
    }

    int getMaterialMap(int _material)
    {
        return materialienMap[_material];
    }


    // Aufgabe 2 das Array befüllen
    void getMaterialien()
    {
        // holz == 1 | metall == 2 | kunsstoff == 3
        int holz;
        int metall;
        int kunsstoff;

        Holz Cholz;
        Metall CMetall;
        Kunststoff CKunsstoff;

        holz		= getMaterialMap(1);
        metall		= getMaterialMap(2);
        kunsstoff	= getMaterialMap(3);

        for (int i = 0; i < holz; i++)
        {
            Materialien[i] = Cholz.name;
        }

        for (int i = holz; i < holz + metall; i++)
        {
            Materialien[i] = CMetall.name;
        }

        for (int i = holz + metall; i < holz + metall + kunsstoff; i++)
        {
            Materialien[i] = CKunsstoff.name;
        }

        for (int i = 0; i < holz + metall + kunsstoff; i++)
        {
            std::cout << Materialien[i] << std::endl;
        }
    }

};

class WasserB : public Building
{
public:
    float grundPreis = 100.00;
    char label = 'W';
    int holz = 7;
    int metall = 2;
    int kunsstoff = 0;
};

class WindB : public Building
{
public:
    float grundPreis = 200.00;
    char label = 'I';
    int holz = 12;
    int metall = 2;
    int kunsstoff = 10;
};

class SolarB : public Building
{
public:
    float grundPreis = 250.00;
    char label = 'S';
    int holz = 0;
    int metall = 10;
    int kunsstoff = 20;
};


class CapycitySim
{

public:
    char* ErstellungDesArrays(int _laenge, int _breite)
    {
        char* pBaubereich = new char[_laenge * _breite]();

        // Initialisierung
        for (int i = 0; i < _laenge * _breite; i++)
        {
            pBaubereich[i] = '0';
        }

        return pBaubereich;
    }


    void DisplayField(char* _pBaubereich, int _laenge, int _breite)
    {


        WasserB wasser;
        WindB wind;
        SolarB solar;

        Holz holz;
        Kunststoff kunsstoff;
        Metall metall;

        int wasserGebaeude	= 0;
        int windGebaeude		= 0;
        int solarGebaeude	= 0;

        float priceWasser	= 0.0;
        float priceSolar	= 0.0;
        float priceWind		= 0.0;

        // die namen der Materialien in das Array schreiben

        for (int y = 0; y < _laenge; y++)
        {
            for (int x = 0; x < _breite; x++)
            {
                std::cout << _pBaubereich[y * _breite + x];

                if (_pBaubereich[y * _breite + x] == wasser.label)
                {
                    wasserGebaeude ++;
                }

                if (_pBaubereich[y * _breite + x] == wind.label)
                {
                    windGebaeude ++;
                }
                if (_pBaubereich[y * _breite + x] == solar.label)
                {
                    solarGebaeude ++;
                }

                if (x == _breite - 1)
                {
                    std::cout << std::endl;
                }
            }
        }

        // holz == 1 | metall == 2 | kunsstoff == 3
        wasser.setMaterialMap(1, wasserGebaeude * wasser.holz);
        wasser.setMaterialMap(2, wasserGebaeude * wasser.metall);
        wasser.setMaterialMap(3, wasserGebaeude * wasser.kunsstoff);

        wind.setMaterialMap(1, windGebaeude  * wind.holz);
        wind.setMaterialMap(2, windGebaeude  * wind.metall);
        wind.setMaterialMap(3, windGebaeude * wind.kunsstoff);

        solar.setMaterialMap(1, solarGebaeude * solar.holz);
        solar.setMaterialMap(2, solarGebaeude * solar.metall);
        solar.setMaterialMap(3, solarGebaeude * solar.kunsstoff);

        priceSolar = (solar.getMaterialMap(1) * holz.price) + (solar.getMaterialMap(2) * metall.price) + (solar.getMaterialMap(3) * kunsstoff.price);
        priceWind = (wind.getMaterialMap(1) * holz.price) + (wind.getMaterialMap(2) * metall.price) + (wind.getMaterialMap(3) * kunsstoff.price);
        priceWasser = (wasser.getMaterialMap(1) * holz.price) + (wasser.getMaterialMap(2) * metall.price) + (wasser.getMaterialMap(3) * kunsstoff.price);

        std::cout << std::endl;
        std::cout << "Flaeche Wasserkraftwerk: " << wasserGebaeude << " Preis: " << priceWasser << " | " << " Materialien: " << wasser.holz * wasserGebaeude << " holz, " << wasser.metall * wasserGebaeude << " metall, " << wasser.kunsstoff * wasserGebaeude << " kunsstoff" << std::endl;
        std::cout << "Flaeche Windkraftwerk:   " << windGebaeude	<< " Preis: " << priceWind << " | " << " Materialien: " << wind.holz * windGebaeude << " holz, "  << wind.metall * windGebaeude << " metall, "  << wind.kunsstoff * windGebaeude << " kunsstoff" << std::endl;
        std::cout << "Flaeche Solarpanele:     " << solarGebaeude << " Preis: " << priceSolar << " | " << " Materialien: " << solar.holz * solarGebaeude << " holz, "  << solar.metall * solarGebaeude << " metall, "  << solar.kunsstoff * solarGebaeude << " kunsstoff" << std::endl;
        std::cout << "Gesamtpreis: " << (wasserGebaeude * wasser.grundPreis) + (windGebaeude * wind.grundPreis) + (solarGebaeude * solar.grundPreis) << std::endl;
        std::cout << std::endl;


        // Ausgaben für das Material array (aber sind sehr lang deswegen auskommentiert)

        /*
        wasser.getMaterialien();
        wind.getMaterialien();
        solar.getMaterialien();
        */

    }

    bool Collision(char* _pBaubereich, int _gebaeudeLaenge,int _gebaeudeBreite,int _posX, int _posY, int _breite)
    {
        bool collision = false;

        for (int y = 0; y < _gebaeudeLaenge; y++)
        {
            for (int x = 0; x < _gebaeudeBreite; x++)
            {
                if (_pBaubereich[(_posY + y) * _breite + (_posX + x)] != '0')
                {
                    std::cout << "Kollision!" << std::endl;
                    return true;
                }
            }
        }
        return false;

    }

    void GebaeudeSetzen(char* _pBaubereich, int _laenge, int _breite)
    {
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

        if (emptySpace == false)
        {
            for (int y = 0; y < gebaeudeLaenge; y++)
            {
                for (int x = 0; x < gebaeudeBreite; x++)
                {
                    switch (gebaeudeTyp)
                    {
                        case 1:
                            _pBaubereich[(positionY + y) * _breite + (positionX + x)] = wasser.label ;
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

    void GebaeudeLoeschen(char* _pBaubereich, int _laenge, int _breite)
    {
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

        for (int y = 0; y < loeschenLaenge; y++)
        {
            for (int x = 0; x < loeschenBreite; x++)
            {
                _pBaubereich[(positionY + y) * _breite + (positionX + x)] = '0';

            }
        }
    }

private:

};

int main()
{
    bool running				= true;
    int laenge, breite			= 0;
    int auswahl					= 0;
    char* pBaubereich			= nullptr;
    char* pSafeState			= nullptr;

    CapycitySim capy;



    std::cout << "Laenge: " << std::endl;
    std::cin >> laenge;

    std::cout << "Breite: " << std::endl;
    std::cin >> breite;

    pBaubereich = capy.ErstellungDesArrays(laenge, breite);

    capy.DisplayField(pBaubereich, laenge, breite);

    while (running)
    {
        std::cout << "(1) Gebaeude setzen | (2) Bereich Loeschen | (3) Ausgabe des Bauplans | (4) Beenden des Programms | (5) Bauplan sichern | (6) Gesicherten Bauplan ausgeben"  << std::endl;
        std::cin >> auswahl;

        switch (auswahl)
        {
            case 1:
                capy.GebaeudeSetzen(pBaubereich, laenge, breite);
                break;
            case 2:
                capy.GebaeudeLoeschen(pBaubereich, laenge, breite);
                break;
            case 3:
                capy.DisplayField(pBaubereich, laenge, breite);
                break;
            case 4:
                running = false;
                break;
            case 5:
                g_safestate.setSafeMap(g_index, pBaubereich, laenge, breite);
                break;
            case 6:
                pSafeState = g_safestate.getSafeMap(g_index);
                capy.DisplayField(pSafeState, laenge, breite);
                break;
        }
    }
    delete pSafeState;
    delete pBaubereich;
}