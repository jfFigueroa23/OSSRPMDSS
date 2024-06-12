import ctypes 
import os 
from ctypes import *

print ("Inicio")
os.add_dll_directory(r'C:\Users\jffig\anaconda3\pkgs\m2w64-gcc-libs-5.3.0-7\Library\mingw-w64\bin')
os.add_dll_directory(r'C:\Users\jffig\anaconda3\Library\mingw-w64\bin')
TestLib = ctypes.WinDLL(r'D:\Software\Sistemas\Investigacion\OSSRPMDSS\MCDA-MS\ELECTREIIIMS\ELECTREIIISL.dll')  
print ("Fin")