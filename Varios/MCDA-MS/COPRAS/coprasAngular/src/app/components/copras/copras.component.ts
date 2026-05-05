import { Component } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { CommonModule } from '@angular/common';
import { CoprasService } from '../../services/copras.service';

@Component({
  selector: 'app-copras',
  standalone: true,
  imports: [FormsModule, CommonModule],
  templateUrl: './copras.component.html',
  styleUrls: ['./copras.component.css']
})
export class CoprasComponent {
  numAlternatives: number = 1;
  numCriteria: number = 1;
  alternatives: number[][] = [];
  criteria: { beneficial: string, weight: number }[] = [];
  criteriaWeights: number[] = [];
  criteriaBeneficial: string[] = [];
  generatedData: any = null;
  ranking: number[][] = [];
  generated: boolean = false;
  constructor(private coprasService: CoprasService) { }

  ngOnInit(): void {
    this.generateArrays();
  }
  // Método para generar los arrays basados en las entradas del usuario
  generateArrays(): void {
    this.generated = false;  // Reinicia el estado generado

    // Genera los criterios con sus pesos y si son beneficiosos o no
    this.criteria = Array.from({ length: this.numCriteria }, () => ({
      beneficial: 'B',
      weight: 1 // Peso por defecto
    }));

    // Genera las alternativas basadas en el número de criterios
    this.alternatives = Array.from({ length: this.numAlternatives }, () =>
      Array(this.numCriteria).fill(0)
    );

    this.generatedData = {
      numAlternatives: this.numAlternatives,
      numCriteria: this.numCriteria,
      alternatives: this.alternatives,
      criteria: this.criteria
    };

    this.generated = true; // Marca que los datos fueron generados
  }

  // Método para enviar los datos (a backend o donde se necesiten)
  submitData(): void {
    this.criteriaBeneficial = this.criteria.map(c => c.beneficial);
    this.criteriaWeights = this.criteria.map(c => c.weight);
    this.coprasService.getNxN(this.alternatives, this.criteriaBeneficial, this.criteriaWeights )
    .subscribe(data => {
      console.log('Datos obtenidos:', data);
      this.ranking = data
      .map((valor: number, indice: number) => [valor, indice] as [number, number])
      .sort((a: number[], b: number[]) => b[0] - a[0]); // Ordenar de mayor a menor según el primer valor

      console.log('Datos obtenidos:', this.ranking);
      this.generated = true;
    });
  }


  onFileSelected($event: Event): void {
    const input = $event.target as HTMLInputElement;
    if (input.files && input.files.length > 0) {
      const file = input.files[0];
      console.log('Archivo seleccionado:', file.name);
      this.coprasService.procesarArchivo(file)
      .then(data => {
        console.log('Datos obtenidos:', data);
        this.alternatives = data.tabla;
        this.criteriaBeneficial = data.beneficio;
        this.criteriaWeights = data.pesos;

        // Actualiza los criterios con los datos del archivo
        this.criteria = this.criteriaBeneficial.map((beneficial, index) => ({
          beneficial,
          weight: this.criteriaWeights[index]
        }));

        this.numAlternatives = this.alternatives.length;
        this.numCriteria = this.criteria.length;

        console.log('Datos obtenidos:', this.alternatives, this.criteria);
        this.generated = true;

        // Llama a submitData para actualizar el ranking con los nuevos datos
        this.submitData();
      })
      .catch(error => {
        console.error('Error procesando el archivo:', error);
      });
    }
  }
}
