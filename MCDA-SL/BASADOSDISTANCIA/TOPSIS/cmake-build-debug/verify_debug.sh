#!/bin/bash

# Script de verificación de configuración de depuración para TOPSIS
# Ejecutar: ./verify_debug.sh

echo "=== Verificación de Configuración de Depuración TOPSIS ==="
echo

# Verificar que estamos en el directorio correcto
if [ ! -f "TOPSIS" ]; then
    echo "❌ Error: Ejecutable TOPSIS no encontrado. Ejecutar desde cmake-build-debug/"
    exit 1
fi

echo "✅ Ejecutable TOPSIS encontrado"

# Verificar símbolos de depuración
echo
echo "🔍 Verificando símbolos de depuración..."
if file TOPSIS | grep -q "with debug_info"; then
    echo "✅ Símbolos de depuración presentes"
else
    echo "❌ Faltan símbolos de depuración"
fi

# Verificar que no está stripped
if file TOPSIS | grep -q "not stripped"; then
    echo "✅ Ejecutable no está stripped (tiene símbolos)"
else
    echo "❌ Ejecutable está stripped (sin símbolos de depuración)"
fi

# Verificar secciones de debug
echo
echo "🔍 Verificando secciones de debug..."
DEBUG_SECTIONS=$(objdump -h TOPSIS | grep -c debug)
if [ $DEBUG_SECTIONS -gt 0 ]; then
    echo "✅ Encontradas $DEBUG_SECTIONS secciones de debug"
    objdump -h TOPSIS | grep debug | head -3
else
    echo "❌ No se encontraron secciones de debug"
fi

# Verificar build type
echo
echo "🔍 Verificando tipo de compilación..."
if grep -q "CMAKE_BUILD_TYPE.*Debug" CMakeCache.txt 2>/dev/null; then
    echo "✅ Compilado en modo Debug"
else
    echo "⚠️  No se pudo verificar modo Debug (CMakeCache.txt no encontrado o no es Debug)"
fi

# Probar ejecución básica
echo
echo "🔍 Probando ejecución del programa..."
if timeout 5 ./TOPSIS >/dev/null 2>&1; then
    echo "✅ Programa ejecuta correctamente"
else
    echo "❌ Error en ejecución del programa"
fi

echo
echo "=== Recomendaciones para Breakpoints ==="
echo "• En CLion/IntelliJ: Asegurar 'Debug' build configuration"
echo "• En VSCode: Usar configuración de debug con gdb"
echo "• Breakpoints sugeridos:"
echo "  - main() en main.cpp"
echo "  - TOPSIS::procesarDatos() en TOPSIS.cpp"
echo "  - TOPSIS::calculateSeparationMeasures() en TOPSIS.cpp"
echo
echo "=== Comandos GDB útiles ==="
echo "gdb ./TOPSIS"
echo "break main"
echo "break TOPSIS::procesarDatos"
echo "run"
echo
echo "Ver debug_config.txt para más información"
