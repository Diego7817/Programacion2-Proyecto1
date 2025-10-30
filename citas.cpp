#include "hospital.h"
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;

// Agendar cita
Cita* agendarCita(Hospital* hospital, int idPaciente, int idDoctor,
                  const char* fecha, const char* hora, const char* motivo) {
    // Validar paciente
    Paciente* paciente = buscarPacientePorId(hospital, idPaciente);
    if (!paciente) {
        cout << "Error: Paciente no encontrado." << endl;
        return nullptr;
    }
    
    // Validar doctor
    Doctor* doctor = buscarDoctorPorId(hospital, idDoctor);
    if (!doctor) {
        cout << "Error: Doctor no encontrado." << endl;
        return nullptr;
    }
    
    // Validar fecha y hora
    if (!validarFecha(fecha)) {
        cout << "Error: Formato de fecha inválido (YYYY-MM-DD)." << endl;
        return nullptr;
    }
    
    if (!validarHora(hora)) {
        cout << "Error: Formato de hora inválido (HH:MM)." << endl;
        return nullptr;
    }
    
    // Verificar disponibilidad
    if (!verificarDisponibilidad(hospital, idDoctor, fecha, hora)) {
        cout << "Error: El doctor no está disponible en esa fecha y hora." << endl;
        return nullptr;
    }
    
    // Redimensionar si es necesario
    if (hospital->cantidadCitas >= hospital->capacidadCitas) {
        redimensionarArrayCitas(hospital);
    }
    
    // Crear cita
    Cita* nuevaCita = &hospital->citas[hospital->cantidadCitas];
    nuevaCita->id = hospital->siguienteIdCita++;
    nuevaCita->idPaciente = idPaciente;
    nuevaCita->idDoctor = idDoctor;
    strcpy(nuevaCita->fecha, fecha);
    strcpy(nuevaCita->hora, hora);
    strcpy(nuevaCita->motivo, motivo);
    strcpy(nuevaCita->estado, "Agendada");
    strcpy(nuevaCita->observaciones, "");
    nuevaCita->atendida = false;
    
    hospital->cantidadCitas++;
    
    // Agregar a arrays de paciente y doctor
    if (paciente->cantidadCitas >= paciente->capacidadCitas) {
        int nuevaCap = paciente->capacidadCitas * 2;
        int* nuevoArray = new int[nuevaCap];
        for (int i = 0; i < paciente->cantidadCitas; i++) {
            nuevoArray[i] = paciente->citasAgendadas[i];
        }
        delete[] paciente->citasAgendadas;
        paciente->citasAgendadas = nuevoArray;
        paciente->capacidadCitas = nuevaCap;
    }
    paciente->citasAgendadas[paciente->cantidadCitas++] = nuevaCita->id;
    
    if (doctor->cantidadCitas >= doctor->capacidadCitas) {
        int nuevaCap = doctor->capacidadCitas * 2;
        int* nuevoArray = new int[nuevaCap];
        for (int i = 0; i < doctor->cantidadCitas; i++) {
            nuevoArray[i] = doctor->citasAgendadas[i];
        }
        delete[] doctor->citasAgendadas;
        doctor->citasAgendadas = nuevoArray;
        doctor->capacidadCitas = nuevaCap;
    }
    doctor->citasAgendadas[doctor->cantidadCitas++] = nuevaCita->id;
    
    cout << "Cita agendada exitosamente. ID: " << nuevaCita->id << endl;
    return nuevaCita;
}

// Cancelar cita
bool cancelarCita(Hospital* hospital, int idCita) {
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].id == idCita) {
            strcpy(hospital->citas[i].estado, "Cancelada");
            cout << "Cita cancelada correctamente." << endl;
            return true;
        }
    }
    cout << "Cita no encontrada." << endl;
    return false;
}

