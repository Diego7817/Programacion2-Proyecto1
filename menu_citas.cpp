#include "hospital.h"
#include <iostream>
#include <string>

using namespace std;

void mostrarMenuCitas() {
    cout << "\n========================================" << endl;
    cout << "           GESTION DE CITAS             " << endl;
    cout << "========================================" << endl;
    cout << " 1. Agendar nueva cita                  " << endl;
    cout << " 2. Cancelar cita                       " << endl;
    cout << " 3. Atender cita                        " << endl;
    cout << " 4. Ver citas de un paciente            " << endl;
    cout << " 5. Ver citas de un doctor              " << endl;
    cout << " 6. Ver citas de una fecha              " << endl;
    cout << " 7. Ver citas pendientes                " << endl;
    cout << " 0. Volver al menu principal            " << endl;
    cout << "========================================" << endl;
    cout << "Seleccione una opcion: ";
}

void agendarCitaInteractivo(Hospital* hospital) {
    cout << "\n--- AGENDAR NUEVA CITA ---" << endl;

    int idPaciente, idDoctor;
    char fecha[11], hora[6], motivo[150];

    cout << "ID del paciente: ";
    cin >> idPaciente;
    limpiarBuffer();

    cout << "ID del doctor: ";
    cin >> idDoctor;
    limpiarBuffer();

    cout << "Fecha (YYYY-MM-DD): ";
    cin.getline(fecha, 11);

    cout << "Hora (HH:MM): ";
    cin.getline(hora, 6);

    cout << "Motivo de la consulta: ";
    cin.getline(motivo, 150);

    Cita* nuevaCita = agendarCita(hospital, idPaciente, idDoctor, fecha, hora, motivo);
    if (nuevaCita) {
        cout << "Cita agendada exitosamente. ID: " << nuevaCita->id << endl;
    }
}

void cancelarCitaInteractivo(Hospital* hospital) {
    cout << "\n--- CANCELAR CITA ---" << endl;

    int idCita;
    cout << "ID de la cita a cancelar: ";
    cin >> idCita;
    limpiarBuffer();

    if (cancelarCita(hospital, idCita)) {
        cout << "Cita cancelada correctamente." << endl;
    }
}

void atenderCitaInteractivo(Hospital* hospital) {
    cout << "\n--- ATENDER CITA ---" << endl;

    int idCita;
    char diagnostico[200], tratamiento[200], medicamentos[150];

    cout << "ID de la cita a atender: ";
    cin >> idCita;
    limpiarBuffer();

    cout << "Diagnostico: ";
    cin.getline(diagnostico, 200);

    cout << "Tratamiento: ";
    cin.getline(tratamiento, 200);

    cout << "Medicamentos recetados: ";
    cin.getline(medicamentos, 150);

    if (atenderCita(hospital, idCita, diagnostico, tratamiento, medicamentos)) {
        cout << "Cita atendida correctamente." << endl;
    }
}

void verCitasPaciente(Hospital* hospital) {
    cout << "\n--- CITAS DE PACIENTE ---" << endl;

    int idPaciente;
    cout << "ID del paciente: ";
    cin >> idPaciente;
    limpiarBuffer();

    int cantidad;
    Cita** citas = obtenerCitasDePaciente(hospital, idPaciente, &cantidad);

    if (citas && cantidad > 0) {
        cout << "\nCitas del paciente:" << endl;
        for (int i = 0; i < cantidad; i++) {
            Cita* c = citas[i];
            cout << "   " << i+1 << ". ID: " << c->id << " - " << c->fecha << " " << c->hora
                 << " - Dr." << c->idDoctor << " - " << c->estado << endl;
        }
        delete[] citas;
    } else {
        cout << "El paciente no tiene citas registradas." << endl;
    }
}

void verCitasDoctor(Hospital* hospital) {
    cout << "\n--- CITAS DE DOCTOR ---" << endl;

    int idDoctor;
    cout << "ID del doctor: ";
    cin >> idDoctor;
    limpiarBuffer();

    int cantidad;
    Cita** citas = obtenerCitasDeDoctor(hospital, idDoctor, &cantidad);

    if (citas && cantidad > 0) {
        cout << "\nCitas del doctor:" << endl;
        for (int i = 0; i < cantidad; i++) {
            Cita* c = citas[i];
            cout << "   " << i+1 << ". ID: " << c->id << " - " << c->fecha << " " << c->hora
                 << " - Pac." << c->idPaciente << " - " << c->estado << endl;
        }
        delete[] citas;
    } else {
        cout << "El doctor no tiene citas registradas." << endl;
    }
}

void verCitasFecha(Hospital* hospital) {
    cout << "\n--- CITAS POR FECHA ---" << endl;

    char fecha[11];
    cout << "Fecha (YYYY-MM-DD): ";
    cin.getline(fecha, 11);

    if (!validarFecha(fecha)) {
        cout << "Formato de fecha invalido." << endl;
        return;
    }

    int cantidad;
    Cita** citas = obtenerCitasPorFecha(hospital, fecha, &cantidad);

    if (citas && cantidad > 0) {
        cout << "\nCitas para " << fecha << ":" << endl;
        for (int i = 0; i < cantidad; i++) {
            Cita* c = citas[i];
            cout << "   " << i+1 << ". ID: " << c->id << " - " << c->hora
                 << " - Dr." << c->idDoctor << " - Pac." << c->idPaciente
                 << " - " << c->estado << endl;
        }
        delete[] citas;
    } else {
        cout << "No hay citas para esta fecha." << endl;
    }
}

void gestionarCitas(Hospital* hospital) {
    int opcion;

    do {
        mostrarMenuCitas();
        cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
            case 1:
                agendarCitaInteractivo(hospital);
                break;
            case 2:
                cancelarCitaInteractivo(hospital);
                break;
            case 3:
                atenderCitaInteractivo(hospital);
                break;
            case 4:
                verCitasPaciente(hospital);
                break;
            case 5:
                verCitasDoctor(hospital);
                break;
            case 6:
                verCitasFecha(hospital);
                break;
            case 7:
                listarCitasPendientes(hospital);
                break;
            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
        }

        if (opcion != 0) {
            cout << "\nPresione Enter para continuar...";
            cin.get();
        }
    } while (opcion != 0);
}