# NAVQ+

## Links
[gitbook](https://nxp.gitbook.io/8mpnavq/)

## Reimage SD Card
You want NavQPlus Ubunto 22.04 with ROS 2 Humble using cyclone dds from here. 

1. Get the latest image from [here](https://github.com/rudislabs/navqplus-create3-images/releases/)
   1. Source code is available here: https://github.com/voxelbotics/meta-vb-imx8mp/
2. Copy to SD Card. Directions [here](https://iroboteducation.github.io/create3_docs/setup/navqplus/)
   1. Be sure to use the right disk: sudo dd if=navqplus-image-<version>.wic of=/dev/rdisk<X> bs=1m status=progress oflag=sync
   2. use disk util to umount subdisks
3. Resize disk [here](https://nxp.gitbook.io/8mmnavq/getting-started/quickstart/expand-space-on-sd-card#easy-to-use-script)
   ```
   chmod u+x resizeDisk.sh
   sudo ./resizeDisk.sh sd
   df -H
   ```
4. Update what is there:
   ``` 
   sudo apt-get update
   sudo apt-get upgrade
   ```

[directions](https://nxp.gitbook.io/8mpnavq/navqplus-user-guide/quickstart/flashing-with-new-firmware#flashing-sd-card-using-linux-mac)

[boot configuration sd vs emmc](https://nxp.gitbook.io/8mpnavq/navqplus-user-guide/quickstart/flashing-with-new-firmware#boot-switches-configuration)

## Imaging eMMC
[directions](https://iroboteducation.github.io/create3_docs/setup/navqplus/)
[boot switches](https://iroboteducation.github.io/create3_docs/setup/navqplus/#boot-switches)

1. Download uuu (part of get_depend)
2. Set your boot switches (sw1 on and sw2 off)
3. connect USB1, should see two lights. 
4. run scripts/flash_emmc fmuk66_v3 or fmuk66_e
5. set for emmc boot (sw1 off and sw2 on)


## Wifi 
```
# connect a wifi network 
sudo nmtui
```
After connecting to wifi you can ssh in. The default user and password:
user: user
password: user
```
# ssh user@192.168.68.104
ssh user@<ip>

# to tunel the local web server 
ssh -L 127.0.0.1:8080:127.0.0.1:8080 user@192.168.68.104


```

To stop the irritating messages from eth1:
```
echo -n "30bf0000.ethernet" > sudo /sys/bus/platform/drivers/imx-dwmac/unbind
```

## Serial Console
Note Mac sucks.
* Look in system report and see any disabled software.
* In privacy and security Allow accessories to connect "automatically when connected". Also under developer tools allow shell to run things outside the security policy.
* You need to close QGroundControl to release the port.

Connect the USB to serial port.
```
# -L logs
# -r reconnects the session
screen -L -r /dev/tty.<your device> 115200

# screen -L -r /dev/tty.usbserial-DM02UQLJ 115200
# user = user
# password = user
```

You likely need to stop QGroundControl for this to work. To see who is using the port:

```
lsof | grep usbserial
```



## Ethernet over USB
Need to use the middle port. Need to use a USB-C cable directly between mac and NAVQ.
Approve the usb gadget.
Under network you will see the RNDIS/Ethernet Gadget.
Use that to get the IP address. 



## installs
```
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install usbutils
```

## General Stuff
```
# see services running
systemctl --type=service
```

## Ethernet
### eth1 Automotive Ethernet
eth1 is the automotive ethernet that doesn't have a phy. To disable it:
```
sudo sh -c "echo -n 30bf0000.ethernet > /sys/bus/platform/drivers/imx-dwmac/unbind"
```
### eth0 2-wire ethernet 100BT 
This is the preferred connection to the FMU.

vi /etc/netplan/01-network-manager-all.yaml
```
network:
  version: 2
  renderer: NetworkManager
  ethernets:
      eth0:
          addresses:
              - 10.0.0.1/24
          nameservers:
              addresses: [10.0.0.1]
          routes:
              - to: 10.0.0.1
                via: 10.0.0.1
```
To get these settings to take affect
```
sudo netplan apply
#test
ping 10.0.0.2
```
works [directions](https://docs.px4.io/main/en/advanced_config/ethernet_setup.html)

