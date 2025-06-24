import { Component, OnInit, ElementRef, ViewChild  } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Router } from '@angular/router';
import { DomSanitizer, SafeHtml } from '@angular/platform-browser';
import { DataService } from '../servicios/data.service';

interface Cell {
  value: number;
  rowIndex: number;
  colIndex: number;
}

@Component({
  selector: 'app-matriz',
  templateUrl: './matriz.component.html',
  styleUrl: './matriz.component.css'
})
export class MatrizComponent implements OnInit{

  filas: number | null = null;
  columnas: number | null = null;;
  matriz: Cell[][] = [];
  columnasArray: number[] = [];
  pesos: number[] = []; // Array para almacenar los pesos
  nombresFilasIzquierda: string[] = []; // Array para almacenar los nombres de las filas a la izquierda de la matriz
  nombresFilasSuperior: string[] = []; // Array para almacenar los nombres de las filas en la parte superior de la matr
  rawData: number[][] = [];
  outputAPI: string = ''; // Variable para almacenar el output de la API
  outputAPIHtml: SafeHtml = ''; // Variable para almacenar el output de la API con formato HTML

  @ViewChild('inputElements', { static: false }) inputElements: ElementRef[];
  
  constructor(private http:HttpClient, private router: Router, private sanitizer: DomSanitizer, private dataService: DataService, private matrizStateService: DataService) {
    this.inputElements = [];
  }

  ngOnInit(): void {
    this.recuperarEstado();
    
  }

  updateFilas(event: Event): void {
    const value = (event.target as HTMLInputElement).value;
    this.filas = value ? parseInt(value, 10) : null;
  }

  updateColumnas(event: Event): void {
    const value = (event.target as HTMLInputElement).value;
    this.columnas = value ? parseInt(value, 10) : null;
  }

  generarMatriz(): void {
    // Limpia la matriz actual
    this.matriz = [];

    // Valida que se hayan ingresado valores validos
    if (this.filas === null || this.columnas === null || this.filas <= 0 || this.columnas <= 0) {
      console.error('Por favor, ingrese valores válidos para filas y columnas.');
      return;
    }


    // Genera las columnas para los criterios
    this.nombresFilasIzquierda = Array.from(Array(this.filas).keys()).map(i => `A${i + 1}`);

    // Genera las filas de alternativas
    this.nombresFilasSuperior = Array.from(Array(this.columnas).keys()).map(i => `C${i + 1}`);

    // Genera la matriz
    for (let i = 0; i < this.filas; i++) {
        const fila: Cell[] = [];
        for (let j = 0; j < this.columnas; j++) {
            fila.push({ value: 0, rowIndex: i, colIndex: j }); // Aqui los inicializo dede 0 toda la matriz
        }
        this.matriz.push(fila);
    }

    // Genero el array de columnas
    this.columnasArray = Array.from(Array(this.columnas).keys()).map(i => i + 1);

    // Inicializo los pesos por defecto
    this.pesos = Array.from(Array(this.columnas).keys()).map(i => 1);

    this.guardarEstado();

    // Aqui Enfoco el primer campo de entrada cuando genero la matriz
    if (this.inputElements.length > 0) {
        this.inputElements[0].nativeElement.focus();
    }
  }

  agregarFila(): void {
    const nuevaFila: Cell[] = [];
    for (let j = 0; j < (this.columnas || 0); j++) {
      nuevaFila.push({ value: 0, rowIndex: this.matriz.length, colIndex: j });
    }
    this.matriz.push(nuevaFila);
    this.filas = this.matriz.length;

    
    this.nombresFilasIzquierda.push(`A${this.filas}`);

    this.guardarEstado();
  }

  agregarColumna(): void {
    this.matriz.forEach(fila => {
      fila.push({ value: 0, rowIndex: fila[0].rowIndex, colIndex: fila.length });
    });
    this.columnas = this.matriz[0].length;

    
    this.nombresFilasSuperior.push(`C${this.columnas}`);
    this.columnasArray = Array.from(Array(this.columnas).keys()).map(i => i + 1);

    
    this.pesos.push(1);

    this.guardarEstado();
  }

  // Limpio los valores de la matriz tanto filas y columnas
  eliminarMatriz(): void {
    
    this.matriz = [];
    this.filas = null;
    this.columnas = null;
    this.nombresFilasIzquierda = [];
    this.nombresFilasSuperior = [];
    this.columnasArray = [];
    this.pesos = [];
  
    this.guardarEstado();
  }
  

  
  realizarCalculoTopsis(): void {

    // Aqui verifico si la matriz ha sido generada
    if (this.matriz.length === 0) {
      this.mostrarToastError('Error: Genera la matriz antes de realizar el cálculo.');
      return;
    }

    
    const raw_data = this.matriz.map(row => row.map(cell => cell.value));
    // Construir el objeto JSON con los datos
    const data = {
      weights: this.pesos,
      attributes: this.nombresFilasSuperior,
      candidates: this.nombresFilasIzquierda,
      raw_data: raw_data,
      benefit_attributes: [0, 0, 0, 0, 0]
    };

    console.log('JSON enviado a la API:', data);
    console.log('JSON esperado por la API:', {
      "attributes": ["C1", "C2"],
      "candidates": ["A1", "A2"],
      "raw_data": [
        [1, 1],
        [9, 9]
      ],
      "weights": [1, 1],
      "benefit_attributes": [0, 0, 0, 0, 0]
    });
  

    // Realizo la solicitud POST a la API
    this.http.post<any>('http://localhost:8000/topsis', data).subscribe(
    (response) => {
      console.log('Respuesta de la API:', response);
      this.outputAPI = response.output;
      this.outputAPIHtml = this.sanitizer.bypassSecurityTrustHtml(this.outputAPI);
      this.dataService.setData(this.outputAPI);  // Aqui guardo los datos en el servicio
      this.router.navigate(['/resultados']);
    },
    (error) => {
      console.error('Error al realizar la solicitud:', error);

      if (error.error && error.error.result) {
        console.error('Salida del proceso:', error.error.output);
      }
    }
  );
  }

