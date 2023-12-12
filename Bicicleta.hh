#ifndef BICICLETA_HH
#define BICICLETA_HH

#include <string>
#include <vector>
using namespace std;

class Bicicleta {
    string id;
    vector<string> viajes;

public:
    // Constructor de Bicicleta
    // Pre: Recibe un identificador de bicicleta válido
    // Post: Crea una bicicleta con el identificador proporcionado
    Bicicleta(const string& id);
    Bicicleta() = default;
    // Agrega un viaje al historial de la bicicleta
    // Pre: Recibe un identificador de estación de destino válido
    // Post: Añade el viaje al historial de la bicicleta
    void agregarViaje(const string& estacionDestino);

    // Devuelve el identificador de la bicicleta
    // Pre: La bicicleta existe
    // Post: Retorna el identificador de la bicicleta
    string getId() const;

    // Devuelve el historial de viajes de la bicicleta
    // Pre: La bicicleta existe
    // Post: Retorna el historial de viajes de la bicicleta
    vector<string> getViajes() const;
};

#endif // BICICLETA_HH
