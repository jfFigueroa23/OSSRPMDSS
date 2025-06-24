# CODIGO HECHO POR JOSE EDUARDO QUINTANA CASTORENA Y NAVARRO COSIO LEONARDO ALEJANDRO
from fastapi import FastAPI, HTTPException
import subprocess
import csv

from pydantic import BaseModel
from starlette.middleware.cors import CORSMiddleware

app = FastAPI()


app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # Reemplaza esto con el origen de la aplicacion Angular
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

class TopsisInput(BaseModel):
    attributes: list
    candidates: list
    raw_data: list
    weights: list
    benefit_attributes: list


def json_to_csv(data, filename):
    attributes = data["attributes"]
    candidates = data["candidates"]
    raw_data = data["raw_data"]
    weights = data["weights"]
    benefit_attributes = data["benefit_attributes"]

    with open(filename, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(attributes)
        writer.writerow(candidates)
        writer.writerow(weights)
        writer.writerow(benefit_attributes)
        for row in raw_data:
            writer.writerow(row)

@app.post("/topsis")
async def run_topsis(data: TopsisInput):
    filename = "datos1.csv"
    try:
        json_to_csv(data.dict(), filename)
        # Ejecutar el ejecutable y capturar la salida
        try:
            result = subprocess.run(["topsis.exe"], capture_output=True, text=True)
            # Comprobar si hubo errores al ejecutar el comando
            if result.returncode != 0:
                return {"error": f"El comando devolvió un código de salida {result.returncode}"}
            else:
                # Devolver la salida de la consola como respuesta
                return {"output": result.stdout}
        except FileNotFoundError:
            return {"error": "No se encontró el archivo ejecutable"}
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="127.0.0.1", port=8000)

