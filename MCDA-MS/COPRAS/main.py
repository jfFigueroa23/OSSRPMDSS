import ctypes
import os
import fastapi
app = fastapi.FastAPI()
from fastapi.middleware.cors import CORSMiddleware
#Agregamos librerias faltantes
#Modificar la ruta para su compilador
os.add_dll_directory(r'C:\msys64\mingw64\bin')
# Cargamos la libreria de copras.dll
lib_path = os.path.join(os.path.dirname(__file__), '..', 'copras.dll')

copras_lib = ctypes.CDLL(lib_path)


# Definimos la funcion para resolver con archivo de texto
copras_lib.resolverText.argtypes = [ctypes.c_char_p]
copras_lib.resolverText.restype = ctypes.POINTER(ctypes.c_float)


# Define la funcion para resolver con matriz
copras_lib.copras.argtypes = [
    ctypes.POINTER(ctypes.POINTER(ctypes.c_float)),
    ctypes.POINTER(ctypes.c_char_p),
    ctypes.POINTER(ctypes.c_float),
    ctypes.c_int,
    ctypes.c_int
]
copras_lib.copras.restype = ctypes.POINTER(ctypes.c_float)

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)
@app.post("/solve")
async def solve(tabla: list[list[float]], beneficio: list[str], pesos: list[float]):
    filas = len(tabla)
    columnas = len(tabla[0])
    print("filas: ", filas)
    print("columnas: ", columnas)
    print("tabla: ", tabla)
    print("beneficio: ", beneficio)
    print("pesos: ", pesos)

    # Convert Python lists to ctypes arrays
    tabla_array = (ctypes.POINTER(ctypes.c_float) * filas)()
    for i in range(filas):
        tabla_array[i] = (ctypes.c_float * columnas)(*tabla[i])

    beneficio_array = (ctypes.c_char_p * columnas)(*map(lambda b: b.encode('utf-8'), beneficio))
    pesos_array = (ctypes.c_float * columnas)(*pesos)

    result = copras_lib.copras(tabla_array, beneficio_array, pesos_array, filas, columnas)

    results = []
    i = 0
    while result[i] >= 0.000000000001:
        results.append(result[i])
        i += 1
    print (results)
    return results

@app.post("/solveText")
async def solvetext(nombre_archivo: str):
    if (CORSMiddleware):
        print("CORSMiddleware")
        print(CORSMiddleware)

    
    nombre_archivo_bytes = nombre_archivo.encode('utf-8')
    result = copras_lib.resolverText(nombre_archivo_bytes)

    results = []
    i = 0
    while result[i] >= 0.00000001:
        results.append(result[i])
        i += 1

    return results