// Atender cita
bool atenderCita(Hospital* hospital, int idCita, const char* diagnostico,
                 const char* tratamiento, const char* medicamentos) {
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        Cita* cita = &hospital->citas[i];
        if (cita->id == idCita && strcmp(cita->estado, "Agendada") == 0) {
            // Cambiar estado de cita
            strcpy(cita->estado, "Atendida");
            cita->atendida = true;
            
            // Buscar paciente
            Paciente* paciente = buscarPacientePorId(hospital, cita->idPaciente);
            if (!paciente) {
                cout << "Error: Paciente no encontrado." << endl;
                return false;
            }
            
            // Buscar doctor
            Doctor* doctor = buscarDoctorPorId(hospital, cita->idDoctor);
            if (!doctor) {
                cout << "Error: Doctor no encontrado." << endl;
                return false;
            }
            
            // Crear historial médico
            HistorialMedico nuevaConsulta;
            nuevaConsulta.idConsulta = hospital->siguienteIdConsulta++;
            strcpy(nuevaConsulta.fecha, cita->fecha);
            strcpy(nuevaConsulta.hora, cita->hora);
            strcpy(nuevaConsulta.diagnostico, diagnostico);
            strcpy(nuevaConsulta.tratamiento, tratamiento);
            strcpy(nuevaConsulta.medicamentos, medicamentos);
            nuevaConsulta.idDoctor = cita->idDoctor;
            nuevaConsulta.costo = doctor->costoConsulta;
            
            // Agregar al historial
            agregarConsultaAlHistorial(paciente, nuevaConsulta);
            
            cout << "Cita atendida y agregada al historial médico." << endl;
            return true;
        }
    }
    cout << "Cita no encontrada o ya fue atendida/cancelada." << endl;
    return false;
}

// Obtener citas de paciente
Cita** obtenerCitasDePaciente(Hospital* hospital, int idPaciente, int* cantidad) {
    *cantidad = 0;
    
    // Contar citas del paciente
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].idPaciente == idPaciente) {
            (*cantidad)++;
        }
    }
    
    if (*cantidad == 0) return nullptr;
    
    Cita** resultados = new Cita*[*cantidad];
    int index = 0;
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].idPaciente == idPaciente) {
            resultados[index++] = &hospital->citas[i];
        }
    }
    
    return resultados;
}

// Obtener citas de doctor
Cita** obtenerCitasDeDoctor(Hospital* hospital, int idDoctor, int* cantidad) {
    *cantidad = 0;
    
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].idDoctor == idDoctor) {
            (*cantidad)++;
        }
    }
    
    if (*cantidad == 0) return nullptr;
    
    Cita** resultados = new Cita*[*cantidad];
    int index = 0;
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].idDoctor == idDoctor) {
            resultados[index++] = &hospital->citas[i];
        }
    }
    
    return resultados;
}

// Obtener citas por fecha
Cita** obtenerCitasPorFecha(Hospital* hospital, const char* fecha, int* cantidad) {
    *cantidad = 0;
    
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (strcmp(hospital->citas[i].fecha, fecha) == 0) {
            (*cantidad)++;
        }
    }
    
    if (*cantidad == 0) return nullptr;
    
    Cita** resultados = new Cita*[*cantidad];
    int index = 0;
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (strcmp(hospital->citas[i].fecha, fecha) == 0) {
            resultados[index++] = &hospital->citas[i];
        }
    }
    
    return resultados;
}

// Listar citas pendientes
void listarCitasPendientes(Hospital* hospital) {
    int pendientes = 0;
    
    cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                           CITAS PENDIENTES                                   ║" << endl;
    cout << "╠═════╦════════════╦════════╦═════╦═════╦══════════════════════════╦══════════╣" << endl;
    cout << "║ ID  ║ FECHA      ║ HORA   ║ PAC ║ DOC ║ MOTIVO                   ║ ESTADO   ║" << endl;
    cout << "╠═════╬════════════╬════════╬═════╬═════╬══════════════════════════╬══════════╣" << endl;
    
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        Cita* c = &hospital->citas[i];
        if (strcmp(c->estado, "Agendada") == 0) {
            pendientes++;
            
            string motivo = c->motivo;
            if (motivo.length() > 24) {
                motivo = motivo.substr(0, 21) + "...";
            }
            
            cout << "║ " << setw(3) << c->id << " ║ "
                 << setw(10) << c->fecha << " ║ "
                 << setw(6) << c->hora << " ║ "
                 << setw(3) << c->idPaciente << " ║ "
                 << setw(3) << c->idDoctor << " ║ "
                 << setw(24) << left << motivo << " ║ "
                 << setw(8) << c->estado << "║" << endl;
        }
    }
    
    cout << "╚═════╩════════════╩════════╩═════╩═════╩══════════════════════════╩══════════╝" << endl;
    cout << "Total: " << pendientes << " citas pendientes" << endl;
}

// Verificar disponibilidad
bool verificarDisponibilidad(Hospital* hospital, int idDoctor, const char* fecha, const char* hora) {
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        Cita* cita = &hospital->citas[i];
        if (cita->idDoctor == idDoctor && 
            strcmp(cita->fecha, fecha) == 0 && 
            strcmp(cita->hora, hora) == 0 &&
            strcmp(cita->estado, "Agendada") == 0) {
            return false; // Ya tiene cita a esa hora
        }
    }
    return true;
}