#include "hospital.h"
#include <iostream>
#include <string>

using namespace std;

void mostrarMenuPacientes() {
    cout << "\n========================================" << endl;
    cout << "          GESTION DE PACIENTES          " << endl;
    cout << "========================================" << endl;
    cout << " 1. Registrar nuevo paciente            " << endl;
    cout << " 2. Buscar paciente por cedula          " << endl;
    cout << " 3. Buscar paciente por nombre          " << endl;
    cout << " 4. Ver historial medico completo       " << endl;
    cout << " 5. Actualizar datos del paciente       " << endl;
    cout << " 6. Listar todos los pacientes          " << endl;
    cout << " 7. Eliminar paciente                   " << endl;
    cout << " 0. Volver al menu principal            " << endl;
    cout << "========================================" << endl;
    cout << "Seleccione una opcion: ";
}

void registrarPaciente(Hospital* hospital) {
    cout << "\n--- REGISTRAR NUEVO PACIENTE ---" << endl;

    char nombre[50], apellido[50], cedula[20];
    int edad;
    char sexo;

    cout << "Nombre: ";
    cin.getline(nombre, 50);

    cout << "Apellido: ";
    cin.getline(apellido, 50);

    cout << "Cedula: ";
    cin.getline(cedula, 20);

    if (buscarPacientePorCedula(hospital, cedula)) {
        cout << "Error: Ya existe un paciente con esta cedula." << endl;
        return;
    }

    cout << "Edad: ";
    cin >> edad;
    limpiarBuffer();

    if (edad < 0 || edad > 120) {
        cout << "Error: La edad debe estar entre 0 y 120 anos." << endl;
        return;
    }

    cout << "Sexo (M/F): ";
    cin >> sexo;
    limpiarBuffer();

    sexo = toupper(sexo);
    if (sexo != 'M' && sexo != 'F') {
        cout << "Error: El sexo debe ser 'M' o 'F'." << endl;
        return;
    }

    Paciente* nuevoPaciente = crearPaciente(hospital, nombre, apellido, cedula, edad, sexo);
    if (nuevoPaciente) {
        cout << "Paciente registrado exitosamente con ID: " << nuevoPaciente->id << endl;
    } else {
        cout << "Error: No se pudo registrar el paciente." << endl;
    }
}

void buscarPacienteCedula(Hospital* hospital) {
    cout << "\n--- BUSCAR PACIENTE POR CEDULA ---" << endl;

    char cedula[20];
    cout << "Ingrese la cedula: ";
    cin.getline(cedula, 20);

    Paciente* paciente = buscarPacientePorCedula(hospital, cedula);
    if (paciente && paciente->activo) {
        cout << "\nPaciente encontrado:" << endl;
        cout << "   ID: " << paciente->id << endl;
        cout << "   Nombre: " << paciente->nombre << " " << paciente->apellido << endl;
        cout << "   Cedula: " << paciente->cedula << endl;
        cout << "   Edad: " << paciente->edad << endl;
        cout << "   Sexo: " << paciente->sexo << endl;
        cout << "   Consultas realizadas: " << paciente->cantidadConsultas << endl;
    } else {
        cout << "No se encontro ningun paciente con esa cedula." << endl;
    }
}

void buscarPacienteNombre(Hospital* hospital) {
    cout << "\n--- BUSCAR PACIENTE POR NOMBRE ---" << endl;

    char nombre[50];
    cout << "Ingrese el nombre o apellido a buscar: ";
    cin.getline(nombre, 50);

    int cantidad;
    Paciente** resultados = buscarPacientesPorNombre(hospital, nombre, &cantidad);

    if (resultados && cantidad > 0) {
        cout << "\nSe encontraron " << cantidad << " pacientes:" << endl;
        for (int i = 0; i < cantidad; i++) {
            Paciente* p = resultados[i];
            cout << "   " << i+1 << ". ID: " << p->id << " - "
                 << p->nombre << " " << p->apellido
                 << " (Cedula: " << p->cedula << ")" << endl;
        }
        delete[] resultados;
    } else {
        cout << "No se encontraron pacientes con ese nombre." << endl;
    }
}

void verHistorialPaciente(Hospital* hospital) {
    cout << "\n--- VER HISTORIAL MEDICO ---" << endl;

    char cedula[20];
    cout << "Ingrese la cedula del paciente: ";
    cin.getline(cedula, 20);

    Paciente* paciente = buscarPacientePorCedula(hospital, cedula);
    if (paciente && paciente->activo) {
        mostrarHistorialMedico(paciente);
    } else {
        cout << "No se encontro ningun paciente con esa cedula." << endl;
    }
}

void actualizarPacienteInteractivo(Hospital* hospital) {
    cout << "\n--- ACTUALIZAR DATOS DE PACIENTE ---" << endl;

    char cedula[20];
    cout << "Ingrese la cedula del paciente a actualizar: ";
    cin.getline(cedula, 20);

    Paciente* paciente = buscarPacientePorCedula(hospital, cedula);
    if (!paciente) {
        cout << "Paciente no encontrado." << endl;
        return;
    }

    cout << "Actualizando datos de: " << paciente->nombre << " " << paciente->apellido << endl;

    cout << "Nuevo telefono (actual: " << paciente->telefono << "): ";
    char telefono[15];
    cin.getline(telefono, 15);
    if (strlen(telefono) > 0) {
        strcpy(paciente->telefono, telefono);
    }

    cout << "Nueva direccion (actual: " << paciente->direccion << "): ";
    char direccion[100];
    cin.getline(direccion, 100);
    if (strlen(direccion) > 0) {
        strcpy(paciente->direccion, direccion);
    }

    cout << "Nuevo email (actual: " << paciente->email << "): ";
    char email[50];
    cin.getline(email, 50);
    if (strlen(email) > 0 && validarEmail(email)) {
        strcpy(paciente->email, email);
    }

    cout << "Alergias: ";
    cin.getline(paciente->alergias, 500);

    cout << "Observaciones: ";
    cin.getline(paciente->observaciones, 500);

    cout << "Datos actualizados correctamente." << endl;
}

void eliminarPacienteInteractivo(Hospital* hospital) {
    cout << "\n--- ELIMINAR PACIENTE ---" << endl;

    char cedula[20];
    cout << "Ingrese la cedula del paciente a eliminar: ";
    cin.getline(cedula, 20);

    Paciente* paciente = buscarPacientePorCedula(hospital, cedula);
    if (!paciente) {
        cout << "Paciente no encontrado." << endl;
        return;
    }

    cout << "Esta seguro de eliminar a " << paciente->nombre << " " << paciente->apellido << "? (S/N): ";
    char confirmacion;
    cin >> confirmacion;
    limpiarBuffer();

    if (toupper(confirmacion) == 'S') {
        if (eliminarPaciente(hospital, paciente->id)) {
            cout << "Paciente eliminado correctamente." << endl;
        } else {
            cout << "Error al eliminar el paciente." << endl;
        }
    } else {
        cout << "Operacion cancelada." << endl;
    }
}

void gestionarPacientes(Hospital* hospital) {
    int opcion;

    do {
        mostrarMenuPacientes();
        cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
            case 1:
                registrarPaciente(hospital);
                break;
            case 2:
                buscarPacienteCedula(hospital);
                break;
            case 3:
                buscarPacienteNombre(hospital);
                break;
            case 4:
                verHistorialPaciente(hospital);
                break;
            case 5:
                actualizarPacienteInteractivo(hospital);
                break;
            case 6:
                listarPacientes(hospital);
                break;
            case 7:
                eliminarPacienteInteractivo(hospital);
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