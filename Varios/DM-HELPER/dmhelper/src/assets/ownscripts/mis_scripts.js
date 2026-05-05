var eTable;

$(function () {

  eTable = $("#source").editTable({
    data : [
      ["","","","","","","","","",""],
      ["","","","","","","","","",""],
      ["","","","","","","","","",""],
      ["","","","","","","","","",""],
      ["","","","","","","","","",""],
      ["","","","","","","","","",""],
      ["","","","","","","","","",""]
  });

  // $('#btnAceptar').on('click', function() {
  //   InicializarMatrizEntrada();
  // })

});

// function InicializarMatrizEntrada(){

//   var arrini = new Array(noalt), i, l;
//   var vecini = [];
//   var noalt = parseInt($('#noalternativaseiii').val()) + 6;
//   var nocri = parseInt($('#nocriterioseiii').val()) + 1;

//   for(var i = 0; i < noalt; i++) {
//     arrini[i] = new Array(nocri);
//   }

//   for(var i = 0; i < noalt; i++) {
//       vecini = arrini[i];
//       for(var j = 0; j < nocri; j++) {
//           vecini[j] = "X";
//       }
//   }

//   for(var i = 0; i < noalt; i++) {
//        vecini = arrini[i];
//        for(var j = 0; j < nocri; j++) {
//         if ((i==0) && (j==0))
//           vecini[j] = "ALT/CRI";
//         else if ((i==0) && (j>0))
//           vecini[j] = "C" + j;
//         else if ((i>0) && (i<noalt-5) && (j==0))
//           vecini[j] = "A" + i;
//         else if ((i>0) && (i<noalt-4) && (j==0))
//         vecini[j] = "W";
//         else if ((i>0) && (i<noalt-3) && (j==0))
//         vecini[j] = "P";
//         else if ((i>0) && (i<noalt-2) && (j==0))
//         vecini[j] = "Q";
//         else if ((i>0) && (i<noalt-1) && (j==0))
//         vecini[j] = "V";
//         else if ((i>0) && (i<noalt-0) && (j==0))
//         vecini[j] = "D";
//         else vecini[j] = "";
//        }
//    }

//    eTable.loadData(arrini);
//   $('#emdl').modal('hide');

// }

function CargarMatrizArchivo()
{
  alert("Cargar desde archivo");
}
