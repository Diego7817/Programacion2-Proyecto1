#include "hospital.h"
#include <iostream>
#include <string>

using namespace std;

void mostrarMenuDoctores() {
    cout << "\n========================================" << endl;
    cout << "          GESTION DE DOCTORES           " << endl;
    cout << "========================================" << endl;
    cout << " 1. Registrar nuevo doctor              " << endl;
    cout << " 2. Buscar doctor por ID                " << endl;
    cout << " 3. Buscar doctores por especialidad    " << endl;
    cout << " 4. Asignar paciente a doctor           " << endl;
    cout << " 5. Ver pacientes asignados a doctor    " << endl;
    cout << " 6. Listar todos los doctores           " << endl;
    cout << " 7. Eliminar doctor                     " << endl;
    cout << " 0. Volver al menu principal            " << endl;
    cout << "========================================" << endl;
    cout << "Seleccione una opcion: ";
}

void registrarDoctor(Hospital* hospital) {
    cout << "\n--- REGISTRAR NUEVO DOCTOR ---" << endl;

    char nombre[50], apellido[50], cedula[20], especialidad[50];
    int aniosExperiencia;
    float costoConsulta;

    cout << "Nombre: ";
    cin.getline(nombre, 50);

    cout << "Apellido: ";
    cin.getline(apellido, 50);

    cout << "Cedula profesional: ";
    cin.getline(cedula, 20);

    cout << "Especialidad: ";
    cin.getline(especialidad, 50);

    cout << "Anios de experiencia: ";
    cin >> aniosExperiencia;
    limpiarBuffer();

    cout << "Costo de consulta: ";
    cin >> costoConsulta;
    limpiarBuffer();

    Doctor* nuevoDoctor = crearDoctor(hospital, nombre, apellido, cedula, especialidad, aniosExperiencia, costoConsulta);
    if (nuevoDoctor) {
        cout << "Doctor registrado exitosamente con ID: " << nuevoDoctor->id << endl;
    } else {
        cout << "Error: No se pudo registrar el doctor." << endl;
    }
}

void buscarDoctorId(Hospital* hospital) {
    cout << "\n--- BUSCAR DOCTOR POR ID ---" << endl;

    int id;
    cout << "Ingrese el ID del doctor: ";
    cin >> id;
    limpiarBuffer();

    Doctor* doctor = buscarDoctorPorId(hospital, id);
    if (doctor) {
        cout << "\nDoctor encontrado:" << endl;
        cout << "   ID: " << doctor->id << endl;
        cout << "   Nombre: " << doctor->nombre << " " << doctor->apellido << endl;
        cout << "   Cedula: " << doctor->cedula << endl;
        cout << "   Especialidad: " << doctor->especialidad << endl;
        cout << "   Anios experiencia: " << doctor->aniosExperiencia << endl;
        cout << "   Costo consulta: $" << doctor->costoConsulta << endl;
        cout << "   Pacientes asignados: " << doctor->cantidadPacientes << endl;
    } else {
        cout << "No se encontro ningun doctor con ese ID." << endl;
    }
}

void buscarDoctorEspecialidad(Hospital* hospital) {
    cout << "\n--- BUSCAR DOCTORES POR ESPECIALIDAD ---" << endl;

    char especialidad[50];
    cout << "Ingrese la especialidad a buscar: ";
    cin.getline(especialidad, 50);

    int cantidad;
    Doctor** resultados = buscarDoctoresPorEspecialidad(hospital, especialidad, &cantidad);

    if (resultados && cantidad > 0) {
        cout << "\nSe encontraron " << cantidad << " doctores:" << endl;
        for (int i = 0; i < cantidad; i++) {
            Doctor* d = resultados[i];
            cout << "   " << i+1 << ". ID: " << d->id << " - "
                 << d->nombre << " " << d->apellido
                 << " (" << d->especialidad << ")" << endl;
        }
        delete[] resultados;
    } else {
        cout << "No se encontraron doctores con esa especialidad." << endl;
    }
}

void asignarPacienteDoctor(Hospital* hospital) {
    cout << "\n--- ASIGNAR PACIENTE A DOCTOR ---" << endl;

    int idDoctor, idPaciente;

    cout << "ID del doctor: ";
    cin >> idDoctor;
    limpiarBuffer();

    cout << "ID del paciente: ";
    cin >> idPaciente;
    limpiarBuffer();

    Doctor* doctor = buscarDoctorPorId(hospital, idDoctor);
    Paciente* paciente = buscarPacientePorId(hospital, idPaciente);

    if (!doctor) {
        cout << "Doctor no encontrado." << endl;
        return;
    }

    if (!paciente) {
        cout << "Paciente no encontrado." << endl;
        return;
    }

    if (asignarPacienteADoctor(doctor, idPaciente)) {
        cout << "Paciente asignado correctamente al doctor." << endl;
    }
}

void verPacientesDoctor(Hospital* hospital) {
    cout << "\n--- VER PACIENTES DE DOCTOR ---" << endl;

    int idDoctor;
    cout << "ID del doctor: ";
    cin >> idDoctor;
    limpiarBuffer();

    listarPacientesDeDoctor(hospital, idDoctor);
}

void eliminarDoctorInteractivo(Hospital* hospital) {
    cout << "\n--- ELIMINAR DOCTOR ---" << endl;

    int id;
    cout << "Ingrese el ID del doctor a eliminar: ";
    cin >> id;
    limpiarBuffer();

    Doctor* doctor = buscarDoctorPorId(hospital, id);
    if (!doctor) {
        cout << "Doctor no encontrado." << endl;
        return;
    }

    cout << "Esta seguro de eliminar al Dr. " << doctor->nombre << " " << doctor->apellido << "? (S/N): ";
    char confirmacion;
    cin >> confirmacion;
    limpiarBuffer();

    if (toupper(confirmacion) == 'S') {
        if (eliminarDoctor(hospital, id)) {
            cout << "Doctor eliminado correctamente." << endl;
        } else {
            cout << "Error al eliminar el doctor." << endl;
        }
    } else {
        cout << "Operacion cancelada." << endl;
    }
}

void gestionarDoctores(Hospital* hospital) {
    int opcion;

    do {
        mostrarMenuDoctores();
        cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
            case 1:
                registrarDoctor(hospital);
                break;
            case 2:
                buscarDoctorId(hospital);
                break;
            case 3:
                buscarDoctorEspecialidad(hospital);
                break;
            case 4:
                asignarPacienteDoctor(hospital);
                break;
            case 5:
                verPacientesDoctor(hospital);
                break;
            case 6:
                listarDoctores(hospital);
                break;
            case 7:
                eliminarDoctorInteractivo(hospital);
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