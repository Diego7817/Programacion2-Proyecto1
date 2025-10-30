#include "hospital.h"
#include <iostream>
#include <iomanip>

using namespace std;

void redimensionarHistorial(Paciente* paciente) {
    int nuevaCapacidad = paciente->capacidadHistorial * 2;
    HistorialMedico* nuevoHistorial = new HistorialMedico[nuevaCapacidad];

    for (int i = 0; i < paciente->cantidadConsultas; i++) {
        nuevoHistorial[i] = paciente->historial[i];
    }

    delete[] paciente->historial;
    paciente->historial = nuevoHistorial;
    paciente->capacidadHistorial = nuevaCapacidad;
}

void agregarConsultaAlHistorial(Paciente* paciente, HistorialMedico consulta) {
    if (paciente->cantidadConsultas >= paciente->capacidadHistorial) {
        redimensionarHistorial(paciente);
    }

    paciente->historial[paciente->cantidadConsultas] = consulta;
    paciente->cantidadConsultas++;

    cout << "Consulta agregada al historial. ID: " << consulta.idConsulta << endl;
}

HistorialMedico* obtenerHistorialCompleto(Paciente* paciente, int* cantidad) {
    *cantidad = paciente->cantidadConsultas;
    return paciente->historial;
}

void mostrarHistorialMedico(Paciente* paciente) {
    if (paciente->cantidadConsultas == 0) {
        cout << "No hay consultas registradas." << endl;
        return;
    }

    cout << "\n╔══════════════════════════════════════════════════════════════════════════════════╗" << endl;

    string titulo = "HISTORIAL MÉDICO - " + string(paciente->nombre) + " " + paciente->apellido;
    if (titulo.length() > 70) {
        titulo = titulo.substr(0, 67) + "...";
    }
    cout << "║ " << setw(70) << left << titulo << " ║" << endl;

    cout << "╠════════╦════════════╦════════╦══════════════════════════════╦══════════╦═════════╣" << endl;
    cout << "║ CONSUL ║ FECHA      ║ HORA   ║ DIAGNÓSTICO                  ║ DOCTOR   ║ COSTO   ║" << endl;
    cout << "╠════════╬════════════╬════════╬══════════════════════════════╬══════════╬═════════╣" << endl;

    for (int i = 0; i < paciente->cantidadConsultas; i++) {
        HistorialMedico* consulta = &paciente->historial[i];

        string diagnosticoStr(consulta->diagnostico);
        if (diagnosticoStr.length() > 28) {
            diagnosticoStr = diagnosticoStr.substr(0, 25) + "...";
        }

        cout << "║ " << setw(6) << consulta->idConsulta << " ║ "
             << setw(10) << consulta->fecha << " ║ "
             << setw(6) << consulta->hora << " ║ "
             << setw(28) << left << diagnosticoStr << " ║ "
             << setw(8) << consulta->idDoctor << " ║ $"
             << setw(6) << fixed << setprecision(2) << consulta->costo << "║" << endl;
    }
    cout << "╚════════╩════════════╩════════╩══════════════════════════════╩══════════╩═════════╝" << endl;
    cout << "Total de consultas: " << paciente->cantidadConsultas << endl;
}

HistorialMedico* obtenerUltimaConsulta(Paciente* paciente) {
    if (paciente->cantidadConsultas == 0) {
        return nullptr;
    }
    return &paciente->historial[paciente->cantidadConsultas - 1];
}