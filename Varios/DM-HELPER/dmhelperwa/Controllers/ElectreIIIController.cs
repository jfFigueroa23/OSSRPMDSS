using System;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using System.Net.Http;
using System.Net.Http.Json;
using System.Collections.Generic;

namespace dmhelperwa
{

    [ApiController]
    [Route("[controller]")]
    public class ElectreIIIController : ControllerBase
    {   
        [HttpGet("/ElectreIII/ExplotarFlujoNeto")]  
        public async Task<Object> ElectreIIIExplotarFlujoNeto()
        {
            string na ="", nc="", c="", md="";               

            HttpClient httpClient = new HttpClient();
            httpClient.DefaultRequestHeaders.TryAddWithoutValidation("Authorization", "dmhwbap:555;xdm(APGTw)(MCDA)-*");

            if (Request.Method == "POST")
            {
                na = Request.Form["na"].ToString();
                nc = Request.Form["nc"].ToString();
                c = Request.Form["c"].ToString();
                md = Request.Form["md"].ToString();
            }
            if (Request.Method == "GET")
            {
                na = Request.Query["na"].ToString();
                nc = Request.Query["nc"].ToString();
                c = Request.Query["c"].ToString();
                md = Request.Query["md"].ToString();
            }

            var parametros = new FormUrlEncodedContent(new[]
            {
                new KeyValuePair<string, string>("na", na), 
                new KeyValuePair<string, string>("nc", nc), 
                new KeyValuePair<string, string>("c", c), 
                new KeyValuePair<string, string>("md", md)
            });

            var response = await httpClient.PostAsync("http://127.0.0.1:8081/ElectreIII/ExplotarFlujoNeto", parametros);
            return await response.Content.ReadFromJsonAsync<Object>();
        }

        [HttpGet("/ElectreIII/ExplotarDestilacion")]  
        public async Task<Object> ElectreIIIExplotarDestilacion()
        {
            string na ="", nc="", c="", md="";               

            HttpClient httpClient = new HttpClient();
            httpClient.DefaultRequestHeaders.TryAddWithoutValidation("Authorization", "dmhwbap:555;xdm(APGTw)(MCDA)-*");

            if (Request.Method == "POST")
            {
                na = Request.Form["na"].ToString();
                nc = Request.Form["nc"].ToString();
                c = Request.Form["c"].ToString();
                md = Request.Form["md"].ToString();
            }
            if (Request.Method == "GET")
            {
                na = Request.Query["na"].ToString();
                nc = Request.Query["nc"].ToString();
                c = Request.Query["c"].ToString();
                md = Request.Query["md"].ToString();
            }

            var parametros = new FormUrlEncodedContent(new[]
            {
                new KeyValuePair<string, string>("na", na), 
                new KeyValuePair<string, string>("nc", nc), 
                new KeyValuePair<string, string>("c", c), 
                new KeyValuePair<string, string>("md", md)
            });

            var response = await httpClient.PostAsync("http://127.0.0.1:8081/ElectreIII/ExplotarDestilacion", parametros);
            return await response.Content.ReadFromJsonAsync<Object>();
        }

    }

}

// Authorization: dmhelper:731;xdm(DMHelp)(MCDA),+