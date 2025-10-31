Sistema de Gestión Hospitalaria - Programación 2
📋 Descripción
Sistema completo de gestión hospitalaria desarrollado en C++ que administra pacientes, doctores, citas médicas e historiales clínicos. Demuestra dominio avanzado de punteros, memoria dinámica y estructuras en C++.

🚀 Características Principales
✅ Módulos Implementados
Gestión de Pacientes: CRUD completo con validaciones

Gestión de Doctores: Registro y asignación de especialidades

Sistema de Citas: Agendamiento, cancelación y atención

Historial Médico: Registro completo de consultas

Memoria Dinámica: Arrays que crecen automáticamente

🛠️ Tecnologías Utilizadas
Lenguaje: C++ (estándar C++11)

Bibliotecas: <iostream>, <cstring>, <ctime>, <iomanip>

Compilador: GCC, Clang o MSVC compatible

Caracteres: 100% ASCII compatible

🎯 Funcionalidades por Módulo
1. Gestión de Pacientes
✅ Registrar nuevo paciente

✅ Buscar por cédula o nombre

✅ Actualizar datos personales

✅ Ver historial médico completo

✅ Listar todos los pacientes

✅ Eliminar pacientes

2. Gestión de Doctores
✅ Registrar doctores con especialidad

✅ Buscar por ID o especialidad

✅ Asignar pacientes a doctores

✅ Listar pacientes asignados

✅ Gestión de disponibilidad

3. Sistema de Citas
✅ Agendar citas con validación de horarios

✅ Cancelar citas

✅ Atender citas (crea historial automático)

✅ Consultar citas por paciente, doctor o fecha

✅ Ver citas pendientes

4. Historial Médico
✅ Registro automático de consultas

✅ Diagnóstico, tratamiento y medicamentos

✅ Costo automático basado en doctor

✅ Visualización en formato tabular

💾 Gestión de Memoria
Características Avanzadas:
Arrays dinámicos que crecen automáticamente

Redimensionamiento cuando se llena capacidad

Cleanup completo sin memory leaks

Deep copy de strings y estructuras

Capacidades Iniciales:
Pacientes: 10 (se duplica al llenarse)

Doctores: 10 (se duplica al llenarse)

Citas: 20 (se duplica al llenarse)

Historial por paciente: 5 consultas (se duplica)

🧪 Datos de Prueba
El sistema incluye datos de ejemplo:

3 pacientes pre-registrados

3 doctores con diferentes especialidades

Listo para pruebas inmediatas

📊 Validaciones Implementadas
Entrada de Datos:
✅ Formato fecha (YYYY-MM-DD)

✅ Formato hora (HH:MM)

✅ Edad (0-120 años)

✅ Cédula única

✅ Email básico

✅ Sexo (M/F)

Lógica de Negocio:
✅ Cédulas únicas para pacientes y doctores

✅ Verificación de disponibilidad de doctores

✅ Evitar duplicados en asignaciones

✅ Estados de citas (Agendada, Atendida, Cancelada)

🎮 Uso del Sistema
Flujo Típico:
Registrar pacientes y doctores

Agendar citas verificando disponibilidad

Atender citas (genera historial automático)

Consultar historiales médicos

Gestionar asignaciones paciente-doctor

Navegación:
Menú principal con 4 opciones

Submenús especializados por módulo

Validación de entrada en cada paso

Confirmaciones para operaciones destructivas

🔍 Búsquedas Disponibles
Pacientes:
Por cédula (exacta)

Por nombre/apellido (parcial, case-insensitive)

Doctores:
Por ID

Por especialidad (parcial, case-insensitive)

Citas:
Por paciente

Por doctor

Por fecha

Pendientes (filtrado por estado)

📝 Formato de Salida
Tablas Estructuradas:
Alineación profesional con <iomanip>

Headers descriptivos

Separadores visuales

Información condensada pero completa
