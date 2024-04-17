import ctypes 
import os 
import platform 
from ctypes import *
from flask import Flask
from flask import request
from flask import jsonify
from flask import Response
from flask_login import LoginManager, UserMixin, login_required

def convert(s): 
    new = "" 
    for x in s: 
        new += x   
    return new       

app = Flask(__name__)

@app.route("/ElectreIII/ExplotarFlujoNeto", methods=['GET', 'POST'])
@login_required
def ElectreIIIExplotarFlujoNeto():
    
    plt = platform.system()
    if   plt == "Windows":  TestLib = ctypes.cdll.LoadLibrary(r'D:\Software\Sistemas\Investigacion\ELECTREIIISL\bin\Debug\ELECTREIIISL.dll')        
    else: TestLib = ctypes.cdll.LoadLibrary('/home/francisco/Software/Sistemas/Investigacion/MADM-SL/ELECTREIIISL/bin/Debug/libELECTREIIISL.so')   
   
    if request.method == 'POST':
        na = int(convert(request.form.get("na")))
        nc = int(convert(request.form.get("nc")))
        c = float(convert(request.form.get("c")))
        md = convert(request.form.get("md"))
    if request.method == 'GET':  
        na = int(convert(request.args.get("na"))) 
        nc = int(convert(request.args.get("nc")))
        c = float(convert(request.args.get("c")))
        md = convert(request.args.get("md")) 
    
    TestLib.ElectreIIIExplotarFlujoNeto.argtypes = [c_long, c_long, c_double, c_char_p]
    TestLib.ElectreIIIExplotarFlujoNeto.restype =  c_char_p
    res = TestLib.ElectreIIIExplotarFlujoNeto(na, nc, c, md.encode('utf-8'))
    return jsonify(res)

@app.route("/ElectreIII/ExplotarDestilacion", methods=['GET', 'POST'])
@login_required
def ElectreIIIExplotarDestilacion():
    
    plt = platform.system()
    if   plt == "Windows":  TestLib = ctypes.cdll.LoadLibrary(r'D:\Software\Sistemas\Investigacion\ELECTREIIISL\bin\Debug\ELECTREIIISL.dll')        
    else: TestLib = ctypes.cdll.LoadLibrary('/home/francisco/Software/Sistemas/Investigacion/ELECTREIIISL/bin/Debug/libELECTREIIISL.so')   
   
    if request.method == 'POST':
        na = int(convert(request.form.get("na")))
        nc = int(convert(request.form.get("nc")))
        c = float(convert(request.form.get("c")))
        md = convert(request.form.get("md"))
    if request.method == 'GET':  
        na = int(convert(request.args.get("na"))) 
        nc = int(convert(request.args.get("nc")))
        c = float(convert(request.args.get("c")))
        md = convert(request.args.get("md")) 
    
    TestLib.ElectreIIIExplotarDestilacion.argtypes = [c_long, c_long, c_double, c_char_p]
    TestLib.ElectreIIIExplotarDestilacion.restype =  c_char_p
    res = TestLib.ElectreIIIExplotarDestilacion(na, nc, c, md.encode('utf-8'))
    return jsonify(res)

login_manager = LoginManager()
login_manager.init_app(app)


class User(UserMixin):
    user_database = {"dmhapgtw": ("dmhapgtw", "628;xdm(Ele3)(MCDA)--")}

    def __init__(self, username, password):
        self.id = username
        self.password = password

    @classmethod
    def get(cls,id):
        return cls.user_database.get(id)


@login_manager.request_loader
def load_user(request):
    token = request.headers.get('Authorization')
    if token is None:
        token = request.args.get('token')

    if token is not None:
        username,password = token.split(":") # naive token
        user_entry = User.get(username)
        if (user_entry is not None):
            user = User(user_entry[0],user_entry[1])
            if (user.password == password):
                return user
    return None

if __name__ == '__main__':
    app.config["SECRET_KEY"] = "2021ARQUITECTURAGTWMCDAx&"    
    app.run(debug=True, host="127.0.0.1", port=int("8082"))    