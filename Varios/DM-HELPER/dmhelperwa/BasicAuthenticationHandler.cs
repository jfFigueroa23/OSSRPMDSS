using System;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;

namespace dmhelperwa
{
    public class BasicAuthMiddleware
    {
        private readonly RequestDelegate _next;

        public BasicAuthMiddleware(RequestDelegate next)
        {
            _next = next;
        }

        public async Task Invoke(HttpContext httpContext)
        {
            string authHeader = httpContext.Request.Headers["Authorization"];            
            if (authHeader != null)
            {
                string username = authHeader.Split(new char[] { ':' })[0];
                string password = authHeader.Split(new char[] { ':' })[1];
                if (username == "dmhelper" && password == "731;xdm(DMHelp)(MCDA),+")
                {
                    await _next(httpContext);
                }
                else
                {
                    httpContext.Response.StatusCode = 401;
                    httpContext.Response.WriteAsync("<title>401 Unauthorized</title><h1>Unauthorized</h1><p>The server could not verify that you are authorized to access the URL requested. You either supplied the wrong credentials (e.g. a bad password), or your browser doesn't understand how to supply the credentials required.</p>");                    
                    return;
                }
            }
            else
            {
                httpContext.Response.StatusCode = 401;
                httpContext.Response.WriteAsync("<title>401 Unauthorized</title><h1>Unauthorized</h1><p>The server could not verify that you are authorized to access the URL requested. You either supplied the wrong credentials (e.g. a bad password), or your browser doesn't understand how to supply the credentials required.</p>");                    
                return;
            }
        }
    }

    public static class BasicAuthMiddlewareExtensions
    {
        public static IApplicationBuilder UseBasicAuthMiddleware(this IApplicationBuilder builder)
        {
            return builder.UseMiddleware<BasicAuthMiddleware>();
        }
    }
}