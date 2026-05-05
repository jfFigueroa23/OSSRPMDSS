import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { from, Observable, switchMap } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class CoprasService {

  private apiUrl = 'http://localhost:8000'; // Cambia esto a la URL de tu API
  
    constructor(private http: HttpClient) { }
  
    getNxN(tabla: number[][], beneficio: string[], pesos: number[] ): Observable<any> {
      console.log('Tabla:', tabla);
      console.log('Beneficio:', beneficio);
      const requestModel = { tabla: tabla, beneficio: beneficio, pesos: pesos };
      console.log('Request:', requestModel);
      return this.http.post<string>(`${this.apiUrl}/solve`, requestModel);
    }
    
    getArchivo(archivo: File): Observable<any> {
      return from(this.procesarArchivo(archivo)).pipe(
        switchMap((resultado) => {
          if (resultado) {
            return this.getNxN(resultado.tabla, resultado.beneficio, resultado.pesos);
          } else {
            throw new Error('Error procesando el archivo');
          }
        })
      );
    }
  
     procesarArchivo(archivo: File): Promise<any> {
      return new Promise((resolve, reject) => {
        const lector = new FileReader();
  
        lector.onload = (e) => {
          const contenido = (e.target?.result as string).trim();
          const lineas = contenido.split('\n');
  
          const beneficio = lineas[0].split(',').map(valor => valor.trim());
          const pesos = lineas[1].split(',').map(valor => parseFloat(valor));
  
          const tabla = lineas.slice(2).map(linea =>
            linea.split(',').map(valor => parseFloat(valor))
          );
  
          const resultado = {
            tabla,
            beneficio,
            pesos
          };
  
          console.log("Resultado lector: ", resultado);
          resolve(resultado);
        };
  
        lector.onerror = (error) => {
          reject(error);
        };
  
        lector.readAsText(archivo);
      });
    }

}
