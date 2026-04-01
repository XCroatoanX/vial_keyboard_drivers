Steps for compiling:

1. Install QMK CLI

2. Clone qmk-vial: `git clone https://github.com/vial-kb/vial-qmk.git`

3. Install submodules inside vial-qmk folder: `git submodule update --init --recursive`

4. Replace sofle_choc folder in keyboards folder with the one in this repository

5. Compile the firmware inside the vial-qmk folder: `qmk compile -kb sofle_choc -km vial -e CONVERT_TO=sparkfun_pm2040`
