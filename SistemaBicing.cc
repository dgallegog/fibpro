#include "SistemaBicing.hh"

void SistemaBicing::anadirBicicleta(const string& idBici, const string& idEstacion) {
    // Verificar si la bicicleta ya existe
    if (bicicletas.find(idBici) != bicicletas.end()) {
        cout << "error: la bici ya existe" << endl;
        return;
    }

    // Verificar si la estación existe
    auto estacion = estaciones.find(idEstacion);
    
    if (estacion == estaciones.end()) {
        cout << "error: la estacion no existe" << endl;
        return;
    }

    // Verificar si hay espacio en la estación para la nueva bicicleta
    if (estacion->second.getBicicletas().size() >= estacion->second.getCapacidad()) {
        cout << "error: la bici no cabe" << endl;
        return;
    }

    // Añadir la bicicleta a la estación y al sistema
    Bicicleta nuevaBici = Bicicleta(idBici);
    bicicletas[idBici] = nuevaBici;
    
    
    estacion->second.anadirBicicleta(nuevaBici);
}


void SistemaBicing::eliminarBicicleta(const string& idBici) {
    // Verificar si la bicicleta existe en el sistema
    auto itBici = bicicletas.find(idBici);
    if (itBici == bicicletas.end()) {
        cout << "error: la bici no existe" << endl;
        return;
    }

    // Si la bicicleta existe, obtener la estación donde está ubicada
    string estacionBici = obtenerEstacionDeBicicleta(idBici);
    if (!estacionBici.empty()) {
        // Suponiendo que Estacion tiene un método para quitar bicicletas
        estaciones[estacionBici].quitarBicicleta(itBici->second);
    }

    // Eliminar la bicicleta del sistema y liberar la memoria
    
    bicicletas.erase(itBici);
}

void SistemaBicing::moverBicicleta(const string& idBici, const string& idEstacionDestino) {
    // Verificar si la bicicleta existe en el sistema
    auto itBici = bicicletas.find(idBici);
    if (itBici == bicicletas.end()) {
        cout << "error: la bici no existe" << endl;
        return;
    }

    // Verificar si la estación de destino existe
    auto itEstacionDestino = estaciones.find(idEstacionDestino);
    if (itEstacionDestino == estaciones.end()) {
        cout << "error: la estacion no existe" << endl;
        return;
    }
    // Verificar si hay espacio en la estación de destino
    if (itEstacionDestino->second.getBicicletas().size() >= itEstacionDestino->second.getCapacidad()) {
        cout << "error: la bici no cabe" << endl;
        return;
    }
    // Obtener la estación de origen de la bicicleta
    string estacionOrigen = obtenerEstacionDeBicicleta(idBici);
    if (estacionOrigen.empty() || estacionOrigen == idEstacionDestino) {
        cout << "error: la bici ya esta en el sitio" << endl;
        return;
    }



    // Mover la bicicleta de la estación de origen a la de destino
    estaciones[estacionOrigen].quitarBicicleta(itBici->second);
   
    itEstacionDestino->second.anadirBicicleta(itBici->second);
    itBici->second.agregarViaje(estacionOrigen);
    itBici->second.agregarViaje(idEstacionDestino); 
}


vector<string> SistemaBicing::listarBicicletasEnEstacion(const string& idEstacion) {
    vector<string> listaBicicletas;
    if (estaciones.find(idEstacion) != estaciones.end()) {
        for (const auto& par : estaciones[idEstacion].getBicicletas()) {
            listaBicicletas.push_back(par.first);
        }
    }
    return listaBicicletas;
}

void SistemaBicing::modificarCapacidadEstacion(const string& idEstacion, int nuevaCapacidad) {
    // Verificar si la estación existe
    auto itEstacion = estaciones.find(idEstacion);
    if (itEstacion == estaciones.end()) {
        cout << "error: la estacion no existe" << endl;
        return;
    }

    // Verificar si la nueva capacidad es menor que la cantidad actual de bicicletas en la estación
    if (itEstacion->second.getBicicletas().size() > nuevaCapacidad) {
        cout << "error: capacidad insuficiente" << endl;
        return;
    }

    // Establecer la nueva capacidad
    itEstacion->second.setCapacidad(nuevaCapacidad);
    
}




