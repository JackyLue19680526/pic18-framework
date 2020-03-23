device PIC18F46K22
set system.disableerrormsg true
hwtool PICkit3 -p
program "dist/default/production/framework.X.production.hex" 
quit