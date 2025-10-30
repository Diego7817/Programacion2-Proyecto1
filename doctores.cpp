#include "hospital.h"
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// Función auxiliar para búsqueda case-insensitive
bool contieneEspecialidadCaseInsensitive(const char* especialidad, const char* busqueda) {
    if (!especialidad || !busqueda) return false;
    
    string espStr(especialidad);
    string busqStr(busqueda);
    
    for (char& c : espStr) c = tolower(c);
    for (char& c : busqStr) c = tolower(c);
    
    return espStr.find(busqStr) != string::npos;
}

// Crear doctor
Doctor* crearDoctor(Hospital* hospital, const char* nombre, const char* apellido,
                   const char* cedula, const char* especialidad, int aniosExperiencia,
                   float costoConsulta) {
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (strcmp(hospital->doctores[i].cedula, cedula) == 0) {
            cout << "Error: Ya existe un doctor con la cédula " << cedula << endl;
            return nullptr;
        }
    }
    
    if (aniosExperiencia < 0) {
        cout << "Error: Los años de experiencia no pueden ser negativos" << endl;
        return nullptr;
    }
    
    if (costoConsulta <= 0) {
        cout << "Error: El costo de consulta debe ser mayor a 0" << endl;
        return nullptr;
    }
    
    if (hospital->cantidadDoctores >= hospital->capacidadDoctores) {
        redimensionarArrayDoctores(hospital);
    }
    
    Doctor* nuevoDoctor = &hospital->doctores[hospital->cantidadDoctores];
    
    nuevoDoctor->id = hospital->siguienteIdDoctor++;
    strcpy(nuevoDoctor->nombre, nombre);
    strcpy(nuevoDoctor->apellido, apellido);
    strcpy(nuevoDoctor->cedula, cedula);
    strcpy(nuevoDoctor->especialidad, especialidad);
    nuevoDoctor->aniosExperiencia = aniosExperiencia;
    nuevoDoctor->costoConsulta = costoConsulta;
    
    nuevoDoctor->capacidadPacientes = 5;
    nuevoDoctor->cantidadPacientes = 0;
    nuevoDoctor->pacientesAsignados = new int[nuevoDoctor->capacidadPacientes];
    
    nuevoDoctor->capacidadCitas = 10;
    nuevoDoctor->cantidadCitas = 0;
    nuevoDoctor->citasAgendadas = new int[nuevoDoctor->capacidadCitas];
    
    strcpy(nuevoDoctor->horarioAtencion, "Lun-Vie 8:00-16:00");
    strcpy(nuevoDoctor->telefono, "");
    strcpy(nuevoDoctor->email, "");
    
    nuevoDoctor->disponible = true;
    
    hospital->cantidadDoctores++;
    
    cout << "Doctor creado exitosamente. ID: " << nuevoDoctor->id << endl;
    return nuevoDoctor;
}

// Buscar doctor por ID
Doctor* buscarDoctorPorId(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (hospital->doctores[i].id == id && hospital->doctores[i].disponible) {
            return &hospital->doctores[i];
        }
    }
    return nullptr;
}

// Buscar doctores por especialidad
Doctor** buscarDoctoresPorEspecialidad(Hospital* hospital, const char* especialidad, int* cantidad) {
    *cantidad = 0;
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (hospital->doctores[i].disponible && 
            contieneEspecialidadCaseInsensitive(hospital->doctores[i].especialidad, especialidad)) {
            (*cantidad)++;
        }
    }
    
    if (*cantidad == 0) return nullptr;
    
    Doctor** resultados = new Doctor*[*cantidad];
    int index = 0;
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (hospital->doctores[i].disponible && 
            contieneEspecialidadCaseInsensitive(hospital->doctores[i].especialidad, especialidad)) {
            resultados[index++] = &hospital->doctores[i];
        }
    }
    
    return resultados;
}

// Asignar paciente a doctor
bool asignarPacienteADoctor(Doctor* doctor, int idPaciente) {
    for (int i = 0; i < doctor->cantidadPacientes; i++) {
        if (doctor->pacientesAsignados[i] == idPaciente) {
            cout << "El paciente ya está asignado a este doctor." << endl;
            return false;
        }
    }
    
    if (doctor->cantidadPacientes >= doctor->capacidadPacientes) {
        // Redimensionar array
        int nuevaCapacidad = doctor->capacidadPacientes * 2;
        int* nuevoArray = new int[nuevaCapacidad];
        
        for (int i = 0; i < doctor->cantidadPacientes; i++) {
            nuevoArray[i] = doctor->pacientesAsignados[i];
        }
        
        delete[] doctor->pacientesAsignados;
        doctor->pacientesAsignados = nuevoArray;
        doctor->capacidadPacientes = nuevaCapacidad;
    }
    
    doctor->pacientesAsignados[doctor->cantidadPacientes] = idPaciente;
    doctor->cantidadPacientes++;
    
    cout << "Paciente asignado correctamente al doctor." << endl;
    return true;
}

