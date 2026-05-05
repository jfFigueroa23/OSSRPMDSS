import { Component, OnInit } from '@angular/core';
import * as bootstrap from 'bootstrap'; //Necesario para jquery (modal)

@Component({
  selector: 'app-tab-electreiii',
  templateUrl: './tabElectreIII.component.html',
  styleUrls: ['./tabElectreIII.component.css']
})
export class TabElectreIIIComponent implements OnInit {

  //users: any[];

  cols: any[];

  users: Array<EstructuraJSON> = [new EstructuraJSON()];

  ngOnInit(): void {

    // this.cols = [
    //   { field: 'id', header: 'Id' },
    //   { field: 'name', header: 'Name' },
    //   { field: 'email', header: 'Email' },
    // ];

    // this.users = [
    //   { id: '1', name: 'kiran',email:'kiran@gmail.com' },
    //   { id: '2', name: 'tom',email:'tom@gmail.com' },
    //   { id: '3', name: 'john',email:'john@gmail.com' },
    //   { id: '4', name: 'Frank',email:'frank@gmail.com' },

    // ];

    this.users =
    [
      {
        key: 'Dato1',
        value: 'Valor1'
      },
      {
        key: 'Dato2',
        value: 'Valor2'
      },
      {
        key: 'Dato3',
        value: 'Valor3'
      }
    ];

    //this.clickEvent();

}

clickEvent()
{

  let vecini = [];
  // const noalt: number = parseInt((document.getElementById('noalternativaseiii') as HTMLInputElement).value) + 6;
  // const nocri: number = parseInt((document.getElementById('nocriterioseiii') as HTMLInputElement).value) + 1;

  const noalt: number = 9;
  const nocri: number = 3;

  const arrini = new Array(noalt);

  for (let i = 0; i < noalt; i++)
  {
    arrini[i] = new Array(nocri);
  }

  for (let i = 0; i < noalt; i++)
  {
      vecini = arrini[i];
      for (let j = 0; j < nocri; j++)
      {
          vecini[j] = 'X';
      }
  }

  for (let i = 0; i < noalt; i++)
  {
    vecini = arrini[i];
    for (let j = 0; j < nocri; j++)
    {
      if ((i == 0) && (j == 0)) {
        vecini[j] = 'ALT/CRI';
      } else if ((i == 0) && (j > 0)) {
        vecini[j] = 'C' + j;
      } else if ((i > 0) && (i < noalt - 5) && (j == 0)) {
        vecini[j] = 'A' + i;
      } else if ((i > 0) && (i < noalt - 4) && (j == 0)) {
      vecini[j] = 'W';
      } else if ((i > 0) && (i < noalt - 3) && (j == 0)) {
      vecini[j] = 'P';
      } else if ((i > 0) && (i < noalt - 2) && (j == 0)) {
      vecini[j] = 'Q';
      } else if ((i > 0) && (i < noalt - 1) && (j == 0)) {
      vecini[j] = 'V';
      } else if ((i > 0) && (i < noalt - 0) && (j == 0)) {
      vecini[j] = 'D';
      } else { vecini[j] = ''; }
    }
  }

  this.users = arrini;
  this.cols = vecini;

  // $('#emdl').modal('hide');

}

}


class EstructuraJSON
{
  key: string;
  value: string;

  constructor()
  {
    this.key = "";
    this.value = "";
  }
}

  // export interface User {
  //   id;
  //   name;
  //   email;
  // }
