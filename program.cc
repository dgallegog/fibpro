#include "SistemaBicing.hh"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>  


int main() {
    SistemaBicing bicing;
    string idEstacion;
    string comando = "";
    
    bicing.construirArbol();
    
    do  {
        if (comando == "alta_bici" || comando == "ab") {
            string idBici, idEstacion;
            cin >> idBici >> idEstacion;
            cout << "#" << "ab" << " " << idBici << " " << idEstacion << endl; 
           
            bicing.anadirBicicleta(idBici, idEstacion);
            
        } else if (comando == "baja_bici" || comando == "bb") {
            string idBici;
            cin >> idBici;
            cout << "#" << "bb" << " " << idBici << endl; 
            bicing.eliminarBicicleta(idBici);
        } else if (comando == "estacion_bici" || comando == "eb") {
            string idBici;
            cin >> idBici;
            cout << "#" << "eb" << " " << idBici << endl;
            cout << bicing.obtenerEstacionDeBicicleta(idBici) << endl;
        } else if (comando == "viajes_bici" || comando == "vb") {
            string idBici;
            cin >> idBici;
            cout << "#" << "vb" << " " << idBici << endl;
            vector<string> viajes = bicing.obtenerViajesBicicleta(idBici);
            bool ex = false;
            int cont = 0;
            for (const auto& viaje : viajes) {
                if (ex && cont % 2 != 0) cout << " ";
                if (cont % 2 == 0 && ex) cout << endl;
                cout << viaje;
                ex = true;
                cont++;
            }
            if (ex) cout << endl;
        } else if (comando == "mover_bici" || comando == "mb") {
            string idBici, idEstacion;
            cin >> idBici >> idEstacion;
            cout << "#" << "mb" << " " << idBici << " " << idEstacion << endl; 
            bicing.moverBicicleta(idBici, idEstacion);
        } else if (comando == "bicis_estacion" || comando == "be") {
            string idEstacion;
            cin >> idEstacion;
            cout << "#" << "be" << " " << idEstacion << endl; 
            vector<string> bicis = bicing.obtenerBicicletasEnEstacion(idEstacion);
            for (const auto& bici : bicis) {
                cout << bici << endl;
            }
        } else if (comando == "modificar_capacidad" || comando == "mc") {
            string idEstacion;
            int nuevaCapacidad;
            cin >> idEstacion >> nuevaCapacidad;
            cout << "#" << "mc" << " " << idEstacion << " " << nuevaCapacidad << endl; 
            bicing.modificarCapacidadEstacion(idEstacion, nuevaCapacidad);
        } else if (comando == "plazas_libres" || comando == "pl") { 
            cout << "#" << "pl" << endl; 
            cout << bicing.obtenerPlazasLibres() << endl;
        } else if (comando == "subir_bicis" || comando == "sb") {
            
            cout << "#" << "sb" << endl; 
            bicing.subirBicicletas();
             
        } else if (comando == "asignar_estacion" || comando == "ae") {
            string idBici;
            cin >> idBici;
            cout << "#" << "ae" << " " << idBici << endl; 
            cout << bicing.asignarEstacionABicicleta(idBici) << endl;
        } else if (comando == "fin") {
            break;
        } 
    } while (cin >> comando);

    return 0;
}
