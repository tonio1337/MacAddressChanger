# MacAddressChanger
This is a simple C program that allows you to change the MAC address of a network interface on your system. It generates a random MAC address and applies it to the specified interface. Useful for testing, privacy, or network troubleshooting.

How to compile with bash:
gcc macspoof.c -o macspoof

Then:
sudo ./macspoof <interface>
Replace <interface> with your network interface (e.g., eth0 or wlan0).
This will change the adress for you.

Few notes:
Requires root/sudo.
MAC resets after reboot.
Linux based systems only.

enjoy :)
