#include "Bicicleta.hh"

Bicicleta::Bicicleta(const string& id) : id(id) {}

void Bicicleta::agregarViaje(const string& estacionDestino) {
    viajes.push_back(estacionDestino);
}

string Bicicleta::getId() const {
    return id;
}

vector<string> Bicicleta::getViajes() const {
    return viajes;
}
