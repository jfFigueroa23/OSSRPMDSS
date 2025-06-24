import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { MatrizComponent } from './paginas/matriz/matriz.component';
import { ResultadosComponent } from './paginas/resultados/resultados.component';
import { GraficaComponent } from './paginas/grafica/grafica.component';

const routes: Routes = [
  {path:'', redirectTo:'matriz', pathMatch:'full'},
  {path: 'matriz', component: MatrizComponent},
  {path: 'resultados', component: ResultadosComponent},
  {path: 'grafica', component: GraficaComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
