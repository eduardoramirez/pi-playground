sudo insmod pmuon.ko
sudo ./memmeasure >> report2.txt
sudo rmmod pmuon.ko
dmesg | tail -2
