import { NgModule } from '@angular/core';
import { BrowserModule, provideClientHydration } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { HttpClient, HttpClientModule, provideHttpClient, withFetch } from '@angular/common/http';
import { MatrizComponent } from './paginas/matriz/matriz.component';
import { CommonModule } from '@angular/common';
import { ResultadosComponent } from './paginas/resultados/resultados.component';
import { GraficaComponent } from './paginas/grafica/grafica.component';

@NgModule({
  declarations: [
    AppComponent,
    MatrizComponent,
    ResultadosComponent,
    GraficaComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    FormsModule,
    ReactiveFormsModule,
    HttpClientModule,
    CommonModule 
  ],
  providers: [
    provideClientHydration(),
    provideHttpClient(withFetch())
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
