import { Component, OnInit, AfterViewInit } from '@angular/core';
import { DataService } from '../servicios/data.service';

@Component({
  selector: 'app-resultados',
  templateUrl: './resultados.component.html',
  styleUrls: ['./resultados.component.css']
})
export class ResultadosComponent implements OnInit, AfterViewInit {
  outputAPI: string = '';
  parsedOutput: any[] = [];
  steps = ['Datos sin procesar', 'Datos Normalizados', 'Datos Ponderados', 'Soluciones ideales positivas y negativas', 'Medidas de separación', 'Orden Clasificado'];
  currentStep: number = 0; // Variable para almacenar el indice del paso actual

  constructor(private dataService: DataService) {}

  ngOnInit(): void {
    this.outputAPI = this.dataService.getData();
    this.parsedOutput = this.parseOutput(this.outputAPI);
  }

  ngAfterViewInit(): void {
    if (this.outputAPI) {
      setTimeout(() => {
        this.scrollToLastSection();
      }, 0);
    }
  }

  parseOutput(output: string): any[] {
    if (!output) {
      return [];
    }

    const sections = output.split('\n\n');
    return sections.map((section) => {
      const lines = section.split('\n');
      const formattedLines = lines.map((line) => this.formatLine(line));
      return formattedLines;
    });
  }

  formatLine(line: string): string {
    if (!line) {
      return '';
    }

    if (line.includes(':')) {
      const items = line.split(/(\S+:\s*[^\s]+)/);
      return items.filter(item => item.trim() !== '').map(item => item.trim()).join('\t');
    } else {
      const items = line.split(/\s+/);
      return items.join('\t');
    }
  }

  scrollToSection(index: number): void {
    this.currentStep = index; // Actualiza el paso actual al hacer clic
    const sectionId = `section-${index}`;
    const sectionElement = document.getElementById(sectionId);
    if (sectionElement) {
      sectionElement.scrollIntoView({ behavior: 'smooth', block: 'end' });
    }
  }

  scrollToLastSection(): void {
    const lastSectionId = `section-${this.parsedOutput.length - 1}`;
    const lastSectionElement = document.getElementById(lastSectionId);
    if (lastSectionElement) {
      lastSectionElement.scrollIntoView({ behavior: 'smooth', block: 'start' });
    }
  }


  //Metodo para optimizar la pantalla de resultados
  trackByFn(index: number, item: any): number {
    return index; 
  }
}



