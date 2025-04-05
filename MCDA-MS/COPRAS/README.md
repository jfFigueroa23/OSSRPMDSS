# FastAPI Project

Este proyecto utiliza [FastAPI](https://fastapi.tiangolo.com/) para construir una API rápida y eficiente.

## Requisitos

- Python 3.7 o superior
- `pip` para instalar dependencias

## Instalación

1. Crea y activa un entorno virtual:
    ```bash
    python -m venv venv
    source venv/bin/activate  # En Windows: venv\Scripts\activate
    ```

2. Instala las dependencias:
    ```bash
    pip install fastapi["standard"]
    ```

## Ejecución

1. Inicia el servidor FastAPI:
    ```bash
    uvicorn main:app --reload
    ```


2. Accede a la documentación interactiva:
    - [http://127.0.0.1:8000/docs](http://127.0.0.1:8000/docs) (Swagger UI)

3. Utiliza el proyecto en angular:
    - [http://127.0.0.1:4200]

