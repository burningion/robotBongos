Pyliblo and WiringPi2 and WiringPi2-Python are required on the Raspberry Pi

Getting pyliblo installed on the Raspbery Pi:

```bash
sudo apt-get install liblo-dev cython
sudo pip install pyliblo
```

Getting WiringPi2 installed:

```bash
git clone git://git.drogon.net/wiringPi
cd wiringPi
sudo ./build
```

Getting WiringPi2-Python installed:

```bash
git clone https://github.com/Gadgetoid/WiringPi2-Python.git
cd WiringPi2-Python
sudo python setup.py install
```

Getting the code up and running:

Replace the pins with the pins you've got the circuit hooked up to in the drummserver.py, and then...

```bash
sudo python drummserver.py
```