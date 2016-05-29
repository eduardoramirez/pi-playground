sudo insmod pmuon.ko
sudo ./memmeasure 
sudo rmmod pmuon.ko
dmesg | tail -2
