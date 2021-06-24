from distutils.core import setup, Extension


module1 = Extension(
	'dif', 
	 sources = ['dif.c'] 
)

setup(
	name = 'dif',              
	version = '1.1',               
	description = 'def_module', 
	ext_modules= [module1]         
)
