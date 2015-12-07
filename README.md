# RPIAFIB
AFIB Detection using Raspberry Pi Compute Module

This is a project created by Yifan Ge and Ben Lampert for the CS241 Embedded Workshop class(http://web.stanford.edu/class/cs241/). The intention is to create an open source AFIB detection wearable which can be used to diagnose patients with the condition.


![alt tag](https://github.com/lampertb/RPIAFIB/blob/master/PCB/BoardFront.png)
![alt tag](https://github.com/lampertb/RPIAFIB/blob/master/PCB/BoardBack.png)

Please reference the instructable for more information on assembling the board.
http://www.instructables.com/id/rPI-Atrial-Fibrillation-Detection-Board/

To install run

sudo sh ./install.sh

Run software:
cd Software
sudo ./execute_afib_detect

Todo:
Software:
-Improve ECG Capture code
-Improve integration between the algorithm detection and sampling code
Hardware:
-Lipo charger circuit does not allow for the board to be powered while charging the LED, need to find a solution for this. Integrated charger?

USE AT YOUR OWN RISK: This project involves ECG measurements which can be dangerous if not done correctly. It is your responsibility to evaluate your own medical and physical condition, or that of your clients, and to independently determine whether to perform, use or adapt any of the information or content on this instructable. By voluntarily undertaking the project displayed on this website, you assume the risk of any resulting injury.
