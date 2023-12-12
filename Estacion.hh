#ifndef ESTACION_HH
#define ESTACION_HH

#include <string>
#include <map>
#include "Bicicleta.hh"
#include <iostream>
using namespace std;

class Estacion {
    string id;
    int capacidad;
    map<string, Bicicleta> bicicletas; // Mapa de bicicletas en la estación

public:
    // Constructor de Estacion
    // Pre: Recibe un identificador y una capacidad válidos
    // Post: Crea una estación con el identificador y capacidad proporcionados
    Estacion(const string& id, int capacidad);
    Estacion() = default;
    // Añade una b  icicleta a la estación
    // Pre: La bicicleta no está ya en la estación y hay espacio disponible
    // Post: Añade la bicicleta a la estación
    void anadirBicicleta(Bicicleta bici);

    // Quita una bicicleta de la estación
    // Pre: La bicicleta está en la estación
    // Post: Quita la bicicleta de la estación
    void quitarBicicleta(Bicicleta bici);

    // Devuelve el identificador de la estación
    // Pre: La estación existe
    // Post: Retorna el identificador de la estación
    string getId() const;

    // Devuelve la capacidad de la estación
    // Pre: La estación existe
    // Post: Retorna la capacidad actual de la estación
    int getCapacidad() const;

    // Modifica la capacidad de la estación
    // Pre: La nueva capacidad es mayor o igual al número actual de bicicletas
    // Post: Actualiza la capacidad de la estación
    void setCapacidad(int nuevaCapacidad);

    // Devuelve las bicicletas de la estación
    // Pre: La estación existe
    // Post: Retorna un mapa con las bicicletas de la estación
    map<string, Bicicleta> getBicicletas() const;

    Bicicleta getPrimeraBici();
};

#endif // ESTACION_HH
