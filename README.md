## Description
It is simplest example to show how to use ethernet over USB with usb-netif component.

Build and flash example, connect board to PC with USB cable (its native USB, not CP210x on board), and then open `http://192.168.4.1/` web page in the browser.

We should see logs like this:
```
I (570) TinyUSB: TinyUSB Driver installed
I (570) esp_netif_lwip: DHCP server started on interface usb-wired with IP: 192.168.4.1
I (580) USB_NCM: Starting server on port: '80'
I (590) USB_NCM: Registering URI handlers
I (590) USB_NCM: USB NCM initialized and started
I (600) main_task: Returned from app_main()
I (1530) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
```