  mostrarToastError(mensaje: string): void {
    const toastElement = document.getElementById('errorToast');
    if (toastElement) {
      const toastBody = toastElement.querySelector('.toast-body');
      if (toastBody) {
        toastBody.textContent = mensaje;
      }
  
      // Agrego la clase 'show' para mostrar el toast
      toastElement.classList.add('show');
  
      // Oculto el toast
      const closeButton = toastElement.querySelector('.btn-close');
      if (closeButton) {
        closeButton.addEventListener('click', () => {
          toastElement.classList.remove('show');
        });
      }
  
      setTimeout(() => {
        toastElement.classList.remove('show');
      }, 3000); // 3000ms = 3 segundos
    }
  }
  

  actualizarValor(event: Event, cell: Cell): void {
    const valor = (event.target as HTMLInputElement).value;
    const newValue = parseFloat(valor);
    if (!isNaN(newValue)) {
      cell.value = newValue;
    }
  }


  //Metodos para guardar el estado de la matriz una ves ingresado los datos que pone el usuario

  private guardarEstado(): void {
    this.matrizStateService.setFilas(this.filas);
    this.matrizStateService.setColumnas(this.columnas);
    this.matrizStateService.setMatriz(this.matriz);
    this.matrizStateService.setPesos(this.pesos);
    this.matrizStateService.setNombresFilasIzquierda(this.nombresFilasIzquierda);
    this.matrizStateService.setNombresFilasSuperior(this.nombresFilasSuperior);
  }

  private recuperarEstado(): void {
    this.filas = this.matrizStateService.getFilas();
    this.columnas = this.matrizStateService.getColumnas();
    this.matriz = this.matrizStateService.getMatriz();
    this.pesos = this.matrizStateService.getPesos();
    this.nombresFilasIzquierda = this.matrizStateService.getNombresFilasIzquierda();
    this.nombresFilasSuperior = this.matrizStateService.getNombresFilasSuperior();

    if (this.filas !== null && this.columnas !== null) {
      this.columnasArray = Array.from(Array(this.columnas).keys()).map(i => i + 1);
    }
  }


  // Convierto los datos de la matriz y los criterios en formato CSV
  exportToCSV(): void {
    let csvContent = "data:text/csv;charset=utf-8,";
    csvContent += "Pesos," + this.pesos.join(",") + "\n";
    csvContent += "Criterios," + this.nombresFilasSuperior.join(",") + "\n";
    csvContent += "Filas," + this.nombresFilasIzquierda.join(",") + "\n";
    this.matriz.forEach(row => {
      csvContent += row.map(cell => cell.value).join(",") + "\n";
    });
  
    // Creo un enlace temporal para descargar el archivo CSV
    const encodedUri = encodeURI(csvContent);
    const link = document.createElement("a");
    link.setAttribute("href", encodedUri);
    link.setAttribute("download", "matriz.csv");
    document.body.appendChild(link);
  
    // Simulo un clic en el enlace para iniciar la descarga
    link.click();
  }

  importFromCSV(event: any): void {
    const file = event.target.files[0];
    const reader = new FileReader();

    reader.onload = (e: any) => {
        const contents = e.target.result;
        const lines = contents.split("\n").filter((line: string) => line.trim() !== "");

        // Limpio la matriz y los criterios actuales
        this.matriz = [];
        this.nombresFilasSuperior = [];
        this.nombresFilasIzquierda = [];
        this.pesos = [];

        // Leo los datos del archivo CSV
        lines.forEach((line: string, rowIndex: number) => {
            const cells = line.split(",");
            if (rowIndex === 0) {
                // Leo los pesos de la primera linea
                this.pesos = cells.slice(1).map(parseFloat);
            } else if (rowIndex === 1) {
                // Leo los nombres de los criterios de la segunda linea
                this.nombresFilasSuperior = cells.slice(1);
            } else if (rowIndex === 2) {
                // Leo los nombres de las filas de la tercera linea
                this.nombresFilasIzquierda = cells.slice(1);
            } else if (rowIndex >= 3 && cells.length > 1) {
                // Leo los valores de las celdas solo si hay mas de una celda en la fila
                const row = cells.map((value: string, colIndex: number) => ({
                    value: parseFloat(value),
                    rowIndex: rowIndex - 3,
                    colIndex: colIndex
                }));
                this.matriz.push(row);
            }
        });

        // Actualizo el numero de filas y columnas
        this.filas = this.matriz.length;
        this.columnas = this.matriz[0] ? this.matriz[0].length : 0;
        this.columnasArray = Array.from(Array(this.columnas).keys()).map(i => i + 1);

        
        this.guardarEstado();
    };

    // Leer el contenido del archivo CSV como texto
    reader.readAsText(file);
  }
  eliminarFila(): void {
    if (this.matriz.length > 1) {
      this.matriz.pop(); 
      this.nombresFilasIzquierda.pop(); 
      
      this.filas = this.matriz.length;
      this.guardarEstado();
    } else {
      console.log('No se pueden eliminar más filas.');
    }
  }
  
  eliminarColumna(): void {
    if (this.columnasArray.length > 1) {
      this.matriz.forEach(row => row.pop()); 
      this.nombresFilasSuperior.pop(); 
      this.columnasArray.pop(); 
      this.columnas = this.columnasArray.length; 
      this.pesos.pop();
      this.guardarEstado();
    } else {
      console.log('No se pueden eliminar más columnas.');
    }
  }

  
  



}




