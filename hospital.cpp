#include "hospital.h"

// Inicializar hospital
Hospital* inicializarHospital(const char* nombre, const char* direccion, const char* telefono) {
    Hospital* hospital = new Hospital;

    // Copiar informacion básica
    strcpy(hospital->nombre, nombre);
    strcpy(hospital->direccion, direccion);
    strcpy(hospital->telefono, telefono);

    // Inicializar arrays de pacientes
    hospital->capacidadPacientes = 10;
    hospital->cantidadPacientes = 0;
    hospital->pacientes = new Paciente[hospital->capacidadPacientes];

    // Inicializar arrays de doctores
    hospital->capacidadDoctores = 10;
    hospital->cantidadDoctores = 0;
    hospital->doctores = new Doctor[hospital->capacidadDoctores];

    // Inicializar arrays de citas
    hospital->capacidadCitas = 20;
    hospital->cantidadCitas = 0;
    hospital->citas = new Cita[hospital->capacidadCitas];

    // Inicializar contadores
    hospital->siguienteIdPaciente = 1;
    hospital->siguienteIdDoctor = 1;
    hospital->siguienteIdCita = 1;
    hospital->siguienteIdConsulta = 1;

    return hospital;
}

// Liberar memoria
void destruirHospital(Hospital* hospital) {
    if (!hospital) return;

    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        Paciente* paciente = &hospital->pacientes[i];
        delete[] paciente->historial;
        delete[] paciente->citasAgendadas;
    }
    delete[] hospital->pacientes;

    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        Doctor* doctor = &hospital->doctores[i];
        delete[] doctor->pacientesAsignados;
        delete[] doctor->citasAgendadas;
    }
    delete[] hospital->doctores;

    delete[] hospital->citas;

    delete hospital;
}

char* copiarString(const char* origen) {
    if (!origen) return nullptr;

    int longitud = strlen(origen);
    char* copia = new char[longitud + 1];
    strcpy(copia, origen);
    return copia;
}

// Validar fecha en formato YYYY-MM-DD
bool validarFecha(const char* fecha) {
    if (strlen(fecha) != 10) return false;
    if (fecha[4] != '-' || fecha[7] != '-') return false;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (fecha[i] < '0' || fecha[i] > '9') return false;
    }

    // Extraer año, mes y día
    int año = (fecha[0] - '0') * 1000 + (fecha[1] - '0') * 100 +
              (fecha[2] - '0') * 10 + (fecha[3] - '0');
    int mes = (fecha[5] - '0') * 10 + (fecha[6] - '0');
    int dia = (fecha[8] - '0') * 10 + (fecha[9] - '0');

    // Validar mes
    if (mes < 1 || mes > 12) return false;

    // Validar dia según mes
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Año bisiesto
    if (mes == 2 && ((año % 4 == 0 && año % 100 != 0) || (año % 400 == 0))) {
        diasPorMes[1] = 29;
    }

    return (dia >= 1 && dia <= diasPorMes[mes - 1]);
}

// Validar hora en formato HH:MM
bool validarHora(const char* hora) {
    if (strlen(hora) != 5) return false;
    if (hora[2] != ':') return false;

    for (int i = 0; i < 5; i++) {
        if (i == 2) continue;
        if (hora[i] < '0' || hora[i] > '9') return false;
    }

    int horas = (hora[0] - '0') * 10 + (hora[1] - '0');
    int minutos = (hora[3] - '0') * 10 + (hora[4] - '0');

    return (horas >= 0 && horas <= 23 && minutos >= 0 && minutos <= 59);
}

// Validar cedula
bool validarCedula(const char* cedula) {
    return (cedula && strlen(cedula) > 0 && strlen(cedula) <= 20);
}

// Validar email
bool validarEmail(const char* email) {
    if (!email || strlen(email) == 0) return false;

    bool tieneArroba = false;
    bool tienePunto = false;

    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') tieneArroba = true;
        if (email[i] == '.' && tieneArroba) tienePunto = true;
    }

    return (tieneArroba && tienePunto);
}

void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}