// Continuación de la implementación de la clase SistemaBicing

vector<string> SistemaBicing::obtenerBicicletasEnEstacion(const string& idEstacion) {
    vector<string> idsBicicletas;

    // Verificar si la estación existe en el sistema
    auto itEstacion = estaciones.find(idEstacion);
    if (itEstacion == estaciones.end()) {
        cout << "error: la estacion no existe" << endl;
        return idsBicicletas; // Retorna un vector vacío
    }

    // Si la estación existe, obtener las bicicletas en esa estación
    auto bicicletasEnEstacion = itEstacion->second.getBicicletas();
    for (const auto& bici : bicicletasEnEstacion) {
        idsBicicletas.push_back(bici.first);
    }

    return idsBicicletas;
}

int SistemaBicing::obtenerPlazasLibres() {
    auto totalPlazasLibres = obtenerPlazasLibresRec(btEstaciones);
    return totalPlazasLibres;
}
int SistemaBicing::obtenerPlazasLibresRec(const BT &t) {
    if (t.empty()) return 0;

    int left = obtenerPlazasLibresRec(t.left());
    int right = obtenerPlazasLibresRec(t.right());

    int res = estaciones[t.value()].getCapacidad()-estaciones[t.value()].getBicicletas().size() + left + right;
    return res;
}

void SistemaBicing::subirBicicletas() {
    
    subirBicicletasRec(btEstaciones, bicicletas);

    
} 

void SistemaBicing::subirBicicletasRec(const BT &t, map<string, Bicicleta>& bicis) {
    
    if (t.empty()) return;

    BT left = t.left();
    BT right = t.right();

    if (estaciones[t.value()].getCapacidad() - estaciones[t.value()].getBicicletas().size() > 0) {
        int nLeft = 0;
        int nRight = 0;
        
        if(!left.empty()) nLeft = estaciones[left.value()].getBicicletas().size();
        if(!right.empty()) nRight = estaciones[right.value()].getBicicletas().size();
        
        if (nLeft > 0 || nRight > 0) {
            while (estaciones[t.value()].getCapacidad() - estaciones[t.value()].getBicicletas().size() > 0 && (nLeft > 0 || nRight > 0)) {
                
                if (nLeft > nRight) {
                    
                    auto bicisIt = estaciones[left.value()].getPrimeraBici();
                    estaciones[t.value()].anadirBicicleta(bicisIt);
                    estaciones[left.value()].quitarBicicleta(bicisIt);
                    nLeft--;
                }
                else if (nLeft < nRight) {
                    
                    auto bicisIt = estaciones[right.value()].getPrimeraBici();
                    estaciones[t.value()].anadirBicicleta(bicisIt);
                    estaciones[right.value()].quitarBicicleta(bicisIt);
                    nRight--;
                }
                else {
                    
                    auto bicisItL = estaciones[left.value()].getPrimeraBici();
                    auto bicisItR = estaciones[right.value()].getPrimeraBici();
                    if (bicisItL.getId() > bicisItR.getId()) {
                        estaciones[t.value()].anadirBicicleta(bicisItL);
                        estaciones[left.value()].quitarBicicleta(bicisItL);
                        nLeft--;
                    }
                    else {
                        
                        estaciones[t.value()].anadirBicicleta(bicisItR);
                        estaciones[right.value()].quitarBicicleta(bicisItR);
                        nRight--;
                    }
                }
            }
        }

    }
    subirBicicletasRec(left, bicis);
    subirBicicletasRec(right, bicis);

    
} 




