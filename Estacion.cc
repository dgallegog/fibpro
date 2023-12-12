#include "Estacion.hh"

Estacion::Estacion(const string& id, int capacidad) : id(id), capacidad(capacidad) {}

void Estacion::anadirBicicleta(Bicicleta bici) {
    if (bicicletas.size() < capacidad) {
        bicicletas[bici.getId()] = bici;
    }
}

void Estacion::quitarBicicleta(Bicicleta bici) {
    bicicletas.erase(bici.getId());
}

string Estacion::getId() const {
    return id;
}

int Estacion::getCapacidad() const {
    return capacidad;
}

void Estacion::setCapacidad(int nuevaCapacidad) {
    if (nuevaCapacidad >= bicicletas.size()) {
        capacidad = nuevaCapacidad;
    }
}

map<string, Bicicleta> Estacion::getBicicletas() const {
    return bicicletas;
}

Bicicleta Estacion::getPrimeraBici() {
    auto it = bicicletas.begin();
    if (it == bicicletas.end()) cout << "error: no hay primera bici" << endl;
    return it->second;
}