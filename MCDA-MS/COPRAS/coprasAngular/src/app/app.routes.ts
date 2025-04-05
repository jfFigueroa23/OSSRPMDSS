import { Routes } from '@angular/router';

import { CoprasComponent } from './components/copras/copras.component';


export const routes: Routes = [
    {path: '', redirectTo: 'copras', pathMatch: 'full'},

    {path: 'copras', component: CoprasComponent},

];