// Remover paciente de doctor
bool removerPacienteDeDoctor(Doctor* doctor, int idPaciente) {
    for (int i = 0; i < doctor->cantidadPacientes; i++) {
        if (doctor->pacientesAsignados[i] == idPaciente) {
            for (int j = i; j < doctor->cantidadPacientes - 1; j++) {
                doctor->pacientesAsignados[j] = doctor->pacientesAsignados[j + 1];
            }
            doctor->cantidadPacientes--;
            cout << "Paciente removido del doctor." << endl;
            return true;
        }
    }
    cout << "Paciente no encontrado en la lista del doctor." << endl;
    return false;
}

// Listar pacientes de doctor
void listarPacientesDeDoctor(Hospital* hospital, int idDoctor) {
    Doctor* doctor = buscarDoctorPorId(hospital, idDoctor);
    if (!doctor) {
        cout << "Doctor no encontrado." << endl;
        return;
    }
    
    if (doctor->cantidadPacientes == 0) {
        cout << "El doctor no tiene pacientes asignados." << endl;
        return;
    }
    
    cout << "\n╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║         PACIENTES ASIGNADOS - Dr. " << setw(25) << left 
         << (string(doctor->nombre) + " " + doctor->apellido).substr(0, 25) << " ║" << endl;
    cout << "╠═════╦═════════════════════╦══════════════╦══════╦════════╣" << endl;
    cout << "║ ID  ║ NOMBRE COMPLETO     ║ CÉDULA       ║ EDAD ║ SEXO   ║" << endl;
    cout << "╠═════╬═════════════════════╬══════════════╬══════╬════════╣" << endl;
    
    for (int i = 0; i < doctor->cantidadPacientes; i++) {
        Paciente* paciente = buscarPacientePorId(hospital, doctor->pacientesAsignados[i]);
        if (paciente && paciente->activo) {
            string nombreCompleto = string(paciente->nombre) + " " + paciente->apellido;
            if (nombreCompleto.length() > 19) {
                nombreCompleto = nombreCompleto.substr(0, 16) + "...";
            }
            
            cout << "║ " << setw(3) << paciente->id << " ║ "
                 << setw(19) << left << nombreCompleto << " ║ "
                 << setw(12) << paciente->cedula << " ║ "
                 << setw(4) << paciente->edad << " ║ "
                 << setw(6) << paciente->sexo << "║" << endl;
        }
    }
    cout << "╚═════╩═════════════════════╩══════════════╩══════╩════════╝" << endl;
    cout << "Total: " << doctor->cantidadPacientes << " pacientes" << endl;
}

// Listar doctores
void listarDoctores(Hospital* hospital) {
    if (hospital->cantidadDoctores == 0) {
        cout << "No hay doctores registrados." << endl;
        return;
    }
    
    cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                            LISTA DE DOCTORES                                 ║" << endl;
    cout << "╠═════╦═════════════════════╦═════════════════════╦══════╦════════╦════════════╣" << endl;
    cout << "║ ID  ║ NOMBRE COMPLETO     ║ ESPECIALIDAD        ║ AÑOS ║ COSTO  ║ PACIENTES  ║" << endl;
    cout << "╠═════╬═════════════════════╬═════════════════════╬══════╬════════╬════════════╣" << endl;
    
    int activos = 0;
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        Doctor* d = &hospital->doctores[i];
        if (d->disponible) {
            activos++;
            string nombreCompleto = string(d->nombre) + " " + d->apellido;
            if (nombreCompleto.length() > 19) {
                nombreCompleto = nombreCompleto.substr(0, 16) + "...";
            }
            
            string especialidad = d->especialidad;
            if (especialidad.length() > 19) {
                especialidad = especialidad.substr(0, 16) + "...";
            }
            
            cout << "║ " << setw(3) << d->id << " ║ "
                 << setw(19) << left << nombreCompleto << " ║ "
                 << setw(19) << especialidad << " ║ "
                 << setw(4) << d->aniosExperiencia << " ║ $"
                 << setw(5) << fixed << setprecision(2) << d->costoConsulta << " ║ "
                 << setw(8) << d->cantidadPacientes << "║" << endl;
        }
    }
    
    cout << "╚═════╩═════════════════════╩═════════════════════╩══════╩════════╩════════════╝" << endl;
    cout << "Total: " << activos << " doctores" << endl;
}

// Eliminar doctor
bool eliminarDoctor(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (hospital->doctores[i].id == id && hospital->doctores[i].disponible) {
            hospital->doctores[i].disponible = false;
            
            delete[] hospital->doctores[i].pacientesAsignados;
            delete[] hospital->doctores[i].citasAgendadas;
            
            cout << "Doctor eliminado correctamente." << endl;
            return true;
        }
    }
    return false;
}