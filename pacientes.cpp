#include "hospital.h"

// Redimensionar array de pacientes
void redimensionarArrayPacientes(Hospital* hospital) {
    int nuevaCapacidad = hospital->capacidadPacientes * 2;
    Paciente* nuevoArray = new Paciente[nuevaCapacidad];

    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        nuevoArray[i] = hospital->pacientes[i];
    }

    delete[] hospital->pacientes;
    hospital->pacientes = nuevoArray;
    hospital->capacidadPacientes = nuevaCapacidad;
    
    std::cout << "Array de pacientes redimensionado a capacidad: " << nuevaCapacidad << std::endl;
}

// Crear nuevo paciente
Paciente* crearPaciente(Hospital* hospital, const char* nombre, 
                       const char* apellido, const char* cedula, 
                       int edad, char sexo) {
    // Verificar si la cedula ya existe
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (strcmp(hospital->pacientes[i].cedula, cedula) == 0) {
            std::cout << "Error: Ya existe un paciente con la cédula " << cedula << std::endl;
            return nullptr; // Cédula duplicada
        }
    }
    
    // Validar edad
    if (edad < 0 || edad > 120) {
        std::cout << "Error: La edad debe estar entre 0 y 120 años" << std::endl;
        return nullptr;
    }

    if (hospital->cantidadPacientes >= hospital->capacidadPacientes) {
        redimensionarArrayPacientes(hospital);
    }

    Paciente* nuevoPaciente = &hospital->pacientes[hospital->cantidadPacientes];
    
    // Inicializar datos básicos
    nuevoPaciente->id = hospital->siguienteIdPaciente++;
    strcpy(nuevoPaciente->nombre, nombre);
    strcpy(nuevoPaciente->apellido, apellido);
    strcpy(nuevoPaciente->cedula, cedula);
    nuevoPaciente->edad = edad;
    nuevoPaciente->sexo = sexo;
    
    // Inicializar arrays dinámicos del paciente
    nuevoPaciente->capacidadHistorial = 5;
    nuevoPaciente->cantidadConsultas = 0;
    nuevoPaciente->historial = new HistorialMedico[nuevoPaciente->capacidadHistorial];
    
    nuevoPaciente->capacidadCitas = 5;
    nuevoPaciente->cantidadCitas = 0;
    nuevoPaciente->citasAgendadas = new int[nuevoPaciente->capacidadCitas];
    
    // Inicializar strings vacíos
    strcpy(nuevoPaciente->tipoSangre, "");
    strcpy(nuevoPaciente->telefono, "");
    strcpy(nuevoPaciente->direccion, "");
    strcpy(nuevoPaciente->email, "");
    strcpy(nuevoPaciente->alergias, "");
    strcpy(nuevoPaciente->observaciones, "");
    
    nuevoPaciente->activo = true;
    
    hospital->cantidadPacientes++;
    
    std::cout << "Paciente creado exitosamente. ID: " << nuevoPaciente->id << std::endl;
    return nuevoPaciente;
}

// Buscar paciente por cedula
Paciente* buscarPacientePorCedula(Hospital* hospital, const char* cedula) {
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        // Comparación case-insensitive
        if (strcasecmp(hospital->pacientes[i].cedula, cedula) == 0 && 
            hospital->pacientes[i].activo) {
            return &hospital->pacientes[i];
        }
    }
    return nullptr;
}

// Buscar paciente por ID
Paciente* buscarPacientePorId(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (hospital->pacientes[i].id == id && hospital->pacientes[i].activo) {
            return &hospital->pacientes[i];
        }
    }
    return nullptr;
}