string SistemaBicing::obtenerEstacionDeBicicleta(const string& idBici) {
    // Primero verificar si la bicicleta existe en el sistema
    if (bicicletas.find(idBici) == bicicletas.end()) {
        return "error: la bici no existe"; // Retorna un error si la bicicleta no existe
    }

    // Recorrer todas las estaciones buscando la bicicleta
    for (const auto& estacion : estaciones) {
        const auto& bicisEnEstacion = estacion.second.getBicicletas();
        if (bicisEnEstacion.find(idBici) != bicisEnEstacion.end()) {
            return estacion.first; // Retorna el identificador de la estación donde se encontró la bicicleta
        }
    }

    return ""; // Retorna un string vacío si la bicicleta no se encuentra en ninguna estación
}


vector<string> SistemaBicing::obtenerViajesBicicleta(const string& idBici) {
    // Implementación de ejemplo
    if (bicicletas.find(idBici) == bicicletas.end()) {
        cout << "error: la bici no existe" << endl; // Retorna si la bicicleta no existe
        return vector<string>();
    }
  
    return bicicletas[idBici].getViajes();
    
   
}

void SistemaBicing::construirArbol() {
    string idEstacion;
    int capacidad;
    cin >> idEstacion >> capacidad; // Leer raíz
    btEstaciones = construirArbolRecursivo(idEstacion, capacidad);
}

BT SistemaBicing::construirArbolRecursivo(const string& idEstacion, int capacidad) {
    string idHijoIzq, idHijoDer;
    int capacidadHijoIzq, capacidadHijoDer;

    BT hijoIzq, hijoDer;

    // Leer identificador del hijo izquierdo y su capacidad (o # si es nulo)
    cin >> idHijoIzq;
    if (idHijoIzq != "#") {
        cin >> capacidadHijoIzq;
        hijoIzq = construirArbolRecursivo(idHijoIzq, capacidadHijoIzq);
    }

    // Leer identificador del hijo derecho y su capacidad (o # si es nulo)
    cin >> idHijoDer;
    if (idHijoDer != "#") {
        cin >> capacidadHijoDer;
        hijoDer = construirArbolRecursivo(idHijoDer, capacidadHijoDer);
    }

    // Añadir la estación actual al mapa de estaciones
    estaciones[idEstacion] = Estacion(idEstacion, capacidad);

    // Crear y devolver el árbol binario con la estación actual y sus hijos
    return BT(idEstacion, hijoIzq, hijoDer);
}


void SistemaBicing::imprimirArbol() {
    btEstaciones.setOutputFormat(BT::VISUALFORMAT);
    cout << btEstaciones << endl;
}

string SistemaBicing::asignarEstacionABicicleta(const string& idBici) {


    
    if (bicicletas.find(idBici) != bicicletas.end()) {
        cout << "error: la bici ya existe";
        return "";
    }
    else if (obtenerPlazasLibres() <= 0) {
        cout << "error: no hay plazas libres";
        return "";
    }

    pair<int, int> librese = {0,1};
    string est = "";
    libresYestaciones(btEstaciones, est, librese);
    
    
    
    if (est != "") estaciones[est].anadirBicicleta(idBici);
    

    return est;
}

pair<int,int> SistemaBicing::libresYestaciones(const BT &t, string &est, pair<int,int> &libresed) {
   
    if (t.empty()) return pair<int,int>(0,0);

    
    auto left = libresYestaciones(t.left(), est, libresed);
    auto right = libresYestaciones(t.right(), est, libresed);

    int desigualdad = left.first+right.first+(estaciones[t.value()].getCapacidad()-estaciones[t.value()].getBicicletas().size());
    int n = left.second + right.second + 1;


    if (libresed.first * n < desigualdad * libresed.second) {
        libresed = {desigualdad, n};
        est = t.value();
    }
    else if(libresed.first * n == desigualdad * libresed.second && est > t.value()) {
        est = t.value();
    }

    return pair<int,int>(desigualdad, n);  


}





