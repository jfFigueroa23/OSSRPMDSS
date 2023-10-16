import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { NgbModule } from '@ng-bootstrap/ng-bootstrap';
import {BrowserAnimationsModule} from '@angular/platform-browser/animations'; // added this
import {TableModule} from 'primeng/table';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { TabElectreIIIComponent } from './tabElectreIII/tabElectreIII.component';
import { IniMatrizEntradaComponent } from './ini-matriz-entrada/ini-matriz-entrada.component';
import { CarMatrizArchivoComponent } from './car-matriz-archivo/car-matriz-archivo.component';

@NgModule({
  declarations: [
    AppComponent,
    TabElectreIIIComponent,
    IniMatrizEntradaComponent,
    CarMatrizArchivoComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    NgbModule,
    BrowserAnimationsModule,
    TableModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
