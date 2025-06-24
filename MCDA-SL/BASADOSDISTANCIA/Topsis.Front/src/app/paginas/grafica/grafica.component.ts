import { Component, OnInit } from '@angular/core';
import { DataService } from '../servicios/data.service';
import { Chart, ChartType } from 'chart.js/auto';

@Component({
  selector: 'app-grafica',
  templateUrl: './grafica.component.html',
  styleUrls: ['./grafica.component.css']
})
export class GraficaComponent implements OnInit {
  public chart!: Chart;

  constructor(private dataService: DataService) {}

  ngOnInit(): void {
    this.loadChart();
  }

  loadChart(): void {
    if (typeof window !== 'undefined' && typeof document !== 'undefined') {
      const ctx = document.getElementById('chart') as HTMLCanvasElement;
      if (ctx) {
        // Obtego los datos de la ultima tabla
        const lastTableData = this.dataService.getLastTableData();
        
        // Extraer nombres y criterios
        const labels = lastTableData.map(item => item.nombre);
        const data = lastTableData.map(item => item.criterio);
        const chartData = {
          labels: labels,
          datasets: [{
            label: 'Criterios por Alternativa',
            data: data,
            backgroundColor: [
              'rgba(255, 99, 132, 0.2)',
              'rgba(255, 159, 64, 0.2)',
              'rgba(255, 205, 86, 0.2)',
              'rgba(75, 192, 192, 0.2)',
              'rgba(54, 162, 235, 0.2)',
              'rgba(153, 102, 255, 0.2)',
              'rgba(201, 203, 207, 0.2)'
            ],
            borderColor: [
              'rgb(255, 99, 132)',
              'rgb(255, 159, 64)',
              'rgb(255, 205, 86)',
              'rgb(75, 192, 192)',
              'rgb(54, 162, 235)',
              'rgb(153, 102, 255)',
              'rgb(201, 203, 207)'
            ],
            borderWidth: 1
          }]
        };
  
        this.chart = new Chart(ctx, {
          type: 'bar' as ChartType,
          data: chartData
        });
      } else {
        console.error('Canvas element not found');
      }
    }
    
  }
}
