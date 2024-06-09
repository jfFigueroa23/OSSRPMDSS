import ctypes 
import os 
from ctypes import *

print (os.getcwd())

os.add_dll_directory(os.getcwd())
       
#TestLib = ctypes.cdll.LoadLibrary(r'ELECTREIIISL.dll')    
#TestLib = CDLL(r'ELECTREIIISL.dll')    
TestLib = ctypes.WinDLL(r'ELECTREIIISL.dll')    

print ("Hola mundo")