import { Injectable } from '@angular/core';

interface Cell {
  value: number;
  rowIndex: number;
  colIndex: number;
}

@Injectable({
  providedIn: 'root'
})
export class DataService {
  private filas: number | null = null;
  private columnas: number | null = null;
  private matriz: Cell[][] = [];
  private pesos: number[] = [];
  private nombresFilasIzquierda: string[] = [];
  private nombresFilasSuperior: string[] = [];
  private data: string = ''; 

  constructor() { }

  setFilas(filas: number | null): void {
    this.filas = filas;
  }

  getFilas(): number | null {
    return this.filas;
  }

  setColumnas(columnas: number | null): void {
    this.columnas = columnas;
  }

  getColumnas(): number | null {
    return this.columnas;
  }

  setMatriz(matriz: Cell[][]): void {
    this.matriz = matriz;
  }

  getMatriz(): Cell[][] {
    return this.matriz;
  }

  setPesos(pesos: number[]): void {
    this.pesos = pesos;
  }

  getPesos(): number[] {
    return this.pesos;
  }

  setNombresFilasIzquierda(nombres: string[]): void {
    this.nombresFilasIzquierda = nombres;
  }

  getNombresFilasIzquierda(): string[] {
    return this.nombresFilasIzquierda;
  }

  setNombresFilasSuperior(nombres: string[]): void {
    this.nombresFilasSuperior = nombres;
  }

  getNombresFilasSuperior(): string[] {
    return this.nombresFilasSuperior;
  }

  setData(data: string): void {
    this.data = data;
  }

  getData(): string {
    return this.data;
  }

  getLastTableData(): any[] {
    if (!this.data) return [];

    const sections = this.data.split('\n\n');
    const lastSection = sections[sections.length - 1]; 
    const lines = lastSection.split('\n').slice(1); 

    const data = lines.map(line => {
        const items = line.split('\t'); 
        if (items.length < 2) return { nombre: items[0].trim(), criterio: 0 }; // Manejo de errores

        const nombre = items[0].trim(); 
        const criterioString = items[1]; 
        
        // Extraigo solo el valor numerico despues de "C+: "
        const criterio = parseFloat(criterioString.split(': ')[1]);

        return { nombre, criterio: isNaN(criterio) ? 0 : criterio }; // Manejo NaN 
    });

    // Filtro nombres vacios y textos no deseados
    const filteredData = data.filter(item => {
        
        const shouldFilter = item.nombre.includes('El mejor candidato/alternativa segun C*') || item.nombre.includes('Las preferencias en orden descendente');
        return item.nombre.trim() !== '' && !shouldFilter; 
    });

    return filteredData;
  }


}
